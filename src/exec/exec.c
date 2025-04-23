/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfirmin <lfirmin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 13:25:52 by tordner           #+#    #+#             */
/*   Updated: 2025/04/23 03:02:28 by lfirmin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <signal.h>
extern volatile sig_atomic_t g_child_running;

int	setup_pipe(int pipefd[2])
{
	if (pipe(pipefd) == -1)
	{
		write(1, "Error creating pipe\n", 21);
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

	if (cmd->args[0][0] == '/' || cmd->args[0][0] == '.') // Chemin absolu ou relatif
	{
		if (file_exists(cmd->args[0]) != 0)
		{
			write(1, "Error: No such file or directory !\n", 36);
			exit(127); // Quitter le processus enfant avec code 127 (commande non trouvée)
		}
		else if (access(cmd->args[0], X_OK) == 0)
			execve(cmd->args[0], cmd->args, envp);
		write(1, "Error: execve error !\n", 23);
		exit(127); // Quitter le processus enfant avec code 127 (commande non trouvée)
	}
	path_env = get_path_env(envp);
	if (!path_env)
	{
		write(1, "Error: PATH not found\n", 22);
		exit(127);
	}
	full_path = find_command(ft_split(path_env, ':'), cmd->args[0]);
	if (!full_path)
	{
		write(1, "Error: Command not found\n", 25);
		exit(127);
	}
	execve(full_path, cmd->args, envp);
	write(1, "Error: Command execution failed\n", 32);
	exit(126); // Quitter le processus enfant avec code 126 (commande non exécutable)
}

// void	run_child_process(int pipefd[2], int infile, t_cmd *cmd, char **envp)
// {
// 	close(pipefd[0]);
// 	dup2(infile, 0);
// 	dup2(pipefd[1], 1);
// 	close(infile);
// 	close(pipefd[1]);
// 	execute_command(cmd, envp);
// }

// void	run_parent_process(int pipefd[2], int outfile, t_cmd *cmd, char **envp)
// {
// 	close(pipefd[1]);
// 	dup2(pipefd[0], 0);
// 	dup2(outfile, 1);
// 	close(pipefd[0]);
// 	close(outfile);
// 	execute_command(cmd, envp);
// }

void	run_child_process(t_cmd *cmd, t_shell *shell, char **envp)
{
	// Dans l'enfant, restaurer le comportement par défaut des signaux
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	execute_ve(cmd, envp); //add parameter from data structure for return value from execve
}

int	ft_exec(t_cmd *cmd, t_shell *shell, char **envp)
{
	pid_t	pid;
	int		status;

	// Indique qu'un child est en cours
	g_child_running = 1;
	pid = fork();
	if (pid == -1)
	{
		write(1, "Error forking process\n", 23);
		return (1);
	}
	if (pid == 0)
	{
		// Faire les redirections uniquement dans le processus enfant
		if (cmd->redir)
			loop_open_files(cmd);
		
		run_child_process(cmd, shell, envp);
	}
	// Le processus parent attend sans modifier ses descripteurs
	waitpid(pid, &status, 0);
	// Child terminé, revient en mode prompt
	g_child_running = 0;
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (0);
}
