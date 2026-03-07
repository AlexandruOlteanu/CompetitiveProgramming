import csv
import glob
import os
from collections import defaultdict
from statistics import median, mean

FILES_PATTERN = "codeforces_users_*.csv"

ACTIVITY_WINDOWS = {
    "ACTIVE_LAST_6_MONTHS": 0.5,
    "ACTIVE_LAST_1_YEAR": 1,
    "ACTIVE_LAST_3_YEARS": 3,
    "ALL_TIME": None
}

RANKS = [
    ("Newbie",-9999,1199),
    ("Pupil",1200,1399),
    ("Specialist",1400,1599),
    ("Expert",1600,1899),
    ("Candidate Master",1900,2099),
    ("Master",2100,2299),
    ("International Master",2300,2399),
    ("Grandmaster",2400,2599),
    ("International Grandmaster",2600,2999),
    ("Legendary Grandmaster",3000,10000)
]

user_current={}
user_last_active={}
user_peak=defaultdict(int)
bucket_times=defaultdict(list)
seen_bucket=set()

# --- CITIRE DATE ---
print("Se citesc datele din fisierele CSV...")
files = glob.glob(FILES_PATTERN)
for file in files:
    with open(file, newline='', encoding="utf-8") as f:
        reader = csv.DictReader(f)
        for row in reader:
            if "NOT_ENOUGH_CONTESTS" in row.values():
                continue
            try:
                user = row["user_index"]
                current = int(float(row["current_rating"]))
                years_since = float(row["years_since_last_contest"])
                new_rating = int(float(row["new_rating_after_contest"]))
                bucket = int(row["bucket_lower"])
                time = float(row["time_to_bucket_years"])

                user_current[user] = current
                user_last_active[user] = years_since
                user_peak[user] = max(user_peak[user], new_rating)

                key = (user, bucket)
                if key not in seen_bucket:
                    seen_bucket.add(key)
                    bucket_times[bucket].append(time)
            except:
                continue

# --- FUNCTII DE UTILITATE ---

def rating_distribution(ratings, step=100):
    buckets = defaultdict(int)
    for r in ratings:
        bucket = (int(r) // step) * step
        buckets[bucket] += 1
    return buckets

def compute_top_percent(bucket, ratings):
    total = len(ratings)
    if total == 0: return 0
    above = sum(1 for r in ratings if r >= bucket)
    return (above / total) * 100

def print_bucket_stats(ratings, title, f):
    buckets = rating_distribution(ratings, 100)
    total_users = len(ratings)
    print(f"\n{title}\n{'-'*90}", file=f)
    print(f"{'BUCKET':<12}{'USERS':<10}{'TOP %':<10}{'MEDIAN_TIME':<15}{'AVG_TIME':<15}", file=f)
    for b in sorted(buckets):
        users = buckets[b]
        top_percent = compute_top_percent(b, ratings)
        times = bucket_times.get(b, [])
        med = round(median(times), 3) if times else "-"
        avg = round(mean(times), 3) if times else "-"
        print(f"{b}-{b+99:<10}{users:<10}{round(top_percent, 3):<10}{med:<15}{avg:<15}", file=f)
    print(f"\nTOTAL USERS: {total_users}", file=f)

def print_fine_grained_data(ratings, title, f):
    buckets = rating_distribution(ratings, 30)
    print(f"\n>>> DATE PENTRU GRAFIC: {title} (PAS 30) <<<\n{'BUCKET':<10}{'USERS':<10}", file=f)
    for b in sorted(buckets):
        print(f"{b:<10}{buckets[b]:<10}", file=f)
    print(">>> SFARSIT DATE GRAFIC <<<\n", file=f)

def get_rank(rating):
    for name, lo, hi in RANKS:
        if lo <= rating <= hi: return name
    return "Unknown"

def print_rank_stats(ratings, title, f):
    ranks = defaultdict(int)
    for r in ratings: ranks[get_rank(r)] += 1
    total_users = len(ratings)
    print(f"\n{title}\n{'-'*90}", file=f)
    print(f"{'RANK':<30}{'USERS':<10}{'TOP %':<10}{'MEDIAN_TIME':<15}{'AVG_TIME':<15}", file=f)
    
    for name, lo, _ in RANKS:
        users = ranks.get(name, 0)
        if users == 0: continue
        # Compute top % for rank
        above = sum(1 for r in ratings if r >= lo)
        top_p = (above / total_users) * 100 if total_users > 0 else 0
        
        times = bucket_times.get(lo, []) if name != "Newbie" else []
        med = round(median(times), 3) if times else "-"
        avg = round(mean(times), 3) if times else "-"
        print(f"{name:<30}{users:<10}{round(top_p, 3):<10}{med:<15}{avg:<15}", file=f)
    print(f"\nTOTAL USERS: {total_users}", file=f)

# --- EXECUTIE ---

# 1. Generare fisiere pentru ferestrele de activitate
for window, limit in ACTIVITY_WINDOWS.items():
    filename = f"{window.lower()}.txt"
    print(f"Se genereaza {filename}...")
    
    with open(filename, "w", encoding="utf-8") as out:
        users_subset = [u for u in user_current if limit is None or user_last_active[u] <= limit]
        if not users_subset:
            print("Niciun utilizator gasit pentru aceasta fereastra.", file=out)
            continue

        curr_r = [user_current[u] for u in users_subset]
        peak_r = [user_peak[u] for u in users_subset]

        print(f"{'='*30}\n ANALIZA: {window}\n{'='*30}", file=out)
        print_bucket_stats(curr_r, "CURRENT RATING STATS (BUCKET 100)", out)
        print_rank_stats(curr_r, "CURRENT RANK STATS", out)
        print_fine_grained_data(curr_r, window, out)

# 2. Generare fisier pentru analiza avansata
print("Se genereaza advanced_analysis.txt...")
with open("advanced_analysis.txt", "w", encoding="utf-8") as adv:
    print(f"{'='*40}\n ADVANCED CODEFORCES ANALYSIS\n{'='*40}", file=adv)
    
    all_peak = list(user_peak.values())
    
    # Probability to reach next rank
    print("\nPROBABILITY TO REACH NEXT RANK\n" + "-"*60, file=adv)
    print(f"{'FROM':<25}{'TO':<25}{'PROBABILITY'}", file=adv)
    for i in range(len(RANKS)-1):
        name, lo, _ = RANKS[i]
        n_name, n_lo, _ = RANKS[i+1]
        reached_curr = sum(1 for r in all_peak if r >= lo)
        reached_next = sum(1 for r in all_peak if r >= n_lo)
        if reached_curr > 0:
            prob = (reached_next / reached_curr) * 100
            print(f"{name:<25}{n_name:<25}{round(prob, 2)}%", file=adv)

    # Median time between ranks
    print("\nMEDIAN TIME BETWEEN RANKS\n" + "-"*60, file=adv)
    print(f"{'FROM':<25}{'TO':<25}{'MEDIAN YEARS'}", file=adv)
    for i in range(len(RANKS)-1):
        name, _, _ = RANKS[i]
        n_name, n_lo, _ = RANKS[i+1]
        times = bucket_times.get(n_lo, [])
        if times:
            print(f"{name:<25}{n_name:<25}{round(median(times), 3)}", file=adv)

print("\nSucces! Fisierele au fost create in folderul curent.")