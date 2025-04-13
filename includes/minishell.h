/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thorgal <thorgal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 17:17:08 by thorgal           #+#    #+#             */
/*   Updated: 2025/03/10 17:49:49 by thorgal          ###   ########.fr       */
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
# include <stddef.h>
# include <fcntl.h>
# include "../libft/include/libft.h"
# include "messages.h"
typedef enum e_token_type
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_REDIRECTION_IN,		// <
	TOKEN_REDIRECTION_OUT,		// >
	TOKEN_APPEND,				// >>
	TOKEN_HEREDOC,				// <<
	TOKEN_ENV_VAR,				// $VAR
	TOKEN_UNKNOWN				// ????	
} t_token_type;

typedef struct s_smd
{
	char			**args;     // Arguments of the command
	char			*infile;    // Input redirection file
	char			*outfile;   // Output redirection file
	int				append;     // Append flag for output redirection (1 = append, 0 = overwrite)
	struct s_smd	*next;      // Pointer to the next command in the pipeline
} t_smd;

typedef struct s_shell
{
	char    **env;			// Environment variables
	int     exit_status;	// Exit status of the last command
	int     running;		// Running flag
} t_shell;

// typedef struct s_redirection
// {
// 	int				type; // 1 = input, 2 = output, 3 = append, 0 = none
// 	char			*file;
// 	t_redirection	*next;
// } t_redirection;

// builtins
int		ft_echo(t_smd *cmd, t_shell *shell);
int		ft_cd(t_smd *cmd, t_shell *shell);
void	ft_pwd(void);
int		ft_ls(void);
int		ft_clear(void);
int 	ft_env(t_shell *shell);
int 	ft_export(t_shell *shell, t_smd *cmd);
int 	ft_unset(t_shell *shell, t_smd *cmd);

//check_pipes
int		validate_pipes(char **tokens);

//check_redirections
int		validate_redirections(char **tokens);

//syntax
int		validate_syntax(char **tokens);

//token_list
t_smd	*parse_tokens_to_list(char **tokens);
t_smd	*create_new_node(void);
void	free_cmd_list(t_smd *cmd_list);

//token_utils
void	*free_tokens(char **tokens, int count);
int		extract_quoted_token(char *input, int *index, char quote_char);
int		is_delimiter(char c);
int		is_special(char c);
void	skip_delimiters(char *str, int *i);

//token
int		count_tokens(char *str);
char	*extract_token(char *input, int *index);
int		check_quotes(char *input);
char	**tokenize_command(char *input);

//utils
char	*get_current_dir_name(void);
char	*ft_get_env_var(char **env, char *var);
char	**copy_env(char **envp);
int		is_git_repository(void);
char	*get_git_branch(void);

//free
void	free_cmd_list(t_smd *cmd_list);
void	*free_tokens(char **tokens, int count);

//main	
void	initialize_shell(t_shell *shell, char **envp);
int		execute_builtin(t_smd *cmd, t_shell *shell);



//shell
void	minishell_loop(t_shell *shell);

//input
char	**parse_input(char *input, t_shell *shell);
void	process_input(char *input, t_shell *shell);

// Token Syntax
t_token_type	classify_token(char *token);
int				validate_pipes(char **tokens);
int				validate_syntax(char **tokens);
int				validate_redirections(char **tokens);

// Token List
t_smd	*parse_tokens_to_list(char **tokens);
t_smd	*create_new_node(void);
void	free_cmd_list(t_smd *cmd_list);

#endif