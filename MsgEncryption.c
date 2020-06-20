// C program for Huffman Coding 
#include <stdio.h> 
#include <stdlib.h> 
#include<string.h>
#include "Huffmanimpl.h"

void main()
{
	int freq[50];
	char c,arr[50],message[50];
	int size,i,j;
	struct encode *e=(struct encode*)malloc(sizeof(struct encode));
	printf("\nENTER THE NUMBER OF CHARACTERS:");
	scanf(" %d",&size);
	for(i=0;i<size;i++)
	{
		scanf(" %c",&c);
		arr[i]=c;
	}
	printf("\nENTER THE FREQUENCIES :");
	for(i=0;i<size;i++){
		printf("\nENTER THE FREQUENCY FOR %c:",arr[i]);
		scanf(" %d",&freq[i]);
	}
	
	HuffmanCodes(arr, freq, size,e); 
	printf("\nTHE CHARACTERS AND FREQUENCIES :\n");
	printf("\n-----------------------------------------------------------------------");
	printf("\n|\tCHARACTER\t|\tFREQUENCIES\t|\tCODE WORDS\t|");
	printf("\n-----------------------------------------------------------------------\n");
	for(i=0;i<size;i++){
		printf("|  %-10c \t\t|\t  %d  \t\t|  %-10s \t\t|\n",arr[i],freq[i],e->codes[i]);
	}
	printf("\n-----------------------------------------------------------------------\n");
    
    ///////////////////////ENCRYPTING A MSG///////////////////////////////
    int op=1;
    while(op){
    	printf("\nENTER MESSAGE TO ENCRYPT:");
    	scanf(" %[^\n]",message);
    	printf("\n\nENCRYPTED MESSAGE:");
    	for(i=0;i<strlen(message);i++)
    	{
        	if(message[i]==' ')
        	    printf(" ");
        
        	for(int j=0;j<size;j++)
        	{
        	    if(message[i]==arr[j])
        	        printf("%s",e->codes[j]);
        	}
    	}
    	printf("\nDO U WANT TO CONTINUE:(0 - EXIT)");
    	scanf(" %d",&op);
    }
 
}

/*
OUTPUT:
ENTER THE NUMBER OF CHARACTERS:8
a
c
d
e
k
l
r
s

ENTER THE FREQUENCIES :
ENTER THE FREQUENCY FOR a:5

ENTER THE FREQUENCY FOR c:12

ENTER THE FREQUENCY FOR d:9

ENTER THE FREQUENCY FOR e:10

ENTER THE FREQUENCY FOR k:15

ENTER THE FREQUENCY FOR l:22

ENTER THE FREQUENCY FOR r:2

ENTER THE FREQUENCY FOR s:1
k: 00
s: 01000
r: 01001
a: 0101
d: 011
l: 10
e: 110
c: 111

THE CHARACTERS AND FREQUENCIES :

-----------------------------------------------------------------------
|	CHARACTER	    |	FREQUENCIES	|	CODE WORDS	|
-----------------------------------------------------------------------
|  a          		|	  5  		|	0101 		|
|  c          		|	  12  		|	111 		|
|  d          		|	  9  		|	011 		|
|  e          		|	  10  		|	110 		|
|  k          		|	  15  		|	00 		    |
|  l          		|	  22  		|	10 		    |
|  r          		|	  2  		|	01001 		|
|  s          		|	  1  		|	01000 		|

-----------------------------------------------------------------------

ENTER MESSAGE TO ENCRYPT:cakes leader / side?

ENCRYPTED MESSAGE:11101010011001000 10110010101111001001  01000011110

*/
