#include <string.h>
#include <stdlib.h>
#include <stdio.h>

int	main(int ac, char **av)
{
	const char buf[] = "f %d %d %d %d";
	const char buf1[] = "f %d/%d/%d %d/%d/%d %d/%d/%d %d/%d/%d";
	
	int a, b, c, d;

	printf("Len: %zu\n", strlen(buf1));
	if (ac != 2)
		return (1);
	printf("Result : %d\n", sscanf(av[1], buf, &a, &b, &c, &d));
	return (0);
}
