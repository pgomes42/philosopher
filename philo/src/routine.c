/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgomes <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 08:20:16 by pgomes            #+#    #+#             */
/*   Updated: 2024/11/22 09:57:36 by pgomes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosopher.h"

static int	take_forks(t_philo *philo)
{
	int	first;
	int	second;
	int	temp;

	first = philo->id;
	second = (philo->id + 1) % philo->philosophers->nb_philos;
	if (first > second)
	{
		temp = first;
		first = second;
		second = temp;
	}
	philo->left_fork = &philo->philosophers->forks[first];
	philo->right_fork = &philo->philosophers->forks[second];
	if (pthread_mutex_lock(philo->left_fork) != 0)
		return (FALSE);
	if (get_state(philo) == DEAD)
		return (pthread_mutex_unlock(philo->left_fork), FALSE);
	print_msg(philo->philosophers, philo->id, TAKE_FORKS);
	if (pthread_mutex_lock(philo->right_fork) != 0)
		return (pthread_mutex_unlock(philo->left_fork), FALSE);
	if (get_state(philo) == DEAD)
		return (pthread_mutex_unlock(philo->left_fork),
			pthread_mutex_unlock(philo->right_fork), FALSE);
	return (print_msg(philo->philosophers, philo->id, TAKE_FORKS), TRUE);
}

static int	eat(t_philo *philo)
{
	if (!take_forks(philo))
		return (FALSE);
	set_state(philo, EAT);
	if (get_state(philo) == DEAD)
	{
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		return (FALSE);
	}
	print_msg(philo->philosophers, philo->id, EATING);
	set_last_meal(philo);
	ft_usleep(philo->philosophers->time_to_eat);
	set_nb_meal(philo);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	return (TRUE);
}

static int	ft_sleep(t_philo *philo)
{
	set_state(philo, SLEEP);
	if (get_state(philo) == DEAD)
		return (FALSE);
	print_msg(philo->philosophers, philo->id, SLEEPING);
	ft_usleep(philo->philosophers->time_to_sleep);
	return (TRUE);
}

static int	think(t_philo *philo)
{
	set_state(philo, THINK);
	if (get_state(philo) == DEAD)
		return (FALSE);
	print_msg(philo->philosophers, philo->id, THINKING);
	return (TRUE);
}

void	*routine(void *philo_p)
{
	t_philo	*philo;

	philo = (t_philo *)philo_p;
	set_last_meal(philo);
	if (philo->id % 2 == 0)
		ft_usleep(philo->philosophers->time_to_eat - 10);
	while (get_state(philo) != DEAD && get_keep_inter(philo->philosophers))
	{
		if (!eat(philo))
			break ;
		if (get_state(philo) == DEAD)
			break ;
		if (!ft_sleep(philo))
			break ;
		if (get_state(philo) == DEAD)
			break ;
		if (!think(philo))
			break ;
	}
	return (NULL);
}
