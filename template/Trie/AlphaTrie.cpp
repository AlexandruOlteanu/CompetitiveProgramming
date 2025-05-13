template <int ALPHA=26>
class AlphaTrie {
private:
    struct TrieNode {
        TrieNode* child[ALPHA];
        int pass;
        int end;
        TrieNode() : child{nullptr}, pass(0), end(0) { for(int i=0;i<ALPHA;i++) child[i]=nullptr; }
    };
    TrieNode* root;

public:
    AlphaTrie() { root = new TrieNode(); }
    ~AlphaTrie() { deleteTrie(root); }

    void insert(const std::string& word){
        TrieNode* node = root;
        node->pass++;
        for(char c: word){
            int id = c-'a';
            if(!node->child[id]) node->child[id]=new TrieNode();
            node = node->child[id];
            node->pass++;
        }
        node->end++;
    }

    bool search(const std::string& word){
        TrieNode* node = root;
        for(char c: word){
            int id = c-'a';
            if(!node->child[id]) return false;
            node = node->child[id];
        }
        return node->end>0;
    }

    int getCount(const std::string& word){
        TrieNode* node = root;
        for(char c: word){
            int id = c-'a';
            if(!node->child[id]) return 0;
            node = node->child[id];
        }
        return node->end;
    }

    void erase(const std::string& word){ eraseHelper(root, word, 0, false); }
    void eraseAll(const std::string& word){ eraseHelper(root, word, 0, true); }

private:
    int eraseHelper(TrieNode* node, const std::string& s, size_t idx, bool all){
        if(idx==s.size()){
            int rem = all ? node->end : (node->end?1:0);
            node->end -= rem;
            node->pass -= rem;
            return rem;
        }
        int id = s[idx]-'a';
        TrieNode* ch = node->child[id];
        if(!ch) return 0;
        int rem = eraseHelper(ch, s, idx+1, all);
        if(rem){
            node->pass -= rem;
            if(ch->pass==0){
                delete ch;
                node->child[id]=nullptr;
            }
        }
        return rem;
    }

    void deleteTrie(TrieNode* node){
        for(int i=0;i<ALPHA;i++) if(node->child[i]) deleteTrie(node->child[i]);
        delete node;
    }
};