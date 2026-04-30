/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fifo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alebaron <alebaron@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/30 10:32:45 by alebaron          #+#    #+#             */
/*   Updated: 2026/04/30 11:26:09 by alebaron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../codexion.h"

void static	compile_fifo(t_coder *coder);

void fifo(t_coder *coder)
{
	while (coder->data->is_sim_active == 0 && coder->has_finished != 1)
	{
		compile_fifo(coder);
		debug(coder);
		refactoring(coder);
	}
}

void static	compile_fifo(t_coder *coder)
{
	(void) coder;
}
