/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noaziki <noaziki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 11:06:45 by noaziki           #+#    #+#             */
/*   Updated: 2025/07/15 16:41:49 by noaziki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mindcore_bonus.h"

void	start_simulation(t_philo *philos, t_params *params)
{
	int	i;

	i = 0;
	while (i < params->num_philos)
	{
		philos[i].pid = fork();
		if (philos[i].pid < 0)
		{
			write(2, "Error: fork failed\n", 19);
			while (--i >= 0)
				kill(philos[i].pid, SIGKILL);
			exit(1);
		}
		if (philos[i].pid == 0)
		{
			philosopher_routine(&philos[i]);
			exit(0);
		}
		i++;
	}
}

void	stop_simulation(t_philo *philos, t_params *params)
{
	int		i;
	int		status;
	pid_t	pid;

	i = 0;
	while (i < params->num_philos)
	{
		pid = waitpid(-1, &status, 0);
		if (WIFEXITED(status) && WEXITSTATUS(status) == 1)
			break ;
		i++;
	}
	i = 0;
	while (i < params->num_philos)
	{
		if (philos[i].pid > 0)
			kill(philos[i].pid, SIGKILL);
		i++;
	}
	cleanup_semaphores();
}
