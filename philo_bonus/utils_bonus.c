/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noaziki <noaziki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 11:07:27 by noaziki           #+#    #+#             */
/*   Updated: 2025/07/15 16:50:56 by noaziki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mindcore_bonus.h"

long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	precise_usleep(long duration_ms)
{
	long	start_time;

	start_time = get_time();
	while ((get_time() - start_time) < duration_ms)
		usleep(50);
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

long	ft_atol(const char *str)
{
	long	i;
	long	s;
	long	r;

	1 && (i = 0, s = 1, r = 0);
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			s *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		r = r * 10 + str[i++] - 48;
		if ((r >= 2147483647 && s == 1) || (r > 2147483647 && s == -1))
			return (-1);
	}
	if (str[i])
		return (-1);
	return (r * s);
}

void	cleanup_semaphores(void)
{
	sem_unlink("/philo_forks");
	sem_unlink("/philo_write");
	sem_unlink("/philo_stop");
}
