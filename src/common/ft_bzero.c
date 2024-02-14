void	ft_bzero(void *mem, unsigned int size)
{
	char			*tmp;
	unsigned int	i;

	tmp = (char *)mem;
	i = 0;
	while (i < size)
	{
		tmp[i] = 0;
		++i;
	}
}