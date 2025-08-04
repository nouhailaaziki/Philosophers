/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noaziki <noaziki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 09:39:12 by noaziki           #+#    #+#             */
/*   Updated: 2025/08/04 09:51:16 by noaziki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mindcore_bonus.h"

void	precise_usleep(long duration_ms)
{
	long	start_time;

	start_time = get_time();
	while ((get_time() - start_time) < duration_ms)
		usleep(50);
}

long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	print_status(t_philo *philo, char *status, int is_dead)
{
	long	timestamp;

	sem_wait(philo->params->write_sem);
	timestamp = get_time() - philo->params->start_time;
	if (is_dead)
		printf("%ld %d %s\n", timestamp, philo->id, status);
	else
	{
		printf("%ld %d %s\n", timestamp, philo->id, status);
		sem_post(philo->params->write_sem);
	}
}
