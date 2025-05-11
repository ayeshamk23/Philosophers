/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aymohamm <aymohamm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 09:09:04 by aymohamm          #+#    #+#             */
/*   Updated: 2024/07/23 09:30:18 by aymohamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	*one_philo(t_philo *philo);
static void	philo_eating(t_philo *philo);
static void	philo_thinking(t_philo *philo, bool state);
static void	philo_sleeping(t_philo *philo);

void	*simulation(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	if (philo->table->time_must_eat == 0)
		return (NULL);
	record_last_eaten_time(philo, philo->table->start_dining);
	if (philo->table->nbr_philo == 1)
		return (one_philo(philo));
	if (philo->id % 2 != 0)
		philo_thinking(philo, false);
	while (true)
	{
		pthread_mutex_lock(&philo->table->dinner_end_lock);
		if (philo->table->dinner_end)
		{
			pthread_mutex_unlock(&philo->table->dinner_end_lock);
			break ;
		}
		pthread_mutex_unlock(&philo->table->dinner_end_lock);
		philo_eating(philo);
		philo_sleeping(philo);
		philo_thinking(philo, true);
	}
	return (NULL);
}

static void	*one_philo(t_philo *philo)
{
	get_status(philo, PHILO_LEFT_FORK);
	philo_sleep(philo->table, philo->table->time_to_die);
	get_status(philo, PHILO_DEAD);
	return (NULL);
}

static void	philo_eating(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->fork_lock[philo->fork[F_LEFT]]);
	get_status(philo, PHILO_LEFT_FORK);
	pthread_mutex_lock(&philo->table->fork_lock[philo->fork[F_RIGHT]]);
	get_status(philo, PHILO_RIGHT_FORK);
	get_status(philo, PHILO_EATING);
	record_last_eaten_time(philo, current_time());
	philo_sleep(philo->table, philo->table->time_to_eat);
	if (dinner_finished(philo->table) == false)
		more_meal(philo);
	pthread_mutex_unlock(&philo->table->fork_lock[philo->fork[F_RIGHT]]);
	pthread_mutex_unlock(&philo->table->fork_lock[philo->fork[F_LEFT]]);
}

static void	philo_thinking(t_philo *philo, bool state)
{
	time_t	time_to_think;

	time_to_think = manage_thinking_time(philo);
	if (state == true)
	{
		get_status(philo, PHILO_THINKING);
	}
	philo_sleep(philo->table, time_to_think);
}

static void	philo_sleeping(t_philo *philo)
{
	get_status(philo, PHILO_SLEEPING);
	philo_sleep(philo->table, philo->table->time_to_sleep);
}
