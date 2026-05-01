/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_check.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alebaron <alebaron@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 14:57:28 by alebaron          #+#    #+#             */
/*   Updated: 2026/05/01 12:03:31 by alebaron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../codexion.h"

int  is_simulation_active(t_codexion *data)
{
	int is_active;
    
	pthread_mutex_lock(&data->main_mutex);
	is_active = data->is_sim_active;
	pthread_mutex_unlock(&data->main_mutex);
	return(is_active);
}

int	check_burnout(t_codexion *data)
{
	int			i;
	long long	last_compile;
	int			finish;

	i = 0;
	while (i < data->number_of_coders)
	{
		pthread_mutex_lock(&data->coders[i].lock);
		last_compile = data->coders[i].last_compile_time;
		finish = data->coders[i].has_finished;
		pthread_mutex_unlock(&data->coders[i].lock);
		if (finish == 0 && (get_time() - last_compile > data->time_to_burnout))
		{
			print_message(data, data->coders[i].number, LOG_BURNS_OUT);
			return (1);
		}
		i++;
	}
	return (0);
}

int has_finished(t_codexion *data)
{
	int	i;
	int	nb_finish;

	i = 0;
	nb_finish = 0;
	while (i < data->number_of_coders)
	{
		pthread_mutex_lock(&data->coders[i].lock);
		if (data->coders[i].has_finished == 1)
			nb_finish++;
		pthread_mutex_unlock(&data->coders[i].lock);
		i++;
	}
	return(nb_finish);
}