#include <unistd.h>

void	msleep(int msec)
{
	usleep(msec * 1000);
}