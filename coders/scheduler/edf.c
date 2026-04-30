/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alebaron <alebaron@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/30 10:32:38 by alebaron          #+#    #+#             */
/*   Updated: 2026/04/30 15:39:07 by alebaron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../codexion.h"

void edf(t_coder *coder)
{
	int	has_finished;

	while (is_simulation_active(coder->data) == 1)
	{
		pthread_mutex_lock(&coder->lock);
		has_finished = coder->has_finished;
		pthread_mutex_unlock(&coder->lock);
		if (has_finished == 1)
			break ;
		// compile_edf(coder);
		debug(coder);
		refactoring(coder);
	}
}
