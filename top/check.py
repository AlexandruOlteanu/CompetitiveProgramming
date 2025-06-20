import requests

MY_RATING = 1634

url = "https://codeforces.com/api/user.ratedList?activeOnly=false&includeRetired=true"
response = requests.get(url)
users = response.json()['result']
users_above_me = [user for user in users if user['rating'] > MY_RATING]

print("There is a total of " + str(len(users)) + " users in total")

print(f"I am in the top {len(users_above_me) / len(users) * 100:.2f}% of users")