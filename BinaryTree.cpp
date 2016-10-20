//Add and remove
//Adding an existing element will just increase it's frequency
struct tree {
    struct node {
        int val;
        int freq = 1;
        node *left = nullptr, *right = nullptr;
    };

    node *root = nullptr;
    int size = 0;

    void add(int x) {
        root = add(x, root);
    }
    node* add(int x, node *h) {
        if (h == nullptr) {
            h = new node;
            h->val = x;
            size++;
            return h;
        }

        if (x > h->val) h->right = add(x, h->right);
        else if (x < h->val) h->left = add(x, h->left);
        else if (x == h->val) {
            h->freq++;
            size++;
        }
        return h;
    }
    bool rm(int x) {
        return rm(x, root);
    }
    bool rm(int x, node *h) {
        if (h == nullptr) {
            return false;
        }
        if (x > h->val) return rm(x, h->right);
        else if (x < h->val) return rm(x, h->left);
        else if (x == h->val) {
            if (h->freq > 0) {
                h->freq--;
                size--;
                return true;
            } else return false;
        }
        return false;
    }
};