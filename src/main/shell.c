/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfirmin <lfirmin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 15:38:19 by lfirmin           #+#    #+#             */
/*   Updated: 2025/04/23 13:11:02 by lfirmin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <signal.h>
#include <termios.h>

static t_shell *g_shell;
volatile sig_atomic_t g_child_running = 0;

char	*create_git_prompt(char *dir_name, int exit_status)
{
	char	*git_branch;
	char	*prompt;
	size_t	prompt_size;

	git_branch = get_git_branch();
	if (!git_branch)
		return (NULL);
	prompt_size = ft_strlen(dir_name) + ft_strlen(git_branch) + 100;
	prompt = malloc(prompt_size);
	if (prompt)
	{
		if (exit_status == 0)
			snprintf(prompt, prompt_size, GREEN PROMPT_GIT, \
					dir_name, git_branch);
		else
			snprintf(prompt, prompt_size, RED PROMPT_GIT, \
					dir_name, git_branch);
	}
	free(git_branch);
	return (prompt);
}

char	*create_standard_prompt(char *dir_name, int exit_status)
{
	char	*prompt;
	size_t	prompt_size;

	prompt_size = ft_strlen(dir_name) + 100;
	prompt = malloc(prompt_size);
	if (prompt)
	{
		if (exit_status == 0)
			printf(prompt, prompt_size, GREEN PROMPT_STD, dir_name);
		else
			printf(prompt, prompt_size, RED PROMPT_STD, dir_name);
	}
	return (prompt);
}

char	*generate_prompt(t_shell *shell)
{
	char	*dir_name;
	char	*prompt;

	dir_name = get_current_dir_name();
	if (!dir_name)
		return (ft_strdup("➜  ❯ "));
	if (is_git_repository())
		prompt = create_git_prompt(dir_name, shell->exit_status);
	else
		prompt = create_standard_prompt(dir_name, shell->exit_status);
	free(dir_name);
	if (prompt)
		return (prompt);
	else
		return (ft_strdup("➜  ❯ "));
}

void sigint_handler(int sig)
{
	char *new_prompt;
	if (g_child_running)
		return;
	write(1, "\n", 1);
	rl_on_new_line();
	if (g_shell)
		g_shell->exit_status = 130;
	new_prompt = generate_prompt(g_shell);
	rl_set_prompt(new_prompt);
	rl_replace_line("", 0);
	rl_redisplay();
}

void handle_input(char *input, t_shell *shell)
{
	int	i;

	i = 0;
	while (input[i] && (input[i] == ' ' || input[i] == '\t'))
		i++;
	if (input[i] != '\0')
	{
		add_history(input);
		process_input(input, shell);
	}
}

void	minishell_loop(t_shell *shell)
{
	g_shell = shell;
	rl_catch_signals = 0;
	struct termios term;
	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
	rl_initialize();
	while (shell->running)
	{
		signal(SIGINT, sigint_handler);
		signal(SIGQUIT, SIG_IGN);
		char	*prompt = generate_prompt(shell);
		char	*input = readline(prompt);
		free(prompt);
		if (!input)
		{
			printf("exit\n");
			break ;
		}
		handle_input(input, shell);
		free(input);
	}
}
