/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thorgal <thorgal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 17:17:08 by thorgal           #+#    #+#             */
/*   Updated: 2025/02/06 16:02:09 by thorgal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <limits.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <dirent.h>

typedef struct s_shell
{
    char    **env;
    int     exit_status;
    int     running;
} t_shell;

// Prototypes des builtins
int     ft_echo(char **args);
int     ft_cd(const char *path);
void    ft_pwd(void);
int     ft_ls(void);
int     ft_clear(void);

// Core functions
char    **tokenize_command(char *input);
size_t  ft_strlcpy(char *dst, const char *src, size_t dstsize);
void    initialize_shell(t_shell *shell, char **envp);
void    minishell_loop(t_shell *shell);

// Dans la section des fonctions utilitaires
char    *get_current_dir_name(void);

#endif