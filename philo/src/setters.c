/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgomes <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 15:59:23 by pgomes            #+#    #+#             */
/*   Updated: 2024/11/04 12:42:43 by pgomes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosopher.h"

void	set_last_meal(t_philo *philo)
{
	pthread_mutex_lock(&philo->mut_last_time);
	philo->last_meal = get_time();
	pthread_mutex_unlock(&philo->mut_last_time);
}

void	set_nb_meal(t_philo *philo)
{
	pthread_mutex_lock(&philo->mut_nb_meal);
	if (philo->must_eat != -1)
		philo->must_eat++;
	pthread_mutex_unlock(&philo->mut_nb_meal);
}

void	set_state(t_philo *philo, int state)
{
	pthread_mutex_lock(&philo->mut_state);
	if (philo->state != DEAD)
		philo->state = state;
	pthread_mutex_unlock(&philo->mut_state);
}
