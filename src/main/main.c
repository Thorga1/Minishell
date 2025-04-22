/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfirmin <lfirmin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 17:17:15 by lfirmin           #+#    #+#             */
/*   Updated: 2025/04/22 15:16:18 by lfirmin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	initialize_shell(t_shell *shell, char **envp)
{
	shell->env = copy_env(envp);
	shell->exit_status = 0;
	shell->running = 1;
	printf(WELCOME_MESS);
}

int	is_builtin(char *cmd)
{
	return (ft_strcmp(cmd, "echo") == 0
		|| ft_strcmp(cmd, "cd") == 0
		|| ft_strcmp(cmd, "pwd") == 0
		|| ft_strcmp(cmd, "exit") == 0
		|| ft_strcmp(cmd, "env") == 0
		|| ft_strcmp(cmd, "export") == 0
		|| ft_strcmp(cmd, "unset") == 0);
}

int	execute_builtin(t_cmd *cmd, t_shell *shell)
{
	if (!cmd || !cmd->args || !cmd->args[0])
		return (1);
	if (ft_strcmp(cmd->args[0], "echo") == 0)
		return (ft_echo(cmd, shell));
	else if (ft_strcmp(cmd->args[0], "cd") == 0)
		return (ft_cd(cmd, shell));
	else if (ft_strcmp(cmd->args[0], "pwd") == 0)
		return (ft_pwd());
	else if (ft_strcmp(cmd->args[0], "exit") == 0)
		return (shell->running = 0);
	else if (ft_strcmp(cmd->args[0], "env") == 0)
		return (ft_env(shell));
	else if (ft_strcmp(cmd->args[0], "export") == 0)
		return (ft_export(shell, cmd));
	else if (ft_strcmp(cmd->args[0], "unset") == 0)
		return (ft_unset(shell, cmd));
	return (1);
}

int	execute_command(t_cmd *cmd, t_shell *shell)
{
	int	saved_stdin;
	int	saved_stdout;

	if (!cmd || !cmd->args || !cmd->args[0])
		return (1);
	if (is_builtin(cmd->args[0]))
	{
		saved_stdin = dup(STDIN_FILENO);
		saved_stdout = dup(STDOUT_FILENO);
		if (cmd->redir)
			loop_open_files(cmd);
		shell->exit_status = execute_builtin(cmd, shell);
		dup2(saved_stdin, STDIN_FILENO);
		dup2(saved_stdout, STDOUT_FILENO);
		close(saved_stdin);
		close(saved_stdout);
	}
	else
		shell->exit_status = ft_exec(cmd, shell, shell->env);
	return (shell->exit_status);
}

int	main(void)
{
	t_shell		shell;
	extern char	**environ;
	int			i;

	initialize_shell(&shell, environ);
	minishell_loop(&shell);
	if (shell.env)
	{
		i = 0;
		while (shell.env[i])
			free(shell.env[i++]);
		free(shell.env);
	}
	return (shell.exit_status);
}
