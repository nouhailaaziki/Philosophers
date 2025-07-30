/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noaziki <noaziki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 16:14:35 by noaziki           #+#    #+#             */
/*   Updated: 2025/07/15 16:50:24 by noaziki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mindcore.h"

int	define_truths(t_axioms *axioms, char **argv, int argc)
{
	axioms->philo = ft_atol(argv[1]);
	axioms->t_die = ft_atol(argv[2]);
	axioms->t_eat = ft_atol(argv[3]);
	axioms->t_sleep = ft_atol(argv[4]);
	if (argc == 6)
		axioms->eats = ft_atol(argv[5]);
	else
		axioms->eats = -1;
	if (axioms->philo <= 0 || axioms->t_die <= 0
		|| axioms->t_eat <= 0 || axioms->t_sleep <= 0
		|| (argc == 6 && axioms->eats <= 0))
	{
		ft_putendl_fd("Invalid input: Arguments must be positive numbers.", 2);
		return (1);
	}
	return (0);
}
// void f(){system("leaks -q philo");}
	// atexit(f);

int	main(int argc, char **argv)
{
	t_sim	sim;

	if (argc != 5 && argc != 6)
	{
		ft_putendl_fd("Invalid input: you must provide 4 or 5 arguments!", 2);
		ft_putendl_fd("Usage: ./philo_bonus num_philos \
TTD TTE TTS [num_eats]", 2);
		return (1);
	}
	memset(&sim, 0, sizeof(t_sim));
	if (define_truths(&sim.axioms, argv, argc))
		return (1);
	if (init_simulation(&sim) != 0)
	{
		ft_putendl_fd("Error: Failed to initialize simulation.", 2);
		cleanup(&sim);
		return (1);
	}
	run_simulation(&sim);
	cleanup(&sim);
	return (0);
}
