#include <stdio.h>
#include <stdlib.h>

typedef struct node {
//	int visit;
	int value;
	struct node *left;
	struct node *right;
} Node;

// int val, front = 0, rear = -1;
int queue[20] , val=0;

void *newNode(int item)
{
	Node *temp =  malloc(sizeof(Node));
	temp->value = item;
	temp->left = temp->right = NULL;
}

Node* insert(Node* node, int value)
{
	if(node == NULL)
		return newNode(value);

	if(value < node->value)
		node->left  = insert(node->left, value);
	else if(value > node->value)
		node->right = insert(node->right, value);

	return node; 
}

void dfs(Node *root)
{
	if (root) {
		if (root->left)
			dfs(root->left);

		if (root->right)
			dfs(root->right);

		// printf("%d  ", root->value);
		queue[val] = root->value;
		val++;
    }
}

int main()
{
	Node *root = NULL;
	int n;

	for(int i=0; i<20; i++)
		queue[i]=0;

	scanf("%d", &n);
	root = insert(root, n);
	for(int i = 0; i < 6; i++) {
		scanf("%d", &n);
		insert(root, n);
	}
	
	dfs(root);

	for(int i=0; i<val; i++) {
		printf("%d", queue[i]);
		if(queue[i+1])
			printf(" ");
	}
	printf("\n");

	return 0;
}
