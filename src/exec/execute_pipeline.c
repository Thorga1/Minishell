/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipeline.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tordner <tordner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 03:04:07 by tordner           #+#    #+#             */
/*   Updated: 2025/06/03 03:04:35 by tordner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handle_single_builtin(t_cmd *cmd, t_shell *shell)
{
	int	saved_stdin;
	int	saved_stdout;
	int	redir_status;

	if (!cmd->redir)
		return (execute_builtin(cmd, shell));
	saved_stdin = dup(STDIN_FILENO);
	saved_stdout = dup(STDOUT_FILENO);
	shell->signaled = 0;
	redir_status = loop_open_files(cmd);
	if (redir_status != 0)
	{
		restore_fds(saved_stdin, saved_stdout);
		return (1);
	}
	shell->exit_status = execute_builtin(cmd, shell);
	restore_fds(saved_stdin, saved_stdout);
	if (g_signal)
	{
		shell->signaled = 1;
		shell->exit_status = g_signal;
	}
	return (shell->exit_status);
}

static int	handle_pipeline(t_cmd *cmd_list, t_shell *shell)
{
	return (spawn_pipeline(cmd_list, shell));
}

int	execute_pipeline(t_cmd *cmd_list, t_shell *shell)
{
	if (cmd_list && !cmd_list->next && is_builtin(cmd_list->args[0]))
		return (handle_single_builtin(cmd_list, shell));
	return (handle_pipeline(cmd_list, shell));
}
