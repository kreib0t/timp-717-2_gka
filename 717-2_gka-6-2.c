#include <stdio.h>

void sort(int a[], int n)
{
	int gap, i, j, temp;

	for(gap=n/2; gap>0; gap/=2) {
		for(i=gap; i<n; i+=1) {
			temp = a[i];

			for(j=i; j>=gap && a[j-gap]>temp; j-=gap)
				a[j] = a[j-gap];

			a[j] = temp;
		}
	}
}

int main()
{
	int a[20],i,n;
	
	scanf("%d",&n);
		
	for(i=0; i<n; ++i)
		scanf("%d", &a[i]);
 
	sort(a,n);

	for(i=0; i<n; ++i) {
		if(i==n-1)
			printf("%d\n", a[i]);
		else
			printf("%d ", a[i]);
	}

	return 0;
}