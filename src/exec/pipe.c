/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfirmin <lfirmin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 13:25:59 by tordner           #+#    #+#             */
/*   Updated: 2025/05/29 13:07:37 by lfirmin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern int g_child_running;

void	handle_child(t_cmd *cmd, int infile, int pipefd[2], t_shell *shell)
{
	if (dup2(infile, STDIN_FILENO) == -1)
		exit(1);
	if (cmd->next && dup2(pipefd[1], STDOUT_FILENO) == -1)
		exit(1);
	if (infile != STDIN_FILENO)
		close(infile);
	if (cmd->next)
	{
		close(pipefd[0]);
		close(pipefd[1]);
	}
	if (cmd->redir && loop_open_files(cmd) != 0)
		exit(1);
	if (is_builtin(cmd->args[0]))
		exit(execute_builtin(cmd, shell));
	execute_ve(cmd, shell->env);
	exit(1);
}

void	handle_parent(int *infile, int pipefd[2], t_cmd *cmd)
{
	if (*infile != STDIN_FILENO)
		close(*infile);
	if (cmd->next)
	{
		close(pipefd[1]);
		*infile = pipefd[0];
	}
	else if (pipefd[0] != -1)
		close(pipefd[0]);
}

int	run_child_pipe(t_cmd *cmd, t_shell *shell, int *infile)
{
	int		pipefd[2];
	pid_t	pid;

	if (cmd->next && pipe(pipefd) == -1)
		return (1);
	else if (!cmd->next)
	{
		pipefd[0] = -1;
		pipefd[1] = STDOUT_FILENO;
	}
	pid = fork();
	if (pid == -1)
		return (1);
	if (pid == 0)
		handle_child(cmd, *infile, pipefd, shell);
	handle_parent(infile, pipefd, cmd);
	return (0);
}

int	spawn_pipeline(t_cmd *cmd, t_shell *shell)
{
	int		infile;
	int		status;
	int		exit_status;

	g_child_running = 1;
	infile = STDIN_FILENO;
	while (cmd)
	{
		if (run_child_pipe(cmd, shell, &infile) != 0)
		{
			g_child_running = 0;
			return (1);
		}
		cmd = cmd->next;
	}
	exit_status = 0;
	while (wait(&status) > 0)
	{
		if (WIFEXITED(status))
			exit_status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
		{
			if (WTERMSIG(status) == SIGINT)
				exit_status = 130;
			else
				exit_status = 128 + WTERMSIG(status);
		}
	}
	g_child_running = 0;
	return (exit_status);
}

void	restore_fds(int saved_stdin, int saved_stdout)
{
	dup2(saved_stdin, STDIN_FILENO);
	dup2(saved_stdout, STDOUT_FILENO);
	close(saved_stdin);
	close(saved_stdout);
}

int	execute_pipeline(t_cmd *cmd_list, t_shell *shell)
{
	int		redir_status;
	int		saved_stdin, saved_stdout;

	if (cmd_list && !cmd_list->next && is_builtin(cmd_list->args[0]))
	{
		if (cmd_list->redir)
		{
			saved_stdin = dup(STDIN_FILENO);
			saved_stdout = dup(STDOUT_FILENO);
			redir_status = loop_open_files(cmd_list);
			if (redir_status != 0)
			{
				restore_fds(saved_stdin, saved_stdout);
				return (shell->exit_status = 1);
			}
			shell->exit_status = execute_builtin(cmd_list, shell);
			restore_fds(saved_stdin, saved_stdout);
			return (shell->exit_status);
		}
		return (shell->exit_status = execute_builtin(cmd_list, shell));
	}
	shell->exit_status = spawn_pipeline(cmd_list, shell);
	return (shell->exit_status);
}
