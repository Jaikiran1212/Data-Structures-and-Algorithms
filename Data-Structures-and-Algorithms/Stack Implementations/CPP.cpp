#include <iostream>
using namespace std;

class Stack {
private:
    int top;
    int arr[100];

public:
    Stack() {
        top = -1;
    }

    void push(int x) {
        if (top >= 99) {
            cout << "Stack Overflow" << endl;
            return;
        }

        arr[++top] = x;
        cout << "Pushed " << x << " to stack." << endl;
    }

    int pop() {
        if (top < 0) {
            cout << "Stack Underflow" << endl;
            return -1;
        }

        return arr[top--];
    }

    int peek() {
        if (top < 0) {
            cout << "Stack is Empty" << endl;
            return -1;
        }

        return arr[top];
    }

    bool isEmpty() {
        return (top == -1);
    }

    int size() {
        return top + 1;
    }
};

int main() {
    Stack s;

    s.push(100);
    s.push(200);
    s.push(300);

    cout << "\nPopped Element: " << s.pop() << endl;

    cout << "Top Element: " << s.peek() << endl;

    cout << "Size of Stack: " << s.size() << endl;

    if (s.isEmpty()) {
        cout << "Stack is Empty" << endl;
    } else {
        cout << "Stack is Not Empty" << endl;
    }

    return 0;
}