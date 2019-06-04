#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	int value; // значение, которое хранит узел
	struct node *next; // ссылка на следующий элемент списка
	struct node *prev; // ссылка на предыдущий элемент
} node;

typedef struct list {
	struct node *head; // начало списка
	struct node *tail; // конец списка
} list;

// инициализация пустого списка
void init(list* l)
{
	l->head = NULL;
	l->tail = NULL;
}

//удалить все элементы из списка
void clear(list* l)
{
	node* tmp = l->head;
	node* tmp1;

	while(tmp != NULL) {
		tmp1 = tmp->next;
		free(tmp);
		tmp = tmp1;
	}
	l->head = NULL;
	l->tail = NULL;
}

// проверка на пустоту списка
int isEmpty(list* l)
{
	if((l->head == NULL) && (l->tail == NULL))
		return 0;
	return 1;
}

// поиск элемента по значению. вернуть NULL если элемент не найден
int find(list* l, int value)
{
	node*  tmp;
	tmp = l->head;

	while(tmp != NULL) {
		if(tmp->value == value)
			return 1;
		tmp = tmp->next;
	}
	return 0;
}

// вставка значения в конец списка, вернуть 0 если успешно
int push_back(list* l, int value)
{
	node* tmp = malloc(sizeof(node));
	tmp->value = value;
	tmp->prev = NULL;
	tmp->next = NULL;

	// Если список пуст
	if(l->head == NULL) {
		l->head = tmp;
		l->tail = tmp;
		return 0;
	}
	// Остальное
	else {
		tmp->prev = l->tail;
		l->tail->next = tmp;
		l->tail = tmp;
		return 0;
	}
	return 1;
}

// вставка значения в начало списка, вернуть 0 если успешно
int push_front(list* l, int value)
{
	node* tmp = malloc(sizeof(node));
	tmp->value = value;
	tmp->prev = NULL;
	tmp->next = NULL;

	// Если список пуст
	if(l->tail == NULL) {
		l->head = tmp;
		l->tail = tmp;
		return 0;
	}
	// Остальное
	else {
		tmp->next = l->head;
		l->head->prev = tmp;
		l->head = tmp;
		return 0;
	}
	return 1;
}

// вставка значения после указанного узла, вернуть 0 если успешно
// int insertAfter(node* n, int value);
int insertAfter(list* l, int num, int value)
{
	node* tmp = l->head;

	for(int i=0; i<num; ++i)
		tmp = tmp->next;

	if(tmp == NULL)
		return 1;

	node* tmp2 = malloc(sizeof(node));
	tmp2->value = value;
	// Если после конца
	if(tmp == l->tail) {
		tmp->next = tmp2;
		tmp2->prev = tmp;
		tmp2->next = NULL;
	}
	// Остальное
	else {
		tmp2->next = tmp->next;
		tmp2->prev = tmp;

		tmp->next = tmp2;
		tmp = tmp->next;
		tmp = tmp->next;
		tmp->prev = tmp2;
		return 0;
	}
}

// вставка значения перед указанным узлом, вернуть 0 если успешно
// int insertBefore(node* n, int value);
int insertBefore(list* l, int num, int value)
{
	node* tmp = l->head;

	for(int i=0; i<num; ++i)
		tmp = tmp->next;

	if(tmp == NULL)
		return 1;

	node* tmp2 = malloc(sizeof(node));
	tmp2->value = value;
	// Если до начала
	if(tmp == l->head) {
		tmp->prev = tmp2;
		tmp2->next = tmp;
		tmp2->prev = NULL;
		l->head = tmp2;
	}
	// Остальное
	else {
		tmp2->prev = tmp->prev;
		tmp2->next = tmp;

		tmp->prev = tmp2;
		tmp = tmp->prev;
		tmp = tmp->prev;
		tmp->next = tmp2;
		return 0;
	}
}

// удалить первый элемент из списка с указанным значением, вернуть 0 если успешно
int removeFirst(list* l, int value)
{
	node* tmp1 = l->head;
	node* tmp2;

	while(tmp1 != NULL) {
		tmp2 = tmp1;
		if(tmp1->value == value) {
			// Если это начало
			if(tmp1 == l->head) {
				tmp1 = tmp1->next;
				tmp1->prev = NULL;
				free(tmp2);
			}
			// Если это конец
			else if(tmp1 == l->tail) {
				tmp1 = tmp1->prev;
				tmp1->next = NULL;
				free(tmp2);
				l->tail = tmp1;
			}
			// Все остальное
			else {
				tmp1 = tmp2->next;
				tmp1->prev = tmp2->prev;
				tmp1 = tmp2->prev;
				tmp1->next = tmp2->next;
				free(tmp2);
			}
			return 0;
		}
		tmp1 = tmp1->next;
	}
	return 1;
}

// удалить последний элемент из списка с указанным значением, вернуть 0 если успешно
int removeLast(list* l, int value)
{
	node* tmp1 = l->tail;
	node* tmp2;

	while(tmp1 != NULL) {
		tmp2 = tmp1;
		if(tmp1->value == value) {
			// Если это конец
			if(tmp1 == l->tail) {
				tmp1 = tmp1->prev;
				tmp1->next = NULL;
				free(tmp2);
			}
			// Если это начало
			else if(tmp1 == l->head) {
				tmp1 = tmp1->next;
				tmp1->prev = NULL;
				free(tmp2);
				l->head = tmp1;
			}
			// Все остальное
			else {
				tmp1 = tmp2->next;
				tmp1->prev = tmp2->prev;
				tmp1 = tmp2->prev;
				tmp1->next = tmp2->next;
				free(tmp2);
			}
			return 0;
		}
		tmp1 = tmp1->prev;
	}
	return 1;
}

// вывести все значения из списка в прямом порядке, через пробел, после окончания вывода перейти на новую строку
void print(list* l)
{
	node*  tmp;
	tmp = l->head;

	while(tmp != NULL) {
		//printf("data %d; point %p; prev %p; next %p\n", tmp->value, tmp, tmp->prev, tmp->next);
		printf("%d", tmp->value);
		tmp = tmp->next;
		if(tmp != NULL)
			printf(" ");
	}
	printf("\n");
}

// вывести все значения из списка в обратном порядке, через пробел, после окончания вывода перейти на новую строку
void print_invers(list* l)
{
	node*  tmp;
	tmp = l->tail;

	while(tmp != NULL) {
		//printf("data %d; point %p; prev %p; next %p\n", tmp->value, tmp, tmp->prev, tmp->next);
		printf("%d", tmp->value);
		tmp = tmp->prev;
		if(tmp != NULL)
			printf(" ");
	}
	printf("\n");
}

int main()
{
	int N, n, y;
	list current;

	//freopen("input.txt", "r", stdin);
	//freopen("output.txt", "w", stdout);

	init(&current);

	scanf("%d", &N);

	for(int i=0; i<N; ++i) {
		scanf("%d", &n);
		push_back(&current, n);
	}

	print(&current);

	for(int i=1; i<=3; ++i) {
		scanf("%d", &y);
		printf("%d", find(&current, y));
	}
	printf("\n");

	scanf("%d", &n);
	push_back(&current, n);

	print_invers(&current);

	scanf("%d", &n);
	push_front(&current, n);

	print(&current);

	scanf("%d %d", &n, &y);
	insertAfter(&current, n-1, y);

	print_invers(&current);

	scanf("%d %d", &n, &y);
	insertBefore(&current, n-1, y);

	print(&current);

	scanf("%d", &n);
	removeFirst(&current, n);

	print_invers(&current);

	scanf("%d", &n);
	removeLast(&current, n);

	print(&current);

	clear(&current);

	return 0;
}
