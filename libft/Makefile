# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lfirmin <lfirmin@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/19 12:59:31 by lfirmin           #+#    #+#              #
#    Updated: 2025/04/19 11:53:48 by lfirmin          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
HEADER = ./include
SRCS_DIR = ./srcs/
SRC =   ft_isalnum.c ft_isprint.c ft_memcmp.c  ft_putchar_fd.c ft_split.c \
        ft_strlcat.c ft_strncmp.c ft_substr.c ft_atoi.c ft_isalpha.c \
        ft_itoa.c ft_memcpy.c  ft_putendl_fd.c ft_strchr.c  ft_strlcpy.c \
        ft_strnstr.c ft_tolower.c ft_bzero.c   ft_isascii.c ft_strtrim.c \
        ft_memmove.c ft_putnbr_fd.c  ft_strdup.c  ft_strlen.c  ft_strrchr.c \
        ft_toupper.c ft_calloc.c  ft_isdigit.c ft_memchr.c  ft_memset.c  \
        ft_putstr_fd.c  ft_strjoin.c ft_strmapi.c ft_striteri.c \
        ft_lstnew_bonus.c ft_lstadd_front_bonus.c ft_lstsize_bonus.c \
        ft_lstlast_bonus.c ft_lstadd_back_bonus.c ft_lstdelone_bonus.c \
        ft_lstclear_bonus.c ft_lstiter_bonus.c ft_lstmap_bonus.c ft_strcmp.c \
        ft_atoll.c ft_straddchar.c ft_strcpy.c

SRCS = $(addprefix $(SRCS_DIR), $(SRC))
CC = cc
CFLAGS = -Wall -Wextra -Werror -g3
INCLUDE = -I $(HEADER)
OBJ_DIR = obj/
OBJ = $(addprefix $(OBJ_DIR), $(SRC:.c=.o))

GREEN = \033[0;32m
YELLOW = \033[0;33m
RESET = \033[0m
WHITE = \033[0;97m

LOADING_CHARS = ⠋ ⠙ ⠹ ⠸ ⠼ ⠴ ⠦ ⠧ ⠇ ⠏

all: $(NAME)

$(NAME): $(OBJ)
	@printf "$(YELLOW)Compiling libft, Please wait...$(RESET)"
	@for char in $(LOADING_CHARS); do \
		printf "\r$(YELLOW)Compiling libft, Please wait... $$char$(RESET)"; \
		sleep 0.1; \
	done
	@ar rc $(NAME) $(OBJ)
	@ranlib $(NAME)
	@printf "\r$(GREEN)Great news ! $(WHITE)Libft compiled successfully !                 $(RESET)\n"

$(OBJ_DIR)%.o: $(SRCS_DIR)%.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

clean:
	@rm -rf $(OBJ_DIR)
	@printf "$(WHITE)Clean process completed for $(GREEN)Libft.$(RESET)\n"

fclean: clean
	@rm -f $(NAME)
	@printf "$(WHITE)Full clean process completed for $(GREEN)Libft.$(RESET)\n"

re: fclean all

.PHONY: all clean fclean re