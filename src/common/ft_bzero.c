#include <string.h>

void	ft_bzero(void *mem, unsigned int size)
{
	memset(mem, 0, size);
}