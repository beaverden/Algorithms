template <class T>
class RedBlackTree
{
public:
    RedBlackTree()
    {
        this->root = nullptr;
    }

    void add(T x)
    {
        root = add(this->root, x);
    }

    bool find(T x)
    {
        return find(this->root, x);
    }

    int lower_bound(T x)
    {
        return lower_bound(this->root, x);
    }

    int upper_bound(T x)
    {
        return size(root) - lower_bound(x);
    }

private:

    struct node
    {
        T value;
        node *left = nullptr;
        node *right = nullptr;
        bool red = true;
        int subtree_size = 0;
    };

    node *root;

    bool isRed(node *h)
    {
        if ( h == nullptr ) return false;
        else return (h->red);
    }

    void flipColors(node *h)
    {
        h->red = !h->red;
        h->left->red = !h->left->red;
        h->right->red = !h->right->red;
    }

    node* rotateRight(node *h)
    {
        node *x = h->left;
        h->left = x->right;
        x->right = h;
        x->red = x->right->red;
        x->right->red = true;
        x->subtree_size = size(h);
        h->subtree_size = size(h->left) + size(h->right) + 1;
        return x;
    }

    node* rotateLeft(node *h)
    {
        node *x = h->right;
        h->right = x->left;
        x->left = h;
        x->red = x->left->red;
        x->left->red = true;
        x->subtree_size = size(h);
        h->subtree_size = size(h->left) + size(h->right) + 1;

        return x;
    }

    int size(node *h)
    {
        if ( h == nullptr) return 0;
        return h->subtree_size;
    }

    node* add(node *h, T x)
    {
        if (h == nullptr)
        {
            h = new node;

            h->value = x;
            h->subtree_size = 1;
            h->red = true;

            return h;
        }
        if (x < h->value)
        {
            h->left = add(h->left, x);
        }
        else
        {
            h->right = add(h->right, x);
        }
        if (isRed(h->right) && !isRed(h->left))  h = rotateLeft(h);
        if (isRed(h->left)  &&  isRed(h->left->left)) h = rotateRight(h);
        if (isRed(h->left)  &&  isRed(h->right))     flipColors(h);

        h->subtree_size = size(h->left) + size(h->right) + 1;

        return h;
    }

    bool find(node *h, T x)
    {
        if (h == nullptr)
        {
            return false;
        }
        if (x == h->value)
        {
            return true;
        }
        else if (x < h->value)
        {
            return find(h->left, x);
        }
        else
        {
            return find(h->right, x);
        }
    }


    int lower_bound(node *h, int x)
    {
        if (h == nullptr)
        {
            return 0;
        }
        if (x >= h->value)
        {
            return 1 + size(h->left) + lower_bound(h->right, x);
        }
        else
        {
            return lower_bound(h->left, x);
        }
    }

};