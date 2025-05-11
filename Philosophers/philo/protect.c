/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   protect.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aymohamm <aymohamm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 09:10:23 by aymohamm          #+#    #+#             */
/*   Updated: 2024/07/31 18:53:43 by aymohamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	record_last_eaten_time(t_philo *philo, time_t time)
{
	pthread_mutex_lock(&philo->general_meal_lock);
	philo->last_meal = time;
	pthread_mutex_unlock(&philo->general_meal_lock);
}

void	record_dinner_end_time(t_table *table, bool value)
{
	pthread_mutex_lock(&table->dinner_end_lock);
	table->dinner_end = value;
	pthread_mutex_unlock(&table->dinner_end_lock);
}

void	more_meal(t_philo *philo)
{
	pthread_mutex_lock(&philo->general_meal_lock);
	philo->nbr_meals_done++;
	pthread_mutex_unlock(&philo->general_meal_lock);
}
