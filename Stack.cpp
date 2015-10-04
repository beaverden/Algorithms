struct Stack {
    struct node {
        int val;
        node *left = nullptr;
    };
    node *first = nullptr;
	int size = 0;

    void push(int x) {
		size++;
        if (first == nullptr) {
            first = new node;
            first->val = x;
        } else {
            node *temp = new node;
            temp->val = x;
            temp->left = first;

            first = temp;
        }
    }
    void pop() {
		size--;
        first = first->left;
    }
    int top() {
        return first->val;
    }
	int size() {
		return size;
	}
};