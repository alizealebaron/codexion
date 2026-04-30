/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alebaron <alebaron@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 13:28:06 by alebaron          #+#    #+#             */
/*   Updated: 2026/04/30 16:23:29 by alebaron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../codexion.h"

void	print_message(t_codexion *data, int num_coder, char *action)
{
	pthread_mutex_lock(&data->print_mutex);

	if (num_coder == -1 && strcmp(action, LOG_SUCCESS) == 0)
		printf(action, data->nb_compiles_required);
	else if (strcmp(action, LOG_BURNS_OUT) == 0)
		printf(action, (get_time() - data->start_time), num_coder);
	else
		printf(action, (get_time() - data->start_time), num_coder);
	pthread_mutex_unlock(&data->print_mutex);
}
