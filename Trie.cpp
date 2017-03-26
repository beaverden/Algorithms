//Works with characters with ascii code less than 200
class Trie
{
public:
	Trie()
	{
		root = new node;
	}

	
	void add(std::string key)
	{
		add(key, 0, this->root);
	}

	int countWithPrefix(std::string prefix)
	{
		return countWithPrefix(prefix, 0, root);
	}

	struct node
	{
		node* nextChar[200] = { nullptr };
		int size = 0;
		bool isKey = false;
	};

private:
	node* root;

	bool add(std::string key, int keyIndex, node* root)
	{
		if (keyIndex == key.length())
		{
			root->isKey = true;
			root->size++;
			return true;
		}

		char currentChar = key[keyIndex];
		bool addedKey = false;

		
		if (root->nextChar[currentChar] == nullptr)
		{
			node* newNode = new node;
			root->nextChar[currentChar] = newNode;
		}

		addedKey |= add(key, keyIndex + 1, root->nextChar[currentChar]);
		if (addedKey) root->size++;

		return addedKey;
	}

	int countWithPrefix(std::string prefix, int prefixIndex, node* root)
	{
		if (root == nullptr) return 0;
		if (prefixIndex == prefix.length()) return root->size;
		return countWithPrefix(prefix, prefixIndex + 1, root->nextChar[prefix[prefixIndex]]);
	}

};