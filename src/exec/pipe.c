/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tordner <tordner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 13:25:59 by tordner           #+#    #+#             */
/*   Updated: 2025/04/24 18:00:50 by tordner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	handle_child_pipe(int pipefd[2], int infile, t_cmd *cmd, char **envp)
{
	close(pipefd[0]);
	dup2(infile, 0);
	dup2(pipefd[1], 1);
	close(infile);
	close(pipefd[1]);
}

int execute_pipeline(t_cmd *cmd_list, t_shell *shell)
{
	int		pipefd[2];
	int		infile;
	pid_t	pid;
	t_cmd	*cmd;

	infile = STDIN_FILENO;
	cmd = cmd_list;
	while (cmd)
	{
		if (cmd->next)
			pipe(pipefd);
		else
			pipefd[1] = STDOUT_FILENO;

		pid = fork();
		if (pid == 0)
		{
		    if (cmd->next)
		        handle_child_pipe(pipefd, infile, cmd, shell->env);
			else
		        dup2(infile, STDIN_FILENO);
			if (cmd->redir)
				loop_open_files(cmd);
		    if (is_builtin(cmd->args[0]))
		        exit(execute_builtin(cmd, shell));
			else
		        execute_ve(cmd, shell->env);
		}
		else
		{
			if (infile != STDIN_FILENO)
				close(infile);
			if (cmd->next)
			{
				close(pipefd[1]);
				infile = pipefd[0];
			}
		}
		cmd = cmd->next;
	}
	while (wait(NULL) > 0)
		;
	return (shell->exit_status);
}
