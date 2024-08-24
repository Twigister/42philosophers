#include <philo.h>
#include <unistd.h>

static int	rl_lock(t_philo *self)
{
	pthread_mutex_lock(&self->rfork);
	if (!action(self, "has taken a fork"))
	{
		pthread_mutex_unlock(&self->rfork);
		return (0);
	}
	if (self->opt->p_count == 1)
	{
		pthread_mutex_unlock(&self->rfork);
		return (0);
	}
	pthread_mutex_lock(self->lfork);
	usleep(50);
	if (!action(self, "has taken a fork"))
	{
		pthread_mutex_unlock(&self->rfork);
		pthread_mutex_unlock(self->lfork);
		return (0);
	}
	usleep(50);
	return (1);
}

static int	lr_lock(t_philo *self)
{
	pthread_mutex_lock(self->lfork);
	if (!action(self, "has taken a fork"))
	{
		pthread_mutex_unlock(self->lfork);
		return (0);
	}
	usleep(50);
	pthread_mutex_lock(&self->rfork);
	if (!action(self, "has taken a fork"))
	{
		pthread_mutex_unlock(&self->rfork);
		pthread_mutex_unlock(self->lfork);
		return (0);
	}
	usleep(50);
	return (1);
}

static int	eating_success(t_philo *self, int *eat_count)
{
	int	tmp;

	qmutex_set(&self->m_last_ate, &self->last_ate,
		get_timestamp(self->opt->start));
	*eat_count += 1;
	if (*eat_count == self->opt->it)
	{
		tmp = qmutex_get(&self->opt->count_m, &self->opt->rem_count);
		qmutex_set(&self->opt->count_m, &self->opt->rem_count, tmp + 1);
	}
	msleep(self->opt->t_eat);
	return (1);
}

int	eat(t_philo *self, int *eat_count)
{
	int	tmp;

	if (self->num % 2 && !rl_lock(self))
		return (0);
	else if (self->num % 2 == 0 && !lr_lock(self))
		return (0);
	if (action(self, "is eating"))
		tmp = eating_success(self, eat_count);
	else
		tmp = 0;
	pthread_mutex_unlock(self->lfork);
	pthread_mutex_unlock(&self->rfork);
	return (tmp);
}
