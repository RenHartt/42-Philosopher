/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgoron <bgoron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 19:56:12 by bgoron            #+#    #+#             */
/*   Updated: 2024/04/15 21:54:20 by bgoron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ph_wait_forks(t_philo *philo)
{
	while (42)
	{
		LOCK(philo->left_fork);
		if (*philo->left_state != (philo->id % 2) || ph_death(philo))
		{
			UNLOCK(philo->left_fork);
			return (ph_death(philo));
		}
		UNLOCK(philo->left_fork);
		usleep(100);
	}
	return (0);
}

int	ph_fork(t_philo *philo)
{
	ph_print(philo, BLUE"%-8dPhilo[%d] has taken a fork.\n"RESET);
	ph_print(philo, BLUE"%-8dPhilo[%d] has taken a fork.\n"RESET);
	LOCK(&philo->var);
	philo->last_meal = ph_time();
	UNLOCK(&philo->var);
	return (ph_death(philo));
}

int	ph_eat(t_philo *philo)
{
	ph_print(philo, GREEN"%-8dPhilo[%d] is eating.\n"RESET);
	ph_wait(philo->args.time_to_eat);
	if (!(philo->id & 1))
		LOCK(philo->left_fork);
	LOCK(philo->right_fork);
	if ((philo->id & 1))
		LOCK(philo->left_fork);
	*philo->left_state ^= 1;
	*philo->right_state ^= 1;
	if ((philo->id & 1))
		UNLOCK(philo->left_fork);
	UNLOCK(philo->right_fork);
	if (!((philo->id & 1)))
		UNLOCK(philo->left_fork);
	LOCK(&philo->var);
	philo->args.meal_count++;
	UNLOCK(&philo->var);
	return (ph_death(philo));
}

int	ph_sleep(t_philo *philo)
{
	ph_print(philo, YELLOW"%-8dPhilo[%d] is sleeping.\n"RESET);
	ph_wait(philo->args.time_to_sleep);
	return (ph_death(philo));
}

void	*ph_routine(void *p)
{
	t_philo	*philo;

	philo = (t_philo *)p;
	while (42)
	{
		if (ph_wait_forks(philo))
			break ;
		else if (ph_fork(philo))
			break ;
		else if (ph_eat(philo))
			break ;
		else if (ph_sleep(philo))
			break ;
		ph_print(philo, MAGENTA"%-8dPhilo[%d] is thinking.\n"RESET);
	}
	return (NULL);
}
