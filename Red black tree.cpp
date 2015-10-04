struct rb_tree {
    struct node {
        int val;
        node *left = nullptr, *right = nullptr;
        bool red = true;
        int sz = 0;
    };
    node *root = nullptr;
    int t;

    bool isRed(node *h) {
        if ( h == nullptr ) return false;
        else return (h->red);
    }

    void add(int x) {
        root = add(root, x);
    }
    node* add(node *h, int x) {
        if (h == nullptr) {
            h = new node;

            h->val = x;
            h->sz = 1;
            h->red = true;

            return h;
        }
        if (x < h->val) {
            h->left = add(h->left, x);
        } else {
            h->right = add(h->right, x);
        }
        if (isRed(h->right) && !isRed(h->left))  h = rotateLeft(h);
        if (isRed(h->left)  &&  isRed(h->left->left)) h = rotateRight(h);
        if (isRed(h->left)  &&  isRed(h->right))     flipColors(h);

        h->sz = size(h->left) + size(h->right) + 1;

        return h;
    }
    int size(node *h) {
        if ( h == nullptr) return 0;
        return h->sz;
    }
    void flipColors(node *h) {
        h->red = !h->red;
        h->left->red = !h->left->red;
        h->right->red = !h->right->red;
    }
    node* rotateRight(node *h) {
        node *x = h->left;
        h->left = x->right;
        x->right = h;
        x->red = x->right->red;
        x->right->red = true;
        x->sz = size(h);
        h->sz = size(h->left) + size(h->right) + 1;
        return x;
    }
    node* rotateLeft(node *h) {
        node *x = h->right;
        h->right = x->left;
        x->left = h;
        x->red = x->left->red;
        x->left->red = true;
        x->sz = size(h);
        h->sz = size(h->left) + size(h->right) + 1;

        return x;
    }
    int lower_bound(node *h, int x) {
        if (h == nullptr) return 0;
        int g = h->val;
        int s = size(h->left);
        if (x >= h->val) return 1 + size(h->left) + lower_bound(h->right,x);
        else return lower_bound(h->left,x);

    }
} tree;