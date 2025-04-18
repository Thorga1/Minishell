/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_redirections.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tordner <tordner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 17:17:19 by tordner           #+#    #+#             */
/*   Updated: 2025/04/18 13:57:59 by tordner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_redirection(char *token)
{
	t_token_type	type;

	type = classify_token(token);
	return (type);
}

static int	check_further_redirections(char **tokens, int i)
{
	if (is_redirection(tokens[i]) && !tokens[i + 1])
	{
		printf("Syntax error: Redirection cannot appear at the end\n");
		return (1);
	}
	if (is_redirection(tokens[i]) && is_redirection(tokens[i + 1]))
	{
		printf("Syntax error: Consecutive"
			"redirection operators are not allowed\n");
		return (1);
	}
	if (tokens[i] && tokens[i + 1] && classify_token(tokens[i]) == TOKEN_PIPE)
	{
		if (is_redirection(tokens[i + 1]))
		{
			printf("Syntax error: Redirection cannot follow a pipe\n");
			return (1);
		}
	}
	return (0);
}

int	validate_redirections(char **tokens)
{
	int	i;

	i = 0;
	if (is_redirection(tokens[i]))
	{
		printf("Syntax error: Redirection cannot appear at the beginning\n");
		return (1);
	}
	while (tokens[i])
	{
		if (check_further_redirections(tokens, i))
			return (1);
		if (tokens[i] && is_redirection(tokens[i]) && !tokens[i - 1])
		{
			printf("Syntax error: Redirection must follow a command or word\n");
			return (1);
		}
		i++;
	}
	return (0);
}