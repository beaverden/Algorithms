struct queue {
    struct node {
        int val;
        node *next = nullptr;
    };
    node *first;
    node *last;
    int size = 0;
    void push(int val) {
        if (size == 0) {
            first = new node;
            first->val = val;
            last = first;
        } else {
            last->next = new node;
            last->next->val = val;
            last = last->next;
        }
        size++;
    }

    int pop() {
        if (size == 0) {
            return -1;
        }

        int val;
        if (size == 1) {
            val = first->val;
			delete first;
            first = nullptr;
            last = nullptr;
        } else {
            val = first->val;
            node *temp = first->next;
            delete first;
            first = temp;
            temp = nullptr;
        }
        size--;
        return val;
    }

    int front() {
        if (size == 0) {
            return -1;
        } else {
            return first->val;
        }
    }

    bool empty() {
        return (size == 0);
    }

    void show() {
        node *temp = first;
        while (temp != nullptr) {
            printf("%d ", temp->val);
            temp = temp->next;
        }
    }
};
