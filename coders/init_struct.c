/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alebaron <alebaron@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 09:51:49 by alebaron          #+#    #+#             */
/*   Updated: 2026/04/16 12:20:21 by alebaron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static t_coder	*create_coder(int num, t_dongle *d_left, t_dongle *d_right);

t_args	*init_args(char **argv)
{
	t_args	*struc_args;

	struc_args = malloc(sizeof(t_args));
	if (!struc_args)
		return (NULL);
	struc_args->number_of_coders = atoi(argv[0]);
	struc_args->time_to_burnout = atoi(argv[1]);
	struc_args->time_to_compile = atoi(argv[2]);
	struc_args->time_to_debug = atoi(argv[3]);
	struc_args->time_to_refactor = atoi(argv[4]);
	struc_args->number_of_compiles_required = atoi(argv[5]);
	struc_args->dongle_cooldown = atoi(argv[6]);
	struc_args->scheduler = argv[7];
	return (struc_args);
}

t_coder	**init_coders(t_args *args)
{
	t_coder	**coders;
	int		i;

	coders = malloc(sizeof(t_coder) * args->number_of_coders);
	if (!coders)
		return (NULL);
	i = 0;
	while (i < args->number_of_coders)
	{
		coders[i] = create_coder(i);
		i++;
	}
	
	return (coders);
}

static t_coder	*create_coder(int num, t_dongle *d_left, t_dongle *d_right)
{
	t_coder		*coder;
	pthread_t	tid1;

	coder = malloc(sizeof(t_coder));
	coder->number = num;
	coder->left_dongle = d_left;
	coder->right_dongle = d_right;
	coder->thread = tid1;
}
