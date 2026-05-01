/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fifo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alebaron <alebaron@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/30 10:32:45 by alebaron          #+#    #+#             */
/*   Updated: 2026/05/01 11:25:36 by alebaron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../codexion.h"

static void	add_queue(t_coder *coder);

void fifo(t_coder *coder, char *action)
{
	pthread_mutex_lock(&coder->data->queue.mutex);
	if (strcmp(action, ADD_QUEUE) == 0)
	{
		add_and_manage_queue(coder);
	}
	else
	{
		remove_queue(coder);
	}
	pthread_mutex_unlock(&coder->data->queue.mutex);
	return (0);
}

static void	add_and_manage_queue(t_coder *coder)
{
	t_codexion	*data;
	
	data = coder->data;
	add_fifo_queue(&data->queue, coder);
	
}
