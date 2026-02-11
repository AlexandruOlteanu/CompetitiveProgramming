import requests
import time
import csv
from pathlib import Path

# ---------------- CONFIG ----------------
STEP = 100
WAIT_TIME = 1.5  # seconds between API calls
USERS_PER_FILE = 200000  # number of users per CSV
NUM_FILES = 5  # number of CSV files

# ---------------- FETCH ALL USERS ----------------
url = "https://codeforces.com/api/user.ratedList?activeOnly=false&includeRetired=true"
users = requests.get(url).json()['result']

# Sort users by maxRating descending
users.sort(key=lambda u: u.get('maxRating', 0), reverse=True)

total_users = len(users)
print(f"Total users fetched: {total_users}")

# ---------------- LOOP PER FILE ----------------
for file_idx in range(NUM_FILES):
    start_idx = file_idx * USERS_PER_FILE
    end_idx = min(start_idx + USERS_PER_FILE, total_users)
    if start_idx >= total_users:
        break  # no more users left

    csv_filename = f"codeforces_users_{file_idx + 1}.csv"
    print(f"\nProcessing users {start_idx} – {end_idx - 1} → {csv_filename}")

    data_path = Path(csv_filename)
    processed_handles = set()
    if data_path.exists():
        # load already processed users to skip them
        with open(data_path, newline='', encoding='utf-8') as f:
            reader = csv.DictReader(f)
            for row in reader:
                processed_handles.add(row['handle'])

    # ---------------- PROCESS USER FUNCTION ----------------
    def process_user(user, index):
        handle = user['handle']
        if handle in processed_handles:
            return  # skip users already processed

        maxRating = user.get('maxRating', 0)

        rating_url = f"https://codeforces.com/api/user.rating?handle={handle}"
        try:
            resp = requests.get(rating_url, timeout=5)
            resp.raise_for_status()
            contests = resp.json()['result']
            time.sleep(WAIT_TIME)

            if len(contests) < 6:
                return  # skip users with less than 6 contests

            registration = user.get('registrationTimeSeconds')
            if not registration:
                return
            print(f"Processing user {index}: {handle} with max rating {maxRating}")
            # Last rating update time & current rating
            last_rating_update = contests[-1]['ratingUpdateTimeSeconds']
            current_rating = contests[-1]['newRating']

            # Years since last rated contest
            current_time = int(time.time())
            years_since_last_contest = (current_time - last_rating_update) / (365*24*3600)

            seen_buckets = set()
            rows_to_write = []

            # iterate contests starting from the 6th
            for contest in contests[5:]:
                rating = contest['newRating']
                lower = (rating // STEP) * STEP
                upper = lower + STEP - 1

                # record first time the user enters this bucket
                if (lower, upper) not in seen_buckets:
                    time_to_bucket = contest['ratingUpdateTimeSeconds'] - registration
                    years_to_bucket = time_to_bucket / (365*24*3600)
                    rows_to_write.append({
                        "user_index": index,
                        "handle": handle,
                        "current_rating": current_rating,
                        "years_since_last_contest": f"{years_since_last_contest:.4f}",
                        "contest_id": contest['contestId'],
                        "contest_name": contest['contestName'],
                        "new_rating_after_contest": contest['newRating'],
                        "time_to_bucket_years": f"{years_to_bucket:.4f}",
                        "bucket_lower": lower,
                        "bucket_upper": upper
                    })
                    seen_buckets.add((lower, upper))

            # Write data to CSV immediately
            if rows_to_write:
                write_header = not data_path.exists()
                with open(csv_filename, 'a', newline='', encoding='utf-8') as f:
                    writer = csv.DictWriter(f, fieldnames=rows_to_write[0].keys())
                    if write_header:
                        writer.writeheader()
                    for row in rows_to_write:
                        writer.writerow(row)

                # mark handle as processed
                processed_handles.add(handle)

        except Exception as e:
            print(f"Failed {handle}: {e}")

    # ---------------- RUN ----------------
    for idx, user in enumerate(users[start_idx:end_idx], start=start_idx):
        process_user(user, idx)

print("\nProcessing complete.")
