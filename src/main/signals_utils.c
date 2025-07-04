/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tordner <tordner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 00:58:26 by tordner           #+#    #+#             */
/*   Updated: 2025/06/03 02:58:02 by tordner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	check_if_signal(t_shell *shell)
// {
// 	if (shell->signaled == 1 && g_signal == 128 + SIGQUIT)
// 	{
// 		ft_putstr_fd("Quit (core dumped)\n", 2);
// 		shell->exit_status = g_signal;
// 	}
// 	if (g_signal == 128 + SIGINT && shell->signaled == 1)
// 	{
// 		write(STDERR_FILENO, "\n", 1);
// 		shell->exit_status = g_signal;
// 	}
// 	if (shell->exit_status == 128 + SIGSEGV && shell->signaled == 1)
// 		ft_putstr_fd("Segmentation fault (core dumped)\n", STDERR_FILENO);
// 	if (shell->signaled == 1)
// 	{
// 		shell->signaled = 0;
// 		g_signal = 0;
// 	}
// }

void	handle_signal_parent(int num)
{
	g_signal = num + 128;
}

int	sig_event(void)
{
	return (EXIT_SUCCESS);
}
