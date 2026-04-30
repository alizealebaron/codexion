/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_threads.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alebaron <alebaron@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 10:02:06 by alebaron          #+#    #+#             */
/*   Updated: 2026/04/30 15:19:38 by alebaron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../codexion.h"

void    join_thread(t_codexion *data)
{
    int i;

    i = 0;
    pthread_join(data->main_thread, NULL);
    while (i < data->number_of_coders)
    {
        pthread_join(data->coders[i].thread, NULL);
        i++;
    }
}
