/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alebaron <alebaron@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 10:27:07 by alebaron          #+#    #+#             */
/*   Updated: 2026/05/04 10:46:03 by alebaron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../codexion.h"

void	broadcast_queue(t_codexion *data)
{
	if (strcmp(data->scheduler, "fifo") == 0)
	{
		pthread_mutex_lock(&data->queue_ctrl.mutex);
		pthread_cond_broadcast(&data->queue_ctrl.cond);
		pthread_mutex_unlock(&data->queue_ctrl.mutex);
	}
	else
	{
		pthread_mutex_lock(&data->heap->mutex);
		pthread_cond_broadcast(&data->heap->cond);
		pthread_mutex_unlock(&data->heap->mutex);
	}
}

void	get_ordered_dongles(t_coder *coder, t_dongle **first, t_dongle **second)
{
	if (coder->left_dongle->id < coder->right_dongle->id)
	{
		*first = coder->left_dongle;
		*second = coder->right_dongle;
	}
	else
	{
		*first = coder->right_dongle;
		*second = coder->left_dongle;
	}
}