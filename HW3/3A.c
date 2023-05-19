#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* Modify from here */


/* Modify to here */


typedef enum {false, true} bool;


typedef struct _Node
{
	int octal;
	struct _Node* next;
} Node;

typedef struct
{
	Node* head;
	int len;
} LinkedList;

void InitList(LinkedList* plist);
int IsEmpty(LinkedList* plist);
void Insert(LinkedList* plist, int data);
void MergeTwoList(LinkedList* plist_a, LinkedList* plist_b, LinkedList* plist_c);
void PrintList(LinkedList* plist);
void PrintListHex (LinkedList* plist);

/* Modify from here */

int ReadOctal(LinkedList *plist, int pos);
void OctToDec(int * num);

/* Modify to here */


int main() {
    int i,j;
    int cnt;
    int input;
    LinkedList list_a,list_b,list_c;

    InitList(&list_a);
    InitList(&list_b);
    InitList(&list_c);

    for(i=0; i<2; i++)
    {
        scanf("%d",&cnt);
        for(j=0; j<cnt; j++)
        {
            scanf("%d",&input);
            if(i == 0)
                Insert(&list_a,input);
            else
                Insert(&list_b,input);
        }
    }

    MergeTwoList(&list_a,&list_b, &list_c);

    PrintList(&list_a);
    PrintList(&list_b);
    PrintList(&list_c);
    PrintListHex(&list_c);

	return 0;
}



/* Modify from here */

void InitList(LinkedList* plist)
{
    plist->head = (Node *) malloc(sizeof(Node));
    plist->head->next = NULL;
    plist->len = 0;
}
int IsEmpty(LinkedList* plist)
{
    int a = 0;
    if (plist->len == 0)
        a = 1;
    
    return a;
}
void Insert(LinkedList* plist, int data)
{
    Node* cur, *newNode;

    newNode = (Node *)malloc(sizeof(Node));
    newNode->octal = data;
    newNode->next = NULL;

    cur = plist->head;

    for (int i = 0; i < plist->len; i++)
    {
        if (newNode->octal > cur->next->octal)
        {
            cur = cur->next;
        }
    }

    newNode->next = cur->next;
    cur->next = newNode;
    plist->len++;
}
void MergeTwoList(LinkedList* plist_a, LinkedList* plist_b, LinkedList* plist_c)
{
    Node* cur;

    cur = plist_a->head;
    for (int i = 0; i < plist_a->len; i++)
    {
        Insert(plist_c, cur->next->octal);
        cur = cur->next;
    }
    cur = plist_b->head;
    for (int i = 0; i < plist_b->len; i++)
    {
        Insert(plist_c, cur->next->octal);
        cur = cur->next;
    }
}
void PrintList(LinkedList* plist)
{
    for (Node* cur = plist->head->next; cur != NULL; cur = cur->next)
        printf("%d ", cur->octal);
    printf("\n");
}
void PrintListHex (LinkedList* plist)
{
    int res[50];

    for (int i = 0; i < plist->len; i++)
    {
        res[i] = ReadOctal(plist, i);
    }

    OctToDec(res);

    for (int i = 0; i < plist->len; i++)
    {
        printf("%X ", res[i]);
    }
    printf("\n");
}
int ReadOctal(LinkedList *plist, int pos)
{
    Node* cur;
    if (IsEmpty(plist))
        exit(1);
    cur = plist->head->next;
    for (int i = 0; i < pos; i++)
        cur = cur->next;
    
    return cur->octal;
}
void OctToDec(int* num)
{
    int a, b, c;

    for (int i = 0; i < 50; i++)
    {
        if ((num[i] / 100) > 0)             // 100 이상
        {
            a = num[i] / 100;
            b = (num[i] % 100) / 10;
            c = (num[i] % 100) % 10;
        }
        else if ((num[i] / 10) > 0)         // 10 이상 100 미만
        {
            a = 0;
            b = num[i] / 10;
            c = num[i] % 10;
        }
        else                                // 10 미만
        {
            a = 0;
            b = 0;
            c = num[i] % 10;
        }
        num[i] = a * 64 + b * 8 + c;
    }
}

/* Modify to here */
