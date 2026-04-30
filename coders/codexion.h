/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alebaron <alebaron@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 14:10:42 by alebaron          #+#    #+#             */
/*   Updated: 2026/04/30 11:19:38 by alebaron         ###   ########.fr       */
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
//         Consts
// ==========================

# define LOG_TAKE_DONGLE	"%lld %d has taken dongle %s\n"
# define LOG_COMPILING		"%lld %d is compiling (%d)\n"
# define LOG_DEBUGGING		"%lld %d is debugging\n"
# define LOG_REFACTOR		"%lld %d is refactoring\n"
# define LOG_BURNS_OUT		"%lld %d burned out\n"
# define LOG_SUCCESS		"All coders have compiled %d time. Good job !"

// ==========================
//         Structures
// ==========================

typedef struct s_codexion	t_codexion;
typedef struct s_dongle		t_dongle;
typedef struct s_coder		t_coder;

typedef struct s_codexion
{
	pthread_t		main_thread;
	pthread_mutex_t	main_mutex;
	pthread_mutex_t	print_mutex;

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

	long long	start_time;
	int			is_sim_active;
}			t_codexion;

typedef struct s_dongle
{
	int				cooldown;
	int				id;
	pthread_mutex_t	lock;
}			t_dongle;

typedef struct s_coder
{
	t_codexion		*data;

	int				number;
	int				compiles_done;
	long long		last_compile_time;

	int				has_finished;

	pthread_t		thread;
	pthread_mutex_t	lock;

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

long long get_time(void);

//     print_utils.c
// =====================

void	print_message(t_codexion *data, int num_coder, char *action);

//     init_struct.c
// =====================

t_codexion	*init_data(char **argv);

//     routines.c
// =====================

void    *main_routine(void *arg);
void    *coders_routine(void *arg);

//     simulation_check.c
// =====================

int		check_burnout(t_codexion *data);
int  	is_simulation_active(t_codexion *data);
int 	has_finished(t_codexion *data);

//     manage_threads.c
// =====================

void    join_thread(t_codexion *data);

//     fifo.c
// =====================

void fifo(t_coder *coder);

//     edf.c
// =====================

void edf(t_coder *coder);

//     debug_and_refact.c
// =====================

void	debug(t_coder *coder);
void	refactoring(t_coder *coder);

#endif