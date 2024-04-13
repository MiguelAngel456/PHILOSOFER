/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfuente- <mfuente-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 18:24:32 by mfuente-          #+#    #+#             */
/*   Updated: 2024/04/13 18:16:55 by mfuente-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosofer.h"

void	clean(t_table *table)
{
	t_philo	*philo;
	int		i;

	i = -1;
	while (++i < table->nphilo)
	{
		philo = table->philos + i;
		mutex_handle(&philo->philo_mutex, DESTROY);
	}
	free(table->froks);
	free(table->philos);
}

void	wait_all_threads(t_table *table)
{
	while (!get_bool(&table->mutex_table, &table->all_thread_ready))
		;
}

bool	all_threads_running(t_mtx *mutex, long *threads, long philo)
{
	bool	ret;

	ret = false;
	mutex_handle(mutex, LOCK);
	if (*threads == philo)
		ret = true;
	mutex_handle(mutex, UNLOCK);
	return (ret);
}

int	parse_imput(t_table *str_table, char **argv)
{
	int	i;

	i = 1;
	str_table->nphilo = ft_atoi(argv[1]);
	str_table->tdeath = ft_atol(argv[2]) * 1000;
	str_table->teat = ft_atol(argv[3]) * 1000;
	str_table->tsleep = ft_atol(argv[4]) * 1000;
	if ((str_table->tdeath < 60000)
		|| (str_table->teat < 60000)
		|| (str_table->tsleep < 60000))
	{
		printf("Error, usa tiempos mayores de 60");
		return (1);
	}
	if (argv[5])
		str_table->numeat = ft_atoi(argv[5]);
	else
		str_table->numeat = -1;
	return (0);
}
