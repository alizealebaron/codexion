# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alebaron <alebaron@student.42lehavre.fr    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/02/03 12:13:28 by alebaron          #+#    #+#              #
#    Updated: 2026/04/30 15:03:40 by alebaron         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ==========================
#        Constantes
# ==========================

CC        = cc
RM        = rm -rf
NAME      = codexion
CFLAGS    = -Wall -Werror -Wextra -pthread
LIB_DIR   = coders
OBJ_DIR   = obj

# ==========================
#         Couleurs
# ==========================

RED     := \033[31m
GREEN   := \033[32m
YELLOW  := \033[33m
BLUE 	:= \033[96m
CYAN    := \033[36m
RESET   := \033[0m
BOLD    := \033[1m

# ==========================
#         Sources
# ==========================

LIB_SRCS = $(LIB_DIR)/codexion.c                   \
           $(LIB_DIR)/init/check_args.c            \
		   $(LIB_DIR)/init/init_struct.c           \
           $(LIB_DIR)/utils/exit_utils.c           \
           $(LIB_DIR)/utils/time_utils.c           \
           $(LIB_DIR)/utils/print_utils.c          \
           $(LIB_DIR)/utils/debug_utils.c          \
		   $(LIB_DIR)/routine/routines.c           \
		   $(LIB_DIR)/routine/manage_threads.c     \
		   $(LIB_DIR)/routine/simulation_check.c   \
		   $(LIB_DIR)/scheduler/edf.c              \
		   $(LIB_DIR)/scheduler/fifo.c             \
		   $(LIB_DIR)/scheduler/fifo_functions.c   \
		   $(LIB_DIR)/scheduler/scheduler_utils.c  \
    

LIB_OBJS = $(LIB_SRCS:%.c=${OBJ_DIR}/%.o)

# ==========================
#         Règles
# ==========================

all: $(NAME)

# Règle pour créer le dossier obj et compiler les objets dedans
$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(@D)
	@echo "$(CYAN)[Compiling]$(RESET) 🦆 $(BLUE)$(BOLD)$<$(RESET)"
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(LIB_OBJS)
	@echo "\nCompiled with $(GREEN)$(BOLD)$(CFLAGS)$(RESET)"
	@$(CC) $(CFLAGS) -o $(NAME) $(LIB_OBJS) -g3
	@echo "$(BLUE)$(BOLD)----------------------------------------"
	@echo "     $(NAME) = NOW READY FOR USE!"
	@echo "----------------------------------------$(RESET)"

clean:
	@echo "$(RED)$(BOLD)[Cleaning objects of ${NAME}]$(RESET)"
	$(RM) $(OBJ_DIR)

fclean: clean
	@echo "$(RED)$(BOLD)[Removing $(NAME)]$(RESET)"
	$(RM) $(NAME)

re: fclean all

run: re
	@echo "$(GREEN)$(BOLD)Running $(NAME) with 4 coders...$(RESET)"
	@./$(NAME) 4 800 200 200 200 5 10 fifo

coin: re 
	@echo "$(YELLOW)$(BOLD)                    $(RESET)"
	@echo "$(YELLOW)$(BOLD)    ~Coin coin~     $(RESET)"
	@echo "$(YELLOW)$(BOLD)  _      _      _   $(RESET)"
	@echo "$(YELLOW)$(BOLD)>(.)__ <(.)__ =(^)__$(RESET)"
	@echo "$(YELLOW)$(BOLD) (___/  (___/  (___/$(RESET)"
	@echo "$(YELLOW)$(BOLD)                    $(RESET)"
	@echo "$(YELLOW)$(BOLD)    ~Coin coin~     $(RESET)"

.PHONY: fclean all clean re coin run
.SILENT:
