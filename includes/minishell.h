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
# include "messages.h"

////////////////////////////////////////////////////////////////
////////////////////////////ENUM////////////////////////////////
////////////////////////////////////////////////////////////////
typedef enum e_token_type
{
	TOKEN_WORD,
	TOKEN_REDIRECTION_IN,		// <
	TOKEN_REDIRECTION_OUT,		// >
	TOKEN_APPEND,				// >>
	TOKEN_HEREDOC,				// <<
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
} t_redirection;

typedef struct s_cmd
{
	char			**args;
	t_redirection	*redir;
	struct s_cmd	*next;
} t_cmd;

typedef struct s_shell
{
	char    **env;
	int     exit_status;
	int     running;
} t_shell;

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
void			sigint_handler(int sig);
void			handle_input(char *input, t_shell *shell);
char			*generate_prompt(t_shell *shell);
char			*create_git_prompt(char *dir_name, int exit_status);
char			*create_standard_prompt(char *dir_name, int exit_status);


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
int				ft_cd(t_cmd *cmd, t_shell *shell);

//////////////////
///////env.c//////
//////////////////
int				ft_env(t_shell *shell);

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
char			*get_env_value(char *var_name, t_shell *shell);
int				is_env_var(char *str);
void			print_echo_args(char **args, int i, t_shell *shell, int first);
int				ft_echo(t_cmd *cmd, t_shell *shell);

/////////////////////////
///////export_utils.c////
/////////////////////////
int				handle_env_var(t_shell *shell, char *arg);


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
void 			free_cmd_node(t_cmd *cmd);
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

///////////////////////////
///////token_utils2.c//////
///////////////////////////
int				extract_token_len(char *input, int *index, int *start);
char			*extract_token(char *input, int *index);
int				check_quotes(char *input);
char			**tokenize_command(char *input);	
void			handle_word_count(char *str, int *i);

// Exec

int		open_file(char *file, int flags, int mode);
int		setup_files(t_redirection *redir);
void	close_files(int infile, int outfile);
char	*find_command(char **paths, char *cmd);
char	*get_path_env(char **envp);
int		ft_exec(t_cmd *cmd, t_shell *shell, char **envp);
int		execute_ve(t_cmd *cmd, char **envp);
int		loop_open_files(t_cmd *cmd);
int		handle_heredoc(char *delim);
int		execute_pipeline(t_cmd *cmd_list, t_shell *shell);


#endif