/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aymohamm <aymohamm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 09:06:54 by aymohamm          #+#    #+#             */
/*   Updated: 2024/07/31 18:02:05 by aymohamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	start_sim(t_table *table);
static void	end_sim(t_table *table);

int	main(int ac, char **av)
{
	t_table	*table;

	table = NULL;
	if (ac != 5 && ac != 6)
		return (printf("ERROR: INVALID ARGUMENTS"), 1);
	if (check_args(ac, av) == false)
		return (printf("ERROR: INVALID INPUT"), 1);
	table = prepare_table(ac, av);
	if (!table)
		return (printf("ERROR: PROBLEM IN TABLE"), 1);
	if (start_sim(table) == false)
		return (printf("ERROR: PROBLEM TO START DINNIND SIMULATION\n"), 1);
	end_sim(table);
	return (0);
}

static bool	start_sim(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->nbr_philo)
	{
		if (pthread_create(&table->philo[i]->thread_philo, NULL, &simulation,
				table->philo[i]) != 0)
			return (error_null("Error: problem creating thread", table));
		i++;
	}
	if (table->nbr_philo > 1)
	{
		if (pthread_create(&table->thread_table, NULL, &end_simulation,
				table) != 0)
			return (error_null("Error: problem creating thread", table));
	}
	return (true);
}

static void	end_sim(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->nbr_philo)
	{
		pthread_join(table->philo[i]->thread_philo, NULL);
		i++;
	}
	if (table->nbr_philo > 1)
		pthread_join(table->thread_table, NULL);
	free_table(table);
}
