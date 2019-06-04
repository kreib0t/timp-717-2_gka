#include <stdio.h>

int main()
{
	int  n, x, s=0;

	scanf("%d", &n);
	for(int i=1; i<=n; i++) {
		scanf("%d", &x);
		s+=x-i;
	}
	printf("%d\n", s);

	return 0;
}
