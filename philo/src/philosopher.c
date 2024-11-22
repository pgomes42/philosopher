/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgomes <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 08:48:10 by pgomes            #+#    #+#             */
/*   Updated: 2024/11/22 09:41:05 by pgomes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosopher.h"

static int	init_forks(t_philosophers *philos)
{
	int	i;

	philos->forks = malloc(sizeof(pthread_mutex_t) * philos->nb_philos);
	if (!philos->forks)
		return (FALSE);
	i = -1;
	while (++i < philos->nb_philos)
		pthread_mutex_init(&philos->forks[i], NULL);
	return (TRUE);
}

static int	init_philosopher(t_philosophers *philos)
{
	int	i;

	i = -1;
	philos->philo = malloc(sizeof(t_philo) * philos->nb_philos);
	if (!philos->philo)
		return (FALSE);
	while (++i < philos->nb_philos)
	{
		philos->philo[i].id = i + 1;
		philos->philo[i].state = IDLE;
		philos->philo[i].philosophers = philos;
		philos->philo[i].must_eat = 0;
		if (philos->must_eat == -1)
			philos->philo[i].must_eat = -1;
		philos->philo[i].last_meal = 0;
		pthread_mutex_init(&philos->philo[i].mut_state, NULL);
		pthread_mutex_init(&philos->philo[i].mut_nb_meal, NULL);
		pthread_mutex_init(&philos->philo[i].mut_last_time, NULL);
	}
	return (TRUE);
}

static int	init_philosophers(t_philosophers *philos, int argc, char **argv)
{
	philos->nb_full_p = 0;
	philos->keep_iter = TRUE;
	philos->nb_philos = ft_atoi(argv[1]);
	philos->time_to_die = (unsigned int)ft_atoi(argv[2]);
	philos->time_to_eat = (unsigned int)ft_atoi(argv[3]);
	philos->time_to_sleep = (unsigned int)ft_atoi(argv[4]);
	philos->must_eat = -1;
	if (argc == 6)
		philos->must_eat = ft_atoi(argv[5]);
	pthread_mutex_init(&philos->mut_eat_t, NULL);
	pthread_mutex_init(&philos->mut_sleep_t, NULL);
	pthread_mutex_init(&philos->mut_die_t, NULL);
	pthread_mutex_init(&philos->mut_print, NULL);
	pthread_mutex_init(&philos->mut_nb_philos, NULL);
	pthread_mutex_init(&philos->mut_keep_iter, NULL);
	pthread_mutex_init(&philos->mut_start_time, NULL);
	if (!init_philosopher(philos))
		return (FALSE);
	if (!init_forks(philos))
		return (free(philos->philo), FALSE);
	philos->philos_thr = malloc(sizeof(pthread_t) * philos->nb_philos);
	if (!philos->philos_thr)
		return (free(philos->philo), free(philos->forks), FALSE);
	return (TRUE);
}

static void	run_threads(t_philosophers *philos, int nb_philos)
{
	int	i;

	i = -1;
	philos->start_time = get_time();
	while (++i < nb_philos)
		pthread_create(&philos->philos_thr[i], NULL, &routine,
			&philos->philo[i]);
	pthread_create(&philos->monit_all_alive, NULL, &all_alive_routine, philos);
	if (philos->must_eat > 0)
		pthread_create(&philos->monit_all_full, NULL, &all_full_routine,
			philos);
	i = -1;
	while (++i < nb_philos)
		pthread_join(philos->philos_thr[i], NULL);
	pthread_join(philos->monit_all_alive, NULL);
	if (philos->must_eat > 0)
		pthread_join(philos->monit_all_full, NULL);
}

int	main(int argc, char *argv[])
{
	t_philosophers	philos;

	if (argc == 5 || argc == 6)
	{
		validate_arg(argc, argv);
		if (init_philosophers(&philos, argc, argv))
		{
			run_threads(&philos, philos.nb_philos);
		}
		free_data(&philos);
		return (0);
	}
	printf("Error\nTo compile enter the below command:\n");
	printf("./philo [number_of_philosophers] [time_to_die]");
	printf("[time_to_eat] [time_to_sleep]");
	printf("[number_of_times_each_philosopher_must_eat]\n");
	return (0);
}
