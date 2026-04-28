/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alebaron <alebaron@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/27 13:07:06 by alebaron          #+#    #+#             */
/*   Updated: 2026/04/28 10:33:43 by alebaron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../codexion.h"

void    *main_routine(void *arg)
{
    (void) arg;
    printf("Coucou 2\n");

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
