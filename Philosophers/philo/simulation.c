/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noaziki <noaziki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 01:08:27 by noaziki           #+#    #+#             */
/*   Updated: 2025/07/15 15:38:42 by noaziki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mindcore.h"

int	check_philosopher_status(t_sim *sim)
{
	int	i;
	int	all_done_eating;

	all_done_eating = 1;
	i = 0;
	while (i < sim->axioms.philo)
	{
		pthread_mutex_lock(&sim->philos[i].meal_lock);
		if (get_time() - sim->philos[i].last_meal > sim->axioms.t_die)
		{
			print_status(&sim->philos[i], "died");
			stop_sim(sim);
			pthread_mutex_unlock(&sim->philos[i].meal_lock);
			return (0);
		}
		if (sim->axioms.eats != -1
			&& sim->philos[i].times_eaten < sim->axioms.eats)
			all_done_eating = 0;
		pthread_mutex_unlock(&sim->philos[i].meal_lock);
		i++;
	}
	if (sim->axioms.eats != -1 && all_done_eating)
		return (stop_sim(sim), 0);
	return (1);
}

void	monitor_philosophers(t_sim *sim)
{
	while (is_sim_running(sim))
	{
		if (!check_philosopher_status(sim))
			return ;
		usleep(1000);
	}
}

int	init_simulation(t_sim *sim)
{
	int	i;

	sim->philos = malloc(sizeof(t_philo) * sim->axioms.philo);
	if (!sim->philos)
		return (1);
	memset(sim->philos, 0, sizeof(t_philo) * sim->axioms.philo);
	sim->forks = malloc(sizeof(pthread_mutex_t) * sim->axioms.philo);
	if (!sim->forks)
		return (1);
	pthread_mutex_init(&sim->print_lock, NULL);
	pthread_mutex_init(&sim->state_lock, NULL);
	sim->start_time = get_time();
	i = 0;
	while (i < sim->axioms.philo)
	{
		pthread_mutex_init(&sim->forks[i], NULL);
		sim->philos[i].id = i + 1;
		sim->philos[i].last_meal = sim->start_time;
		sim->philos[i].times_eaten = 0;
		sim->philos[i].sim = sim;
		pthread_mutex_init(&sim->philos[i].meal_lock, NULL);
		i++;
	}
	sim->is_running = 1;
	return (0);
}

void	run_simulation(t_sim *sim)
{
	int	i;
	int	j;

	i = 0;
	while (i < sim->axioms.philo)
	{
		if (pthread_create(&sim->philos[i].thread, NULL,
				&philosopher_routine, &sim->philos[i]) != 0)
		{
			stop_sim(sim);
			break ;
		}
		i++;
	}
	monitor_philosophers(sim);
	j = 0;
	while (j < i)
	{
		pthread_join(sim->philos[j].thread, NULL);
		j++;
	}
}

void	cleanup(t_sim *sim)
{
	int	i;

	if (sim->forks)
	{
		i = 0;
		while (i < sim->axioms.philo)
		{
			pthread_mutex_destroy(&sim->forks[i]);
			i++;
		}
		free(sim->forks);
	}
	if (sim->philos)
	{
		i = 0;
		while (i < sim->axioms.philo)
		{
			pthread_mutex_destroy(&sim->philos[i].meal_lock);
			i++;
		}
		free(sim->philos);
	}
	pthread_mutex_destroy(&sim->print_lock);
	pthread_mutex_destroy(&sim->state_lock);
}
