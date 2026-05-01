/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alebaron <alebaron@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 09:51:49 by alebaron          #+#    #+#             */
/*   Updated: 2026/05/01 10:42:48 by alebaron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../codexion.h"

static t_dongle	*init_dongle(int nb_dongle);
static t_coder	*init_coders(int nb_coders, t_codexion *data);

t_codexion	*init_data(char **argv)
{
	t_codexion	*data;

	data = malloc(sizeof(*data));
	if (!data)
		return (NULL);
	pthread_mutex_init(&data->main_mutex, NULL);
	pthread_mutex_init(&data->print_mutex, NULL);
	pthread_mutex_init(&data->queue.mutex, NULL);
	data->number_of_coders = atoi(argv[1]);
	data->time_to_burnout = atoi(argv[2]);
	data->time_to_compile = atoi(argv[3]);
	data->time_to_debug = atoi(argv[4]);
	data->time_to_refactor = atoi(argv[5]);
	data->nb_compiles_required = atoi(argv[6]);
	data->dongle_cooldown = atoi(argv[7]);
	data->scheduler = argv[8];
	data->is_sim_active = 1;
	data->start_time = get_time();
	data->dongles = init_dongle(data->number_of_coders);
	data->coders = init_coders(data->number_of_coders, data);
	data->queue.first = NULL;
	pthread_create(&data->main_thread, NULL, main_routine, data);
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

static t_coder	*init_coders(int nb_coders, t_codexion *data)
{
	t_coder		*coders;
	t_dongle	*dongles;
	int			i;

	dongles = data->dongles;
	coders = malloc(sizeof(t_coder) * nb_coders);
	if (!coders)
		return (NULL);
	i = 0;
	while (i < nb_coders)
	{
		coders[i].data = data;
		coders[i].number = i + 1;
		coders[i].compiles_done = 0;
		coders[i].has_finished = 0;
		coders[i].last_compile_time = get_time();
		coders[i].left_dongle = &dongles[i];
		coders[i].right_dongle = &dongles[(i + 1) % nb_coders];
		pthread_mutex_init(&coders[i].lock, NULL);
		pthread_create(&coders[i].thread, NULL, coders_routine, &coders[i]);
		i++;
	}
	return (coders);
}
