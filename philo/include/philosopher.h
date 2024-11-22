/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgomes <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 08:46:33 by pgomes            #+#    #+#             */
/*   Updated: 2024/11/22 09:48:34 by pgomes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

# include <pthread.h>
# include <stdbool.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>
// marco strings
# define TAKE_FORKS "has taken a fork"
# define EATING "is eating"
# define SLEEPING "is sleeping"
# define THINKING "is thinking"
# define DIED "died"
// marco int
# define TRUE 1
# define FALSE 0
# define EAT 0
# define SLEEP 1
# define THINK 2
# define DEAD 3
# define FULL 4
# define IDLE 5

struct	s_phlosophers;
typedef struct s_philo
{
	int						id;
	int						must_eat;
	int						state;
	unsigned int			last_meal;
	struct s_philosophers	*philosophers;
	pthread_mutex_t			*left_fork;
	pthread_mutex_t			*right_fork;
	pthread_mutex_t			mut_state;
	pthread_mutex_t			mut_nb_meal;
	pthread_mutex_t			mut_last_time;
}							t_philo;

typedef struct s_philosophers
{
	int						state;
	int						nb_philos;
	int						must_eat;
	int						nb_full_p;
	int						keep_iter;
	unsigned int			time_to_die;
	unsigned int			time_to_eat;
	unsigned int			time_to_sleep;
	unsigned int			start_time;

	t_philo					*philo;

	pthread_t				monit_all_alive;
	pthread_t				monit_all_full;

	pthread_t				*philos_thr;

	pthread_mutex_t			*forks;

	pthread_mutex_t			mut_eat_t;
	pthread_mutex_t			mut_die_t;
	pthread_mutex_t			mut_sleep_t;
	pthread_mutex_t			mut_print;
	pthread_mutex_t			mut_nb_philos;
	pthread_mutex_t			mut_keep_iter;
	pthread_mutex_t			mut_start_time;

}							t_philosophers;

unsigned int				get_time(void);
unsigned int				get_last_meal(t_philo *philo);

long						ft_atoi(const char *str);

void						*all_full_routine(void *data_p);
void						*all_alive_routine(void *data_p);
void						set_last_meal(t_philo *philo);
void						set_nb_meal(t_philo *philo);
void						set_state(t_philo *philo, int state);
void						wait_until(unsigned int wakeup_time);
void						*routine(void *philo_p);
void						validate_arg(int argc, char *argv[]);
void						ft_usleep(unsigned int sleep_time);
void						print_msg(t_philosophers *data, int id, char *msg);
void						free_data(t_philosophers *philos);

int							get_state(t_philo *philo);
int							philo_died(t_philo *philo);
int							get_numb_philo(t_philosophers *philos);
int							get_must_eat_philos(t_philosophers *philos);
int							get_keep_inter(t_philosophers *philos);
int							get_how_eat(t_philo *philo);
int							get_num_meal(t_philo *philo);
#endif
