/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfirmin <lfirmin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 17:17:15 by lfirmin           #+#    #+#             */
/*   Updated: 2025/04/19 13:54:52 by lfirmin          ###   ########.fr       */
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

int	execute_builtin(t_cmd *cmd, t_shell *shell)
{
	if (!cmd || !cmd->args || !cmd->args[0])
		return (0);
	if (ft_strcmp(cmd->args[0], "echo") == 0)
		return (ft_echo(cmd, shell));
	else if (ft_strcmp(cmd->args[0], "cd") == 0)
		return (ft_cd(cmd, shell));
	else if (ft_strcmp(cmd->args[0], "pwd") == 0)
		return (ft_pwd(), 0);
	else if (ft_strcmp(cmd->args[0], "exit") == 0)
		return (shell->running = 0, 0);
	else if (ft_strcmp(cmd->args[0], "env") == 0) //out
		return (ft_env(shell));
	else if (ft_strcmp(cmd->args[0], "export") == 0) // out
		return (ft_export(shell, cmd));
	else if (ft_strcmp(cmd->args[0], "unset") == 0)
		return (ft_unset(shell, cmd));
	else
	{
		int status = ft_exec(cmd, shell->env);
		shell->exit_status = status; // Met à jour le code de retour dans la structure shell
		return (status);
	}
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
