#include <unistd.h>
#include <sys/time.h>

static long	mstime(void)
{
	struct timeval	ini;

	gettimeofday(&ini, 0);
	return (ini.tv_sec * 1000 + ini.tv_usec / 1000);
}

void	msleep(int msec)
{
	long	goal;

	goal = mstime() + msec;
	while (goal > mstime())
	{
		usleep(50);
	}
}
