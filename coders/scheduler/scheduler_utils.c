/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scheduler_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alebaron <alebaron@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/30 11:07:16 by alebaron          #+#    #+#             */
/*   Updated: 2026/05/01 12:12:16 by alebaron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../codexion.h"

void	debug(t_coder *coder)
{
	print_message(coder->data, coder->number, LOG_DEBUGGING);
	usleep(coder->data->time_to_debug * 1000);
}

void	refactoring(t_coder *coder)
{
	print_message(coder->data, coder->number, LOG_REFACTOR);
	coder->compiles_done++;
	usleep(coder->data->time_to_refactor * 1000);
}

void	update_coder_compile(t_coder *coder)
{
	pthread_mutex_lock(&coder->lock);
	coder->last_compile_time = get_time();
	pthread_mutex_unlock(&coder->lock);
}

