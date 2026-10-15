#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool isBalanced(char str[]){
    char stack[100];
    int top = -1;

    for(int i = 0; i < strlen(str);i++){
        char ch = str[i];
        if(ch == '(' || ch == '[' || ch == '{'){
            stack[++top] = ch;
        }else if(ch ==')' || ch == ']' || ch == '}'){
            if(top < 0){
                return false;
            }
            top--;
            char topchar = stack[top];
            if((ch == ')' && topchar != '(') || (ch == ']' && topchar != '[') || (ch == '}' && topchar != '{')){
                return false;
            }
        }
    }
    return (top == -1);
}