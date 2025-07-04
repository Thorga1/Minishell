/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_redirections.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tordner <tordner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 17:17:19 by tordner           #+#    #+#             */
/*   Updated: 2025/06/03 02:50:31 by tordner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_redirection(char *token)
{
	t_token_type	type;

	type = classify_token(token);
	return (type == TOKEN_REDIRECTION_IN || type == TOKEN_REDIRECTION_OUT
		|| type == TOKEN_APPEND || type == TOKEN_HEREDOC);
}

int	check_further_redirections(char **tokens, int i)
{
	if (is_redirection(tokens[i]) && !tokens[i + 1])
	{
		write(STDERR_FILENO, \
			"Syntax error: Redirection cannot appear at the end\n", 52);
		return (2);
	}
	if (is_redirection(tokens[i]) && is_redirection(tokens[i + 1]))
	{
		write(STDERR_FILENO, "Syntax error: Consecutive redirection operators "
			"are not allowed\n", 65);
		return (2);
	}
	return (0);
}

static int	has_valid_command(char **tokens)
{
	int	j;
	int	has_command;

	j = 0;
	has_command = 0;
	while (tokens[j])
	{
		if (classify_token(tokens[j]) == TOKEN_WORD)
		{
			if (j == 0 || !is_redirection(tokens[j - 1]))
				has_command = 1;
		}
		j++;
	}
	if (!has_command)
	{
		write(STDERR_FILENO, "Syntax error: No command found\n", 32);
		return (0);
	}
	return (1);
}

int	validate_redirections(char **tokens)
{
	int	i;

	if (!has_valid_command(tokens))
		return (2);
	i = 0;
	while (tokens[i])
	{
		if (check_further_redirections(tokens, i))
			return (2);
		i++;
	}
	return (0);
}

int	validate_pipes(char **tokens)
{
	int	end;

	end = 0;
	while (tokens[end + 1] != NULL)
		end++;
	if (classify_token(tokens[0]) == TOKEN_PIPE
		|| classify_token(tokens[end]) == TOKEN_PIPE)
		return (1);
	return (pipe_sequence_invalid(tokens));
}
