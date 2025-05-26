/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfirmin <lfirmin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 15:38:19 by lfirmin           #+#    #+#             */
/*   Updated: 2025/05/26 14:52:43 by lfirmin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int g_child_running = 0;

char	*create_standard_prompt(char *dir_name, int exit_status)
{
	char	*prompt;
	char	*tmp;

	if (exit_status == 0)
	{
		tmp = ft_strjoin(GREEN "➜\001\033[0m\002  \001\033[1;36m\002", dir_name);
		if (!tmp)
			return (NULL);
		prompt = ft_strjoin(tmp, "\001\033[0m\002 ❯ ");
		free(tmp);
	}
	else
	{
		tmp = ft_strjoin(RED "➜\001\033[0m\002  \001\033[1;36m\002", dir_name);
		if (!tmp)
			return (NULL);
		prompt = ft_strjoin(tmp, "\001\033[0m\002 ❯ ");
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
	(void)sig;
	if (g_child_running)
		return;
	write(1, "\n", 1);
	rl_on_new_line();
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
		if (shell->exit_status == 130)
			shell->exit_status = 130;
	}
}
