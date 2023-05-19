#include <stdlib.h>
#include <stdio.h>
#include <string.h>
/* Modify from here */


/* Modify to here */

#define MAX_HEAP 100

typedef enum { false, true } bool;

typedef struct {
	char small;
	char middle;
	char large;
} Hexa_num;

typedef struct {
    Hexa_num data; // This is a priority as well as data
} PNode;

typedef struct {
	PNode items[MAX_HEAP + 1];
	int num;
} Heap;

void InitHeap(Heap *pheap);

bool IsEmpty(Heap *pheap);

bool IsFull(Heap *pheap);

void Insert(Heap *pheap, Hexa_num data);

Hexa_num Delete(Heap *pheap);

void HeapSort(Hexa_num a[], int n);

Hexa_num *CreateHexaNum(int n);

void GetInput();

/* Modify from here */

int GetParent(int idx);
int GetLChild(int idx);
int GetRChild(int idx);
int GetHighPriorityChild(Heap* pheap, int idx);
int HexToDec(Hexa_num data);
int CharToInt(char num);

/* Modify to here */



int main() {
    
	GetInput();
	/*
	5
	0E0
	321
	EEE
	CCC
	3D0
	*/

	return 0;
}

void HeapSort(Hexa_num a[], int n) {
	Heap heap;
	InitHeap(&heap);
	// Insert all elements to the heap.
	for (int i = 0; i < n; i++)
		Insert(&heap, a[i]);

	// Remove all elements from the heap.
	for (int i = 0; i <= n-1; i++)
		a[i] = Delete(&heap);

	for (int i = 0; i < n; i++)
		printf("%c%c%c\n", a[i].large, a[i].middle, a[i].small);
}

Hexa_num *CreateHexaNum(int n){
    char a[4];
	Hexa_num *res = (Hexa_num*)malloc(sizeof(Hexa_num)*(n));
	for (int i = 0; i < n; i++) {
        scanf("%s", &a);
        res[i].large = a[0];
		res[i].middle = a[1];
		res[i].small = a[2];
	}
	return res;
}

void GetInput() {
    int n;
    Hexa_num *data;
    scanf("%d", &n);
    data = CreateHexaNum(n);
	HeapSort(data, n);
}

/* Modify from here */

void InitHeap(Heap *pheap)
{
	pheap->num = 0;
}
bool IsEmpty(Heap *pheap)
{
	return pheap->num == 0;
}
bool IsFull(Heap *pheap)
{
	return pheap->num == MAX_HEAP;
}
void Insert(Heap *pheap, Hexa_num data)
{
	PNode newNode;
	int idx = pheap->num + 1;
	if (IsFull(pheap))
		exit(1);
	while (idx > 1)
	{
		int parent = GetParent(idx);
		if (HexToDec(data) < HexToDec(pheap->items[parent].data))
		{
			pheap->items[idx] = pheap->items[parent];
			idx = parent;
		}
		else
			break;	
	}	
	newNode.data = data;
	
	pheap->items[idx] = newNode;
	pheap->num++;
}
Hexa_num Delete(Heap *pheap)
{
	Hexa_num min = pheap->items[1].data;
	PNode last = pheap->items[pheap->num];
	int parent = 1, child;

	while (child = GetHighPriorityChild(pheap, parent))
	{
		if (HexToDec(last.data) > HexToDec(pheap->items[child].data))
		{
			pheap->items[parent] = pheap->items[child];
			parent = child;
		}
		else
			break;
	}

	pheap->items[parent] = last;
	pheap->num--;

	return min;
}
int GetParent(int idx)
{
	return idx / 2;
}
int GetLChild(int idx)
{
	return idx * 2;
}
int GetRChild(int idx)
{
	return idx * 2 + 1;
}
int GetHighPriorityChild(Heap* pheap, int idx)
{
	if (GetLChild(idx) > pheap->num)
		return 0;
	else if (GetLChild(idx) == pheap->num)
		return GetLChild(idx);
	else
	{
		int left = GetLChild(idx), right = GetRChild(idx);
		if (HexToDec(pheap->items[left].data) < HexToDec(pheap->items[right].data))
			return left;
		else
			return right;
	}
}
int HexToDec(Hexa_num data)
{
	int Dec;
	Dec = CharToInt(data.large) * 16 * 16 + CharToInt(data.middle) * 16 + CharToInt(data.small);

	return Dec;
}
int CharToInt(char num)
{
	int Inum;
	if (num >= 48 && num <= 57)
		Inum = num - 48;
	else if (num >= 65 && num <= 70)
		Inum = num - 55;
	else
		return 0;
	
	return Inum;
}

/* Modify to here */
