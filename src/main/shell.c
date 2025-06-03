/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tordner <tordner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 15:38:19 by lfirmin           #+#    #+#             */
/*   Updated: 2025/06/03 03:01:28 by tordner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	handle_input(char *input, t_shell *shell)
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

static void	handle_signal_state(t_shell *shell)
{
	if (g_signal && !shell->child_running)
	{
		shell->exit_status = g_signal;
		g_signal = 0;
	}
}

static char	*get_input(char *prompt)
{
	char	*input;

	input = readline(prompt);
	free(prompt);
	return (input);
}

static void	init_terminal_settings(void)
{
	struct termios	term;

	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag &= ~(ECHOCTL);
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
	rl_initialize();
}

void	minishell_loop(t_shell *shell)
{
	char	*input;
	char	*prompt;

	init_terminal_settings();
	while (shell->running)
	{
		set_signal_parent();
		prompt = generate_prompt(shell);
		input = get_input(prompt);
		if (!input)
		{
			printf("exit\n");
			break ;
		}
		handle_signal_state(shell);
		handle_input(input, shell);
		free(input);
	}
}
