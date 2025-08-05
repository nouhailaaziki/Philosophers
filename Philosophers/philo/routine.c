/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noaziki <noaziki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 00:57:53 by noaziki           #+#    #+#             */
/*   Updated: 2025/08/05 13:18:11 by noaziki          ###   ########.fr       */
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

void	*launch_philosopher_life(t_philo *philo)
{
	t_sim	*sim;

	sim = philo->sim;
	if (philo->id % 2 != 0)
		usleep(1000);
	while (is_sim_running(sim))
	{
		pthread_mutex_lock(&philo->meal_lock);
		if (sim->axioms.eats != -1 && philo->times_eaten >= sim->axioms.eats)
		{
			pthread_mutex_unlock(&philo->meal_lock);
			break ;
		}
		(pthread_mutex_unlock(&philo->meal_lock), philosopher_cycle(philo));
		if (sim->axioms.philo % 2 != 0)
			usleep (1000);
	}
	return (NULL);
}

void	*philosopher_routine(void *arg)
{
	t_philo	*philo;
	t_sim	*sim;

	1 && (philo = (t_philo *)arg, sim = philo->sim);
	if (sim->axioms.philo == 1)
	{
		pthread_mutex_lock(&sim->forks[0]);
		print_status(philo, "has taken a fork");
		pthread_mutex_unlock(&sim->forks[0]);
		precise_usleep(sim->axioms.t_die, sim);
		return (NULL);
	}
	return (launch_philosopher_life(philo));
}
