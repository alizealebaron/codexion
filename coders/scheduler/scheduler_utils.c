/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scheduler_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alebaron <alebaron@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/30 11:07:16 by alebaron          #+#    #+#             */
/*   Updated: 2026/05/01 11:28:23 by alebaron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../codexion.h"

void	debug(t_coder *coder)
{
	print_message(coder->data, coder->number, LOG_DEBUGGING);
	usleep(coder->data->time_to_debug);
}

void	refactoring(t_coder *coder)
{
	print_message(coder->data, coder->number, LOG_REFACTOR);
	usleep(coder->data->time_to_refactor);
}

void	update_coder_compile(t_coder *coder)
{
	pthread_mutex_lock(&coder->lock);
	coder->compiles_done++;
	coder->last_compile_time = get_time();
	if (coder->compiles_done >= coder->data->nb_compiles_required)
		coder->has_finished = 1;
	pthread_mutex_unlock(&coder->lock);
}

int	take_dongle(t_coder *coder)
{
	
}
