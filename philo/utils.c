/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noaziki <noaziki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 10:18:55 by noaziki           #+#    #+#             */
/*   Updated: 2025/07/15 16:49:57 by noaziki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mindcore.h"

void	ft_putendl_fd(char *s, int fd)
{
	size_t	i;

	if (!s)
		return ;
	i = 0;
	while (s[i] != '\0')
	{
		write(fd, &s[i], 1);
		i++;
	}
	write(fd, "\n", 1);
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
