/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thorgal <thorgal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 17:17:08 by thorgal           #+#    #+#             */
/*   Updated: 2025/03/04 17:55:54 by thorgal          ###   ########.fr       */
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

typedef enum e_token_type
{
	TOKEN_COMMAND,
	TOKEN_ARGUMENT,
	TOKEN_PIPE,
	TOKEN_REDIRECTION_IN,     // <
	TOKEN_REDIRECTION_OUT,    // >
	TOKEN_REDIRECTION_APPEND, // >>
	TOKEN_HEREDOC,            // <<
	TOKEN_ENV_VAR,            // $VAR
	TOKEN_QUOTED_STRING,
	TOKEN_UNKNOWN
}	t_token_type;
 
typedef struct s_smd
{
	char			**args;
	char			*infile;
	char			*outfile;
	int				append;
	struct s_smd	*next;
}	t_smd;

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
int 	ft_strcmp(const char *s1, const char *s2);
int		ft_strlen(char *str);
void    initialize_shell(t_shell *shell, char **envp);
void    minishell_loop(t_shell *shell);

// Dans la section des fonctions utilitaires
char    *get_current_dir_name(void);

// Token Syntax
t_token_type	classify_token(char *token);


#endif