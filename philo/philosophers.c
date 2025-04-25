/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noaziki <noaziki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 16:14:35 by noaziki           #+#    #+#             */
/*   Updated: 2025/04/25 17:06:12 by noaziki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int argc, char **argv)
{
	int			i;
	t_axioms	axioms;

	i = 1;
	if (argc != 5 && argc != 6)
	{
		printf("Invalid input: you must provide 4 or 5 arguments!\n");
		return (1);
	}
	define_truths(&axioms, argv, argc);
	return (0);
}
