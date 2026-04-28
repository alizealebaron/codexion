/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alebaron <alebaron@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 14:10:54 by alebaron          #+#    #+#             */
/*   Updated: 2026/04/28 11:38:36 by alebaron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../codexion.h"

int	exit_program(void)
{
	char	*end_message;

	end_message = "Invalid arguments.\nTemplate: ./codexion <number_of_coders> "
		"<time_to_burnout> <time_to_compile> <time_to_debug> <time_to_refactor>"
		" <number_of_compiles_required> <dongle_cooldown> <scheduler>\n"
		"Example : ./codexion 4 800 200 200 200 5 10 fifo\n";
	write(2, end_message, strlen(end_message));
	return (1);
}

void	free_all(t_codexion *args)
{
	if (!args)
		return ;
	free(args->dongles);
	free(args->coders);
	free(args);
}

void destroy_threads_and_mutex(t_codexion *data)
{
	int	i;

	i = 0;
	while (i < data->number_of_coders)
	{
		pthread_mutex_destroy(&data->dongles[i].lock);
	}
	
}
