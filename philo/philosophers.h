/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noaziki <noaziki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 16:13:04 by noaziki           #+#    #+#             */
/*   Updated: 2025/04/25 17:06:38 by noaziki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdlib.h>
# include <stdio.h>

typedef struct s_axioms
{
	long	philo;
	long	t_sleep;
	long	t_die;
	long	t_eat;
	long	eats;
}	t_axioms;

void	define_truths(t_axioms *axioms, char **argv, int argc);

#endif