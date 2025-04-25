/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_guard.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noaziki <noaziki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 10:18:55 by noaziki           #+#    #+#             */
/*   Updated: 2025/04/25 17:02:06 by noaziki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long	ft_atoi(const char *str)
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

void	define_truths(t_axioms *axioms, char **argv, int argc)
{
	1 && (axioms->philo = ft_atoi(argv[1]), axioms->t_die = ft_atoi(argv[2]));
	1 && (axioms->t_eat = ft_atoi(argv[3]), axioms->t_sleep = ft_atoi(argv[4]));
	if (argc == 6)
	{
		axioms->eats = ft_atoi(argv[5]);
		if (axioms->eats < 0)
		{
			printf("Invalid input: One of the arguments \
violates the terms!\n");
			exit(1);
		}
	}
	else
		axioms->eats = -1;
	if (axioms->philo <= 0 || axioms->t_die <= 0
		|| axioms->t_eat <= 0 || axioms->t_sleep <= 0)
	{
		printf("Invalid input: One of the arguments \
violates the terms!\n");
		exit(1);
	}
}
