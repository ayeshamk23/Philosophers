/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aymohamm <aymohamm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 09:06:49 by aymohamm          #+#    #+#             */
/*   Updated: 2024/07/31 18:10:31 by aymohamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	free_mutex(t_table *table);

void	*free_table(t_table *table)
{
	int	i;

	if (!table)
		return (NULL);
	free_mutex(table);
	if (table->fork_lock != NULL)
		free(table->fork_lock);
	if (table->philo)
	{
		i = 0;
		while (i < table->nbr_philo)
		{
			free(table->philo[i]);
			i++;
		}
		free(table->philo);
	}
	free(table);
	return (NULL);
}

static void	free_mutex(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->nbr_philo)
	{
		pthread_mutex_destroy(&table->philo[i]->general_meal_lock);
		pthread_mutex_destroy(&table->fork_lock[i]);
		i++;
	}
	pthread_mutex_destroy(&table->dinner_end_lock);
	pthread_mutex_destroy(&table->log_lock);
}
