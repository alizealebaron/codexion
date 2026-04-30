/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alebaron <alebaron@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/27 13:07:06 by alebaron          #+#    #+#             */
/*   Updated: 2026/04/30 10:36:04 by alebaron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../codexion.h"

static void	end_simulation(t_codexion *data);

void    *main_routine(void *arg)
{
	t_codexion	*data;

	data = (t_codexion *)arg;
	while (is_simulation_active(data))
	{
		if(check_burnout(data))
		{
			end_simulation(data);
			return (NULL);
		}
		if (has_finished(data) == data->number_of_coders)
		{
			print_message(data, -1, LOG_SUCCESS);
			end_simulation(data);
			return (NULL);
		}
		usleep(100);
	}

	return (NULL);
}

void    *coders_routine(void *arg)
{
	t_coder *coder;
	
	coder = (t_coder *)arg;
	(void) coder;
	if (strcmp(coder->data->scheduler, "fifo") == 0)
		fifo(coder);
	else
		edf(coder);
	return (NULL);
}

static void	end_simulation(t_codexion *data)
{
	pthread_mutex_lock(&data->main_mutex);
	data->is_sim_active = 0;
	pthread_mutex_unlock(&data->main_mutex);
}
