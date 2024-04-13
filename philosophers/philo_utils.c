/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfuente- <mfuente-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 10:46:52 by mfuente-          #+#    #+#             */
/*   Updated: 2024/04/13 18:06:12 by mfuente-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosofer.h"

static int	ignorar_espacios(int cont, char *str)
{
	while (str[cont] == '\t' || str[cont] == '\n'
		|| str[cont] == '\v' || str[cont] == '\f'
		|| str[cont] == '\r' || str[cont] == ' ')
		cont++;
	return (cont);
}

int	ft_atoi(const char *str)
{
	int		cont;
	int		num_final;
	char	*original;
	char	signo;

	cont = 0;
	num_final = 0;
	original = (char *)str;
	cont = ignorar_espacios(cont, original);
	signo = str[cont];
	if ((signo != '+' && signo != '-') && (signo < '0' && signo > '9'))
		return (0);
	if ((signo == '+' || signo == '-'))
		cont++;
	while (str[cont] != '\0' && (str[cont] >= '0' && str[cont] <= '9'))
	{
		num_final = num_final * 10 + (str[cont] - '0');
		cont++;
	}
	if (signo == '-')
		num_final = num_final * -1;
	return (num_final);
}

long	ft_atol(const char *str)
{
	int		cont;
	long	num_final;
	char	*original;
	char	signo;

	cont = 0;
	num_final = 0;
	original = (char *)str;
	cont = ignorar_espacios(cont, original);
	signo = str[cont];
	if ((signo != '+' && signo != '-') && (signo < '0' && signo > '9'))
		return (0);
	if ((signo == '+' || signo == '-'))
		cont++;
	while (str[cont] != '\0' && (str[cont] >= '0' && str[cont] <= '9'))
	{
		num_final = num_final * 10 + (str[cont] - '0');
		cont++;
	}
	if (signo == '-')
		num_final = num_final * -1;
	return (num_final);
}

// FUNCION QUE ME AYUDARA A ESCRIBIR 
void	write_status(t_philo_status status, t_philo *philo)
{
	long	time;

	time = get_time(MILLISECOND) - philo->table->start_simulation;
	if ((TAKE_LEFT_FORK == status || TAKE_RIGTH_FORK == status)
		&& !simulation_finished(philo->table))
		printf("%ld\t%d has taken a fork\n", time, philo->id);
	else if (get_bool(&philo->philo_mutex, &philo->is_full))
		return ;
	mutex_handle(&philo->table->write_lock, LOCK);
	if (EATING == status && !simulation_finished(philo->table))
		printf("%ld\t%d is eating\n", time, philo->id);
	else if (SLEEPING == status && !simulation_finished(philo->table))
		printf("%ld\t%d is sleeping\n", time, philo->id);
	else if (THINKING == status && !simulation_finished(philo->table))
		printf("%ld\t%d is thinking\n", time, philo->id);
	else if (DIED == status)
		printf("%ld\t%d died\n", time, philo->id);
	mutex_handle(&philo->table->write_lock, UNLOCK);
}
