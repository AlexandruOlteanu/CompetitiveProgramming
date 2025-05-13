using hash_t = uint64_t;

mt19937_64 rng1(chrono::steady_clock::now().time_since_epoch().count() * ((uint64_t) new char | 1));

// When P = 2^32 - 13337, both P and (P - 1) / 2 are prime.
const hash_t HASH_P = (unsigned) -13337;
uniform_int_distribution<hash_t> MULT_DIST(0.1 * HASH_P, 0.9 * HASH_P);
const hash_t HASH_MULT[] = {MULT_DIST(rng1), MULT_DIST(rng1)};
const int HASH_COUNT = 2;

vector<unsigned> hash_pow[HASH_COUNT];

struct StringHash {
    vector<unsigned> prefix_hash[HASH_COUNT];
    string result;

    // Default constructor
    StringHash() {}

    // Constructor that builds the string hash for a given string
    template<typename T_string>
    StringHash(const T_string &str) {
        build(str);
    }

    // Get the length of the string stored in the hash
    int length() const {
        return max((int)prefix_hash[0].size() - 1, 0);
    }

    // Build the prefix hashes for a given string
    template<typename T_string>
    void build(const T_string &str) {
        result = str;
        for (int h = 0; h < HASH_COUNT; h++) {
            if (hash_pow[h].empty())
                hash_pow[h] = {1};

            while (hash_pow[h].size() <= str.size())
                hash_pow[h].push_back(HASH_MULT[h] * hash_pow[h].back() % HASH_P);

            prefix_hash[h].resize(str.size() + 1);
            prefix_hash[h][0] = 0;

            for (int i = 0; i < (int) str.size(); i++)
                prefix_hash[h][i + 1] = (HASH_MULT[h] * prefix_hash[h][i] + str[i]) % HASH_P;
        }
    }

    // Add a character to the result and update the prefix hashes
    void add_char(char c) {
        result += c;

        for (int h = 0; h < HASH_COUNT; h++) {
            if (hash_pow[h].empty())
                hash_pow[h] = {1};

            hash_pow[h].push_back(HASH_MULT[h] * hash_pow[h].back() % HASH_P);

            if (prefix_hash[h].empty())
                prefix_hash[h] = {0};

            prefix_hash[h].push_back((HASH_MULT[h] * prefix_hash[h].back() + c) % HASH_P);
        }
    }

    // Compute the hash for a substring from start to end for a specific hash function
    hash_t _substring_hash(int h, int start, int end) const {
        hash_t start_hash = (hash_t)prefix_hash[h][start] * hash_pow[h][end - start];
        return (prefix_hash[h][end] + HASH_P * HASH_P - start_hash) % HASH_P;
    }

    // Combine the results of all hash functions into a single hash for the substring
    hash_t combined_hash(int start, int end) const {
        return _substring_hash(0, start, end) + (HASH_COUNT > 1 ? _substring_hash(1, start, end) << 32 : 0);
    }

    // Equality operator to compare two string_hash objects
    bool operator==(const StringHash &sh2) const {
        if (length() != sh2.length()) return false;

        return combined_hash(0, length()) == sh2.combined_hash(0, length());
    }

};

// Returns length of longest prefix of a that it's also a suffix of b
int kmpMaxPrefSufMatch(StringHash &a, StringHash &b) {
    int sza = a.length(), szb = b.length();
    int overlap = 0;
    for (int i = 1; i <= min(sza, szb); ++i) {
        if (a.combined_hash(0, i) == b.combined_hash(szb - i, szb)) {
            overlap = i;
        }
    }
    return overlap;
}

int kmpMaxPrefSufMatch(const string& a, const string& b) {
    StringHash aHash(a);
    StringHash bHash(b);
    return kmpMaxPrefSufMatch(a, b);
}

// KMP matching function that checks if a pattern exists in the text using hashing
bool kmpMatch(StringHash &text_hash, StringHash &pattern_hash) {
    int pattern_length = pattern_hash.length();
    int text_length = text_hash.length();

    for (int i = 0; i <= text_length - pattern_length; ++i) {
        if (text_hash.combined_hash(i, i + pattern_length) == pattern_hash.combined_hash(0, pattern_length)) {
            return true;  // Match found
        }
    }
    return false;  // No match found
}

bool kmpMatch(const string &text, const string &pattern) {
    StringHash text_hash(text);
    StringHash pattern_hash(pattern);
    return kmpMatch(text_hash, pattern_hash);
}