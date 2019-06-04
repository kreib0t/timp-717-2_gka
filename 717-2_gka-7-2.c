#include <stdio.h>

void a(int arr[], int n, int i)
{
	int tmp;

	int largest = i;
	int l = 2*i + 1;
	int r = 2*i + 2;

	if (l < n && arr[l] > arr[largest])
		largest = l;

	if (r < n && arr[r] > arr[largest])
		largest = r;

	if (largest != i) {
		tmp = arr[i];
		arr[i] = arr[largest];
		arr[largest] = tmp;
		a(arr, n, largest);
	}
}

void heapSort(int arr[], int n)
{
	int tmp;

	for (int i = n / 2 - 1; i >= 0; i--)
		a(arr, n, i);

	for (int i=n-1; i>=0; i--) {
		tmp = arr[0];
		arr[0] = arr[i];
		arr[i] = tmp;
		a(arr, i, 0);
	}
}

int main()
{
	int n, a[25];

	scanf("%d", &n);

	for(int i = 0; i < n; i++)
		scanf("%d", &a[i]);

	heapSort(a, n); 

	for(int i = 0; i < n; i++) {
		printf("%d", a[i]);
		if(a[i+1])
			printf(" ");
	}
	printf("\n");
 
	return 0;
}
