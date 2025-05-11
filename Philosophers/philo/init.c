/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aymohamm <aymohamm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 08:54:50 by aymohamm          #+#    #+#             */
/*   Updated: 2024/07/31 20:09:05 by aymohamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool				prepare_philo(t_table *table);
static void				assign_forks(t_philo *philo);
static pthread_mutex_t	*init_fork(t_table *table);
static bool				init_mutex(t_table *table);

t_table	*prepare_table(int ac, char **av)
{
	t_table	*table;

	table = malloc(sizeof(t_table));
	if (!table)
		return (error_null("Error: Could not allocate memory.\n", NULL));
	table->nbr_philo = check_valid(av[1]);
	table->time_to_die = check_valid(av[2]);
	table->time_to_eat = check_valid(av[3]);
	table->time_to_sleep = check_valid(av[4]);
	table->time_must_eat = -1;
	if (ac == 6)
		table->time_must_eat = check_valid(av[5]);
	if (is_param_valid(table) == false)
	{
		free (table);
		return (0);
	}
	table->dinner_end = false;
	table->start_dining = current_time();
	if (prepare_philo(table) == false || table->philo == NULL)
		return (NULL);
	if (init_mutex(table) == false || is_param_valid(table) == false)
		return (NULL);
	return (table);
}

static bool	prepare_philo(t_table *table)
{
	t_philo	**philos;
	long	i;

	i = 0;
	philos = malloc(sizeof(t_philo) * table->nbr_philo);
	while (i < table->nbr_philo)
	{
		philos[i] = malloc(sizeof(t_philo));
		if (!philos[i])
		{
			while (i > 0)
				free(philos[--i]);
			free(philos);
			return (error_null("Error: Could not allocate memory.\n", NULL));
		}
		philos[i]->table = table;
		philos[i]->id = i;
		philos[i]->nbr_meals_done = 0;
		philos[i]->last_meal = 0;
		assign_forks(philos[i]);
		if (pthread_mutex_init(&philos[i]->general_meal_lock, 0) != 0)
			return (error_null("Error: Could not allocate memory.\n", NULL));
		i++;
	}
	return (table->philo = philos, true);
}

static void	assign_forks(t_philo *philo)
{
	philo->fork[0] = philo->id;
	if (philo->table->nbr_philo > 1)
	{
		philo->fork[1] = (philo->id + 1) % philo->table->nbr_philo;
		if (philo->id % 2 != 0)
		{
			philo->fork[0] = (philo->id + 1) % philo->table->nbr_philo;
			philo->fork[1] = philo->id;
		}
	}
}

static pthread_mutex_t	*init_fork(t_table *table)
{
	pthread_mutex_t	*forks;
	long			i;

	i = 0;
	forks = malloc(sizeof(pthread_mutex_t) * table->nbr_philo);
	if (!forks)
		return (error_null("Error: Could not allocate memory.\n", NULL));
	while (i < table->nbr_philo)
	{
		if (pthread_mutex_init(&forks[i], 0) != 0)
			return (error_null("Error: Could not allocate memory.\n", NULL));
		i++;
	}
	return (forks);
}

static bool	init_mutex(t_table *table)
{
	table->fork_lock = init_fork(table);
	if (!table->fork_lock)
		return (false);
	if (pthread_mutex_init(&table->dinner_end_lock, 0) != 0)
		return (error_null("Error: problem creating mutex.\n", NULL));
	if (pthread_mutex_init(&table->log_lock, 0) != 0)
		return (error_null("Error:problem creating mutex.\n", NULL));
	return (true);
}
