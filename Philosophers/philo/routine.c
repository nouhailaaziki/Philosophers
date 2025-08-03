/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noaziki <noaziki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 00:57:53 by noaziki           #+#    #+#             */
/*   Updated: 2025/08/03 10:28:52 by noaziki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mindcore.h"

void	take_forks(t_philo *philo)
{
	int	left_fork_idx;
	int	right_fork_idx;

	left_fork_idx = philo->id - 1;
	right_fork_idx = philo->id % philo->sim->axioms.philo;
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(&philo->sim->forks[left_fork_idx]);
		print_status(philo, "has taken a fork");
		pthread_mutex_lock(&philo->sim->forks[right_fork_idx]);
		print_status(philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(&philo->sim->forks[right_fork_idx]);
		print_status(philo, "has taken a fork");
		pthread_mutex_lock(&philo->sim->forks[left_fork_idx]);
		print_status(philo, "has taken a fork");
	}
}

void	release_forks(t_philo *philo)
{
	int	left_fork_idx;
	int	right_fork_idx;

	left_fork_idx = philo->id - 1;
	right_fork_idx = philo->id % philo->sim->axioms.philo;
	if (philo->id % 2 == 0)
	{
		pthread_mutex_unlock(&philo->sim->forks[right_fork_idx]);
		pthread_mutex_unlock(&philo->sim->forks[left_fork_idx]);
	}
	else
	{
		pthread_mutex_unlock(&philo->sim->forks[left_fork_idx]);
		pthread_mutex_unlock(&philo->sim->forks[right_fork_idx]);
	}
}

void	philosopher_cycle(t_philo *philo)
{
	t_sim	*sim;

	sim = philo->sim;
	print_status(philo, "is thinking");
	take_forks(philo);
	if (!is_sim_running(sim))
	{
		release_forks(philo);
		return ;
	}
	pthread_mutex_lock(&philo->meal_lock);
	print_status(philo, "is eating");
	philo->last_meal = get_time();
	philo->times_eaten++;
	pthread_mutex_unlock(&philo->meal_lock);
	precise_usleep(sim->axioms.t_eat, sim);
	release_forks(philo);
	print_status(philo, "is sleeping");
	precise_usleep(sim->axioms.t_sleep, sim);
}

void	*philosopher_routine(void *arg)
{
	t_philo	*philo;
	t_sim	*sim;

	philo = (t_philo *)arg;
	sim = philo->sim;
	if (sim->axioms.philo == 1)
	{
		print_status(philo, "has taken a fork");
		precise_usleep(sim->axioms.t_die, sim);
		return (NULL);
	}
	if (philo->id % 2 != 0)
		usleep(1000);
	while (is_sim_running(sim))
		philosopher_cycle(philo);
	return (NULL);
}
