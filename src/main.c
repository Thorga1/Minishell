/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thorgal <thorgal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 17:17:15 by thorgal           #+#    #+#             */
/*   Updated: 2025/02/19 19:00:23 by thorgal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_welcome(void)
{
	printf("Welcome to our MiniShell.\n");
	return ;
}

void	minishell_loop(void)
{
	char	**tokens;
	char	*input;
	int		i;

	while (1)
	{
		input = readline("minishell> ");
		if (input == NULL)
		{
			printf("exit\n");
			free(input);
			break ;
		}
		i = 0;
		while (input[i] && (input[i] == ' ' || input[i] == '\t'))
			i++;
		if (input[i] != '\0')
			add_history(input);
		tokens = tokenize_command(input);
		if (tokens == NULL)
		{
			printf("Error: Tokenization failed\n");
			free(input);
			continue ;
		}
		i = 0;
		while (tokens[i])
		{
			printf("Token[%d]: %s\n", i, tokens[i]);
			free(tokens[i]);
			i++;
		}
		free(tokens);
		free(input);
	}
}

int	main(void)
{
	print_welcome();
	minishell_loop();
	return (0);
}
