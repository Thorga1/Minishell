/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thorgal <thorgal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 17:17:15 by thorgal           #+#    #+#             */
/*   Updated: 2025/03/10 17:32:16 by thorgal          ###   ########.fr       */
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

static int execute_builtin(t_smd *cmd, t_shell *shell)
{
	if (!cmd || !cmd->args || !cmd->args[0])
		return (0);
	if (strcmp(cmd->args[0], "echo") == 0)
		return (ft_echo(cmd, shell));
	else if (strcmp(cmd->args[0], "cd") == 0)
		return (ft_cd(cmd, shell));
	else if (strcmp(cmd->args[0], "pwd") == 0)
		return (ft_pwd(), 0);
	else if (strcmp(cmd->args[0], "ls") == 0)
		return (ft_ls());
	else if (strcmp(cmd->args[0], "clear") == 0)
		return (ft_clear());
	else if (strcmp(cmd->args[0], "exit") == 0)
		return (shell->running = 0, 0);
	else if (strcmp(cmd->args[0], "env") == 0)
		return (ft_env(shell));
	else if (strcmp(cmd->args[0], "export") == 0)
		return (ft_export(shell, cmd));
	else if (strcmp(cmd->args[0], "unset") == 0)
		return (ft_unset(shell, cmd));
	return (-1);
}

void process_input(char *input, t_shell *shell)
{
	char			**tokens;
	int				i;
	int				ret;
	t_smd			*cmd_list;

	tokens = tokenize_command(input);
	if (!tokens)
	{
		printf(ERROR_TOKEN);
		shell->exit_status = 1;
		return;
	}

	if (validate_syntax(tokens))
	{
		i = 0;
		while (tokens[i])
			free(tokens[i++]); 
		free(tokens);
		return;
	}
	
	cmd_list = parse_tokens_to_list(tokens);
	if (cmd_list)
	{
		ret = execute_builtin(cmd_list, shell);
		if (ret == -1)
		{
			printf(ERROR_NOT_FOUND, cmd_list->args[0]);
			shell->exit_status = 127;
		}
		else
			shell->exit_status = ret;
		
		free_cmd_list(cmd_list);
	}
	i = 0;
	while (tokens[i])
		free(tokens[i++]);
	free(tokens);
}

int main(void)
{
	t_shell shell;
	extern char **environ;
	
	initialize_shell(&shell, environ);
	minishell_loop(&shell);	// Cleanup
	if (shell.env)
	{
		int i = 0;
		while (shell.env[i])
			free(shell.env[i++]);
		free(shell.env);
	}
	return (shell.exit_status);
}
