/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alebaron <alebaron@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/01 14:37:37 by alebaron          #+#    #+#             */
/*   Updated: 2026/05/01 15:33:17 by alebaron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../codexion.h"

t_queue	*get_last_one(t_queue_controller *ctrl)
{
	t_queue	*last;

	last = ctrl->first;
	while (last->next)
	{
		last = last->next;
	}
	return (last);
}

void	queue_add_back(t_queue_controller *ctrl, t_coder *new_coder)
{
	t_queue	*new_thing;

	new_thing = malloc(sizeof(t_queue));
	new_thing->coder = new_coder;
	new_thing->next = NULL;
	if (ctrl->first == NULL)
		ctrl->first = new_thing;
	else
		get_last_one(ctrl)->next = new_thing;
}

void	remove_first_one(t_queue_controller *ctrl)
{
	t_queue	*next;

	if (ctrl->first == NULL)
		return ;
	next = ctrl->first->next;
	free(ctrl->first);
	ctrl->first = next;
}
