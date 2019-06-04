#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	int visit;
	int value;
	struct node *left;
	struct node *right;
} Node;

int val, front = 0, rear = -1;
int queue[20];

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

void bfs(Node *root)
{
	val = root->value;
	if ((front <= rear)&&(root->value == queue[front])) {
		if (root->left != NULL)
			queue[++rear] = root->left->value;
		if (root->right != NULL || root->right  ==  NULL)
			queue[++rear] = root->right->value;
		front++;
	}

	if (root->left != NULL)
		bfs(root->left);

	if (root->right != NULL)
		bfs(root->right);
}

int main()
{
	Node *root = NULL;
	int n;

	scanf("%d", &n);
	root = insert(root, n);
	for(int i = 0; i < 6; i++) {
		scanf("%d", &n);
		insert(root, n);
	}
	
	queue[++rear] = root->value;
	bfs(root);
	for(int i = 0; i <= rear; i++) {
		printf("%d", queue[i]);
		if(queue[i+1])
			printf(" ");
	}
	printf("\n");

	return 0;
}
