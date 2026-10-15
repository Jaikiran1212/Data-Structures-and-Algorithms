#include <iostream>
#include <stack>
using namespace std;

bool isBalanced(string str){
    stack<char> s;

    for(char ch : str){
        if(ch == '(' ||
           ch == '[' ||
           ch == '{'){
            s.push(ch);
        }
        else if(ch == ')' ||
                ch == ']' ||
                ch == '}'){
            if(s.empty()){
                return false;
            }
            char top = s.top();
            s.pop();

            if((ch == ')' && top != '(') ||
               (ch == ']' && top != '[') || 
               (ch == '}' && top != '{')){
                return false;
            }
        }
    }
    return s.empty();
}

int main(){
    string str;
    cout << "Enter the string of brackets : " << endl;
    cin >> str;

    if(isBalanced(str)){
        cout << "The brackets are balanced." << endl;
    }else{
        cout << "The brackets are not balanced." << endl;
    }
    return 0;
}