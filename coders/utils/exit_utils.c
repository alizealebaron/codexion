/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alebaron <alebaron@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 14:10:54 by alebaron          #+#    #+#             */
/*   Updated: 2026/04/27 14:48:42 by alebaron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../codexion.h"

int	exit_program(char *end_message)
{
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
