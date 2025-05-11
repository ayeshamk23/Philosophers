/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aymohamm <aymohamm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 14:05:03 by aymohamm          #+#    #+#             */
/*   Updated: 2024/07/31 20:25:51 by aymohamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	check_valid2(int argc, char **argv);
static bool	is_only_digit(char *str);

bool	check_args(int argc, char **argv)
{
	if (argc != 5 && argc != 6)
	{
		printf("Error: check arguments!");
		return (false);
	}
	if (check_valid2(argc, argv) == false)
		return (false);
	return (true);
}

static bool	check_valid2(int argc, char **argv)
{
	int		i;
	long	value;

	value = 0;
	i = 1;
	while (i < argc)
	{
		if (is_only_digit(argv[i]) == false)
		{
			printf("Invalid input in [%s]. Only digit accepted.\n", argv[i]);
			return (false);
		}
		value = check_valid(argv[i]);
		if (value < 0 || value > LONG_MAX)
		{
			printf("Invalid input in [%ld]. Negative or so long.\n", value);
			return (false);
		}
		i++;
	}
	return (true);
}

bool	is_param_valid(t_table *table)
{
	if (table->nbr_philo > 200 || table->nbr_philo == 0)
	{
		printf("Error: invalid input");
		return (false);
	}
	if (table->time_to_die < 60 || table->time_to_eat < 60
		|| table->time_to_sleep < 60)
	{
		printf("Error: wrong input, NOTE: IT MUST BE GREATER THAN 60\n");
		return (false);
	}
	return (true);
}

static bool	is_only_digit(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_isdigit(str[i]) == false)
			return (false);
		i++;
	}
	return (true);
}
