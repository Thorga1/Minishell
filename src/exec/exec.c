/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfirmin <lfirmin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 13:25:52 by tordner           #+#    #+#             */
/*   Updated: 2025/05/19 06:27:28 by lfirmin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <signal.h>

extern int g_child_running;

int	setup_pipe(int pipefd[2])
{
	if (pipe(pipefd) == -1)
	{
		write(2, "Error creating pipe\n", 21);
		return (1);
	}
	return (0);
}

int	file_exists(const char *path)
{
	return (access(path, F_OK));
}

int	execute_ve(t_cmd *cmd, char **envp)
{
	char	*full_path;
	char	*path_env;

	full_path = NULL;
	if (cmd->args[0][0] == '/' || cmd->args[0][0] == '.')
	{
		if (file_exists(cmd->args[0]) != 0)
		{
			write(2, "Error: No such file or directory !\n", 36);
			exit(127);
		}
		else if (access(cmd->args[0], X_OK) == 0)
			execve(cmd->args[0], cmd->args, envp);
		write(2, "Error: execve error !\n", 23);
		exit(127);
	}
	path_env = get_path_env(envp);
	full_path = execute_ve_2(cmd, path_env, full_path);
	execve(full_path, cmd->args, envp);
	write(1, "Error: Command execution failed\n", 32);
	exit(126);
}

char *execute_ve_2(t_cmd *cmd, char	*path_env, char	*full_path)
{
	if (!path_env)
	{
		write(2, "Error: PATH not found\n", 22);
		exit(127);
	}
	full_path = find_command(ft_split(path_env, ':'), cmd->args[0]);
	if (!full_path)
	{
		write(2, "Error: Command not found\n", 25);
		exit(127);
	}
	return (full_path);
}

void	run_child_process(t_cmd *cmd, char **envp)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	execute_ve(cmd, envp);
}

int	ft_exec(t_cmd *cmd, char **envp)
{
	pid_t	pid;
	int		status;
	int		exit_status;

	g_child_running = 1;
	pid = fork();
	if (pid == -1)
	{
		write(2, "Error forking process\n", 23);
		return (1);
	}
	if (pid == 0)
	{
		if (cmd->redir)
		{
			if (loop_open_files(cmd) != 0)
				exit(1);
		}
		run_child_process(cmd, envp);
	}
	waitpid(pid, &status, 0);
	g_child_running = 0;
	if (WIFEXITED(status))
		exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		exit_status = 128 + WTERMSIG(status);
	else
		exit_status = 1;
	return (exit_status);
}
