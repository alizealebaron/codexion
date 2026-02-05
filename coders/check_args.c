/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alebaron <alebaron@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 14:10:24 by alebaron          #+#    #+#             */
/*   Updated: 2026/02/05 14:24:21 by alebaron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	check_arg(int argc, char **argv)
{
	if (argc != 9)
		return (0);

	char *str = argv[0];
	printf("%s", str);
	return (1);
}

