/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_arg.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgomes <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 10:07:12 by pgomes            #+#    #+#             */
/*   Updated: 2024/11/04 14:47:20 by pgomes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosopher.h"

static int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

static int	ft_isnumber(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (FALSE);
		i++;
	}
	return (TRUE);
}

long	ft_atoi(const char *str)
{
	long	i;
	long	sign;
	long	res;

	i = 0;
	sign = 1;
	res = 0;
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	while (ft_isdigit(str[i]))
	{
		res = res * 10 + str[i] - '0';
		i++;
	}
	return (res * sign);
}

void	validate_arg(int argc, char *argv[])
{
	int		i;
	long	num;

	i = 1;
	if (argc == 5 || argc == 6)
	{
		while (i < argc)
		{
			num = ft_atoi(argv[i]);
			if (!ft_isnumber(argv[i]) || (!(i == 1 && (num > 0 && num <= 100))
					&& !(i > 1 && i < 5 && num >= 60) && !(i == 5 && num > 0)))
			{
				printf("ERROR\nCheck de input numbers\n");
				exit(0);
			}
			i++;
		}
	}
}
