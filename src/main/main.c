/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thorgal <thorgal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 17:17:15 by thorgal           #+#    #+#             */
/*   Updated: 2025/03/04 16:39:30 by thorgal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char **copy_env(char **envp)
{
	char	**env;
	int		i;

	i = 0;
	while (envp[i])
		i++;
	env = malloc(sizeof(char *) * (i + 1));
	if (!env)
		return (NULL);
	i = 0;
	while (envp[i])
	{
		env[i] = strdup(envp[i]);
		if (!env[i])
		{
			while (--i >= 0)
				free(env[i]);
			free(env);
			return (NULL);
		}
		i++;
	}
	env[i] = NULL;
	return (env);
}

void	initialize_shell(t_shell *shell, char **envp)
{
	shell->env = copy_env(envp);
	shell->exit_status = 0;
	shell->running = 1;
	printf("Welcome to our MiniShell.\n");
}

static int execute_builtin(char **tokens, t_shell *shell)
{
	if (!tokens || !tokens[0])
		return (0);
	
	if (strcmp(tokens[0], "echo") == 0)
		return (ft_echo(tokens));
	else if (strcmp(tokens[0], "cd") == 0)
		return (ft_cd(tokens[1]));
	else if (strcmp(tokens[0], "pwd") == 0)
	{
		ft_pwd();
		return (0);
	}
	else if (strcmp(tokens[0], "ls") == 0)
		return (ft_ls());
	else if (strcmp(tokens[0], "clear") == 0)
		return (ft_clear());
	else if (strcmp(tokens[0], "exit") == 0)
	{
		shell->running = 0;
		return (0);
	}
	return (-1); // Pas une commande builtin
}

static void process_input(char *input, t_shell *shell)
{
	char			**tokens;
	int				i;
	int				ret;
	t_token_type	type;

	tokens = tokenize_command(input);
	if (!tokens)
	{
		printf("Error: Tokenization failed\n");
		shell->exit_status = 1;
		return;
	}

	// ret = execute_builtin(tokens, shell);
	// if (ret == -1)
	// {
	// 	printf("Command not found: %s\n", tokens[0]);
	// 	shell->exit_status = 127;
	// }
	// else
	// 	shell->exit_status = ret;

	
	// Libération des tokens
	i = 0;
	while (tokens[i])
	{
		type = classify_token(tokens[i]);
		printf("Token[%d]: %s → Type: %d\n", i, tokens[i], type);
		i++;
	}
	i = 0;
	while (tokens[i])
		free(tokens[i++]); 
	free(tokens);
}

void	minishell_loop(t_shell *shell)
{
	char	*input;
	char	*dir_name;
	char	*prompt;
	int		i;

	while (shell->running)
	{
		dir_name = get_current_dir_name();
		prompt = malloc(strlen(dir_name) + 35); // Plus d'espace pour les codes couleur
		if (prompt)
		{
			// Si exit_status est 0 (succès) -> flèche verte, sinon rouge
			if (shell->exit_status == 0)
				sprintf(prompt, "\033[1;32m➜\033[0m  \033[1;36m%s\033[0m ❯ ", dir_name);
			else
				sprintf(prompt, "\033[1;31m➜\033[0m  \033[1;36m%s\033[0m ❯ ", dir_name);
		}
		else
			prompt = strdup("➜  ❯ ");
			
		input = readline(prompt);
		free(prompt);
		free(dir_name);
		
		if (!input)
		{
			printf("exit\n");
			break;
		}

		i = 0;
		while (input[i] && (input[i] == ' ' || input[i] == '\t'))
			i++;
		
		if (input[i] != '\0')
		{
			add_history(input);
			process_input(input, shell);
		}
		free(input);
	}
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
