/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosofer.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfuente- <mfuente-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 18:18:06 by mfuente-          #+#    #+#             */
/*   Updated: 2024/04/13 18:26:46 by mfuente-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOFER_H
# define PHILOSOFER_H

//LIBRERIAS NECESARIAS
# include <stdarg.h>
# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <limits.h>
# include <sys/time.h>
# include <stdbool.h>
# include <errno.h>
# include <unistd.h>

//PARA AHORARME ESCRIBIR TODO ESE TOCHO
typedef pthread_mutex_t	t_mtx;
typedef struct s_philo	t_philo;
//ESTRUCTURA PARA LAS BIFURCACION(TENEDORES)
typedef struct s_fork
{
	t_mtx	fork;
	int		fork_id;
}	t_fork;

//ESTRUCTURA CON LOS DATOS GENERALES
typedef struct s_table
{
	int			nphilo; //NUMERO DE PHILOSOFO Y TENEDORES
	int			numeat; //NUMERO DE VECES MAXIMA QUE COMA LOS PHILOS
	//PARA TERMINAR EL PROGRAMA  (ARGUMENTO OPCIONAL)
	long		tdeath; //TIEMPO PARA MORRIR SI NO COME
	long		teat; //TIEMPO QUE TARDA EN COMER
	long		tsleep; //TIEMPO QUE TIENE PARA DORMIR
	long		start_simulation; //MOMENTO EN EL QUE EMPIEZA LA SIMULACION
	long		thread_running; //PARA SINCRONIZAR
	bool		all_thread_ready; //PARA SABER SI TODOS LOS
	//HILOS(PHILOSOFOS) ESTAN LISTOS Y SINCRONIZADOS
	bool		end_simulation; //CUANDO UNO MUERE O CUANDO ESTEN LLENOS
	pthread_t	monitor; //PARA IR MONITORIZANDO LOS TENEDORES, ETC
	t_philo		*philos; //LOS HILOS DE LOS PHILOSOFOS
	t_mtx		mutex_table; //PARA NO LEER LA TABLA
	t_mtx		write_lock; //PARA LEER LOS DATOS CORRECTAMENTE
	t_fork		*froks; //ARRAY DE TENEDORES
}	t_table;

//ESTRUCTURA CON LOS DATOS DEL PHILOSOFO
struct s_philo
{
	int			id; //ID
	int			cont_eat; //CONTADOR DE CANTIDA DE COMIDAS QUE HA HECHO
	bool		is_full; //SI YA ESTA LLENO
	long		time_last_eat; //MOMENTO DE LA ULTIMA COMIDA
	t_fork		*left_fork; //TENEDOR DE LA IZQUIERDA
	t_fork		*right_fork; //TENEDOR DE LA DERECHA
	pthread_t	thread_id; //HILO DEL PHILOSOFO
	t_mtx		philo_mutex; // MUTEX CORRESPONDIENTE A DICHO PHILOSOFO
	t_table		*table; //PARA QUE PUEDA TENER ACCESO A LOS DATOS GENERALES
};

//ENUMERACIONES PARA FACILIRAR EL CODIGO
typedef enum e_opmutex
{
	LOCK,
	UNLOCK,
	INIT,
	DESTROY,
	CREATE,
	JOIN,
	DETACH,
}	t_opmutex;

typedef enum e_time_code
{
	SECONDS,
	MILLISECOND,
	MICROSECOND,
}		t_time_code;

typedef enum e_status
{
	EATING,
	SLEEPING,
	THINKING,
	TAKE_LEFT_FORK,
	TAKE_RIGTH_FORK,
	DIED,
}			t_philo_status;

//FUNCIONES
int		errors(int argc, char **argv);
int		ft_atoi(const char *str);
int		mutex_handle(t_mtx *mutex, t_opmutex opmutex);
void	*ft_calloc(size_t count, size_t size);
long	get_time(int time_code);
long	ft_atol(const char *str);
int		thread_handle(pthread_t *thread,
			void *(*foo)(void *), void *data, t_opmutex opcode);
int		set_bool(t_mtx *mutex, bool *dest, bool value);
bool	get_bool(t_mtx *mutex, bool *value);
void	set_long(t_mtx *mutex, long *dest, long value);
long	get_long(t_mtx *mutex, long *value);
bool	simulation_finished(t_table *table);
void	precise_usleep(long usec, t_table *str_table);
void	write_status(t_philo_status status, t_philo *philo);
void	eat(t_philo *philo);
void	think(t_philo *philo, bool pre_simulation);
void	*dinner_simulation(void *data);
void	*monitor_dinner(void *data);
void	start_dinner(t_table *str_table);
void	clean(t_table *table);
void	increase_long(t_mtx *mutex, long *value);
bool	all_threads_running(t_mtx *mutex, long *threads, long philo);
void	wait_all_threads(t_table *table);
int		parse_imput(t_table *str_table, char **argv);
#endif