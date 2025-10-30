/* ========================================================================
   -> Read Line
   ======================================================================== */
string readLine() {
    string line;
    getline(cin, line);
    return line;
}

/* ========================================================================
   -> Split words
   ======================================================================== */
vector<string> splitWords(const string& line, const string& extraDelimiters = "") {
    const unordered_set<char> delimiters(extraDelimiters.begin(), extraDelimiters.end());
    vector<string> words;
    string current;

    for (char ch : line) {
        if (isalnum(ch)) {
            current += ch;
        } else if (!current.empty() && (isspace(ch) || delimiters.count(ch) || !isalnum(ch))) {
            words.push_back(current);
            current.clear();
        }
    }

    if (!current.empty()) {
        words.push_back(current);
    }

    return words;
}