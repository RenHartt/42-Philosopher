/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgoron <bgoron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 19:57:19 by bgoron            #+#    #+#             */
/*   Updated: 2024/04/16 10:51:49 by bgoron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ph_args(t_info *t, int ac, char **av)
{
	if (ac == 5 || ac == 6)
	{
		t->philo_count = ph_atoi(av[1]);
		t->time_to_die = ph_atoi(av[2]);
		t->time_to_eat = ph_atoi(av[3]);
		t->time_to_sleep = ph_atoi(av[4]);
		if (ac == 6)
			t->max_meal = ph_atoi(av[5]);
		else
			t->max_meal = -1;
		t->meal_count = 0;
	}
	else if (ac < 5)
	{
		printf(RED_BLINK"Error: Not enough arguments.\n"RESET);
		exit(EXIT_FAILURE);
	}
	else
	{
		printf(RED_BLINK"Error: Too many arguments.\n"RESET);
		exit(EXIT_FAILURE);
	}
}

void	ph_parsing(t_info t)
{
	if (t.time_to_die < 60 || t.time_to_eat < 60 || t.time_to_sleep < 60)
	{
		printf(RED_BLINK"We told you not to try !\n"RESET);
		exit(EXIT_FAILURE);
	}
	else if (t.philo_count < 1 || (t.max_meal < 1 && t.max_meal != -1))
	{
		printf(RED_BLINK"Error: Invalid arguments.\n"RESET);
		exit(EXIT_FAILURE);
	}
}

void	ph_init(t_info t, t_data *data)
{
	ph_time();
	memset(data, 0, sizeof(t_data));
	data->threads = ph_calloc(t.philo_count, sizeof(pthread_t));
	if (!data->threads)
		ph_exit(*data, EXIT_FAILURE);
	data->philos = ph_calloc(t.philo_count, sizeof(t_philo));
	if (!data->philos)
		ph_exit(*data, EXIT_FAILURE);
	data->forks = ph_calloc(t.philo_count, sizeof(MUTEX));
	if (!data->forks)
		ph_exit(*data, EXIT_FAILURE);
	data->states = ph_calloc(t.philo_count, sizeof(int));
	if (!data->states)
		ph_exit(*data, EXIT_FAILURE);
}

void	ph_setup(t_data *d, t_info t, int i)
{
	d->philos[i].id = i;
	d->philos[i].args = t;
	d->philos[i].left_fork = &d->forks[i];
	d->philos[i].right_fork = &d->forks[(i + 1) % t.philo_count];
	d->philos[i].left_state = &d->states[i];
	d->philos[i].right_state = &d->states[(i + 1) % t.philo_count];
	pthread_create(&d->threads[i], NULL, &ph_routine, (void *)&d->philos[i]);
}
