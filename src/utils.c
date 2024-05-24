/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgoron <bgoron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 19:58:05 by bgoron            #+#    #+#             */
/*   Updated: 2024/04/15 20:01:24 by bgoron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ph_atoi(char *nbr)
{
	int	i;
	int	nb;

	i = 0;
	nb = 0;
	while (nbr[i])
		nb = nb * 10 + nbr[i++] - '0';
	return (nb);
}

void	*ph_calloc(size_t nb, size_t size)
{
	void	*ptr;

	if (!nb || !size)
		return (malloc(0));
	if (nb * size / size != nb)
		return (NULL);
	ptr = malloc(nb * size);
	if (!ptr)
		return (NULL);
	memset(ptr, 0, nb * size);
	return (ptr);
}

void	ph_print(t_philo *philo, char *msg)
{
	LOCK(philo->print);
	printf(msg, ph_time(), philo->id + 1);
	UNLOCK(philo->print);
}

void	ph_wait(int time)
{
	int	start;

	start = ph_time();
	while (ph_time() - start < time)
		usleep(100);
}

int	ph_time(void)
{
	struct timeval	tv;
	static int		start_time;
	int				time;

	gettimeofday(&tv, NULL);
	time = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	if (!start_time)
		start_time = time;
	return (time - start_time);
}
