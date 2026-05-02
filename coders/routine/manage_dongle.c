/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_dongle.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alebaron <alebaron@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/01 14:55:29 by alebaron          #+#    #+#             */
/*   Updated: 2026/05/02 12:22:05 by alebaron         ###   ########.fr       */
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
	(void) coder;
}

int	take_dongle(t_coder *coder)
{
	pthread_mutex_lock(&coder->right_dongle->lock);
	if (coder->right_dongle->cooldown <= get_time())
	{
		pthread_mutex_lock(&coder->left_dongle->lock);
		if (coder->left_dongle->cooldown <= get_time())
		{
			print_message(coder->data, coder->number, LOG_TAKE_DONGLE);
			print_message(coder->data, coder->number, LOG_TAKE_DONGLE);
			return (1);
		}
		pthread_mutex_unlock(&coder->left_dongle->lock);
	}
	pthread_mutex_unlock(&coder->right_dongle->lock);
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
	long long time;

	time = get_time();
	coder->left_dongle->cooldown = time + coder->data->dongle_cooldown;
	coder->right_dongle->cooldown = time + coder->data->dongle_cooldown;
	pthread_mutex_unlock(&coder->left_dongle->lock);
	pthread_mutex_unlock(&coder->right_dongle->lock);
	if (strcmp(coder->data->scheduler, "fifo") == 0)
	{
		pthread_mutex_lock(&coder->data->queue_ctrl.mutex);
		pthread_cond_broadcast(&coder->data->queue_ctrl.cond);
		pthread_mutex_unlock(&coder->data->queue_ctrl.mutex);
	}
}
