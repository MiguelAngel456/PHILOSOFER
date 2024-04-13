/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfuente- <mfuente-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 16:03:38 by mfuente-          #+#    #+#             */
/*   Updated: 2024/04/13 17:57:12 by mfuente-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosofer.h"

static int	isdigit(char **argv)
{
	int		i;
	int		k;
	char	*cero;

	i = 1;
	cero = "0";
	while (argv[i] != NULL)
	{
		k = 0;
		if (argv[i] == cero)
			return (1);
		while (argv[i][k] != '\0')
		{
			if (argv[i][k] < '0' || argv[i][k] > '9')
				return (1);
			k++;
		}
		i++;
	}
	return (0);
}

int	errors(int argc, char **argv)
{
	if (argc != 5 && argc != 6)
	{
		printf("Error, en el numero de argumentos");
		return (1);
	}
	if (isdigit(argv) == 1)
	{
		printf("Error, los argumentos tienen que ser numericos");
		return (1);
	}
	return (0);
}
