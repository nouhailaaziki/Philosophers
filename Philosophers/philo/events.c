/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noaziki <noaziki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 12:03:12 by noaziki           #+#    #+#             */
/*   Updated: 2025/08/03 15:43:14 by noaziki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mindcore.h"

void	precise_usleep(long milliseconds, t_sim *sim)
{
	long	start_time;

	start_time = get_time();
	while (is_sim_running(sim) && (get_time() - start_time) < milliseconds)
		usleep(50);
}

long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

int	is_sim_running(t_sim *sim)
{
	int	running;

	pthread_mutex_lock(&sim->state_lock);
	running = sim->is_running;
	pthread_mutex_unlock(&sim->state_lock);
	return (running);
}

void	stop_sim(t_sim *sim)
{
	pthread_mutex_lock(&sim->state_lock);
	sim->is_running = 0;
	pthread_mutex_unlock(&sim->state_lock);
}

void	print_status(t_philo *philo, const char *status)
{
	pthread_mutex_lock(&philo->sim->print_lock);
	if (!ft_strcmp((char *)status, "died"))
	{
		stop_sim(philo->sim);
		printf("%ld %d %s\n", \
			get_time() - philo->sim->start_time, philo->id, status);
	}
	else if (is_sim_running(philo->sim) && ft_strcmp((char *)status, "died"))
		printf("%ld %d %s\n", \
			get_time() - philo->sim->start_time, philo->id, status);
	pthread_mutex_unlock(&philo->sim->print_lock);
}
