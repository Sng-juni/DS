#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_STACK 100

typedef enum {false , true} bool;

typedef struct {
    char small;
    char large;
    // *Variable "operator" 
    // used in ConvInfixToPostfix function
    char operator;	
}Hexa_num;

typedef struct {
    Hexa_num items[MAX_STACK];
    int top;
}Stack;

/* Modify from here */
int GetPriority(char op);
bool ComPriority(char op1, char op2);
int isOp(char op);
Hexa_num HexToDec(Hexa_num a1);
Hexa_num DecToHex(int res);
/* Modify to here */

Hexa_num add(Hexa_num b1,Hexa_num b2);
Hexa_num subtract(Hexa_num b1,Hexa_num b2);
Hexa_num multiply(Hexa_num b1,Hexa_num b2);
Hexa_num division(Hexa_num b1,Hexa_num b2);

void InitStack (Stack *pstack);
bool IsFull(Stack *pstack);
bool IsEmpty(Stack *pstack);
Hexa_num Peek(Stack *pstack);
void Push(Stack *pstack,Hexa_num item);
void Pop(Stack *pstack); 
void ConvInfixToPostfix(char* exp,char* convExp, int len);
Hexa_num EvalPostfix(char* exp,int len);
void print_Hexa_num(Hexa_num result);



int main() {
    char infix_exp[100];
    char postfix_exp[100];
    Hexa_num result;

    scanf("%s",infix_exp);
    ConvInfixToPostfix(infix_exp,postfix_exp,strlen(infix_exp));
    printf("%s\n",postfix_exp);
    result = EvalPostfix(postfix_exp,strlen(postfix_exp));
    print_Hexa_num(result);
    return 0;
}
/* Modify from here */
void InitStack(Stack *pstack)
{
    pstack->top = -1;
}
bool IsFull(Stack *pstack)
{
    return pstack->top == MAX_STACK - 1;
}
bool IsEmpty(Stack *pstack)
{
    return pstack->top == -1;
}
Hexa_num Peek(Stack *pstack)
{
    if (IsEmpty(pstack))
        exit(1);
    return pstack->items[pstack->top];
}
void Push(Stack *pstack, Hexa_num item)
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
int GetPriority(char op)
{
    if (op == '*' || op == '/')
        return 2;
    else if (op == '+' || op == '-')
        return 1;
    else
        return 0;
}
bool ComPriority(char op1, char op2)
{
    int op1_pr = GetPriority(op1);
    int op2_pr = GetPriority(op2);

    return (op1_pr >= op2_pr);
}
int isOp(char op)
{
    if (op == '+' || op == '-' || op == '*' || op == '/')
        return 1;
    else
        return 0;
}
void ConvInfixToPostfix(char *exp, char *convexp, int len)
{
    Stack stack;
    Hexa_num op;
    int idx = 0;
    InitStack(&stack);
    for (int i = 0; i < len; i++)
    {
        if (!isOp(exp[i]))
            convexp[idx++] = exp[i];
        else
        {
            while (!IsEmpty(&stack) && ComPriority(Peek(&stack).operator, exp[i]))
            {
                convexp[idx++] = Peek(&stack).operator;
                Pop(&stack);
            }
            op.operator = exp[i];
            Push(&stack, op);
        }
    }
    while (!IsEmpty(&stack))
    {
        convexp[idx++] = Peek(&stack).operator;
        Pop(&stack);
    }
}
Hexa_num HexToDec(Hexa_num a1)
{
    Hexa_num dec;

    if (a1.large >= 48 && a1.large <= 57)
        dec.large = (a1.large - 48);
    else if (a1.large >= 65 && a1.large <= 70)
        dec.large = (a1.large - 55);
    if (a1.small >= 48 && a1.small <= 57)
        dec.small = (a1.small - 48);
    else if (a1.small >= 65 && a1.small <= 70)
        dec.small = (a1.small - 55);
    
    return dec;
}
Hexa_num DecToHex(int res)
{
    int dec = res;
    Hexa_num Hex;

    int mod = dec % 16;
    if (mod < 10)
        Hex.small = 48 + mod;
    else
        Hex.small = 55 + mod;
    dec = dec / 16;
    mod = dec % 16;
    if (mod < 10)
        Hex.large = 48 + mod;
    else
        Hex.large = 55 + mod;

    return Hex;
}
Hexa_num add(Hexa_num b1, Hexa_num b2)
{
    Hexa_num res;
    int d_res;
    d_res = (16 * HexToDec(b1).large + HexToDec(b1).small) + (16 * HexToDec(b2).large + HexToDec(b2).small); 
         
    res = DecToHex(d_res);
    return res;
}
Hexa_num subtract(Hexa_num b1, Hexa_num b2)
{
    Hexa_num res;
    int d_res;
    d_res = (16 * HexToDec(b1).large + HexToDec(b1).small) - (16 * HexToDec(b2).large + HexToDec(b2).small);

    res = DecToHex(d_res);
    return res;
}
Hexa_num multiply(Hexa_num b1, Hexa_num b2)
{
    Hexa_num res;
    int d_res;
    d_res = (16 * HexToDec(b1).large + HexToDec(b1).small) * (16 * HexToDec(b2).large + HexToDec(b2).small);

    res = DecToHex(d_res);
    return res;
}
Hexa_num division(Hexa_num b1, Hexa_num b2)
{
    Hexa_num res;
    int d_res;
    d_res = (16 * HexToDec(b1).large + HexToDec(b1).small) / (16 * HexToDec(b2).large + HexToDec(b2).small);

    res = DecToHex(d_res);
    return res;
}
Hexa_num EvalPostfix(char *exp, int len)
{
    Stack stack;
    Hexa_num op;
    Hexa_num op1, op2;
    InitStack(&stack);
    for (int i = 0; i < len; i++)
    {
        if (!isOp(exp[i]))
        {
            if (!isOp(exp[i + 1]))
            {
                op.large = exp[i];
                op.small = exp[i + 1];
                Push(&stack, op);
                i++;
            }
        }
        else
        {
            op2 = Peek(&stack); Pop(&stack);
            op1 = Peek(&stack); Pop(&stack);
            if (exp[i] == '+')
            {
                Push(&stack, add(op1, op2));
            }
            else if (exp[i] == '-')
            {
                Push(&stack, subtract(op1, op2));
            }
            else if (exp[i] == '*')
            {
                Push(&stack, multiply(op1, op2));
            }
            else if (exp[i] == '/')
            {
                Push(&stack, division(op1, op2));
            }
        }      
    }
    return Peek(&stack);
}
void print_Hexa_num(Hexa_num result)
{
    printf("%c%c", result.large, result.small);
}
/* Modify to here */


