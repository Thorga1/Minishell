# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: thorgal <thorgal@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/29 17:32:15 by thorgal           #+#    #+#              #
#    Updated: 2025/03/10 17:50:06 by thorgal          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = cc

CFLAGS = -pthread -Iincludes

SRCDIR = src
LIBFT = libft.a
OBJDIR = obj

INCDIR = includes

SRCS = 	$(SRCDIR)/main/main.c \
		$(SRCDIR)/main/shell.c \
		$(SRCDIR)/utils/utils.c \
		$(SRCDIR)/utils/free.c \
		$(SRCDIR)/main/input.c \
		$(SRCDIR)/tokens/tokens.c \
		$(SRCDIR)/tokens/tokens_utils.c \
		$(SRCDIR)/tokens/syntax.c \
		$(SRCDIR)/tokens/check_pipes.c \
		$(SRCDIR)/tokens/check_redirections.c \
		$(SRCDIR)/tokens/token_list.c \
		$(SRCDIR)/builtins/echo.c \
		$(SRCDIR)/builtins/cd.c \
		$(SRCDIR)/builtins/pwd.c \
		$(SRCDIR)/builtins/ls.c \
		$(SRCDIR)/builtins/clear.c \
		$(SRCDIR)/builtins/env.c \
		$(SRCDIR)/builtins/export.c \
		$(SRCDIR)/builtins/unset.c

OBJS = $(SRCS:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

OBJSUBDIRS = $(sort $(dir $(OBJS)))

all: $(NAME)

$(NAME): $(OBJS)
	@$(MAKE) -s -C libft
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME) -g3 -lreadline libft/$(LIBFT)

# Règle pour créer les fichiers objets
$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJSUBDIRS)
	@$(CC) $(CFLAGS) -I $(INCDIR) -c $< -o $@

# Règle pour créer les sous-répertoires
$(OBJSUBDIRS):
	@mkdir -p $@

clean:
	@make clean -s -C libft
	@rm -rf $(OBJDIR)

clean1:
	@rm -rf $(OBJDIR)

fclean: clean1
	@make fclean -s -C libft
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re clean1