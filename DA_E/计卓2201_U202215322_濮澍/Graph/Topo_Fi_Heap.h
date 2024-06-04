//Heap
typedef struct{
	int * InDeg;
	int length;
}Heap;

status InitHeap(Heap &H,int n);
status DestroyHeap(Heap &H);
status InsertHeap(Heap &H,int e);
status DeleteHeap(Heap &H,int &e);
status BuildHeap(Heap &H,int a[],int n);