#include <stdio.h>

void quicksort(int *A, int len)
{
	if (len < 2) return;

	int N = A[len / 2];
	int i, j, tmp;

	for (i = 0, j = len - 1; ; i++, j--) {
		while (A[i] < N) i++;
		while (A[j] > N) j--;

		if (i >= j) break;

		tmp = A[i];
		A[i] = A[j];
		A[j] = tmp;
	}

	quicksort(A, i);
	quicksort(A + i, len - i);
}

int main()
{
	int n, a[25];

	scanf("%d", &n);

	for(int i = 0; i < n; i++)
		scanf("%d", &a[i]);

	quicksort(a, n);

	for(int i = 0; i < n; i++) {
		printf("%d", a[i]);
		if(a[i+1])
			printf(" ");
	}
	printf("\n");
 
	return 0;
}