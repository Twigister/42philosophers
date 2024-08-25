#include <philo.h>

void	*routine(t_philo *self)
{
	int	eat_count;

	eat_count = 0;
	if (!action(self, "is thinking"))
		return (NULL);
	if (self->num == 1)
		msleep(1);
	while (1)
	{
		msleep(1);
		if (self->opt->p_count % 2 && self->num % 2)
			msleep(1);
		if (!eat(self, &eat_count))
			break ;
		if (!action(self, "is sleeping"))
			break ;
		msleep(self->opt->t_sleep);
		if (!action(self, "is thinking"))
			break ;
		msleep(self->opt->t_eat - self->opt->t_sleep);
	}
	return (NULL);
}
