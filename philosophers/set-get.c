/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set-get.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfuente- <mfuente-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 16:16:45 by mfuente-          #+#    #+#             */
/*   Updated: 2024/04/13 18:17:50 by mfuente-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosofer.h"

int	set_bool(t_mtx *mutex, bool *dest, bool value)
{
	if (mutex_handle(mutex, LOCK) == 1)
		return (1);
	*dest = value;
	if (mutex_handle(mutex, UNLOCK) == 1)
		return (1);
	return (0);
}

bool	get_bool(t_mtx *mutex, bool *value)
{
	bool	ret;

	mutex_handle(mutex, LOCK);
	ret = *value;
	mutex_handle(mutex, UNLOCK);
	return (ret);
}

void	set_long(t_mtx *mutex, long *dest, long value)
{
	mutex_handle(mutex, LOCK);
	*dest = value;
	mutex_handle(mutex, UNLOCK);
}

long	get_long(t_mtx *mutex, long *value)
{
	long	ret;

	mutex_handle(mutex, LOCK);
	ret = *value;
	mutex_handle(mutex, UNLOCK);
	return (ret);
}

bool	simulation_finished(t_table *table)
{
	return (get_bool(&table->mutex_table, &table->end_simulation));
}
