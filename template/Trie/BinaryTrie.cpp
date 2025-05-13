/*
    How to use:
    BinaryTrie<32> trie32; (for 32 byte numbers)
    or
    BinaryTrie<64> trie64; (for 64 byte numbers)
*/
template <int N>
class BinaryTrie {
private:
    struct TrieNode {
        TrieNode* child[2];
        int pass;
        int end;
        TrieNode() : child{nullptr,nullptr}, pass(0), end(0) {}
    };
    TrieNode* root;

public:
    BinaryTrie() { root = new TrieNode(); }
    ~BinaryTrie() { deleteTrie(root); }

    void insert(int64_t number) {
        std::string s = std::bitset<N>(static_cast<uint64_t>(number)).to_string();
        TrieNode* node = root;
        node->pass++;
        for(char c: s) {
            int b = c - '0';
            if(!node->child[b]) node->child[b] = new TrieNode();
            node = node->child[b];
            node->pass++;
        }
        node->end++;
    }

    bool search(int64_t number) {
        std::string s = std::bitset<N>(static_cast<uint64_t>(number)).to_string();
        TrieNode* node = root;
        for(char c: s) {
            int b = c - '0';
            if(!node->child[b]) return false;
            node = node->child[b];
        }
        return node->end > 0;
    }

    bool searchMostSignificantBits(int64_t number, int X) {
        if (X >= N) return false;
        TrieNode* node = root;
        for (int i = N - 1; i >= X; --i) {
            int b = (number >> i) & 1;
            if (!node->child[b]) return false;
            node = node->child[b];
        }
        return node->pass > 0;
    }

    int getCount(int64_t number) {
        std::string s = std::bitset<N>(static_cast<uint64_t>(number)).to_string();
        TrieNode* node = root;
        for(char c: s) {
            int b = c - '0';
            if(!node->child[b]) return 0;
            node = node->child[b];
        }
        return node->end;
    }

    void erase(int64_t number) { eraseHelper(root, std::bitset<N>(static_cast<uint64_t>(number)).to_string(), 0, false); }
    void eraseAll(int64_t number){ eraseHelper(root, std::bitset<N>(static_cast<uint64_t>(number)).to_string(), 0, true); }

private:
    int eraseHelper(TrieNode* node, const std::string& s, size_t idx, bool all) {
        if(idx == s.size()){
            int rem = all ? node->end : (node->end?1:0);
            node->end -= rem;
            node->pass -= rem;
            return rem;
        }
        int b = s[idx]-'0';
        TrieNode* ch = node->child[b];
        if(!ch) return 0;
        int rem = eraseHelper(ch, s, idx+1, all);
        if(rem){
            node->pass -= rem;
            if(ch->pass==0){
                delete ch;
                node->child[b]=nullptr;
            }
        }
        return rem;
    }

    void deleteTrie(TrieNode* node){
        if(node->child[0]) deleteTrie(node->child[0]);
        if(node->child[1]) deleteTrie(node->child[1]);
        delete node;
    }
};