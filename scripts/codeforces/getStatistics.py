import csv
import glob
import os
from collections import defaultdict
from statistics import median, mean

# ---------- CONFIGURARE ----------
FILES_PATTERN = "codeforces_users_*.csv"

ACTIVITY_WINDOWS = {
    "ACTIVE_LAST_6_MONTHS": 0.5,
    "ACTIVE_LAST_1_YEAR": 1,
    "ACTIVE_LAST_3_YEARS": 3,
    "ALL_TIME": None
}

RANKS = [
    ("Newbie", -9999, 1199),
    ("Pupil", 1200, 1399),
    ("Specialist", 1400, 1599),
    ("Expert", 1600, 1899),
    ("Candidate Master", 1900, 2099),
    ("Master", 2100, 2299),
    ("International Master", 2300, 2399),
    ("Grandmaster", 2400, 2599),
    ("International Grandmaster", 2600, 2999),
    ("Legendary Grandmaster", 3000, 10000)
]

# Structuri de date
user_current = {}
user_last_active = {}
user_peak = defaultdict(int)
# MODIFICARE: bucket_times[rating] = [(user1, timp1), (user2, timp2)...]
bucket_times = defaultdict(list)
seen_bucket = set()

# ---------- 1. CITIRE DATE ----------
print("Se citesc datele din fisierele CSV...")
files = glob.glob(FILES_PATTERN)

for file in files:
    with open(file, newline='', encoding="utf-8") as f:
        reader = csv.DictReader(f)
        for row in reader:
            if "NOT_ENOUGH_CONTESTS" in row.values():
                continue
            try:
                u = row["user_index"]
                curr = int(float(row["current_rating"]))
                last = float(row["years_since_last_contest"])
                peak_val = int(float(row["new_rating_after_contest"]))
                b = int(row["bucket_lower"])
                t = float(row["time_to_bucket_years"])

                # Salvăm datele de bază ale utilizatorului
                user_current[u] = curr
                user_last_active[u] = last
                user_peak[u] = max(user_peak[u], peak_val)

                # Salvăm timpul pentru bucket-ul respectiv (doar o dată per user/bucket)
                key = (u, b)
                if key not in seen_bucket:
                    seen_bucket.add(key)
                    bucket_times[b].append((u, t)) # Stocăm tuplul pentru filtrare ulterioară
            except:
                continue

# ---------- 2. FUNCTII DE CALCUL SI FILTRARE ----------

def get_filtered_times(bucket_val, active_users_set):
    """Extrage timpii doar pentru utilizatorii activi în setul furnizat."""
    all_data = bucket_times.get(bucket_val, [])
    return [t for u, t in all_data if u in active_users_set]

def rating_distribution(ratings, step=100):
    buckets = defaultdict(int)
    for r in ratings:
        bucket = (int(r) // step) * step
        buckets[bucket] += 1
    return buckets

def compute_top_percent(bucket_val, all_ratings):
    total = len(all_ratings)
    if total == 0: return 0
    above = sum(1 for r in all_ratings if r >= bucket_val)
    return (above / total) * 100

def print_bucket_stats(ratings, active_users_set, title, f):
    dist = rating_distribution(ratings, 100)
    total = len(ratings)
    print(f"\n{title}\n{'-'*95}", file=f)
    print(f"{'BUCKET':<15}{'USERS':<10}{'TOP %':<12}{'MEDIAN_TIME':<15}{'AVG_TIME':<15}", file=f)
    
    for b in sorted(dist):
        count = dist[b]
        top_p = compute_top_percent(b, ratings)
        
        # Filtrare timp per fereastra de activitate
        times = get_filtered_times(b, active_users_set)
        
        med = round(median(times), 3) if times else "-"
        avg = round(mean(times), 3) if times else "-"
        
        bucket_label = f"{b}-{b+99}"
        print(f"{bucket_label:<15}{count:<10}{round(top_p, 3):<12}{med:<15}{avg:<15}", file=f)
    print(f"TOTAL USERS: {total}", file=f)

def print_rank_stats(ratings, active_users_set, title, f):
    # Calculăm câți useri sunt în fiecare rank
    rank_counts = defaultdict(int)
    for r in ratings:
        for name, lo, hi in RANKS:
            if lo <= r <= hi:
                rank_counts[name] += 1
                break

    total = len(ratings)
    print(f"\n{title}\n{'-'*95}", file=f)
    print(f"{'RANK':<30}{'USERS':<10}{'TOP %':<12}{'MEDIAN_TIME':<15}{'AVG_TIME':<15}", file=f)
    
    for name, lo, hi in RANKS:
        count = rank_counts[name]
        if count == 0: continue
        
        # Top % calculat raportat la pragul de jos al rank-ului
        above = sum(1 for r in ratings if r >= lo)
        top_p = (above / total) * 100 if total > 0 else 0
        
        # Filtrare timp: Newbie nu are timp de bucket (e startul)
        if name == "Newbie":
            med, avg = "-", "-"
        else:
            times = get_filtered_times(lo, active_users_set)
            med = round(median(times), 3) if times else "-"
            avg = round(mean(times), 3) if times else "-"
            
        print(f"{name:<30}{count:<10}{round(top_p, 3):<12}{med:<15}{avg:<15}", file=f)

def print_fine_grained_data(ratings, title, f):
    dist = rating_distribution(ratings, 30)
    print(f"\n>>> DATE PENTRU GRAFIC: {title} (PAS 30) <<<\n{'BUCKET':<10}{'USERS':<10}", file=f)
    for b in sorted(dist):
        print(f"{b:<10}{dist[b]:<10}", file=f)
    print(">>> SFARSIT DATE GRAFIC <<<\n", file=f)

# ---------- 3. EXECUTIE PE FERESTRE ----------

for window, limit in ACTIVITY_WINDOWS.items():
    filename = f"{window.lower()}.txt"
    print(f"Se genereaza {filename}...")
    
    with open(filename, "w", encoding="utf-8") as out:
        # Identificăm userii care respectă limita de timp
        users_in_window = [u for u in user_current if limit is None or user_last_active[u] <= limit]
        active_set = set(users_in_window)
        
        if not users_in_window:
            print("Niciun utilizator gasit.", file=out)
            continue

        curr_r = [user_current[u] for u in users_in_window]
        peak_r = [user_peak[u] for u in users_in_window]

        print(f"{'='*40}\n ANALIZA: {window}\n{'='*40}", file=out)
        
        # CURRENT STATS
        print_bucket_stats(curr_r, active_set, "CURRENT RATING STATS (BUCKET 100)", out)
        print_rank_stats(curr_r, active_set, "CURRENT RANK STATS", out)
        
        # MAX STATS
        print_bucket_stats(peak_r, active_set, "MAX RATING STATS (BUCKET 100)", out)
        print_rank_stats(peak_r, active_set, "MAX RANK STATS", out)
        
        # DATE GRAFIC
        print_fine_grained_data(curr_r, window, out)

# ---------- 4. ANALIZA AVANSATA (ALL USERS) ----------

print("Se genereaza advanced_analysis.txt...")
with open("advanced_analysis.txt", "w", encoding="utf-8") as adv:
    print(f"{'='*45}\n ADVANCED CODEFORCES ANALYSIS (ALL USERS)\n{'='*45}", file=adv)
    
    all_users_set = set(user_current.keys())
    all_peak = list(user_peak.values())
    
    # Probabilitatea de a urca
    print("\nPROBABILITY TO REACH NEXT RANK\n" + "-"*65, file=adv)
    print(f"{'FROM':<25}{'TO':<25}{'PROBABILITY'}", file=adv)
    for i in range(len(RANKS)-1):
        name, lo, _ = RANKS[i]
        n_name, n_lo, _ = RANKS[i+1]
        reached_curr = sum(1 for r in all_peak if r >= lo)
        reached_next = sum(1 for r in all_peak if r >= n_lo)
        if reached_curr > 0:
            prob = (reached_next / reached_curr) * 100
            print(f"{name:<25}{n_name:<25}{round(prob, 2)}%", file=adv)

    # Timp median intre rank-uri (filtrare globala)
    print("\nMEDIAN TIME TO REACH RANK (FROM START)\n" + "-"*65, file=adv)
    print(f"{'RANK':<30}{'MEDIAN YEARS'}", file=adv)
    for name, lo, _ in RANKS:
        if name == "Newbie": continue
        times = get_filtered_times(lo, all_users_set)
        if times:
            print(f"{name:<30}{round(median(times), 3)}", file=adv)

print("\nSucces! Fisierele au fost create. Timpii sunt acum filtrati corect per utilizator.")