/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mindcore_bonus.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noaziki <noaziki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 10:59:25 by noaziki           #+#    #+#             */
/*   Updated: 2025/08/04 09:41:51 by noaziki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINDCORE_BONUS_H
# define MINDCORE_BONUS_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <pthread.h>
# include <semaphore.h>
# include <signal.h>

typedef struct s_params
{
	long	num_philos;
	long	time_to_die;
	long	time_to_eat;
	long	time_to_sleep;
	long	num_eats;
	long	start_time;
	sem_t	*forks_sem;
	sem_t	*write_sem;
	sem_t	*stop_sem;
}	t_params;

typedef struct s_philo
{
	int			id;
	pid_t		pid;
	long		last_meal_time;
	int			meals_eaten;
	char		eat_sem_name[255];
	sem_t		*eat_sem;
	t_params	*params;
}	t_philo;

long	get_time(void);
void	cleanup_semaphores(void);
long	ft_atol(const char *str);
void	ft_putendl_fd(char *s, int fd);
void	precise_usleep(long duration_ms);
void	philosopher_routine(t_philo *philo);
void	stop_simulation(t_philo *philos, t_params *params);
void	start_simulation(t_philo *philos, t_params *params);
void	print_status(t_philo *philo, char *status, int is_dead);

#endif