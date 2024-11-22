/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgomes <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 08:12:28 by pgomes            #+#    #+#             */
/*   Updated: 2024/10/07 08:46:54 by pgomes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosopher.h"

void	wait_until(unsigned int wakeup_time)
{
	int				margin;
	unsigned int	time;

	margin = 5;
	while (1)
	{
		time = get_time();
		if (wakeup_time <= time + margin)
		{
			while (wakeup_time > time)
				time = get_time();
			break ;
		}
		else
		{
			usleep(1000 * (wakeup_time - time - margin));
		}
	}
}

void	ft_usleep(unsigned int sleep_time)
{
	unsigned int	start;

	start = get_time();
	while ((get_time() - start) < sleep_time)
		usleep(500);
}

unsigned int	get_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
		return (0);
	return ((tv.tv_sec * (unsigned int)1000) + (tv.tv_usec / 1000));
}
