/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgomes <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 15:53:33 by pgomes            #+#    #+#             */
/*   Updated: 2024/10/08 15:53:33 by pgomes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosopher.h"

int	get_state(t_philo *philo)
{
	int	state;

	pthread_mutex_lock(&philo->mut_state);
	state = philo->state;
	pthread_mutex_unlock(&philo->mut_state);
	return (state);
}

unsigned int	get_last_meal(t_philo *philo)
{
	unsigned int	last_meal;

	pthread_mutex_lock(&philo->mut_last_time);
	last_meal = philo->last_meal;
	pthread_mutex_unlock(&philo->mut_last_time);
	return (last_meal);
}

int	get_numb_philo(t_philosophers *philos)
{
	int	number;

	pthread_mutex_lock(&philos->mut_nb_philos);
	number = philos->nb_philos;
	pthread_mutex_unlock(&philos->mut_nb_philos);
	return (number);
}

int	get_must_eat_philos(t_philosophers *philos)
{
	int	must_eat;

	pthread_mutex_lock(&philos->mut_nb_philos);
	must_eat = philos->must_eat;
	pthread_mutex_unlock(&philos->mut_nb_philos);
	return (must_eat);
}

int	get_keep_inter(t_philosophers *philos)
{
	int	kep_inter;

	pthread_mutex_lock(&philos->mut_keep_iter);
	kep_inter = philos->keep_iter;
	pthread_mutex_unlock(&philos->mut_keep_iter);
	return (kep_inter);
}
