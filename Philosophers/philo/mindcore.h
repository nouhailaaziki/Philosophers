/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mindcore.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noaziki <noaziki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 16:13:04 by noaziki           #+#    #+#             */
/*   Updated: 2025/07/15 16:50:24 by noaziki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINDCORE_H
# define MINDCORE_H

# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>
# include <string.h>
# include <unistd.h>

typedef struct s_axioms
{
	long	philo;
	long	t_die;
	long	t_eat;
	long	t_sleep;
	long	eats;
}	t_axioms;

typedef struct s_philo
{
	int				id;
	long			last_meal;
	int				times_eaten;
	pthread_t		thread;
	struct s_sim	*sim;
	pthread_mutex_t	meal_lock;
}	t_philo;

typedef struct s_sim
{
	t_axioms		axioms;
	t_philo			*philos;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_lock;
	pthread_mutex_t	state_lock;
	int				is_running;
	long			start_time;
}	t_sim;

long	get_time(void);
void	cleanup(t_sim *sim);
void	stop_sim(t_sim *sim);
long	ft_atol(const char *str);
void	run_simulation(t_sim *sim);
int		is_sim_running(t_sim *sim);
int		init_simulation(t_sim *sim);
void	ft_putendl_fd(char *s, int fd);
void	*philosopher_routine(void *arg);
void	precise_usleep(long milliseconds, t_sim *sim);
void	print_status(t_philo *philo, const char *status);

#endif