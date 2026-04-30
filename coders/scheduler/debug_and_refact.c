/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_and_refact.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alebaron <alebaron@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/30 11:07:16 by alebaron          #+#    #+#             */
/*   Updated: 2026/04/30 11:10:19 by alebaron         ###   ########.fr       */
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
