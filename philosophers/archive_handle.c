/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   archive_handle.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfuente- <mfuente-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 18:04:22 by mfuente-          #+#    #+#             */
/*   Updated: 2024/04/13 18:05:58 by mfuente-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosofer.h"

static int	handle_thread_error(int status, t_opmutex opcode)
{
	if (0 == status)
		return (0);
	if (EAGAIN == status)
		return (printf("No resources to create another thread"), 1);
	else if (EPERM == status)
		return (printf("The caller does not have appropriate permission\n"), 1);
	else if (EINVAL == status && CREATE == opcode)
		return (printf("The value specified by attr is invalid."), 1);
	else if (EINVAL == status && (JOIN == opcode || DETACH == opcode))
		return (printf("The value specified by thread is not joinable\n"), 1);
	else if (ESRCH == status)
	{
		printf("No thread could be found corresponding to that"
			"specified by the given thread ID, thread.");
		return (1);
	}
	else if (EDEADLK == status)
	{
		printf("A deadlock was detected or the value of"
			"thread specifies the calling thread.");
		return (1);
	}
	return (0);
}

int	mutex_handle(t_mtx *mutex, t_opmutex opmutex)
{
	if (LOCK == opmutex)
	{
		if (pthread_mutex_lock(mutex) == 1)
			return (1);
		return (0);
	}
	else if (UNLOCK == opmutex)
	{
		if (pthread_mutex_unlock(mutex) == 1)
			return (1);
		return (0);
	}
	else if (INIT == opmutex)
	{
		if (pthread_mutex_init(mutex, NULL) == 1)
			return (1);
		return (0);
	}
	else if (DESTROY == opmutex)
	{
		if (pthread_mutex_destroy(mutex) == 1)
			return (1);
		return (0);
	}
	return (0);
}

int	thread_handle(pthread_t *thread, void *(*foo)(void *),
		void *data, t_opmutex opcode)
{
	if (CREATE == opcode)
	{
		if (handle_thread_error(pthread_create(thread, NULL, foo, data)
				, opcode) == 1)
			return (1);
		return (0);
	}
	else if (JOIN == opcode)
	{
		if (handle_thread_error(pthread_join(*thread, NULL), opcode) == 1)
			return (1);
		return (0);
	}
	else if (DETACH == opcode)
	{
		if (handle_thread_error(pthread_detach(*thread), opcode) == 1)
			return (1);
		return (0);
	}
	else
		return (1);
}
