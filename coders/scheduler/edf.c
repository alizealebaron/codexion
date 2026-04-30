/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alebaron <alebaron@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/30 10:32:38 by alebaron          #+#    #+#             */
/*   Updated: 2026/04/30 11:18:15 by alebaron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../codexion.h"

void edf(t_coder *coder)
{
	while (coder->data->is_sim_active == 0 && coder->has_finished != 1)
	{
		// compile_edf(coder);
		debug(coder);
		refactoring(coder);
	}
}
