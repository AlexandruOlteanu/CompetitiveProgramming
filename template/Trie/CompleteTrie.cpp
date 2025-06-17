/*
    How to use:
    CompleteTrie<32> trie32; (for 32 byte numbers)
    or
    CompleteTrie<64> trie64; (for 64 byte numbers)

    Of course it works with strings as well;
*/
// https://github.com/AlexandruOlteanu/CompetitiveProgramming/blob/main/template/Trie/CompleteTrie.cpp
template <int N>
class CompleteTrie {
private:
    struct TrieNode {
        std::unordered_map<char, TrieNode*> children;
        int pass;
        int end;
        TrieNode() : pass(0), end(0) {}
    };

    TrieNode* root;

public:
    CompleteTrie() {
        root = new TrieNode();
    }

    ~Trie() {
        deleteTrie(root);
    }

    void insert(int64_t number) {
        std::string s = toBinaryString(number);
        TrieNode* node = root;
        node->pass++;
        for (char c : s) {
            if (node->children.find(c) == node->children.end()) {
                node->children[c] = new TrieNode();
            }
            node = node->children[c];
            node->pass++;
        }
        node->end++;
    }

    void insert(const std::string& word) {
        TrieNode* node = root;
        node->pass++;
        for (char c : word) {
            if (node->children.find(c) == node->children.end()) {
                node->children[c] = new TrieNode();
            }
            node = node->children[c];
            node->pass++;
        }
        node->end++;
    }

    bool searchMostSignificantBits(int64_t number, int X) {
        if (X >= N) return false;
        std::string binaryString = toBinaryString(number);
        std::string bitsToCheck = binaryString.substr(binaryString.size() - N, N - X);
        TrieNode* node = root;
        for (char c : bitsToCheck) {
            auto it = node->children.find(c);
            if (it == node->children.end()) return false;
            node = it->second;
        }
        return node->pass > 0;
    }

    bool startsWith(const std::string& prefix) {
        TrieNode* node = root;
        for (char c : prefix) {
            auto it = node->children.find(c);
            if (it == node->children.end()) return false;
            node = it->second;
        }
        return node->pass > 0;
    }

    bool search(int64_t number) {
        std::string s = toBinaryString(number);
        TrieNode* node = root;
        for (char c : s) {
            auto it = node->children.find(c);
            if (it == node->children.end()) return false;
            node = it->second;
        }
        return node->end > 0;
    }

    bool search(const std::string& word) {
        TrieNode* node = root;
        for (char c : word) {
            auto it = node->children.find(c);
            if (it == node->children.end()) return false;
            node = it->second;
        }
        return node->end > 0;
    }

    int getCount(int64_t number) {
        std::string s = toBinaryString(number);
        TrieNode* node = root;
        for (char c : s) {
            auto it = node->children.find(c);
            if (it == node->children.end()) return 0;
            node = it->second;
        }
        return node->end;
    }

    int getCount(const std::string& word) {
        TrieNode* node = root;
        for (char c : word) {
            auto it = node->children.find(c);
            if (it == node->children.end()) return 0;
            node = it->second;
        }
        return node->end;
    }

    void erase(int64_t number) {
        std::string s = toBinaryString(number);
        eraseHelper(root, s, 0, false);
    }

    void eraseAll(int64_t number) {
        std::string s = toBinaryString(number);
        eraseHelper(root, s, 0, true);
    }

    void erase(const std::string& word) {
        eraseHelper(root, word, 0, false);
    }

    void eraseAll(const std::string& word) {
        eraseHelper(root, word, 0, true);
    }

private:
    std::string toBinaryString(int64_t number) {
        return std::bitset<N>(static_cast<uint64_t>(number)).to_string();
    }

    int eraseHelper(TrieNode* node, const std::string& str, size_t index, bool removeAll) {
        if (index == str.size()) {
            int removed = removeAll ? node->end : (node->end ? 1 : 0);
            node->end -= removed;
            node->pass -= removed;
            return removed;
        }
        char c = str[index];
        auto it = node->children.find(c);
        if (it == node->children.end()) return 0;
        TrieNode* child = it->second;
        int removed = eraseHelper(child, str, index + 1, removeAll);
        if (removed) {
            node->pass -= removed;
            if (child->pass == 0) {
                delete child;
                node->children.erase(it);
            }
        }
        return removed;
    }

    void deleteTrie(TrieNode* node) {
        for (auto& p : node->children) {
            deleteTrie(p.second);
        }
        delete node;
    }
};