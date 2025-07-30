/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noaziki <noaziki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 11:05:26 by noaziki           #+#    #+#             */
/*   Updated: 2025/07/13 11:40:32 by noaziki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mindcore_bonus.h"

void	*death_checker(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		sem_wait(philo->eat_sem);
		if (get_time() - philo->last_meal_time > philo->params->time_to_die)
		{
			print_status(philo, "died", 1);
			sem_post(philo->params->stop_sem);
			exit(1);
		}
		sem_post(philo->eat_sem);
		usleep(1000);
	}
	return (NULL);
}

void	philo_eat(t_philo *philo)
{
	sem_wait(philo->params->forks_sem);
	print_status(philo, "has taken a fork", 0);
	sem_wait(philo->params->forks_sem);
	print_status(philo, "has taken a fork", 0);
	sem_wait(philo->eat_sem);
	philo->last_meal_time = get_time();
	print_status(philo, "is eating", 0);
	philo->meals_eaten++;
	sem_post(philo->eat_sem);
	precise_usleep(philo->params->time_to_eat);
	sem_post(philo->params->forks_sem);
	sem_post(philo->params->forks_sem);
}

void	philosopher_lifecycle(t_philo *philo)
{
	if (philo->id % 2 == 0)
		usleep (1000);
	while (1)
	{
		philo_eat(philo);
		if (philo->params->num_eats != -1
			&& philo->meals_eaten >= philo->params->num_eats)
			break ;
		print_status(philo, "is sleeping", 0);
		precise_usleep(philo->params->time_to_sleep);
		print_status(philo, "is thinking", 0);
	}
}

void	philosopher_routine(t_philo *philo)
{
	pthread_t	monitor;

	sem_unlink(philo->eat_sem_name);
	philo->eat_sem = sem_open(philo->eat_sem_name, O_CREAT, 0644, 1);
	if (philo->eat_sem == SEM_FAILED)
		exit(1);
	if (pthread_create(&monitor, NULL, &death_checker, philo) != 0)
	{
		sem_close(philo->eat_sem);
		sem_unlink(philo->eat_sem_name);
		exit(1);
	}
	pthread_detach(monitor);
	philosopher_lifecycle(philo);
	sem_close(philo->eat_sem);
	sem_unlink(philo->eat_sem_name);
	exit(0);
}
