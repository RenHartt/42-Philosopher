/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgoron <bgoron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 22:42:00 by baptistegor       #+#    #+#             */
/*   Updated: 2024/04/15 22:12:47 by bgoron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <string.h>

# define RED		"\033[1;31m"
# define GREEN		"\033[1;32m"
# define YELLOW		"\033[1;33m"
# define BLUE		"\033[1;34m"
# define MAGENTA	"\033[1;35m"
# define RED_BLINK	"\033[1;5;31m"
# define RESET		"\033[0m"

# define MUTEX		pthread_mutex_t
# define LOCK		pthread_mutex_lock
# define UNLOCK		pthread_mutex_unlock

typedef struct s_info
{
	int	philo_count;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	max_meal;
	int	meal_count;
}			t_info;

typedef struct s_philo
{
	int		id;
	t_info	args;
	MUTEX	*left_fork;
	MUTEX	*right_fork;
	int		*left_state;
	int		*right_state;
	int		*int_death;
	int		last_meal;
	MUTEX	*death;
	MUTEX	*print;
	MUTEX	var;
}			t_philo;

typedef struct s_data
{
	pthread_t	*threads;
	t_philo		*philos;
	MUTEX		*forks;
	int			*states;
}			t_data;

typedef enum s_msg
{
	DEAD,
	EAT,
	SLEEP,
	THINK,
	FORK
}			t_msg;

/* ************************************************************************** */
/*                                    LOOP                                    */
/* ************************************************************************** */

int		ph_death(t_philo *philo);
int		ph_dead(t_philo *tmp, t_info t);
void	ph_monitoring(t_info t, t_data *d);
void	ph_loop(t_info t, t_data *d);
void	ph_exit(t_data data, int exit_code);

/* ************************************************************************** */
/*                                  ROUTINE                                   */
/* ************************************************************************** */

int		ph_wait_forks(t_philo *philo);
int		ph_fork(t_philo *philo);
int		ph_eat(t_philo *philo);
int		ph_sleep(t_philo *philo);
void	*ph_routine(void *p);

/* ************************************************************************** */
/*                                   SETUP                                    */
/* ************************************************************************** */

void	ph_args(t_info *t, int ac, char **av);
void	ph_parsing(t_info t);
void	ph_init(t_info t, t_data *data);
void	ph_setup(t_data *d, t_info t, int i);

/* ************************************************************************** */
/*                                   UTILS                                    */
/* ************************************************************************** */

int		ph_atoi(char *nbr);
void	*ph_calloc(size_t nb, size_t size);
void	ph_print(t_philo *philo, char *msg);
void	ph_wait(int time);
int		ph_time(void);

#endif