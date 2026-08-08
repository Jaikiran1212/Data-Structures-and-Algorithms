#include <iostream>
using namespace std;

// A single node of a singly linked list. Each node stores one digit.
class Node {
    public:
    int data;
    Node* next;

    Node(int num){
        data = num;
        next = nullptr;
    }
};

class Linked_List_add{
    public:
    // Adds two numbers that are represented as linked lists (one digit
    // per node) and returns the head of the resulting linked list.
    static Node* addTwoNUmber(Node* l1 , Node* l2){
        Node* temp = new Node(0);   // dummy head node, makes list building easier
        Node* current = temp;

        int carry = 0;
        // Keep going while either list still has nodes, or there is a
        // leftover carry to push into a new node.
        while(l1 != nullptr || l2 != nullptr || carry != 0){
            int x;

            if(l1 != nullptr){
                x = l1 -> data;
            }else{
                x=0;
            }

            int y;
            if(l2 != nullptr){
                y=l2->data;
            }else{
                y=0;
            }
            int sum = (x+y+carry);

            carry = sum /10;

            current->next = new Node(sum%10);
            current = current -> next;

            if(l1 != nullptr){
                l1 = l1 -> next;
            }
            if(l2 != nullptr){
                l2 = l2 -> next;
            }
        }

        return temp->next; // skip the dummy head
    }
};

// Prints a linked list in "a -> b -> c" format.
void printList(Node* head){
    Node* current = head;

    while(current != nullptr){
        cout << current->data;

        if(current -> next != nullptr){
            cout << " -> ";
        }

        current = current -> next;
    }
    cout << endl;
}

int main(){

    int T;
    cin >> T;

    while(T > 0){
        int N;
        cin >> N;

        if(N < 1 || N > 100000){
            cerr << "N must be between 1 and 10^5" <<endl;
            return 0;
        }
        int M;
        cin >> M;

        if(M < 1 || M > 100000){
            cerr << "M must be between 1 and 10^5"<<endl;
            return 0;
        }

        // Build the first linked list from N input digits.
        Node* temp1 = new Node(0);
        Node* current1 = temp1;

        for(int i = 0; i < N; i++){
            int data;
            cin >> data;

            if(data < 0 || data > 9){
                cerr << "List1 elements must be between 0 and 9"<<endl;
                return 0;
            }

            current1 -> next = new Node(data);
            current1 = current1 -> next;
        }

        // Build the second linked list from M input digits.
        Node* temp2 = new Node(0);
        Node* current2 = temp2;

        for(int i = 0; i < M; i++){
            int data;
            cin >> data;

            if(data < 0 || data > 9){
                cerr << "List2 elements must be between 0 and 9"<<endl;
                return 0;
            }

            current2 -> next = new Node(data);
            current2 = current2 -> next;
        }

        // Add the two lists and print the result.
        Node* result = Linked_List_add::addTwoNUmber(temp1 -> next, temp2 -> next);
        printList(result);

        T--;
    }
    return 0;
}
