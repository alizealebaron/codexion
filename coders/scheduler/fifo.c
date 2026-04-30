/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fifo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alebaron <alebaron@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/30 10:32:45 by alebaron          #+#    #+#             */
/*   Updated: 2026/04/30 16:13:35 by alebaron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../codexion.h"

static void	compile_fifo(t_coder *coder);
static void	update_cooldown(t_coder *coder, t_dongle *first, t_dongle *second);
static void	print_and_compile(t_coder *coder);

void fifo(t_coder *coder)
{
	int	has_finished;

	while (is_simulation_active(coder->data) == 1)
	{
		pthread_mutex_lock(&coder->lock);
		has_finished = coder->has_finished;
		pthread_mutex_unlock(&coder->lock);
		if (has_finished == 1)
			break ;
		compile_fifo(coder);
		debug(coder);
		refactoring(coder);
	}
}

static void	compile_fifo(t_coder *coder)
{
	t_dongle	*first_dongle;
	t_dongle	*second_dongle;

	get_first_dongle(coder, &first_dongle, &second_dongle);
	pthread_mutex_lock(&first_dongle->lock);
	pthread_mutex_lock(&second_dongle->lock);
	if (check_dongle_cd(first_dongle, second_dongle) == 0)
	{
		pthread_mutex_unlock(&second_dongle->lock);
		pthread_mutex_unlock(&first_dongle->lock);
		return ;
	}
	update_cooldown(coder, first_dongle, second_dongle);
	pthread_mutex_unlock(&second_dongle->lock);
	pthread_mutex_unlock(&first_dongle->lock);
	print_and_compile(coder);
	update_coder_compile(coder);
}

static void	update_cooldown(t_coder *coder, t_dongle *first, t_dongle *second)
{
	long long	time;

	time = get_time();
	first->cooldown = time + coder->data->dongle_cooldown;
	second->cooldown = time + coder->data->dongle_cooldown;
}

static void	print_and_compile(t_coder *coder)
{
	print_message(coder->data, coder->number, LOG_TAKE_DONGLE);
	print_message(coder->data, coder->number, LOG_COMPILING);
	usleep(coder->data->time_to_compile);
}
