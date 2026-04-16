/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alebaron <alebaron@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 14:10:42 by alebaron          #+#    #+#             */
/*   Updated: 2026/04/16 11:44:18 by alebaron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CODEXION_H
# define CODEXION_H

// ==========================
//         Includes
// ==========================

# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <stdio.h>
# include <pthread.h>

// ==========================
//         Structures
// ==========================

typedef struct s_args
{
	int		number_of_coders;
	int		time_to_burnout;
	int		time_to_compile;
	int		time_to_debug;
	int		time_to_refactor;
	int		number_of_compiles_required;
	int		dongle_cooldown;
	char	*scheduler;
}			t_args;

typedef struct s_dongle
{
	int				cooldown;
	int				id;
	pthread_mutex_t	lock;
}			t_dongle;

typedef struct s_coder
{
	int				number;
	pthread_t		thread;
	t_dongle		*left_dongle;
	t_dongle		*right_dongle;
}			t_coder;

// ==========================
//         Prototype
// ==========================

//      check_args.c
// =====================

int		check_arg(int argc, char **argv);

//        utils.c
// =====================

int		exit_program(char *end_message);
void	free_all(t_args *args);

//     init_struct.c
// =====================

t_args	*init_args(char **argv);

#endif