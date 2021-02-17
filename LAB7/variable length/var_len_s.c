#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<netinet/in.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<string.h>
#define MAX_TREE_HT 100 
struct MinHeapNode 
{ 
  char data; 
  unsigned freq; 
  struct MinHeapNode *left, *right; 
}; 
struct MinHeapNode* rootpt;
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
	minHeap->array = (struct MinHeapNode**)malloc(minHeap-> 
        capacity * sizeof(struct MinHeapNode*)); 
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
		int i; 
		for (i = 0; i < top; ++i) 
		{
			printf("%d", arr[i]);	 
		}
		printf("\n");  
	} 
} 

void HuffmanCodes(char data[], int freq[], int size) 
{ 
	struct MinHeapNode* root = buildHuffmanTree(data, freq, size); 
	int arr[MAX_TREE_HT], top = 0, fin=-2; 
	rootpt = root;
        printf("CHARACTERS\tCODE\n--------------------------------\n");
	printCodes(root, arr, top); 
}
void decode(struct MinHeapNode* root, char s[], int z) 
{ 		
  struct MinHeapNode* curr = root; 
  for (int i=0;i<z;i++) 
  { 
    if (s[i] == '0') 
        curr = curr->left; 
    else
        curr = curr->right;  
    if (curr->left==NULL && curr->right==NULL) 
    { 
        printf("%c",curr->data);
        curr = root; 
    } 
  }  
} 
int main()
{
	int s_sock,c_sock,j,c,f[100],z=0;
	char a[100],en[1024];
	struct sockaddr_in server, other;
	memset(&server, 0, sizeof(server));
	memset(&other, 0, sizeof(other));
	s_sock = socket(AF_INET, SOCK_STREAM, 0);
	server.sin_family = AF_INET;
	server.sin_port = htons(9009);
	server.sin_addr.s_addr = INADDR_ANY;
	if(bind(s_sock, (struct sockaddr*)&server, sizeof(server))==-1)
	{
		printf("Error in binding..\n");
		exit(1);
	}
	listen(s_sock, 10);
	socklen_t add;
	add = sizeof(other);
	c_sock = accept(s_sock, (struct sockaddr*)&other, &add);
	recv(c_sock, &j, sizeof(j), 0);
	printf("COUNT OF UNIQUE CHARACTERS >>> %d\n",j);
	recv(c_sock, a, sizeof(a), 0);
	recv(c_sock, f, sizeof(f), 0);
	HuffmanCodes(a, f, j); 
	FILE *fp;
	fp =fopen("decode.txt","w");
	recv(c_sock, &c, sizeof(c), 0);
	while(c!=2)
	{
		fputc(c,fp);
		en[z++]=c;
		recv(c_sock, &c, sizeof(c), 0);
	}
	fclose(fp);
	printf("DECODED DATA: \n------------------------------\n");
	decode(rootpt, en, z); 
	close(s_sock);
	return 0;
}
