const int AL = 26;
struct aho_corasick{
    struct node{
        int p = 0;
        array<int, AL> nx;
        array<int, AL> kmp;
        int link = -1;
        int val = 0;
        char ch;
        node(char ch) : ch(ch){
            fill(nx.begin(), nx.end(), -1);
            fill(kmp.begin(), kmp.end(), -1);
        }
        int& operator[](char c){
            return nx[c-'a'];
        }
        int& operator()(char c){
            return kmp[c-'a'];
        }
    };
    vector<node> trie;
    aho_corasick() : trie(1, '!') {}
    void add_string(const string &s,int a){
        int cr = 0;
        for(auto &c : s){
            if(trie[cr][c] == -1){
                trie[cr][c] = trie.size();
                trie.emplace_back(c);
                trie.back().p = cr;
            }
            cr = trie[cr][c];
        }
        trie[cr].val += a;
    }
    int go(int x, char c = '!'){
        if(c == '!'){
            if(trie[x].link != -1) return trie[x].link;
            if(x == 0 || trie[x].p == 0) trie[x].link = 0;
            else trie[x].link = go(go(trie[x].p), trie[x].ch);
            go(trie[x].link);
            trie[x].val += trie[trie[x].link].val;
            return trie[x].link;
        }
        if(trie[x](c) != -1) return trie[x](c);
        if(trie[x][c] != -1) return trie[x](c) = trie[x][c];
        if(x == 0) return 0;
        return trie[x](c) = go(go(x), c);
    }
    void build(){
        for(int i=0;i<trie.size();i++){
            go(i);
        }
        /*for(int i=0;i<trie.size();i++){
            cout<<trie[i].link<<" "<<trie[i].val<<"\n";
        }
        cout<<"\n";*/
    }
    int getpos(string s){
        int cr = 0;
        for(auto &c : s) cr = go(cr, c);
        return cr;
    }
};

// Build the trie of words
aho_corasick trie;
for (const auto& word : words) {
  trie.add_string(word, 1);
}
trie.build();

// Traverse the text and update the values of the nodes in the trie
int node = 0;
for (const auto& c : text) {
  node = trie.go(node, c);
  trie[node].val++;
}

// Print the number of occurrences of each word
for (const auto& word : words) {
  int node = trie.getpos(word);
  std::cout << word << ": " << trie[node].val << std::endl;
}


/*
  This is a C++ implementation of the Aho-Corasick algorithm. 
  The aho_corasick class is used to build a trie of strings, and then find all the occurrences of these strings in a given text. 
  The node struct represents a node in the trie. It has fields for storing the parent node,
  the character associated with this node, the children of this node, the "failure link" of this node, 
  and the value associated with this node (the number of occurrences of the string associated with this node in the text). 
  The add_string method is used to add a string to the trie,
  and the build method is used to construct the failure links for each node in the trie. 
  The go method is used to traverse the trie and find the next node 
  to visit given the current node and the next character in the text. 
  The getpos method is used to find the node in the trie corresponding to a given string.
*/

/*
  
*/
