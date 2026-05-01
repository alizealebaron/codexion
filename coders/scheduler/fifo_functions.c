/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fifo_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alebaron <alebaron@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/30 13:12:42 by alebaron          #+#    #+#             */
/*   Updated: 2026/05/01 11:23:04 by alebaron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../codexion.h"

void	add_fifo_queue(t_queue_controller *queue, t_coder *coder)
{
	t_queue	*new_chain;
	t_queue	*last;

	new_chain = malloc(sizeof(t_queue));
	new_chain->coder = coder;
	new_chain->next = NULL;
	last = get_last_coder(queue);
	if (queue->first == NULL)
		queue->first == new_chain;
	else
	{
		last->next = new_chain;
	}
}

t_queue	*get_last_coder(t_queue_controller *queue)
{
	t_queue	*last;

	last = queue->first;
	while (last->next)
	{
		last = last->next;
	}
	return (last);
}