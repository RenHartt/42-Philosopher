/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgoron <bgoron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 19:54:46 by bgoron            #+#    #+#             */
/*   Updated: 2024/04/16 13:13:02 by bgoron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ph_death(t_philo *philo)
{
	LOCK(philo->death);
	if (*philo->int_death)
	{
		UNLOCK(philo->death);
		return (1);
	}
	UNLOCK(philo->death);
	return (0);
}

int	ph_dead(t_philo *tmp, t_info t)
{
	LOCK(&tmp->var);
	if (t.time_to_die < ph_time() - tmp->last_meal)
	{
		UNLOCK(&tmp->var);
		LOCK(tmp->death);
		*tmp->int_death = 1;
		UNLOCK(tmp->death);
		ph_print(tmp, RED"%-8dPhilo[%d] died.\n"RESET);
		return (1);
	}
	UNLOCK(&tmp->var);
	return (0);
}

void	ph_monitoring(t_info t, t_data *d)
{
	t_philo	*tmp;
	int		full;

	while (42)
	{
		tmp = d->philos;
		full = 0;
		while (tmp - d->philos < t.philo_count && !ph_dead(tmp, t))
		{
			LOCK(&tmp->var);
			full += (tmp->args.meal_count >= t.max_meal && t.max_meal > 0);
			UNLOCK(&tmp++->var);
		}
		if (full == t.philo_count)
		{
			LOCK(d->philos->death);
			*d->philos->int_death = 1;
			UNLOCK(d->philos->death);
			break ;
		}
		if (ph_death(d->philos))
			break ;
		usleep(100);
	}
}

void	ph_loop(t_info t, t_data *d)
{
	int		i;
	int		int_death;
	MUTEX	death;
	MUTEX	print;

	i = 0;
	int_death = 0;
	memset(&death, 0, sizeof(MUTEX));
	memset(&print, 0, sizeof(MUTEX));
	while (i < t.philo_count)
	{
		d->philos[i].int_death = &int_death;
		d->philos[i].death = &death;
		d->philos[i].print = &print;
		ph_setup(d, t, i++);
	}
	ph_monitoring(t, d);
	while (i)
		pthread_join(d->threads[--i], NULL);
	ph_exit(*d, EXIT_SUCCESS);
}

void	ph_exit(t_data data, int exit_code)
{
	free(data.states);
	free(data.philos);
	free(data.forks);
	free(data.threads);
	exit(exit_code);
}
