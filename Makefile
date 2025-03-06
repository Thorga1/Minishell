# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: thorgal <thorgal@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/29 17:32:15 by thorgal           #+#    #+#              #
#    Updated: 2025/03/03 13:31:29 by thorgal          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = cc

CFLAGS = -pthread -Iincludes

# -Wall -Wextra -Werror rajouter apres les tests

SRCDIR = src

OBJDIR = obj

INCDIR = includes

SRCS = 	$(SRCDIR)/main/main.c \
		$(SRCDIR)/utils/utils.c \
		$(SRCDIR)/tokens/tokens.c \
		$(SRCDIR)/tokens/syntax.c \
		$(SRCDIR)/builtins/echo.c \
		$(SRCDIR)/builtins/cd.c \
		$(SRCDIR)/builtins/pwd.c \
		$(SRCDIR)/builtins/ls.c \
		$(SRCDIR)/builtins/clear.c \

OBJS = $(SRCS:$(SRCDIR)/%.c=$(OBJDIR)/%.o)


OBJSUBDIRS = $(sort $(dir $(OBJS)))

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME) -lreadline

# Règle pour créer les fichiers objets
$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJSUBDIRS)
	@$(CC) $(CFLAGS) -I $(INCDIR) -c $< -o $@

# Règle pour créer les sous-répertoires
$(OBJSUBDIRS):
	@mkdir -p $@

clean:
	@rm -rf $(OBJDIR)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re