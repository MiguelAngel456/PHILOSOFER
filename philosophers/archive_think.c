/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   archive_think.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfuente- <mfuente-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 15:34:02 by mfuente-          #+#    #+#             */
/*   Updated: 2024/04/13 17:54:59 by mfuente-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosofer.h"

void	think(t_philo *philo, bool pre_simulation)
{
	long	t_eat;
	long	t_sleep;
	long	t_think;

	if (!pre_simulation)
		write_status(THINKING, philo);
	if (philo->table->nphilo % 2 == 0)
		return ;
	t_eat = philo->table->teat;
	t_sleep = philo->table->tsleep;
	t_think = (t_eat * 2) - t_sleep;
	if (t_think < 0)
		t_think = 0;
	precise_usleep(t_think * 0.42, philo->table);
}

static bool	philo_died(t_philo *philo)
{
	long	elapsed;
	long	t_to_die;

	if (get_bool(&philo->philo_mutex, &philo->is_full))
		return (false);
	elapsed = get_time(MILLISECOND)
		- get_long(&philo->philo_mutex, &philo->time_last_eat);
	t_to_die = philo->table->tdeath / 1000;
	if (elapsed > t_to_die)
		return (true);
	return (false);
}

void	*monitor_dinner(void *data)
{
	int		i;
	t_table	*table;

	table = (t_table *) data;
	while (!all_threads_running(&table->mutex_table,
			&table->thread_running, table->nphilo))
		;
	while (!simulation_finished(table))
	{
		i = -1;
		while (((++i) < table->nphilo) && !simulation_finished(table))
		{
			if (philo_died(&table->philos[i]))
			{
				set_bool(&table->mutex_table, &table->end_simulation, true);
				write_status(DIED, table->philos + i);
			}
		}
	}
	return (NULL);
}

void	wait_all_theards(t_table *table)
{
	while (get_bool(&table->mutex_table, &table->all_thread_ready))
		;
}

void	increase_long(t_mtx *mutex, long *value)
{
	mutex_handle(mutex, LOCK);
	(*value)++;
	mutex_handle(mutex, UNLOCK);
}
