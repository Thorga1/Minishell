/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   messages.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tordner <tordner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 15:38:19 by lfirmin           #+#    #+#             */
/*   Updated: 2025/06/02 00:35:25 by tordner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MESSAGES_H
# define MESSAGES_H

# include "minishell.h"

# define RED "\001\033[1;31m\002"
# define GREEN "\001\033[1;32m\002"
# define YELLOW "\001\033[1;33m\002"
# define BLUE "\001\033[1;34m\002"
# define MAGENTA "\001\033[1;35m\002"
# define CYAN "\001\033[1;36m\002"
# define RESET "\001\033[0m\002"

# define WELCOME_MESS "Welcome to our MiniShell.\n"
# define ERROR_TOKEN "Error: Tokenization failed\n"
# define ERROR_NOT_FOUND "Command not found: %s\n"
# define PROMPT_GIT "➜\001\033[0m\002  \001\033[1;36m\002%s\001\033[0\
m\002 \001\033[1;32m\002git:(\001\033[1;31m\002%s\001\033[1;\
32m\002)\001\033[0m\002 ❯ "
# define PROMPT_STD "➜\001\033[0m\002  \001\033[1;36m\002%s\001\033[0m\002 ❯ "

void	debug_tokens(char **tokens);
#endif
