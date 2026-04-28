/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alebaron <alebaron@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 14:10:42 by alebaron          #+#    #+#             */
/*   Updated: 2026/04/28 11:35:26 by alebaron         ###   ########.fr       */
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
# include <sys/time.h>

// ==========================
//         Structures
// ==========================

typedef struct s_codexion	t_codexion;
typedef struct s_dongle		t_dongle;
typedef struct s_coder		t_coder;

typedef struct s_codexion
{
	pthread_t	main_thread;

	int			number_of_coders;
	int			time_to_burnout;
	int			time_to_compile;
	int			time_to_debug;
	int			time_to_refactor;
	int			nb_compiles_required;
	int			dongle_cooldown;
	char		*scheduler;

	t_coder		*coders;
	t_dongle	*dongles;

	int			start_time;
}			t_codexion;

typedef struct s_dongle
{
	int				cooldown;
	int				id;
	pthread_mutex_t	lock;
}			t_dongle;

typedef struct s_coder
{
	int				number;
	int				compiles_done;
	int				is_burned_out;
	int				last_compile_time;
	pthread_t		thread;
	t_dongle		*left_dongle;
	t_dongle		*right_dongle;
}			t_coder;

// ==========================
//         Prototype
// ==========================

//     check_args.c
// =====================

int		check_arg(int argc, char **argv);

//     exit_utils.c
// =====================

int		exit_program(void);
void	free_all(t_codexion *args);

//     time_utils.c
// =====================

int get_time(void);

//     init_struct.c
// =====================

t_codexion	*init_data(char **argv);

//     coder_routine.c
// =====================

void    *main_routine(void *arg);
void    *coders_routine(void *arg);

//     manage_threads.c
// =====================

void    join_thread(t_codexion *data);

#endif