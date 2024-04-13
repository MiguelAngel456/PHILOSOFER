/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosofer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfuente- <mfuente-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 12:07:50 by mfuente-          #+#    #+#             */
/*   Updated: 2024/04/13 18:17:30 by mfuente-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosofer.h"

void	*thread_function(void *arg)
{
	arg++;
	return (NULL);
}

//ASIGNA LOS TENEDORES Y EVITA LOS BLOQUEOS
//TIENE EN CUENTA SI ES PAR O IMPAR
//LA FORMULA ESA ES PARA SI ESTA EN EL ULTIMO QUE 
//ME COJA EL TENEDOR 0 EN VEZ DE COJER UNO INEXISTENTE
static void	assign_fork(t_philo *str_philo, t_fork *str_fork, int i)
{
	int	nphilo;

	nphilo = str_philo->table->nphilo;
	if (str_philo->id % 2 == 0)
	{
		str_philo->left_fork = &str_fork[(i + 1) % nphilo];
		str_philo->right_fork = &str_fork[i];
	}
	else
	{
		str_philo->left_fork = &str_fork[i];
		str_philo->right_fork = &str_fork[(i + 1) % nphilo];
	}
}

//INIZIALIZA PARTE DE LOS DATOS DE LOS PHILOSOFOS
static void	philo_init(t_table *str_table)
{
	int		i;
	t_philo	*str_philo;

	i = -1;
	while ((++i) < str_table->nphilo)
	{
		str_philo = str_table->philos + i;
		str_philo->id = i + 1;
		str_philo->cont_eat = 0;
		str_philo->is_full = false;
		mutex_handle(&str_philo->philo_mutex, INIT);
		str_philo->table = str_table;
		assign_fork(str_philo, str_table->froks, i);
	}
}

static int	data_init(t_table *str_table)
{
	int	i;

	i = -1;
	str_table->end_simulation = false;
	str_table->all_thread_ready = false;
	str_table->thread_running = 0;
	str_table->philos = malloc (sizeof(t_philo) * str_table->nphilo);
	if (str_table->philos == NULL)
		return (1);
	str_table->froks = malloc (sizeof(t_fork) * str_table->nphilo);
	if (str_table->froks == NULL)
		return (1);
	mutex_handle(&str_table->write_lock, INIT);
	mutex_handle(&str_table->mutex_table, INIT);
	while ((++i) < str_table->nphilo)
	{
		if (mutex_handle(&str_table->froks[i].fork, INIT) == 1)
			return (1);
		str_table->froks[i].fork_id = i;
	}
	philo_init(str_table);
	return (0);
}

int	main(int argc, char **argv)
{
	t_table	str_table;
	char	*aux;

	if (errors(argc, argv))
	{
		return (1);
	}
	else
	{
		aux = "1";
		if (parse_imput(&str_table, argv) == 1)
			return (1);
		data_init(&str_table);
		if (argv[1][0] == aux[0] && argv[1][1] == '\0')
		{
			printf("%d\t%d has taken a fork\n", 0,
				str_table.philos[0].id);
			printf("%d\t%d died\n", ft_atoi(argv[2]) + 1,
				str_table.philos[0].id);
			return (1);
		}
		start_dinner(&str_table);
		clean(&str_table);
	}
	return (0);
}
