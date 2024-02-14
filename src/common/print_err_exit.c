#include <unistd.h>
#include <stdlib.h>

int	ft_strlen(const char *s);

void	print_err_exit(const char *msg)
{
	write(2, "Error", 6);
	if (msg)
	{
		write(2, ": ", 2);
		write(2, msg, ft_strlen(msg));
	}
	write(1, "\n", 1);
	exit(1);
}
