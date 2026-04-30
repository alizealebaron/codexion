/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alebaron <alebaron@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 14:10:33 by alebaron          #+#    #+#             */
/*   Updated: 2026/04/30 15:36:08 by alebaron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void print_debug_coders(t_codexion *data);

int	main(int argc, char **argv)
{
	t_codexion	*data;

	if (!check_arg(argc, argv))
		return (exit_program());
	data = init_data(argv);
	// join_thread(data);
	free_all(data);
	return (0);
}
