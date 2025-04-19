/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfirmin <lfirmin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 17:17:08 by thorgal           #+#    #+#             */
/*   Updated: 2025/04/19 13:22:56 by lfirmin          ###   ########.fr       */
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
# include <stdbool.h>
# include <sys/types.h>
# include <sys/wait.h>
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
}	t_token_type;

typedef struct s_redirection
{
	int						type; // 1 = input, 2 = output, 3 = append, 0 = none
	char					*file;
	struct s_redirection	*next;
} t_redirection;

typedef struct s_cmd
{
	char			**args;
	t_redirection	*redir;
	struct s_cmd	*next;
} t_cmd;


typedef struct s_shell
{
	char    **env;			// Environment variables
	int     exit_status;	// Exit status of the last command
	int     running;		// Running flag
} t_shell;

// builtins
int		ft_echo(t_cmd *cmd, t_shell *shell);
int		ft_cd(t_cmd *cmd, t_shell *shell);
void	ft_pwd(void);
int 	ft_env(t_shell *shell);
int 	ft_export(t_shell *shell, t_cmd *cmd);
int 	ft_unset(t_shell *shell, t_cmd *cmd);

//check_pipes
int		validate_pipes(char **tokens);

//check_redirections
int		validate_redirections(char **tokens);

//syntax
int		validate_syntax(char **tokens);

//token_list
t_cmd	*parse_tokens_to_list(char **tokens);
t_cmd	*create_new_node(void);
void	free_cmd_list(t_cmd *cmd_list);

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
void	free_cmd_list(t_cmd *cmd_list);
void	*free_tokens(char **tokens, int count);

//main	
void	initialize_shell(t_shell *shell, char **envp);
int		execute_builtin(t_cmd *cmd, t_shell *shell);



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
t_cmd	*parse_tokens_to_list(char **tokens);
t_cmd	*create_new_node(void);
void	free_cmd_list(t_cmd *cmd_list);
int		is_redirection(char *token);

// Exec

int		open_file(char *file, int flags, int mode);
int		setup_files(char **av, int *infile, int *outfile);
void	close_files(int infile, int outfile);
char	*find_command(char **paths, char *cmd);
char	*get_path_env(char **envp);
int		ft_exec(t_cmd *cmd, char **envp);
int		execute_command(t_cmd *cmd, char **envp);

#endif