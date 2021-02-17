#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<unistd.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<string.h>
#include<math.h>
#define MAX_TREE_HT 100 
int j=0,k=0,z=0,c_sock,f[100]={0},d=0;
char ip[1024];
FILE *fptr;
struct sockaddr_in client;
struct MinHeapNode 
{ 
  char data; 
  unsigned freq; 
  struct MinHeapNode *left, *right; 
}; 
struct MinHeap 
{ 
  unsigned size; 
  unsigned capacity; 
  struct MinHeapNode** array; 
}; 
struct MinHeapNode* newNode(char data, unsigned freq) 
{ 
	struct MinHeapNode* temp = (struct MinHeapNode*)malloc(sizeof(struct MinHeapNode)); 
	temp->left = temp->right = NULL; 
	temp->data = data; 
	temp->freq = freq; 
	return temp; 
} 
struct MinHeap* createMinHeap(unsigned capacity) 
{ 
	struct MinHeap* minHeap = (struct MinHeap*)malloc(sizeof(struct MinHeap)); 
	minHeap->size = 0; 
	minHeap->capacity = capacity; 
	minHeap->array = (struct MinHeapNode**)malloc(minHeap->capacity * sizeof(struct MinHeapNode*)); 
    return minHeap; 
} 
void swapMinHeapNode(struct MinHeapNode** a,struct MinHeapNode** b) 
{ 
	struct MinHeapNode* t = *a; 
	*a = *b; 
	*b = t; 
} 
void minHeapify(struct MinHeap* minHeap, int idx) 
{ 
	int smallest = idx; 
	int left = 2 * idx + 1; 
	int right = 2 * idx + 2; 
	if (left < minHeap->size && minHeap->array[left]-> freq < minHeap->array[smallest]->freq) 
		smallest = left; 
	if (right < minHeap->size && minHeap->array[right]-> freq < minHeap->array[smallest]->freq) 
		smallest = right; 
	if (smallest != idx) 
    { 
		swapMinHeapNode(&minHeap->array[smallest], &minHeap->array[idx]); 
		minHeapify(minHeap, smallest); 
	} 
}
int isSizeOne(struct MinHeap* minHeap) 
{ 
	return (minHeap->size == 1); 
} 
struct MinHeapNode* extractMin(struct MinHeap* minHeap) 
{ 

	struct MinHeapNode* temp = minHeap->array[0]; 
	minHeap->array[0] = minHeap->array[minHeap->size - 1]; 
        --minHeap->size; 
	minHeapify(minHeap, 0); 
	return temp; 
}  
void insertMinHeap(struct MinHeap* minHeap, struct MinHeapNode* minHeapNode) 
{ 

	++minHeap->size; 
	int i = minHeap->size - 1; 
	while (i && minHeapNode->freq < minHeap->array[(i - 1) / 2]->freq) 
        { 
		minHeap->array[i] = minHeap->array[(i - 1) / 2]; 
		i = (i - 1) / 2; 
	} 
	minHeap->array[i] = minHeapNode; 
} 
void buildMinHeap(struct MinHeap* minHeap) 
{ 

	int n = minHeap->size - 1; 
	int i; 
	for (i = (n - 1) / 2; i >= 0; --i) 
		minHeapify(minHeap, i); 
} 
int isLeaf(struct MinHeapNode* root) 
{ 
	return !(root->left) && !(root->right); 
} 
struct MinHeap* createAndBuildMinHeap(char data[], int freq[], int size) 
{ 

	struct MinHeap* minHeap = createMinHeap(size); 
	for (int i = 0; i < size; ++i) 
		minHeap->array[i] = newNode(data[i], freq[i]); 
	minHeap->size = size; 
	buildMinHeap(minHeap); 
	return minHeap; 
} 
struct MinHeapNode* buildHuffmanTree(char data[], int freq[], int size) 
{ 
	struct MinHeapNode *left, *right, *top; 
	struct MinHeap* minHeap = createAndBuildMinHeap(data, freq, size); 
	while (!isSizeOne(minHeap)) 
       { 
		left = extractMin(minHeap); 
		right = extractMin(minHeap); 
		top = newNode('$', left->freq + right->freq); 
		top->left = left; 
		top->right = right; 

		insertMinHeap(minHeap, top); 
	} 
	return extractMin(minHeap); 
} 
void printCodes(struct MinHeapNode* root, int arr[], int top) 
{ 
	if (root->left) 
        { 
		arr[top] = 0; 
		printCodes(root->left, arr, top + 1); 
	} 
	if (root->right) 
        { 
		arr[top] = 1; 
		printCodes(root->right, arr, top + 1); 
	} 
	if (isLeaf(root)) 
    { 
		printf("%c\t\t", root->data);
		d++; 
		int i,end=-1; 
		for (i = 0; i < top; ++i) 
			printf("%d", arr[i]);	 
		printf("\n");  
	} 
} 
void encode(struct MinHeapNode* root, int arr[], int top, char ch) 
{ 
	if (root->left) 
    { 
		arr[top] = 0; 
		encode(root->left, arr, top + 1, ch); 
	} 
	if (root->right) 
    { 
		arr[top] = 1; 
		encode(root->right, arr, top + 1, ch); 
	} 
	if (isLeaf(root)) 
    { 
		if(root->data == ch)
		{ 
			int i; 
			for (i = 0; i < top; ++i) 
			{
				fprintf(fptr,"%d",arr[i]);	 
			}
		} 
	}
} 
void HuffmanCodes(char data[], int freq[], int size) 
{ 
	struct MinHeapNode* root = buildHuffmanTree(data, freq, size); 
	int arr[MAX_TREE_HT], top = 0, fin=-2; 
	fptr = fopen("encode.txt","w");
	for(int m=0; m<z; m++)
		encode(root, arr, top, ip[m]);
	fclose(fptr);
        printf("CHARACTER\tCODE\n---------------------------------------\n");
	printCodes(root, arr, top); 
}
int main()
{
	int i,n,flag=0,ind,flag1=2,r;
	char a[100],c;
	memset(&client,0, sizeof(client));
	c_sock = socket(AF_INET, SOCK_STREAM, 0);
	client.sin_family = AF_INET;
	client.sin_port = htons(9009);
	client.sin_addr.s_addr = INADDR_ANY;
	if((connect(c_sock, (struct sockaddr*)&client, sizeof(client)))==-1)
	{
		printf("Connection error\n");
		exit(0);
	}
	FILE *fp;
	fp =fopen("inputtext.txt","r");
	printf("INFORMATION IN THE FILE : \n------------------------------\n");
	while((c=fgetc(fp))!=EOF)
	{
		printf("%c",c);
		ip[z++]=c;
		for(i=0; i<j; i++)
		{
			if(a[i]==c)
			{
				ind=i;
				flag=1;
				break;
			}
			else
				flag=0;
		}
		if(flag==1)
			f[ind]=f[ind]+1;
		else
		{
			a[j]=c;
			f[j]=f[j]+1;
			j++;
		}
	}
	printf("\n");
	send(c_sock, &j, sizeof(j), 0);
	fclose(fp);
	send(c_sock, a, sizeof(a), 0);
	send(c_sock, f, sizeof(f), 0);
	HuffmanCodes(a, f, j); 
	fp =fopen("encode.txt","r");
	printf("\nCOMPRESSED ENCODED DATA:\n");
	while((r=fgetc(fp))!= EOF)
	{
		printf("%c",r);
		send(c_sock, &r, sizeof(r), 0);
	}
	send(c_sock, &flag1, sizeof(flag1), 0);
	printf("\n");
	return 0;
}
