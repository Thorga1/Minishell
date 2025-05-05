/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thorgal <thorgal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 13:25:59 by tordner           #+#    #+#             */
/*   Updated: 2025/05/05 15:10:55 by thorgal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	handle_child_pipe(int pipefd[2], int infile)
{
	close(pipefd[0]);
	dup2(infile, 0);
	dup2(pipefd[1], 1);
	close(infile);
	close(pipefd[1]);
}

// int	execute_pipeline(t_cmd *cmd_list, t_shell *shell)
// {
// 	int		pipefd[2];
// 	int		infile;
// 	pid_t	pid;
// 	t_cmd	*cmd;

// 	infile = STDIN_FILENO;
// 	cmd = cmd_list;

// 	if (cmd && !cmd->next && is_builtin(cmd->args[0]))
// 	{
// 		if (cmd->redir)
// 			loop_open_files(cmd);
// 		shell->exit_status = execute_builtin(cmd, shell);
// 		return (shell->exit_status);
// 	}
// 	while (cmd)
// 	{
// 		if (cmd->next)
// 			pipe(pipefd);
// 		else
// 			pipefd[1] = STDOUT_FILENO;

// 		pid = fork();
// 		if (pid == 0)
// 		{
// 			if (cmd->next)
// 				handle_child_pipe(pipefd, infile, cmd, shell->env);
// 			else
// 				dup2(infile, STDIN_FILENO);

// 			if (cmd->redir)
// 				loop_open_files(cmd);

// 			if (is_builtin(cmd->args[0]))
// 				exit(execute_builtin(cmd, shell));
// 			else
// 				execute_ve(cmd, shell->env);
// 		}
// 		else
// 		{
// 			if (infile != STDIN_FILENO)
// 				close(infile);
// 			if (cmd->next)
// 			{
// 				close(pipefd[1]);
// 				infile = pipefd[0];
// 			}
// 		}
// 		cmd = cmd->next;
// 	}
// 	while (wait(NULL) > 0)
// 		;
// 	return (shell->exit_status);
// }

static void	exec_child(t_cmd *cmd, int infile, int pipefd[2], t_shell *shell)
{
	if (cmd->next)
		handle_child_pipe(pipefd, infile);
	else
		dup2(infile, STDIN_FILENO);
	if (cmd->redir)
		loop_open_files(cmd);
	if (is_builtin(cmd->args[0]))
		exit(execute_builtin(cmd, shell));
	else
		execute_ve(cmd, shell->env);
}

static void	exec_parent(int *infile, int pipefd[2], t_cmd *cmd)
{
	if (*infile != STDIN_FILENO)
		close(*infile);
	if (cmd->next)
	{
		close(pipefd[1]);
		*infile = pipefd[0];
	}
}

static void	spawn_processes(t_cmd *cmd, t_shell *shell, int infile)
{
	int		pipefd[2];
	pid_t	pid;

	while (cmd)
	{
		if (cmd->next)
			pipe(pipefd);
		else
			pipefd[1] = STDOUT_FILENO;
		pid = fork();
		if (pid == 0)
			exec_child(cmd, infile, pipefd, shell);
		else
			exec_parent(&infile, pipefd, cmd);
		cmd = cmd->next;
	}
	while (wait(NULL) > 0)
		;
}

int	execute_pipeline(t_cmd *cmd_list, t_shell *shell)
{
	int		infile;

	infile = STDIN_FILENO;
	if (cmd_list && !cmd_list->next && is_builtin(cmd_list->args[0]))
	{
		if (cmd_list->redir)
			loop_open_files(cmd_list);
		return (shell->exit_status = execute_builtin(cmd_list, shell));
	}
	spawn_processes(cmd_list, shell, infile);
	return (shell->exit_status);
}
