#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	int value;
	struct node *left;
	struct node *right;
} Node;

#define STACK_SIZE 10

typedef struct stack {
	int top;
	Node *items[STACK_SIZE];
} stack;

int queue[20] , val=0;

void push(stack *ms, Node *item)
{
	if(ms->top < STACK_SIZE-1)
		ms->items[++(ms->top)] = item;
	else
		printf("full\n");
}

Node* pop(stack *ms)
{
	if(ms->top > -1 )
		return ms->items[(ms->top)--];
	else
		printf("empty\n");
}

Node* peek(stack ms)
{
	if(ms.top < 0) {
		printf("empty\n");
		return 0;
	}
	return ms.items[ms.top];
}

int isEmpty(stack ms)
{
	if(ms.top < 0)
		return 1;
	else
		return 0;
}

void dfs(Node *root)
{
	stack ms;
	ms.top = -1;

	if(root == NULL)
		return ;

	Node *currentNode = NULL;
	// Закидываем корень
	push(&ms,root);

	while(!isEmpty(ms)) {
		// вытаскиваем ноду
		currentNode = pop(&ms);
		// выводим ноду
		//printf("%d  ", currentNode->value);
		// В очередь
		queue[val] = currentNode->value;
		val++;
		// закидываем правого потомка
		if(currentNode->right)
			push(&ms, currentNode->right);
		// закидываем левого потомка
		if(currentNode->left)
			push(&ms, currentNode->left);
	}
}

// void preorder(Node *root)
// {
// 	if(!root)
// 		return;

// 	printf("%d ", root->value );
// 	preorder(root->left);
// 	preorder(root->right);
// }

Node* createNode(int value)
{
	Node * newNode =  (Node *)malloc(sizeof(Node));

	newNode->value = value;
	newNode->right= NULL;
	newNode->left = NULL;

	return newNode;
}

Node* addNode(Node *node, int value)
{
	if(node == NULL)
        return createNode(value);
	else {
		if (node->value > value)
			node->left = addNode(node->left, value);
		else
			node->right = addNode(node->right, value);
	}
	return node;
}

int main()
{
	Node *root = NULL;
	int n;

	// создание дерева
	for(int i=0; i<7; i++) {
		scanf("%d", &n);
		root = addNode(root, n);
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