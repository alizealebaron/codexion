/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alebaron <alebaron@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 14:10:24 by alebaron          #+#    #+#             */
/*   Updated: 2026/04/16 09:49:09 by alebaron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static int	is_num(char *str);
static int	check_scheduler(char *str);

int	check_arg(int argc, char **argv)
{
	int	i;

	if (argc != 9)
		return (0);
	i = 1;
	while (i < 8)
	{
		if (!(is_num(argv[i])) || atoi(argv[i]) == -1)
			return (0);
		if (atoi(argv[i]) < 1)
			return (0);
		i++;
	}
	return (check_scheduler(argv[i]));
}

static int	is_num(char *str)
{
	while (*str)
	{
		if (*str < '0' || *str > '9')
			return (0);
		str++;
	}
	return (1);
}

static int	check_scheduler(char *str)
{
	return (!(strcmp(str, "edf")) || !(strcmp(str, "fifo")));
}
