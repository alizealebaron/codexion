/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alebaron <alebaron@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/27 14:09:15 by alebaron          #+#    #+#             */
/*   Updated: 2026/04/27 14:14:33 by alebaron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../codexion.h"

int get_time(void)
{
    struct timeval start;

    gettimeofday(&start, NULL);
    return ((start.tv_sec * 1000) + (start.tv_usec / 1000));
}