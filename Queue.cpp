template <typename T>
struct queue {
    typedef T value_type;

    struct node {
        value_type val;
        node *next = nullptr;
    };

    node *first;
    node *last;
    int size = 0;
    void push(value_type val) {
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

    value_type pop() {
        value_type val;
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

    value_type front() {
        return first->val;
    }

    bool empty() {
        return (size == 0);
    }
};