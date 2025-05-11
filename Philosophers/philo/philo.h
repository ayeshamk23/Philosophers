/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aymohamm <aymohamm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 09:07:26 by aymohamm          #+#    #+#             */
/*   Updated: 2024/07/21 15:38:43 by aymohamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <time.h>
# include <unistd.h>

typedef struct s_table	t_table;
typedef struct s_philo	t_philo;

typedef enum e_fork
{
	F_LEFT = 0,
	F_RIGHT = 1
}						t_fork;

typedef enum e_state
{
	PHILO_EATING,
	PHILO_SLEEPING,
	PHILO_THINKING,
	PHILO_DEAD,
	PHILO_LEFT_FORK,
	PHILO_RIGHT_FORK,
	END_dining
}						t_state;

struct					s_philo
{
	pthread_t			thread_philo;
	long				id;
	int					fork[2];
	t_table				*table;
	long				nbr_meals_done;
	pthread_mutex_t		general_meal_lock;
	time_t				last_meal;
};

struct					s_table
{
	pthread_t			thread_table;
	time_t				start_dining;
	long				nbr_philo;
	long				time_to_die;
	long				time_to_eat;
	long				time_to_sleep;
	long				time_must_eat;
	t_philo				**philo;
	bool				dinner_end;
	pthread_mutex_t		dinner_end_lock;
	pthread_mutex_t		*fork_lock;
	pthread_mutex_t		log_lock;
};

bool					check_args(int argc, char **argv);

bool					is_param_valid(t_table *table);

long					check_valid(const char *str);

bool					ft_isdigit(int c);

t_table					*prepare_table(int ac, char **av);

void					*error_null(char *err, t_table *table);

long long				current_time(void);

void					philo_sleep(t_table *table, time_t duration);

bool					dinner_finished(t_table *table);

int						get_time_ms(int start_dining);

long					manage_thinking_time(t_philo *philo);

void					*free_table(t_table *table);

void					*simulation(void *data);

void					record_last_eaten_time(t_philo *philo, time_t time);

void					record_dinner_end_time(t_table *table, bool value);

void					get_status(t_philo *philo, t_state status);

const char				*get_status_message(t_state status);

void					*end_simulation(void *data);

void					more_meal(t_philo *philo);

#endif