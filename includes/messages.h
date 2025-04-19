/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   messages.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfirmin <lfirmin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 15:38:19 by lfirmin           #+#    #+#             */
/*   Updated: 2025/04/19 11:48:59 by lfirmin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MESSAGES_H
# define MESSAGES_H

# define RED "\033[1;31m"
# define GREEN "\033[1;32m"
# define YELLOW "\033[1;33m"
# define BLUE "\033[1;34m"
# define MAGENTA "\033[1;35m"
# define CYAN "\033[1;36m"
# define RESET "\033[0m"

# define WELCOME_MESS "Welcome to our MiniShell.\n"
# define ERROR_TOKEN "Error: Tokenization failed\n"
# define ERROR_NOT_FOUND "Command not found: %s\n"
# define PROMPT_GIT "➜\033[0m  \033[1;36m%s\033[0m \033[1;32mgit:(\033[1;31m%s\033[1;32m)\033[0m ❯ "
# define PROMPT_STD "➜\033[0m  \033[1;36m%s\033[0m ❯ "
#endif
