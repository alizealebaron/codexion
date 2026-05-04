/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_dongle.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alebaron <alebaron@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/01 14:55:29 by alebaron          #+#    #+#             */
/*   Updated: 2026/05/04 11:31:19 by alebaron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../codexion.h"

void	wait_for_dongle_fifo(t_coder *coder)
{
	t_codexion	*data;
	
	data = coder->data;
	pthread_mutex_lock(&data->queue_ctrl.mutex);
	queue_add_back(&data->queue_ctrl, coder);
	while (is_simulation_active(data) && (data->queue_ctrl.first == NULL ||
		data->queue_ctrl.first->coder != coder || take_dongle(coder) == 0))
	{
		if (is_simulation_active(data) && data->queue_ctrl.first != NULL &&
			data->queue_ctrl.first->coder == coder)
		{
			pthread_mutex_unlock(&data->queue_ctrl.mutex);
			usleep(1000);
			pthread_mutex_lock(&data->queue_ctrl.mutex);
		}
		else
			pthread_cond_wait(&data->queue_ctrl.cond, &data->queue_ctrl.mutex);
	}
	pthread_mutex_unlock(&data->queue_ctrl.mutex);
}

void	wait_for_dongle_edf(t_coder *coder)
{
	t_codexion	*data;
	
	data = coder->data;
	pthread_mutex_lock(&data->heap->mutex);
	heap_insert(data->heap, coder);
	while (is_simulation_active(data) && (data->heap->binary_tree[0] == NULL ||
		data->heap->binary_tree[0] != coder || take_dongle(coder) == 0))
	{
		if (is_simulation_active(data) && data->heap->binary_tree[0] != NULL &&
			data->heap->binary_tree[0] == coder)
		{
			pthread_mutex_unlock(&data->heap->mutex);
			usleep(1000);
			pthread_mutex_lock(&data->heap->mutex);
		}
		else
			pthread_cond_wait(&data->heap->cond, &data->heap->mutex);
	}
	pthread_mutex_unlock(&data->heap->mutex);
}

int	take_dongle(t_coder *coder)
{
	t_dongle	*first;
	t_dongle	*second;

	get_ordered_dongles(coder, &first, &second);
	pthread_mutex_lock(&first->lock);
	if (first->cooldown <= get_time())
	{
		pthread_mutex_lock(&second->lock);
		if (second->cooldown <= get_time())
		{
			print_message(coder->data, coder->number, LOG_TAKE_DONGLE);
			print_message(coder->data, coder->number, LOG_TAKE_DONGLE);
			coder->left_dongle->is_lock = 1;
			coder->right_dongle->is_lock = 1;
			pthread_mutex_unlock(&second->lock);
			pthread_mutex_unlock(&first->lock);
			return (1);
		}
		pthread_mutex_unlock(&second->lock);
	}
	pthread_mutex_unlock(&first->lock);
	return (0);
}

int	is_dongle_free(t_dongle *dongle)
{
	pthread_mutex_lock(&dongle->lock);
	if (dongle->cooldown > get_time())
		return (0);
	pthread_mutex_unlock(&dongle->lock);
	return (1);
}

void	free_dongle(t_coder *coder)
{
	long long	time;
	t_dongle	*first;
	t_dongle	*second;

	time = get_time();
	get_ordered_dongles(coder, &first, &second);
	pthread_mutex_lock(&first->lock);
	pthread_mutex_lock(&second->lock);
	if (coder->left_dongle->is_lock)
		coder->left_dongle->is_lock = 0;
	if (coder->right_dongle->is_lock)
		coder->right_dongle->is_lock = 0;
	coder->left_dongle->cooldown = time + coder->data->dongle_cooldown;
	coder->right_dongle->cooldown = time + coder->data->dongle_cooldown;
	pthread_mutex_unlock(&second->lock);
	pthread_mutex_unlock(&first->lock);
	broadcast_queue(coder->data);
}
