# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tordner <tordner@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/29 17:32:15 by thorgal           #+#    #+#              #
#    Updated: 2025/06/03 04:09:04 by tordner          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = cc

CFLAGS = -pthread -Iincludes -Wall -Wextra -Wextra

SRCDIR = src
LIBFT = libft.a
OBJDIR = obj

INCDIR = includes

SRCS = 	$(SRCDIR)/main/main.c \
		$(SRCDIR)/main/shell.c \
		$(SRCDIR)/main/signals.c \
		$(SRCDIR)/main/signals_utils.c \
		$(SRCDIR)/utils/utils.c \
		$(SRCDIR)/main/prompt.c \
		$(SRCDIR)/exec/execute_pipeline.c \
		$(SRCDIR)/utils/free.c \
		$(SRCDIR)/utils/get_env_value.c \
		$(SRCDIR)/main/input.c \
		$(SRCDIR)/tokens/tokens.c \
		$(SRCDIR)/tokens/handle_quoted_count.c \
		$(SRCDIR)/tokens/extract_quoted_content.c \
		$(SRCDIR)/tokens/tokens_utils.c \
		$(SRCDIR)/tokens/syntax.c \
		$(SRCDIR)/tokens/check_pipes.c \
		$(SRCDIR)/tokens/check_redirections.c \
		$(SRCDIR)/tokens/token_list.c \
		$(SRCDIR)/builtins/echo.c \
		$(SRCDIR)/builtins/cd.c \
		$(SRCDIR)/builtins/cd_utils.c \
		$(SRCDIR)/builtins/pwd.c \
		$(SRCDIR)/builtins/env.c \
		$(SRCDIR)/builtins/export.c \
		$(SRCDIR)/builtins/unset.c \
		$(SRCDIR)/exec/exec.c \
		$(SRCDIR)/exec/file_handler.c \
		$(SRCDIR)/exec/get_env.c \
		$(SRCDIR)/exec/heredoc.c \
		$(SRCDIR)/exec/pipe.c \
		$(SRCDIR)/tokens/tokens_list2.c \
		$(SRCDIR)/tokens/tokens_utils2.c \
		$(SRCDIR)/tokens/tokenize_command.c \
		$(SRCDIR)/tokens/extract_token_len.c \
		$(SRCDIR)/builtins/export_utils.c \
		$(SRCDIR)/builtins/export_utils2.c \
		$(SRCDIR)/builtins/exit.c	\
		$(SRCDIR)/exec/exec_utils.c	\
		$(SRCDIR)/exec/setup_files.c	\
		$(SRCDIR)/exec/execute_ve.c	\
		$(SRCDIR)/exec/ft_exec.c	\
		$(SRCDIR)/exec/setup_output_redirections.c	\
		$(SRCDIR)/tokens/expander.c \
		$(SRCDIR)/builtins/exit_utils.c \
		$(SRCDIR)/builtins/export_utils_3.c
	
OBJS = $(SRCS:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

OBJSUBDIRS = $(sort $(dir $(OBJS)))

GREEN = \033[0;32m
YELLOW = \033[0;33m
CYAN = \033[0;36m
RESET = \033[0m
BOLD = \033[1m
WHITE = \033[0;97m
BLUE = \033[0;34m

LOADING_CHARS = ⠋ ⠙ ⠹ ⠸ ⠼ ⠴ ⠦ ⠧ ⠇ ⠏

define MINISHELL_ART

 ███▄ ▄███▓ ██▓ ███▄    █  ██▓  ██████  ██░ ██ ▓█████  ██▓     ██▓    
▓██▒▀█▀ ██▒▓██▒ ██ ▀█   █ ▓██▒▒██    ▒ ▓██░ ██▒▓█   ▀ ▓██▒    ▓██▒    
▓██    ▓██░▒██▒▓██  ▀█ ██▒▒██▒░ ▓██▄   ▒██▀▀██░▒███   ▒██░    ▒██░    
▒██    ▒██ ░██░▓██▒  ▐▌██▒░██░  ▒   ██▒░▓█ ░██ ▒▓█  ▄ ▒██░    ▒██░    
▒██▒   ░██▒░██░▒██░   ▓██░░██░▒██████▒▒░▓█▒░██▓░▒████▒░██████▒░██████▒
░ ▒░   ░  ░░▓  ░ ▒░   ▒ ▒ ░▓  ▒ ▒▓▒ ▒ ░ ▒ ░░▒░▒░░ ▒░ ░░ ▒░▓  ░░ ▒░▓  ░
░  ░      ░ ▒ ░░ ░░   ░ ▒░ ▒ ░░ ░▒  ░ ░ ▒ ░▒░ ░ ░ ░  ░░ ░ ▒  ░░ ░ ▒  ░
░      ░    ▒ ░   ░   ░ ░  ▒ ░░  ░  ░   ░  ░░ ░   ░     ░ ░     ░ ░   
       ░    ░           ░  ░        ░   ░  ░  ░   ░  ░    ░  ░    ░  ░

endef
export MINISHELL_ART

all: print_art $(NAME)

print_art:
	@printf "$(CYAN)%s$(RESET)\n" "$$MINISHELL_ART"

$(NAME): $(OBJS)
	@$(MAKE) -s -C libft
	@printf "$(BOLD)$(WHITE)Welcome to the $(BLUE)Minishell$(WHITE) compilation process.\nPlease hold on as we prepare your program.\n\n$(RESET)"
	@printf "$(YELLOW)Compiling Minishell, Please wait...$(RESET)"
	@for char in $(LOADING_CHARS); do \
		printf "\r$(YELLOW)Compiling Minishell, Please wait... $$char$(RESET)"; \
		sleep 0.1; \
	done
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME) -g3 -lreadline libft/$(LIBFT)
	@printf "\r$(GREEN)Nice ! $(WHITE)Minishell compiled successfully !     $(RESET)\n\n"
	@printf "$(BOLD)$(WHITE)Compilation complete !\n$(BLUE)Minishell$(WHITE) is ready to use !\n$(RESET)"

# Règle pour créer les fichiers objets
$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJSUBDIRS)
	@$(CC) $(CFLAGS) -I $(INCDIR) -c $< -o $@

# Règle pour créer les sous-répertoires
$(OBJSUBDIRS):
	@mkdir -p $@

clean:
	@make clean -s -C libft
	@rm -rf $(OBJDIR)
	@printf "$(WHITE)Clean process completed for $(BLUE)Minishell.$(RESET)\n"

clean1:
	@rm -rf $(OBJDIR)

fclean: clean1
	@make fclean -s -C libft
	@rm -f $(NAME)
	@printf "$(WHITE)Full clean process completed for $(BLUE)Minishell.$(RESET)\n"

re: fclean all

.PHONY: all clean fclean re clean1 print_art

norminette:
	norminette src/* includes/* | grep "Error"