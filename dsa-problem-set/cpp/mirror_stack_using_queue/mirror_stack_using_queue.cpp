#include <iostream>
#include <stack>
#include <queue>
#include <stdexcept>

using namespace std;

// Empties the stack into the queue, one element at a time.
void stack2queue(stack<int>& s, queue<int>& q){
    while(!s.empty()){
        q.push(s.top());
        s.pop();
    }
}

// Empties the queue into the stack, one element at a time.
void queue2stack(queue<int>& q, stack<int>& s){
    while(!q.empty()){
        s.push(q.front());
        q.pop();
    }
}

// Reverses ("mirrors") the contents of a stack using only an auxiliary
// queue as extra storage.
void mirror(stack<int>& s){
    if(s.empty()){
        return;
    }

    queue<int> q;

    // Draining the stack into a queue (LIFO -> FIFO) and then draining
    // that queue back into the stack (FIFO -> LIFO) reverses the order
    // of the elements exactly once, which mirrors the stack.
    stack2queue(s, q);
    queue2stack(q, s);
}

// Prints a stack from top to bottom without modifying it.
void printStack(stack<int> s){
    cout << "[";
    bool first = true;
    while(!s.empty()){
        if(!first){
            cout << ", ";
        }
        cout << s.top();
        s.pop();
        first = false;
    }
    cout << "]" << endl;
}

int main(){

    stack<int> s;

    s.push(1);
    s.push(2);
    s.push(3);
    s.push(4);
    s.push(5);

    cout << "Before mirror: ";
    printStack(s);

    mirror(s);

    cout << "After mirror: ";
    printStack(s);

    return 0;
}
