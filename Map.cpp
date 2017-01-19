#pragma once
#include <stdexcept>

template <class Key, class Value>
class Map
{
public:
	Map()
	{
		this->root = nullptr;
	}

	~Map() {}

	void insert(Key key, Value value)
	{
		root = add(root, key, value);
	}

	bool empty()
	{
		return (size(root) == 0);
	}

	int size()
	{
		return size(root);
	}

	Value& operator[](const Key key)
	{
		TreeNode* found = find(root, key);
		if (found)
		{
			return found->value;
		}
		else
		{
			root = add(root, key, Value());
			return at(key);
		}
	}

	Value& at(const Key key)
	{
		TreeNode* found = find(root, key);
		if (found)
		{
			return found->value;
		}
		else
		{
			throw std::runtime_error("No such element");
		}
	}

	bool hasKey(const Key key)
	{
		TreeNode* found = find(root, key);
		if (found)
		{
			return true;
		}
		return false;
	}

	void clear()
	{
		clear(this->root);
		this->root = nullptr;
	}
private:

	struct TreeNode
	{
		Key key;
		Value value;
		TreeNode* left = nullptr;
		TreeNode* right = nullptr;
		bool red = true;
		int subtree_size = 0;
	};

	TreeNode* root = nullptr;

	/* Helper functions */
	bool isRed(TreeNode* h)
	{
		if (h == nullptr) return false;
		else return (h->red);
	}

	void flipColors(TreeNode* h)
	{
		h->red = !h->red;
		h->left->red = !h->left->red;
		h->right->red = !h->right->red;
	}

	TreeNode* rotateRight(TreeNode* h)
	{
		TreeNode* x = h->left;
		h->left = x->right;
		x->right = h;
		x->red = x->right->red;
		x->right->red = true;
		x->subtree_size = size(h);
		h->subtree_size = size(h->left) + size(h->right) + 1;
		return x;
	}

	TreeNode* rotateLeft(TreeNode* h)
	{
		TreeNode* x = h->right;
		h->right = x->left;
		x->left = h;
		x->red = x->left->red;
		x->left->red = true;
		x->subtree_size = size(h);
		h->subtree_size = size(h->left) + size(h->right) + 1;

		return x;
	}

	int size(TreeNode* h)
	{
		if (h == nullptr) return 0;
		return h->subtree_size;
	}
	/* End Helper functions */

	TreeNode* add(TreeNode* h, Key key, Value value)
	{
		if (h == nullptr)
		{
			h = new TreeNode;
			h->key = key;
			h->value = value;
			h->subtree_size = 1;
			h->red = true;

			return h;
		}
		if (key < h->key)
		{
			h->left = add(h->left, key, value);
		}
		else if (key > h->key)
		{
			h->right = add(h->right, key, value);
		}
		else
		{
			return h;
		}

		if (isRed(h->right) && !isRed(h->left))  h = rotateLeft(h);
		if (isRed(h->left) && isRed(h->left->left)) h = rotateRight(h);
		if (isRed(h->left) && isRed(h->right))     flipColors(h);

		h->subtree_size = size(h->left) + size(h->right) + 1;

		return h;
	}

	TreeNode* find(TreeNode* h, Key key)
	{
		if (h == nullptr)
		{
			return nullptr;
		}
		if (key == h->key)
		{
			return h;
		}
		else if (key < h->key)
		{
			return find(h->left, key);
		}
		else
		{
			return find(h->right, key);
		}
	}

	void clear(TreeNode* h)
	{
		if (h == nullptr) return;
		clear(h->right);
		clear(h->left);
		delete h;
	}
};