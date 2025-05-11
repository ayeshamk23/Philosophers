/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aymohamm <aymohamm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 09:17:18 by aymohamm          #+#    #+#             */
/*   Updated: 2024/07/23 09:31:07 by aymohamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	current_time(void)
{
	struct timeval	time_now;

	gettimeofday(&time_now, NULL);
	return (time_now.tv_sec * 1000LL + time_now.tv_usec / 1000);
}

void	philo_sleep(t_table *table, time_t duration)
{
	time_t	time_wake_up;

	time_wake_up = current_time() + duration;
	while (current_time() < time_wake_up)
	{
		if (dinner_finished(table))
			break ;
		usleep(100);
	}
}

int	get_time_ms(int start_dining)
{
	return (current_time() - start_dining);
}

bool	dinner_finished(t_table *table)
{
	bool	result;

	result = false;
	pthread_mutex_lock(&table->dinner_end_lock);
	if (table->dinner_end == true)
		result = true;
	pthread_mutex_unlock(&table->dinner_end_lock);
	return (result);
}

long	manage_thinking_time(t_philo *philo)
{
	long	time_to_think;

	pthread_mutex_lock(&philo->general_meal_lock);
	time_to_think = (philo->table->time_to_die - (current_time()
				- philo->last_meal) - philo->table->time_to_eat) / 2;
	pthread_mutex_unlock(&philo->general_meal_lock);
	if (time_to_think > 500)
		return (200);
	else
		return (1);
}
