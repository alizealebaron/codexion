/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alebaron <alebaron@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 09:51:49 by alebaron          #+#    #+#             */
/*   Updated: 2026/04/28 14:42:47 by alebaron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../codexion.h"

static t_dongle	*init_dongle(int nb_dongle);
static t_coder	*init_coders(int nb_coders);
static void	init_coders_dongle(int nb_coders, t_codexion *codexion);

t_codexion	*init_data(char **argv)
{
	t_codexion	*data;

	data = malloc(sizeof(*data));
	if (!data)
		return (NULL);
	pthread_create(&data->main_thread, NULL, main_routine, data);
	pthread_mutex_init(&data->main_mutex, NULL);
	pthread_mutex_init(&data->print_mutex, NULL);
	data->number_of_coders = atoi(argv[0]);
	data->time_to_burnout = atoi(argv[1]);
	data->time_to_compile = atoi(argv[2]);
	data->time_to_debug = atoi(argv[3]);
	data->time_to_refactor = atoi(argv[4]);
	data->nb_compiles_required = atoi(argv[5]);
	data->dongle_cooldown = atoi(argv[6]);
	data->scheduler = argv[7];
	data->dongles = init_dongle(data->number_of_coders);
	data->coders = init_coders(data->number_of_coders);
	init_coders_dongle(data->number_of_coders, data);
	data->is_sim_active = 1;
	data->start_time = get_time();
	return (data);
}

static t_dongle	*init_dongle(int nb_dongle)
{
	t_dongle	*dongles;
	int			i;

	dongles = malloc(sizeof(t_dongle) * nb_dongle);
	if (!dongles)
		return (NULL);
	i = 0;
	while (i < nb_dongle)
	{
		dongles[i].id = i;
		dongles[i].cooldown = 0;
		pthread_mutex_init(&dongles[i].lock, NULL);
		i++;
	}
	return (dongles);
}

static t_coder	*init_coders(int nb_coders)
{
	t_coder	*coders;
	int		i;

	coders = malloc(sizeof(t_coder) * nb_coders);
	if (!coders)
		return (NULL);
	i = 0;
	while (i < nb_coders)
	{
		coders[i].number = i;
		coders[i].compiles_done = 0;
		coders[i].has_finished = 0;
		coders[i].last_compile_time = 0;
		pthread_create(&coders[i].thread, NULL, coders_routine, NULL);
		pthread_mutex_init(&coders[i].lock, NULL);
		i++;
	}
	return (coders);
}

static void	init_coders_dongle(int nb_coders, t_codexion *codexion)
{
	int	i;
	t_dongle	*dongles;
	t_coder		*coders;

	dongles = codexion->dongles;
	coders = codexion->coders;
	i = 0;
	while (i < nb_coders)
	{
		coders[i].left_dongle = &dongles[i];
		coders[i].right_dongle = &dongles[(i + 1) % nb_coders];
		i++;
	}
}
