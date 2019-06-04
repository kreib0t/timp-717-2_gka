#include <stdio.h>
#include <stdlib.h>

//////////////////////////////////// структуры

//////////////////////////////////// структуры для дерева

// узел дерева
typedef struct node_tree {
	int value; // хранимое число
	struct node_tree *left; // ссылка на левого потомка (меньше)
	struct node_tree *right; // сылка на правого потомка (больше)
	struct node_tree *parent;  // ссылка на предка
} node_tree;

// дерево
typedef struct tree {
	struct node_tree *root; //ссылка на корень
	int tnumber; // количество элементов в дереве
} tree;

//////////////////////////////////// структуры для очереди

// узел очереди
typedef struct node_queue {
	struct node_tree* branch;  // ссылается на узел дерева
	struct node_queue* next; // ссылается на следующий элемент очереди
} node_queue;

// Очередь
typedef struct queue {
	int qnumber; // кол-во узлов в очереди !!!!! может пригодится
	struct node_queue* head; // начало очереди
	struct node_queue* tail; // конец очереди
} queue;

//////////////////////////////////// функции

//////////////////////////////////// функции для очереди

// инициализация очереди
void init_queue(queue *q)
{
	q->qnumber = 0;
	q->head = NULL;
	q->tail = NULL;
}

// проверка очереди на пустоту
// 1 если пустое; 0 если не пустое
int isEmpty_queue(queue *q)
{
	return (q->tail == NULL);
}

// отоброзить элементы очереди
void print_queue(queue *q)
{
	node_queue* tmp = q->head;

	// условие изменить тк NULL может означать что одного потомка нет
	while(tmp != NULL) {
		if(tmp->branch == NULL)
			printf("_");
		else
			printf("%d", tmp->branch->value);

		// если нужны пробелы
		if(tmp->next != NULL)
		 	printf(" ");

		//printf("%p\n", tmp->branch);
		// printf("! %p\n", tmp);
		// printf("!! %p\n", tmp->next);
		tmp = tmp->next;
	}
	printf("\n");
}

// вставить элемент в конец
void push_in_queue(queue *q, node_tree *value)
{
	// создаем узел очереди
	node_queue *tmp;
	tmp = malloc(sizeof(node_queue));

	// закидываем туда узел дерева
	tmp->branch = value;
	tmp->next = NULL;

	if(value != NULL)
		q->qnumber++;

	// если не пуста
	if(!isEmpty_queue(q)) {
		q->tail->next = tmp;
		q->tail = tmp;
	}
	// если пуста
	else {
		q->head = q->tail = tmp;
	}
	//q->qnumber++;
}

// вытащить элемент с начала 
node_tree* pop_out_queue(queue *q)
{
	node_queue *tmp = q->head;
	node_tree* n = q->head->branch;

	q->head = q->head->next;

	// если был последний элемент в очереди
	// для проверки на пустоту
	if(q->head == NULL)
		q->tail = NULL;

	// q->qnumber--;
	free(tmp);

	return(n);
}

// проверка что в очереди только null
// возвращает 1 если все null и 0 если хотя бы 1 элем не null
int control(queue *q)
{
	node_queue* tmp = q->head;

	while(tmp != NULL) {
		if(tmp->branch != NULL)
			return 0;

		tmp = tmp->next;
	}
	return 1;
}

//////////////////////////////////// функции для дерева

// инициализация пустого дерева
void init_tree(tree* t)
{
	t->root = NULL;
	t->tnumber = 0;
}

//удалить все элементы из дерева
void clear_tree(tree* t, queue* q)
{
	node_tree* tmp = t->root;
	node_tree* del;

	// закидываем в очередь корень
	push_in_queue(q, tmp);

	// очистка пока очередь не станет пустой
	while(!isEmpty_queue(q)) {
		del = tmp;
		// вытащить потомка
		tmp = pop_out_queue(q);

		//free(del);

		if(tmp->left != NULL)
			push_in_queue(q, tmp->left);
		if(tmp->right != NULL)
			push_in_queue(q, tmp->right);
	}
	t->root = NULL;
}

/* поиск элемента по значению. вернуть 0 если элемент найден
и ссылку на найденный элемент в переменную n если n !=
NULL. в случае если элемент не найден вернуть 1*/
int find_tree(tree* t, int value, node_tree* n, queue* q)
{
	node_tree* tmp = t->root;

	while(tmp != NULL) {
		if(tmp->value == value)
				break;

		if(value > tmp->value) {
			// если нет нужного элемента
			if(tmp->right == NULL) {
				printf("-\n");
				return 0;
			}
			tmp = tmp->right;
		}
		else {
			// если нет нужного элемента
			if(tmp->left == NULL) {
				printf("-\n");
				return 0;
			}
			tmp = tmp->left;
		}
	}

	printf("%d ", tmp->parent->value);
	if(tmp->left == NULL)
		printf("_ ");
	else
		printf("%d ", tmp->left->value);
	if(tmp->right == NULL)
		printf("_");
	else
		printf("%d", tmp->right->value);
	printf("\n");
}

/* вставка значения в дерево. вернуть 0 если вставка выпол
нена успешна,
1 если элемент уже существует
2 если не удалось выделить память для нового элемента
*/
int insert_tree(tree* t, int value)
{
	node_tree* tmp = malloc(sizeof(node_tree));

	// не удалось выделить память для нового элемента
	if(tmp == NULL) {
		return 2;
	}

	tmp->value = value;
	tmp->left = NULL;
	tmp->right = NULL;

	// если корень пуст
	if(t->root == NULL) {
		t->root = tmp;
	}
	// если корень не пуст
	else {

		node_tree* current = t->root;
		node_tree* prev = NULL;
		int check;

		// вставка нового узла
		while(current != NULL){
			prev = current;
			// если значение узла меньше текущего
			if(value < current->value) {
				current = current->left;
				check = 1;
			}
			// если узел с таким значением уже был
			else if(value == current->value) {
				return 1;
			}
			// если значение узла больше текущего
			else {
				current = current->right;
				check = 0;
			}
		}
		// линковка с предком
		if(check) {
			prev->left = tmp;
			tmp->parent = prev;
		}
		else {
			prev->right = tmp;
			tmp->parent = prev;
		}
	}

	// кол-во элементов в дереве
	t->tnumber++;

	return 0;
}

/* удалить элемент из дерева. вернуть 0 если элемент был у
дален и 1 если нет элемента с указанным значением */
// работает только для корня дерева и то если у правого потомка нет левого
// не представляю как это сделать универсальным для любого узла (ну вообще-то представляю)
// но это сложно, а может нет? хз, может потом допилю
// не универсальное !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
int delete_tree(tree* t, int value, queue* q)
{
	node_tree* tmp = t->root;
	node_tree* hell;
	node_tree* qwe;

	// поиск элемента на удаление
	while(tmp != NULL) {
		if(tmp->value == value)
			break;

		if(value > tmp->value) {
			// если нет нужного элемента
			if(tmp->right == NULL) {
				return 1;
			}
			tmp = tmp->right;
		}
		else  {
			// если нет нужного элемента
			if(tmp->left == NULL) {
				return 1;
			}
			tmp = tmp->left;
		}
	}

	// если это корень
	if(tmp->value == t->root->value) {
		hell = tmp;
		// ищем самый правый элемент
		if(tmp->right != NULL) {
			hell = tmp->right;

			while(hell->left != NULL) {
				hell = hell->left;
			}
		}

		// Линковку
		hell->parent = NULL;
		hell->left = tmp->left;
		qwe = tmp;
		qwe = qwe->left;
		qwe->parent = hell;
		
		t->root = hell;
		free(tmp);
		t->tnumber--;
		return 1;
	}
	// hell = tmp; // элемент на удаление

	// while(tmp->right != NULL)
	// 	tmp = tmp->right;
	// while(tmp->left != NULL)
	// 	tmp = tmp->left;

	// printf("%d\n", tmp->value);

	// qwe = tmp->parent;
	// qwe->left = NULL;

	// tmp->parent = hell->parent;
	// tmp->left = hell->left;
	// tmp->right = hell->right;
	return 0;
}

/* удалить минимальный элемент из поддерева, корнем которо
го является n. вернуть значение удаленного элемента */
// не используется допилю потом
//int removeMin_tree(node_tree* n, queue* q)
int removeMin_tree(tree* t, int value, queue* q)
{
	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
}

/* выполнить правое вращение поддерева, корнем которого яв
ляется n. вернуть 0 при успещшно выполнение операции и 1 в
случае если вращение невозможно */
// не универсальное !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! (ДОБАВЬ ЛИНКОВКУ С ПРЕДКОМ!!!!!!)
int rotateRight_tree(tree* t)
{
	node_tree* tmp = t->root;
	node_tree* qwe;

	// ищем самый левый
	while(tmp->left != NULL) {
		tmp = tmp->left;
	}
	
	t->root = tmp;
	while(qwe->parent != NULL) {
		qwe = tmp->parent;
		// printf("%d\n", qwe->value);
		qwe->left = NULL;
		tmp->right = qwe;
		tmp = tmp->right;
	}

	// налаживаем линковку
	tmp = t->root;
	tmp->parent = NULL;
	while(tmp->right != NULL) {
		qwe = tmp;
		tmp = tmp->right;
		tmp->parent = qwe;
	}
}

/* выполнить левое вращение поддерева, корнем которого явл
яется n. вернуть 0 при успещшно выполнение операции и 1 в
случае если вращение невозможно */
// не универсальное !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
int rotateLeft_tree(tree* t)
{
	node_tree* tmp = t->root;
	node_tree* qwe;

	// ищем самый правый
	while(tmp->right != NULL) {
		tmp = tmp->right;
	}
	
	t->root = tmp;

	while(qwe->parent != NULL) {
		qwe = tmp->parent;
		qwe->right = NULL;
		tmp->left = qwe;
		tmp = tmp->left;
	}

	// налаживаем линковку
	tmp = t->root;
	tmp->parent = NULL;
	while(tmp->left != NULL) {
		qwe = tmp;
		tmp = tmp->left;
		tmp->parent = qwe;
	}
}

/* вывести все значения из поддерева корнем которого являе
тся n по уровнем, начиная с корня. каждый уровень выводитс
я на своей строке. элементы в строке разделяются пробелом.
если на указанном месте нет элемента, заменить его значен
ием '_'. Если дерево пусто вывести '-'*/
// void print_tree(node_tree* n)
void print_tree(tree* t, int value, queue* q)
{
	node_tree* tmp = t->root;
	queue* tmp_q;
	tmp_q = malloc(sizeof(queue));

	// поиск нужного элемента
	while(tmp != NULL) {
		if(value > tmp->value) {
			if(tmp->value == value)
				break;

			// если нет нужного элемента
			if(tmp->right == NULL) {
				printf("-\n");
				return;
			}
			tmp = tmp->right;
		}
		else {
			// если нет нужного элемента
			if(tmp->left == NULL) {
				printf("-\n");
				return;
			}
			tmp = tmp->left;
		}
	}

	// закидываем узел
	push_in_queue(q, tmp);
	// Если один элемент
	print_queue(q);

	for(;;) {
		// очистка старой очереди
		// и запись ее элементов во временную
		while(!isEmpty_queue(q)) {
			tmp = pop_out_queue(q);
			push_in_queue(tmp_q, tmp);
		}

		// очистка временной очереди
		// и запись ее элементов в новую
		while(!isEmpty_queue(tmp_q)) {
			tmp = pop_out_queue(tmp_q);
			if(tmp == NULL) {
				push_in_queue(q, NULL);
				push_in_queue(q, NULL);
			}
			else {
				push_in_queue(q, tmp->left);
				push_in_queue(q, tmp->right);
			}
		}

		// проверка если все элементы очереди NULL
		// значит дерево закончилось
		if(control(q)) {
			while(!isEmpty_queue(q))
				pop_out_queue(q);

			break;
		}

		print_queue(q);
	}
}

// вывести все значения дерева t, аналогично функции print
void printTree(tree* t, queue* q)
{
	node_tree* tmp = t->root;
	queue* tmp_q;
	tmp_q = malloc(sizeof(queue));

	if(tmp == NULL) {
		printf("-\n");
		return;
	}

	// закидываем корень
	push_in_queue(q, tmp);
	// Если один элемент
	print_queue(q);

	for(;;) {
		// очистка старой очереди
		// и запись ее элементов во временную
		while(!isEmpty_queue(q)) {
			tmp = pop_out_queue(q);
			push_in_queue(tmp_q, tmp);
		}

		// очистка временной очереди
		// и запись ее элементов в новую
		while(!isEmpty_queue(tmp_q)) {
			tmp = pop_out_queue(tmp_q);
			if(tmp == NULL) {
				push_in_queue(q, NULL);
				push_in_queue(q, NULL);
			}
			else {
				push_in_queue(q, tmp->left);
				push_in_queue(q, tmp->right);
			}
		}

		// проверка если все элементы очереди NULL
		// значит дерево закончилось
		if(control(q)) {
			while(!isEmpty_queue(q))
				pop_out_queue(q);

			break;
		}

		print_queue(q);
	}
}

//////////////////////////////////// главная функция

int main()
{
	int n;
	queue *q;
	tree *Tree;

	Tree = malloc(sizeof(tree));
	init_tree(Tree);
	q = malloc(sizeof(queue));
	init_queue(q);

	for (int i = 0; i < 4; ++i) {
		scanf("%d", &n);
		insert_tree(Tree, n);
	}

	printTree(Tree, q);

	for (int i = 0; i < 3; ++i) {
		scanf("%d", &n);
		insert_tree(Tree, n);
	}

	printTree(Tree, q);

	scanf("%d", &n);
	find_tree(Tree, n, NULL, q);

	scanf("%d", &n);
	find_tree(Tree, n, NULL, q);

	scanf("%d", &n);
	delete_tree(Tree, n, q);
	printTree(Tree, q);

	rotateLeft_tree(Tree);
	printTree(Tree, q);

	rotateRight_tree(Tree);
	printTree(Tree, q);

	printf("%d\n", Tree->tnumber);
	clear_tree(Tree, q);

	printTree(Tree, q);

	return 0;
}
