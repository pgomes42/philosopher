/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgomes <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 08:38:28 by pgomes            #+#    #+#             */
/*   Updated: 2024/11/22 09:53:55 by pgomes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosopher.h"

void	free_data(t_philosophers *philos)
{
	int	i;

	i = -1;
	while (++i < philos->nb_philos)
	{
		pthread_mutex_destroy(&philos->forks[i]);
		pthread_mutex_destroy(&philos->philo[i].mut_state);
		pthread_mutex_destroy(&philos->philo[i].mut_nb_meal);
		pthread_mutex_destroy(&philos->philo[i].mut_last_time);
	}
	pthread_mutex_destroy(&philos->mut_die_t);
	pthread_mutex_destroy(&philos->mut_eat_t);
	pthread_mutex_destroy(&philos->mut_sleep_t);
	pthread_mutex_destroy(&philos->mut_nb_philos);
	pthread_mutex_destroy(&philos->mut_print);
	pthread_mutex_destroy(&philos->mut_keep_iter);
	pthread_mutex_destroy(&philos->mut_start_time);
	free(philos->philos_thr);
	free(philos->philo);
	free(philos->forks);
}

int	get_num_meal(t_philo *philo)
{
	int	num_meal;

	pthread_mutex_lock(&philo->mut_nb_meal);
	num_meal = philo->must_eat;
	pthread_mutex_unlock(&philo->mut_nb_meal);
	return (num_meal);
}

void	print_msg(t_philosophers *philos, int id, char *msg)
{
	unsigned int	time;

	time = get_time() - philos->start_time;
	pthread_mutex_lock(&philos->mut_print);
	printf("%u %d %s\n", time, id, msg);
	pthread_mutex_unlock(&philos->mut_print);
}
