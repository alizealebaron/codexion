/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_mutex.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alebaron <alebaron@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 17:00:50 by alebaron          #+#    #+#             */
/*   Updated: 2026/05/04 17:47:30 by alebaron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../codexion.h"

void	destroy_mutex(t_codexion *data)
{
	int	i;

	i = 0;
	while (i < data->number_of_coders)
	{
		pthread_mutex_destroy(&data->dongles[i].lock);
		pthread_mutex_destroy(&data->coders[i].lock);
		i++;
	}
	pthread_mutex_destroy(&data->main_mutex);
	pthread_mutex_destroy(&data->print_mutex);
	pthread_mutex_destroy(&data->queue_ctrl.mutex);
	pthread_mutex_destroy(&data->heap->mutex);
	pthread_cond_destroy(&data->queue_ctrl.cond);
	pthread_cond_destroy(&data->heap->cond);
}
