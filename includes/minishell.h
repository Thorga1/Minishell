/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tordner <tordner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 15:00:11 by thorgal           #+#    #+#             */
/*   Updated: 2025/06/02 21:24:27 by tordner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

////////////////////////////////////////////////////////////////
////////////////////////////INCLUDES////////////////////////////
////////////////////////////////////////////////////////////////
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
# include <signal.h>
# include <termios.h>
# include "messages.h"

////////////////////////////////////////////////////////////////
////////////////////////////GLOBALS/////////////////////////////
////////////////////////////////////////////////////////////////
extern int	g_signal;

////////////////////////////////////////////////////////////////
////////////////////////////ENUM////////////////////////////////
////////////////////////////////////////////////////////////////
typedef enum e_token_type
{
	TOKEN_WORD,
	TOKEN_REDIRECTION_IN,
	TOKEN_REDIRECTION_OUT,
	TOKEN_APPEND,
	TOKEN_HEREDOC,
	TOKEN_PIPE
}	t_token_type;

////////////////////////////////////////////////////////////////
////////////////////////////DATA////////////////////////////////
////////////////////////////////////////////////////////////////
typedef struct s_redirection
{
	int						type;
	char					*file;
	struct s_redirection	*next;
}	t_redirection;

typedef struct s_cmd
{
	char			**args;
	t_redirection	*redir;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_shell
{
	char	**env;
	int		exit_status;
	int		running;
	int		signaled;
	int		child_running;
	int		single_quoted_token;
}	t_shell;

////////////////////////////////////////////////////////////////
////////////////////////////MAIN////////////////////////////////
////////////////////////////////////////////////////////////////

////////////////////
///////main.c///////
////////////////////
void			initialize_shell(t_shell *shell, char **envp);
int				execute_command(t_cmd *cmd, t_shell *shell);
int				execute_builtin(t_cmd *cmd, t_shell *shell);
int				is_builtin(char *cmd);
int				main(void);

////////////////////
///////input.c//////
////////////////////
char			**parse_input(char *input, t_shell *shell);
void			process_input(char *input, t_shell *shell);

/////////////////////
///////shell.c///////
/////////////////////
void			minishell_loop(t_shell *shell);	
void			handle_input(char *input, t_shell *shell);
char			*generate_prompt(t_shell *shell);
char			*create_git_prompt(char *dir_name, int exit_status);
char			*create_standard_prompt(char *dir_name, int exit_status);

/////////////////////
///////signals.c/////
/////////////////////
void			check_if_signal(t_shell *shell);
void			handle_signal_parent(int num);
int				sig_event(void);
void			if_sigint(int sig);
void			set_status_if_signal(t_shell *shell);
void			set_signal_child(void);
void			set_signal_parent_exec(void);
void			set_signal_parent(void);

/////////////////////////////////////////////////////////////////
////////////////////////////UTILS////////////////////////////////
/////////////////////////////////////////////////////////////////

////////////////////
///////utils.c//////
////////////////////
char			*get_current_dir_name(void);
char			*ft_get_env_var(char **env, char *var);
char			**copy_env(char **envp);
int				is_git_repository(void);
char			*get_git_branch(void);

////////////////////
///////free.c///////
////////////////////
void			*free_tokens(char **tokens, int count);

/////////////////////////////////////////////////////////////////
////////////////////////////BULTINS//////////////////////////////
/////////////////////////////////////////////////////////////////

///////////////////
///////pwd.c///////
///////////////////
int				ft_pwd(void);

//////////////////
///////cd.c///////
//////////////////
int				handle_home_directory(t_shell *shell);
int				handle_previous_directory(t_shell *shell);
int				update_pwd_env(t_shell *shell);
char			*resolve_env_variables(char *path, t_shell *shell);
char			*expand_tilde(char *path, t_shell *shell);
int				ft_cd(t_cmd *cmd, t_shell *shell);

//////////////////
///////env.c//////
//////////////////
int				ft_env(t_shell *shell, t_cmd *cmd);

//////////////////
///////export.c///
//////////////////
int				ft_export(t_shell *shell, t_cmd *cmd);
int				process_export_args(t_shell *shell, char **args, int i);
int				update_env_var(char **env, char *var);
char			**add_env_var(char **env, char *new_var);
int				is_valid_identifier(char *str);

//////////////////
///////unset.c////
//////////////////
int				delete_line(char **array, int index);
int				find_env_var(char **env, char *var);
int				ft_unset(t_shell *shell, t_cmd *cmd);

//////////////////
///////echo.c/////
//////////////////
void			print_echo_args(char **args, int i, int first);
int				ft_echo(t_cmd *cmd, t_shell *shell);

/////////////////////////
///////export_utils.c////
/////////////////////////
int				handle_env_var(t_shell *shell, char *arg);
char			*handle_quotes_in_env_var(char *arg);

/////////////////////////
///////export_utils2.c////
/////////////////////////
char			*find_next_var(char *result, char **var_start, char **var_end);
char			*build_expanded_string(char *result, char *var_start, \
	char *var_end, char *var_value);
char			*extract_var_name(char *result, char *var_start, char *var_end);
char			*get_env_value_for_expansion(char **env, char *var_name);

/////////////////////////////////////////////////////////////////
////////////////////////////TOKENS///////////////////////////////
/////////////////////////////////////////////////////////////////

///////////////////////////
///////check_pipes.c///////
///////////////////////////
int				check_before_pipe(char **tokens);
int				pipe_sequence_invalid(char **tokens);
int				validate_pipes(char **tokens);

//////////////////////////////////
///////check_redirections.c///////
//////////////////////////////////
int				is_redirection(char *token);
int				check_further_redirections(char **tokens, int i);
int				validate_redirections(char **tokens);

//////////////////////
///////syntax.c///////
//////////////////////
t_token_type	classify_token(char *token);
int				validate_syntax(char **tokens);

//////////////////////////
///////token_list.c///////
//////////////////////////
void			free_cmd_node(t_cmd *cmd);
t_cmd			*create_command_node(void);
t_redirection	*create_redirection_node(int type, char *file);
int				add_argument(t_cmd *cmd, char *arg);
void			add_redirection(t_cmd *cmd, t_redirection *redir);

///////////////////////////
///////token_list2.c///////
///////////////////////////
int				handle_redirection(t_cmd *cmd, char **tokens, int *i);
t_cmd			*init_cmd_segment(t_cmd **cmd_list, char **tokens, int *i);
int				add_token_to_cmd(t_cmd *current, char **tokens, int *i);
t_cmd			*parse_tokens_to_list(char **tokens);
void			free_cmd_list(t_cmd *cmd_list);

///////////////////////////
///////token_utils.c///////
///////////////////////////
int				count_tokens(char *str);
int				handle_quoted_token(char *input, int *index, int *start);
int				handle_special_token(char *input, int *index);
void			handle_quoted_count(char *str, int *i, char quote);
void			handle_special_count(char *str, int *i);

////////////////////
///////token.c//////
////////////////////
int				extract_quoted_token(char *input, int *index, char quote_char);
int				is_delimiter(char c);
int				is_special(char c);
void			skip_delimiters(char *str, int *i);
char			*extract_quoted_content(char *input, \
	int start, int len, char quote_char);

///////////////////////////
///////token_utils2.c//////
///////////////////////////
int				extract_token_len(char *input, int *index, int *start);
char			*extract_token(char *input, int *index, t_shell *shell);
int				check_quotes(char *input);
char			**tokenize_command(char *input, t_shell *shell);	
void			handle_word_count(char *str, int *i);

// Exec

int				open_file(char *file, int flags, int mode);
int				setup_files(t_redirection *redir);
int				setup_input_redirections(t_redirection *redir);
int				setup_output_redirections(t_redirection *redir);
int				has_input_redirection(t_redirection *redir);
void			close_files(int infile, int outfile);
char			*find_command(char **paths, char *cmd);
char			*get_path_env(char **envp);
int				ft_exec(t_cmd *cmd, char **envp, t_shell *shell);
int				execute_ve(t_cmd *cmd, char **envp);
int				loop_open_files(t_cmd *cmd);
int				handle_heredoc(char *delim);
int				execute_pipeline(t_cmd *cmd_list, t_shell *shell);
char			*execute_ve_2(t_cmd *cmd, char	*path_env, char	*full_path);
int				ft_exit(t_cmd *cmd, t_shell *shell);
int				setup_pipe(int pipefd[2]);

// expand.c

char			*expand_variables(char *str, t_shell *shell);
char			*get_env_value(char *var, t_shell *shell);
void			handle_child(t_cmd *cmd, int infile, int pipefd[2], \
	t_shell *shell);
int				wait_for_children(pid_t last_pid);

#endif