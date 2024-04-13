/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   archive_dinner.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfuente- <mfuente-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 14:58:00 by mfuente-          #+#    #+#             */
/*   Updated: 2024/04/13 17:26:23 by mfuente-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosofer.h"

void	de_synchronize_philos(t_philo *philo)
{
	if (philo->table->nphilo % 2 == 0)
	{
		if (philo->id % 2 == 0)
			precise_usleep(3e4, philo->table);
	}
	else
	{
		if (philo->id % 2)
			think(philo, true);
	}
}

void	*dinner_simulation(void *data)
{
	t_philo	*philo;

	philo = (t_philo *) data;
	wait_all_threads(philo->table);
	set_long(&philo->philo_mutex, &philo->time_last_eat, get_time(MILLISECOND));
	increase_long(&philo->table->mutex_table,
		&philo->table->thread_running);
	de_synchronize_philos(philo);
	while (!simulation_finished(philo->table))
	{
		if (get_bool(&philo->philo_mutex, &philo->is_full))
			break ;
		eat(philo);
		write_status(SLEEPING, philo);
		precise_usleep(philo->table->tsleep, philo->table);
		think(philo, false);
	}
	return (NULL);
}

void	*lone_philo(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	wait_all_threads(philo->table);
	set_long(&philo->philo_mutex, &philo->time_last_eat, get_time(MILLISECOND));
	increase_long(&philo->table->mutex_table,
		&philo->table->thread_running);
	write_status(TAKE_LEFT_FORK, philo);
	while (!simulation_finished(philo->table))
		precise_usleep(200, philo->table);
	return (NULL);
}

void	start_dinner(t_table *str_table)
{
	int			i;

	i = -1;
	if (0 == str_table->numeat)
		return ;
	else if (1 == str_table->nphilo)
		thread_handle(&str_table->philos[0].thread_id, lone_philo,
			&str_table->philos[0], CREATE);
	else
	{
		while (++i < str_table->nphilo)
		{
			thread_handle(&str_table->philos[i].thread_id, dinner_simulation,
				&str_table->philos[i], CREATE);
		}
	}
	thread_handle(&str_table->monitor, monitor_dinner, str_table, CREATE);
	str_table->start_simulation = get_time(MILLISECOND);
	set_bool(&str_table->mutex_table, &str_table->all_thread_ready, true);
	i = -1;
	while (++i < str_table->nphilo)
		thread_handle(&str_table->philos[i].thread_id, NULL, NULL, JOIN);
	set_bool(&str_table->mutex_table, &str_table->end_simulation, true);
	thread_handle(&str_table->monitor, NULL, NULL, JOIN);
}

void	eat(t_philo *philo)
{
	mutex_handle(&philo->left_fork->fork, LOCK);
	write_status(TAKE_LEFT_FORK, philo);
	mutex_handle(&philo->right_fork->fork, LOCK);
	write_status(TAKE_RIGTH_FORK, philo);
	set_long(&philo->philo_mutex, &philo->time_last_eat, get_time(MILLISECOND));
	philo->cont_eat++;
	write_status(EATING, philo);
	precise_usleep(philo->table->teat, philo->table);
	if (philo->table->numeat > 0
		&& philo->cont_eat == philo->table->numeat)
		set_bool(&philo->philo_mutex, &philo->is_full, true);
	mutex_handle(&philo->left_fork->fork, UNLOCK);
	mutex_handle(&philo->right_fork->fork, UNLOCK);
}
