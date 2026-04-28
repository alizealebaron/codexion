/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alebaron <alebaron@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/27 13:07:06 by alebaron          #+#    #+#             */
/*   Updated: 2026/04/28 14:58:48 by alebaron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../codexion.h"

void    *main_routine(void *arg)
{
	t_codexion	*data;

	data = (t_codexion *)arg;
	while (is_simulation_active(data))
	{
		if(check_burnout(data))
		{
			// TODO: Delete tout
			return (NULL);
		}
		if (has_finished(data) == data->number_of_coders)
		{
			// TODO: Delete tout
			return (NULL);
		}
		usleep(100);
	}

	return (NULL);
}

void    *coders_routine(void *arg)
{
	for (size_t i = 0; i < strlen(arg); i++)
	{
		printf("Test\n");
	}
	printf("Coucou\n");

	return (NULL);
}
