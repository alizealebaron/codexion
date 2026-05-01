/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alebaron <alebaron@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 14:10:42 by alebaron          #+#    #+#             */
/*   Updated: 2026/05/01 13:13:36 by alebaron         ###   ########.fr       */
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

# define LOG_TAKE_DONGLE	"%lld %d has taken dongle\n"
# define LOG_COMPILING		"%lld %d is compiling\n"
# define LOG_DEBUGGING		"%lld %d is debugging\n"
# define LOG_REFACTOR		"%lld %d is refactoring\n"
# define LOG_BURNS_OUT		"%lld %d burned out\n"
# define LOG_SUCCESS		"All coders have compiled %d time. Good job !"

// Action //
# define TAKE			"takedongle"
# define COMPILE		"compile"
# define DEBUG			"debug"
# define REFAC			"refac"
# define BURNS			"burns_out"
# define REMOVE_QUEUE	"remove_q"
# define ADD_QUEUE		"add_q"

// ==========================
//         Structures
// ==========================

typedef struct s_codexion			t_codexion;
typedef struct s_dongle				t_dongle;
typedef struct s_coder				t_coder;
typedef struct s_queue				t_queue;
typedef struct s_queue_controller	t_queue_controller;

typedef struct s_queue
{
	t_coder			*coder;
	struct s_queue	*next;
}					t_queue;

typedef struct s_queue_controller
{
	t_queue			*first;
	pthread_mutex_t	mutex;
	pthread_cond_t	cond;
}					t_queue_controller;

typedef struct s_codexion
{
	pthread_t			main_thread;
	pthread_mutex_t		main_mutex;
	pthread_mutex_t		print_mutex;

	int					number_of_coders;
	int					time_to_burnout;
	int					time_to_compile;
	int					time_to_debug;
	int					time_to_refactor;
	int					nb_compiles_required;
	int					dongle_cooldown;
	char				*scheduler;

	t_coder				*coders;
	t_dongle			*dongles;

	long long			start_time;
	int					is_sim_active;

	t_queue_controller	queue;
}			t_codexion;

typedef struct s_dongle
{
	long long		cooldown;
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

//     /init
// =====================

int			check_arg(int argc, char **argv);

t_codexion	*init_data(char **argv);

//     /routine
// =====================

void    	*main_routine(void *arg);
void    	*coders_routine(void *arg);

int			check_burnout(t_codexion *data);
int  		is_simulation_active(t_codexion *data);
int 		has_finished(t_codexion *data);

void    	join_thread(t_codexion *data);

void		debug(t_coder *coder);
void		refactoring(t_coder *coder);
void		compile(t_coder *coder);

//     /utils
// =====================

long long	get_time(void);

int			exit_program(void);
void		free_all(t_codexion *args);

void		print_message(t_codexion *data, int num_coder, char *action);

#endif