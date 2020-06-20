#include <stdio.h> 
#include <stdlib.h> 
#include<string.h>

#define treeHeight 100                     //height of huffman tree

// structure for huffman tree node 
struct Node 
{ 
	char data; 
	int freq; 
	struct Node *left, *right; 
}; 

//structure for minheap
struct MinHeap 
{ 
	int size; 
	int capacity; 
	struct Node **array; 
}; 

//structure used to save the codes for encoding
struct encode
{
    char codes[50][50];
};

//function to allocate a new min heap node with given character and frequency of the character 
struct Node* newNode(char data, int freq) 
{ 
	struct Node* temp= (struct Node*)malloc(sizeof(struct Node)); 

	temp->left = temp->right = NULL; 
	temp->data = data; 
	temp->freq = freq; 

	return temp; 
} 

//function to create a min heap of given capacity 
struct MinHeap* createMinHeap(int capacity) 
{ 
	struct MinHeap *H=(struct MinHeap*)malloc(sizeof(struct MinHeap)); 
	H->size=0; 
	H->capacity=capacity; 
	H->array=(struct Node**)malloc(H->capacity*sizeof(struct Node*)); 
	return H; 
} 

//function to swap two min heap nodes 
void swapNode(struct Node **a,struct Node **b) 
{ 
	struct Node* t = *a; 
	*a = *b; 
	*b = t; 
} 

// function to re arrange the min heap if there is a violation  
void rearrangeHeap(struct MinHeap *H, int index) 
{ 
	int min=index; 
	int left=2*index+1; 
	int right=2*index+2; 

	if (left < H->size && H->array[left]->freq < H->array[min]->freq) 
		min=left; 

	if (right < H->size && H->array[right]-> freq < H->array[min]->freq) 
		min=right; 

	if (H->array[min]-> freq < H->array[index]->freq) 
	{ 
		swapNode(&H->array[min],&H->array[index]); 
		rearrangeHeap(H,min); 
	} 
} 


//function to extract minimum value node from heap 
struct Node* extractMin(struct MinHeap *H) 
{ 
	struct Node* temp=H->array[0]; 
	H->array[0]=H->array[H->size-1]; 

	H->size--; 
	rearrangeHeap(H,0); 

	return temp; 
} 

// function to insert a new node to Min Heap 
void insertMinHeap(struct MinHeap *H, struct Node *minHeapNode) 
{ 
    H->size++; 
    int i=H->size-1; 
  
    while (i && minHeapNode->freq<H->array[(i-1)/2]->freq) 
    { 
  
        H->array[i]=H->array[(i-1)/2]; 
        i=(i-1)/2; 
    } 
  
    H->array[i]=minHeapNode; 
} 


// function to create a min heap of capacity equal to size and inserts all character of data[] in min heap
struct MinHeap* createAndBuildMinHeap(char data[], int freq[], int size) 
{ 
	struct MinHeap* H=createMinHeap(size); 

	for (int i=0;i<size;i++) 
		H->array[i]=newNode(data[i],freq[i]); 

	H->size=size; 
	int n=H->size-1; 
	int i; 

	for (i =(n-1)/2;i>=0;i--) 
		rearrangeHeap(H,i);

	return H; 
} 

// a driver function to build the huffman tree
struct Node* buildHuffmanTree(char data[], int freq[], int size) 
{ 
	struct Node *left,*right,*top; 
	struct MinHeap *H=createAndBuildMinHeap(data,freq,size); 

	while (H->size!=1) 
	{ 

		// Extract the two minimum freq items from min heap 
		left=extractMin(H); 
		right=extractMin(H); 

		// Create a new internal node with frequency equal to the sum of the two nodes frequencies. 
		// Make the two extracted node as left and right children of this new node. 
		// Add this node to the min heap 
		// ' ' is a special value for internal nodes, not used (dummy)
		top = newNode(' ',left->freq+right->freq); 

		top->left=left; 
		top->right=right; 

		insertMinHeap(H,top); 
	} 
 
	return extractMin(H); 
} 

// function to print an array of size n 
void printArr(int arr[], int n,int k,struct encode *e) 
{ 
	int i;
	char code[20];
	for(i=0;i<n;i++) 
	{
	    printf("%d",arr[i]);
	    code[i]=(char)arr[i]+'0';
	}
	code[i]='\0';
    printf("\n"); 
    strcpy(e->codes[k],code);
    
} 


// function to print huffman codes from the root of Huffman Tree 
void printCodes(struct Node *root,int arr[],int top,char data[],struct encode *e)
{ 
	if(root->left) 
	{ 
		arr[top] = 0; 
		printCodes(root->left,arr,top + 1,data,e); 
	}
	if(root->right) 
	{ 
		arr[top] = 1; 
		printCodes(root->right,arr,top + 1,data,e); 
	} 
	// If this is a leaf node, then it contains one of the input characters
	if(!root->left&&!root->right) 
	{ 
		printf("%c: ",root->data); 
		
		int i=0;
      	for( ;i<strlen(data);i++)
      	{
          	if(data[i]==root->data) 
          	{
                printArr(arr,top,i,e);
                break;
          	}
        }
		
	} 
	 
	    
} 

// function that builds a huffman Tree and print codes from the tree
void HuffmanCodes(char data[],int freq[],int size,struct encode *e) 
{ 
	// Construct Huffman Tree 
	struct Node* root=buildHuffmanTree(data,freq,size); 
	int arr[treeHeight],top=0; 
	
    printCodes(root,arr,top,data,e);// Print Huffman codes from the huffman tree

} 



	



			



