/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noaziki <noaziki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 11:01:50 by noaziki           #+#    #+#             */
/*   Updated: 2025/07/30 17:45:07 by noaziki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mindcore_bonus.h"

int	init_params(t_params *params, int argc, char **argv)
{
	params->num_philos = ft_atol(argv[1]);
	params->time_to_die = ft_atol(argv[2]);
	params->time_to_eat = ft_atol(argv[3]);
	params->time_to_sleep = ft_atol(argv[4]);
	if (argc == 6)
		params->num_eats = ft_atol(argv[5]);
	else
		params->num_eats = -1;
	if (params->num_philos <= 0 || params->time_to_die <= 0
		|| params->time_to_eat <= 0 || params->time_to_sleep <= 0
		|| (argc == 6 && params->num_eats <= 0))
	{
		printf("Error: All arguments must be positive integers.\n");
		return (1);
	}
	params->start_time = get_time();
	return (0);
}

int	init_semaphores(t_params *params)
{
	params->forks_sem = sem_open("/philo_forks", O_CREAT, 0644,
			params->num_philos);
	if (params->forks_sem == SEM_FAILED)
		return (printf("Error: sem_open failed for forks.\n"), 1);
	params->write_sem = sem_open("/philo_write", O_CREAT, 0644, 1);
	if (params->write_sem == SEM_FAILED)
		return (printf("Error: sem_open failed for write lock.\n"), 1);
	params->stop_sem = sem_open("/philo_stop", O_CREAT, 0644, 0);
	if (params->stop_sem == SEM_FAILED)
		return (printf("Error: sem_open failed for stop lock.\n"), 1);
	return (0);
}

void	build_sem_name(char *dest, const char *base, int index)
{
	int		i;
	int		j;
	char	num_buf[11];
	int		k;

	i = 0;
	while (base[i])
	{
		dest[i] = base[i];
		i++;
	}
	if (index == 0)
	{
		1 && (dest[i++] = '0', dest[i] = '\0');
		return ;
	}
	1 && (j = 0, k = index);
	while (k > 0)
	{
		num_buf[j++] = (k % 10) + '0';
		k /= 10;
	}
	while (j > 0)
		dest[i++] = num_buf[--j];
	dest[i] = '\0';
}

void	init_philos(t_philo *philos, t_params *params)
{
	long	i;

	i = 0;
	while (i < params->num_philos)
	{
		philos[i].id = i + 1;
		philos[i].pid = -1;
		philos[i].meals_eaten = 0;
		philos[i].last_meal_time = params->start_time;
		philos[i].params = params;
		build_sem_name(philos[i].eat_sem_name, "/philo_eat_", i);
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_params	params;
	t_philo		*philos;

	if (argc != 5 && argc != 6)
	{
		printf("Error: Invalid number of arguments.\n");
		printf("Usage: ./philo_bonus num_philos TTD TTE TTS [num_eats]\n");
		return (1);
	}
	if (init_params(&params, argc, argv) != 0)
		return (1);
	philos = malloc(sizeof(t_philo) * params.num_philos);
	if (!philos)
	{
		printf("Error: Malloc failed for philosophers.\n");
		return (1);
	}
	cleanup_semaphores();
	if (init_semaphores(&params) != 0)
		return (free(philos), 1);
	init_philos(philos, &params);
	start_simulation(philos, &params);
	stop_simulation(philos, &params);
	free(philos);
	return (0);
}
