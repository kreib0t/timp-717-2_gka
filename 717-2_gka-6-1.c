#include <stdio.h>
#include <stdlib.h>

int sorting_function(int *arr, int arr_len)
{
	int tmp, gap = arr_len;
	int oper = 0;
	while(gap >= 1) {
		for(int i=0; i<arr_len-gap; i++) {
			++oper; // сравнения
			if (arr[i] > arr[i+gap]) {
				tmp = arr[i];
				arr[i] = arr[i+gap];
				arr[i+gap] = tmp;
				++oper; // перестановок
			}
		}
		gap/=1.24733;
	}
	return oper;
}

int main()
{
	int n;
	int *mas;

	mas = (int*)calloc(n, sizeof(int));

	scanf("%d", &n);

	for(int i=0; i<n; i++)
		scanf("%d", &mas[i]);

	sorting_function(mas, n);

	for(int i=0; i<n-1; i++)
		printf("%d ", mas[i]);
	printf("%d\n", mas[n-1]);

	return 0;
}
