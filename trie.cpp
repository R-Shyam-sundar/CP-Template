const int mxCnt = 26;
const char baseChar = 'a';

struct Node{
	Node *links[mxCnt];
	int freq=0;
	int endCnt=0;

	bool containsKey(char ch){
		return (links[ch-baseChar] != NULL);
	}

	void put(char ch, Node *node){
		links[ch-baseChar] = node;
	}

	Node* get(char ch){
		return links[ch-baseChar];
	}

	bool isEnd(){
		return endCnt>0;
	}
};


class Trie{
private:
	Node* root;
public:
	Trie(){
		root = new Node();
	}
	void insert(string word){
		Node *node = root;
		for(auto &x: word){
			if(!node->containsKey(x)){
				Node *newNode = new Node();
				newNode->freq++;
				node->put(x, newNode);
			}else{
				Node *nextNode = node->get(x);
				nextNode->freq++;
			}
			node = node->get(x);
		}
		node->endCnt++;
	}

	bool search(string word){
		Node *node = root;
		for(auto &x: word){
			if(!node->containsKey(x)){
				return false;
			}
			node = node->get(x);
		}
		return node->isEnd();
	}

	bool deleteString(string word){
		Node *node = root;
		if(!this->search(word)){
			return false;
		}
		for(auto &x: word){
			Node *nextNode = node->get(x);
			nextNode->freq--;
			node = node->get(x);
		}
		node->endCnt--;
		node = root;
		for(auto &x: word){
			Node *nextNode = node->get(x);
			if(nextNode->freq == 0){
				node->links[x] = NULL;
			}
			node = nextNode;
		}
		return true;
	}
};
