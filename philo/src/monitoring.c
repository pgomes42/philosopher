/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgomes <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 10:29:19 by pgomes            #+#    #+#             */
/*   Updated: 2024/11/04 15:04:40 by pgomes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosopher.h"

int	philo_died(t_philo *philo)
{
	t_philosophers	*philos;

	philos = philo->philosophers;
	if (get_time() - get_last_meal(philo) > philos->time_to_die
		&& get_state(philo) != EAT)
	{
		set_state(philo, DEAD);
		return (TRUE);
	}
	return (FALSE);
}

static void	notify_all_philos(t_philosophers *philos)
{
	int	i;

	i = -1;
	while (++i < philos->nb_philos)
		set_state(&philos->philo[i], DEAD);
}

void	*all_full_routine(void *data_p)
{
	t_philosophers	*philos;
	int				i;
	int				num_philos;

	philos = (t_philosophers *)data_p;
	i = -1;
	num_philos = get_numb_philo(philos);
	while (++i < num_philos && get_keep_inter(philos))
	{
		usleep(1000);
		if (philos->philo[i].must_eat < philos->must_eat && i <= num_philos - 1)
			i = -1;
	}
	if (get_keep_inter(philos))
	{
		pthread_mutex_lock(&philos->mut_keep_iter);
		philos->keep_iter = FALSE;
		pthread_mutex_unlock(&philos->mut_keep_iter);
		notify_all_philos(philos);
	}
	return (NULL);
}

void	*all_alive_routine(void *data_p)
{
	t_philosophers	*philos;
	int				i;
	int				num_philos;

	philos = (t_philosophers *)data_p;
	num_philos = get_numb_philo(philos);
	i = -1;
	while (++i < num_philos && get_keep_inter(philos))
	{
		if (philo_died(&philos->philo[i]) && get_keep_inter(philos))
		{
			print_msg(philos, philos->philo[i].id, DIED);
			pthread_mutex_lock(&philos->mut_keep_iter);
			philos->keep_iter = FALSE;
			pthread_mutex_unlock(&philos->mut_keep_iter);
			notify_all_philos(philos);
			break ;
		}
		if (i == num_philos - 1)
			i = -1;
		usleep(1000);
	}
	return (NULL);
}
