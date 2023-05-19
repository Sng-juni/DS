#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

typedef enum {false, true} bool;

typedef char Data;

typedef struct {
    Data items[MAX];
    int top;
} Stack;

void InitStack(Stack *pstack);
bool IsFull(Stack *pstack);
bool IsEmpty(Stack *pstack);
Data Peek(Stack *pstack);
void Push(Stack *pstack, Data item);
void Pop(Stack *pstack);
void R_Char(char* for_char, char* back_char, int len);
int Check_Palindrome(char* for_char, char* back_char, int len);

int main()
{
    char forward[100] = {0, };
    char backward[100] = {0, };
    int result = 0;

    scanf("%s", forward);
    R_Char(forward, backward, strlen(forward));
    printf("%s\n", backward);
    result = Check_Palindrome(forward, backward, strlen(forward));
    printf("%d", result);
    return 0;
}   

void InitStack(Stack *pstack)
{
    pstack->top = -1;
}
bool IsFull(Stack *pstack)
{
    return pstack->top == MAX - 1;
}
bool IsEmpty(Stack *pstack)
{
    return pstack->top == -1;
}
Data Peek(Stack *pstack)
{
    if (IsEmpty(pstack))
        exit(1);
    return pstack->items[pstack->top];
}
void Push(Stack *pstack, Data item)
{
    if (IsFull(pstack))
        exit(1);
    pstack->items[++(pstack->top)] = item;
}

void Pop(Stack *pstack)
{
    if (IsEmpty(pstack))
        exit(1);
    --(pstack->top);
}
void R_Char(char* for_char, char* back_char, int len)
{
    Stack stack;
    int idx = 0;

    InitStack(&stack);
    for (int i = 0; i < len; i++)
    {
        Push(&stack, for_char[i]);
    }
    while (!IsEmpty(&stack))
    {
        back_char[idx++] = Peek(&stack);
        Pop(&stack);
    }
}
int Check_Palindrome(char* for_char, char* back_char, int len)
{
    int res = 0;
    for (int i = 0; i < len; i++)
    {
        if (for_char[i] == '*' || back_char[i] == '*')
            res += 0;
        else if (for_char[i] == back_char[i])
            res += 0;
        else if (for_char[i] != back_char[i])
            res += 1;
    }

    return res;
}