/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aymohamm <aymohamm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 08:39:27 by aymohamm          #+#    #+#             */
/*   Updated: 2024/07/23 09:32:58 by aymohamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	get_status(t_philo *philo, t_state state)
{
	pthread_mutex_lock(&philo->table->dinner_end_lock);
	if (philo->table->dinner_end)
	{
		pthread_mutex_unlock(&philo->table->dinner_end_lock);
		return ;
	}
	pthread_mutex_unlock(&philo->table->dinner_end_lock);
	pthread_mutex_lock(&philo->table->log_lock);
	printf("%i %ld %s\n",
		get_time_ms(philo->table->start_dining),
		philo->id + 1,
		get_status_message(state));
	pthread_mutex_unlock(&philo->table->log_lock);
}

const char	*get_status_message(t_state status)
{
	if (status == PHILO_EATING)
		return ("is eating");
	else if (status == PHILO_LEFT_FORK || status == PHILO_RIGHT_FORK)
		return ("has taken a fork");
	else if (status == PHILO_SLEEPING)
		return ("is sleeping");
	else if (status == PHILO_THINKING)
		return ("is thinking");
	else if (status == PHILO_DEAD)
		return ("died");
	else
		return ("");
}
