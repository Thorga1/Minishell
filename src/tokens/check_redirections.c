/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_redirections.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfirmin <lfirmin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 17:17:19 by tordner           #+#    #+#             */
/*   Updated: 2025/05/29 14:25:34 by lfirmin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_redirection(char *token)
{
	t_token_type	type;

	type = classify_token(token);
	return (type);
}

int	check_further_redirections(char **tokens, int i)
{
	if (is_redirection(tokens[i]) && !tokens[i + 1])
	{
		write(STDERR_FILENO, "Syntax error: Redirection cannot appear at the end\n", 52);
		return (2);
	}
	if (is_redirection(tokens[i]) && is_redirection(tokens[i + 1]))
	{
		write(STDERR_FILENO, "Syntax error: Consecutive redirection operators are not allowed\n", 65);
		return (2);
	}
	if (tokens[i] && tokens[i + 1] && classify_token(tokens[i]) == TOKEN_PIPE)
	{
		if (is_redirection(tokens[i + 1]))
		{
			write(STDERR_FILENO, "Syntax error: Redirection cannot follow a pipe\n", 48);
			return (2);
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
		write(STDERR_FILENO, "Syntax error: Redirection cannot appear at the beginning\n", 57);
		return (2);
	}
	while (tokens[i])
	{
		if (check_further_redirections(tokens, i))
			return (2);
		if (tokens[i] && is_redirection(tokens[i]) && !tokens[i - 1])
		{
			write(STDERR_FILENO, "Syntax error: Redirection must follow a command or word\n", 56);
			return (2);
		}
		i++;
	}
	return (0);
}