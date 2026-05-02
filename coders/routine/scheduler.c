/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scheduler.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alebaron <alebaron@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/01 15:14:53 by alebaron          #+#    #+#             */
/*   Updated: 2026/05/02 12:22:48 by alebaron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../codexion.h"

void	fifo(t_coder *coder)
{
	wait_for_dongle_fifo(coder);
	compile(coder);
	free_dongle(coder);
	pthread_mutex_lock(&coder->data->queue_ctrl.mutex);
	remove_first_one(&coder->data->queue_ctrl);
	pthread_mutex_unlock(&coder->data->queue_ctrl.mutex);
}

void	edf(t_coder *coder)
{
	wait_for_dongle_edf(coder);
	compile(coder);
	free_dongle(coder);
	pthread_mutex_lock(&coder->data->queue_ctrl.mutex);
	remove_first_one(&coder->data->queue_ctrl);
	pthread_mutex_unlock(&coder->data->queue_ctrl.mutex);
}
