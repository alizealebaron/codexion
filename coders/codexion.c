/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alebaron <alebaron@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 14:10:33 by alebaron          #+#    #+#             */
/*   Updated: 2026/04/28 11:33:47 by alebaron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	main(int argc, char **argv)
{
	t_codexion	*data;

	if (!check_arg(argc, argv))
		return (exit_program());

	data = init_data(argv);
	join_thread(data);

	free_all(data);
	return (0);
}
