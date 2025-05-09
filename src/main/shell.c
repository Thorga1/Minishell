/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfirmin <lfirmin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 15:38:19 by lfirmin           #+#    #+#             */
/*   Updated: 2025/05/05 15:41:26 by lfirmin          ###   ########.fr       */
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
	char	*tmp1;
	char	*tmp2;

	git_branch = get_git_branch();
	if (!git_branch)
		return (NULL);
	if (exit_status == 0)
	{
		tmp1 = ft_strjoin(GREEN "➜\033[0m  \033[1;36m", dir_name);
		if (!tmp1)
		{
			free(git_branch);
			return (NULL);
		}
		tmp2 = ft_strjoin(tmp1, "\033[0m \033[1;32mgit:(\033[1;31m");
		free(tmp1);
		if (!tmp2)
		{
			free(git_branch);
			return (NULL);
		}
		tmp1 = ft_strjoin(tmp2, git_branch);
		free(tmp2);
		if (!tmp1)
		{
			free(git_branch);
			return (NULL);
		}
		prompt = ft_strjoin(tmp1, "\033[1;32m)\033[0m ❯ ");
		free(tmp1);
	}
	else
	{
		tmp1 = ft_strjoin(RED "➜\033[0m  \033[1;36m", dir_name);
		if (!tmp1)
		{
			free(git_branch);
			return (NULL);
		}
		tmp2 = ft_strjoin(tmp1, "\033[0m \033[1;32mgit:(\033[1;31m");
		free(tmp1);
		if (!tmp2)
		{
			free(git_branch);
			return (NULL);
		}
		tmp1 = ft_strjoin(tmp2, git_branch);
		free(tmp2);
		if (!tmp1)
		{
			free(git_branch);
			return (NULL);
		}
		prompt = ft_strjoin(tmp1, "\033[1;32m)\033[0m ❯ ");
		free(tmp1);
	}
	free(git_branch);
	return (prompt);
}

char	*create_standard_prompt(char *dir_name, int exit_status)
{
	char	*prompt;
	char	*tmp;

	if (exit_status == 0)
	{
		tmp = ft_strjoin(GREEN "➜\033[0m  \033[1;36m", dir_name);
		if (!tmp)
			return (NULL);
		prompt = ft_strjoin(tmp, "\033[0m ❯ ");
		free(tmp);
	}
	else
	{
		tmp = ft_strjoin(RED "➜\033[0m  \033[1;36m", dir_name);
		if (!tmp)
			return (NULL);
		prompt = ft_strjoin(tmp, "\033[0m ❯ ");
		free(tmp);
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

	(void)sig;
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
	struct termios term;
	char	*prompt;
	char	*input;

	g_shell = shell;
	rl_catch_signals = 0;
	tcgetattr(STDIN_FILENO, &term);
	// term.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
	rl_initialize();
	while (shell->running)
	{
		signal(SIGINT, sigint_handler);
		signal(SIGQUIT, SIG_IGN);
		prompt = generate_prompt(shell);
		input = readline(prompt);
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
