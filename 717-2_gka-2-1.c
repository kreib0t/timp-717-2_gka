#include <stdio.h>

int main()
{
	int n, x, y;

	scanf("%d", &n);
	scanf("%d", &x);
	for(int i=1; i<n; i++) {
		scanf("%d", &y);
		x<=y ? printf("1") : printf("0");
		x=y;
	}

	return 0;
}
