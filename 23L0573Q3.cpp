#include <iostream>
using namespace std;

template<typename T>
class StackList {
    struct Node {
        T data;
        Node* next;
        Node(T val) : data(val), next(nullptr) {}
    };

    Node* top;
    Node* min; // Stack to store minimum values

public:
    StackList() : top(nullptr), min(nullptr) {}

    ~StackList() {
        while (!isEmpty()) {
            pop();
        }
    }

    void push(const T& val) {
        Node* newNode = new Node(val);
        newNode->next = top;
        top = newNode;

        if (!min || val <= min->data) {
            Node* nmin = new Node(val);
            nmin->next = min;
            min = nmin;
        }
    }

    void pop() {
        if (isEmpty()) {
            return;
        }
        if (top->data == min->data) {
            Node* minTemp = min;
            min = min->next;
            delete minTemp;
        }
        Node* temp = top;
        top = top->next;
        delete temp;
    }

    T Top() const {
        if (!isEmpty()) {
            return top->data;
        }
        cout << "Stack is empty\n";
        return T(); 
    }

    bool isEmpty() const {
        return top == nullptr;
    }

    void print() const {
        if (isEmpty()) {
            return;
        }
        Node* temp = top;
        while (temp != nullptr) {
            cout << temp->data << " ";
            temp = temp->next;
        }
        cout << endl;
    }

    T getMin() const {
        if (min != nullptr) {
            return min->data;
        }
        return T();
    }
};

int main() {
    cout << "\n\tQ3\n\n\t";
    StackList<int> stack;
    stack.push(4);
    stack.push(2);
    stack.push(3);
    stack.push(1);
    stack.print();

    cout << "\tMin element: " << stack.getMin() << "\n\n\t";
    stack.pop();
    stack.print();
    cout << "\tMin element: " << stack.getMin() << "\n\n\t";

    return 0;
}
