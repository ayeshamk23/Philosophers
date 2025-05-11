/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_simulation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aymohamm <aymohamm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 09:09:43 by aymohamm          #+#    #+#             */
/*   Updated: 2024/07/31 20:08:34 by aymohamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	end_dinner(t_table *table);
static bool	killing(t_philo *philo);

void	*end_simulation(void *data)
{
	t_table	*table;

	table = (t_table *)data;
	if (table->time_must_eat == 0)
		return (NULL);
	record_dinner_end_time(table, false);
	while (true)
	{
		if (end_dinner(table) == true)
			return (NULL);
		usleep(360);
	}
	return (NULL);
}

static bool	killing(t_philo *philo)
{
	if ((current_time() - philo->last_meal) >= philo->table->time_to_die)
	{
		get_status(philo, PHILO_DEAD);
		record_dinner_end_time(philo->table, true);
		pthread_mutex_unlock(&philo->general_meal_lock);
		return (true);
	}
	return (false);
}

static bool	end_dinner(t_table *table)
{
	int		i;
	bool	flag;

	i = 0;
	flag = true;
	while (i < table->nbr_philo)
	{
		pthread_mutex_lock(&table->philo[i]->general_meal_lock);
		if (killing(table->philo[i]) == true)
			return (true);
		if (table->time_must_eat != -1)
			if (table->philo[i]->nbr_meals_done < table->time_must_eat)
				flag = false;
		pthread_mutex_unlock(&table->philo[i]->general_meal_lock);
		i++;
	}
	if (table->time_must_eat != -1 && flag == true)
	{
		record_dinner_end_time(table, true);
		return (true);
	}
	return (false);
}
