/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_pipes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tordner <tordner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 16:55:42 by tordner           #+#    #+#             */
/*   Updated: 2025/06/03 02:50:07 by tordner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_before_pipe(char **tokens)
{
	int	i;

	i = 0;
	while (tokens[i])
	{
		if (classify_token(tokens[i]) == TOKEN_PIPE && i > 0)
		{
			if (classify_token(tokens[i - 1]) == TOKEN_REDIRECTION_IN
				|| classify_token(tokens[i - 1]) == TOKEN_REDIRECTION_OUT
				|| classify_token(tokens[i - 1]) == TOKEN_APPEND
				|| classify_token(tokens[i - 1]) == TOKEN_HEREDOC)
				return (1);
		}
		i++;
	}
	return (0);
}

static int	has_consecutive_pipes(char **tokens)
{
	int	i;

	i = 0;
	while (tokens[i])
	{
		if (classify_token(tokens[i]) == TOKEN_PIPE && tokens[i + 1]
			&& classify_token(tokens[i + 1]) == TOKEN_PIPE)
			return (1);
		i++;
	}
	return (0);
}

static int	has_valid_command_after_pipe(char **tokens, int pipe_pos)
{
	int	j;
	int	has_command;

	j = pipe_pos + 1;
	has_command = 0;
	while (tokens[j] && classify_token(tokens[j]) != TOKEN_PIPE)
	{
		if (classify_token(tokens[j]) == TOKEN_WORD)
		{
			if (j == pipe_pos + 1 \
				|| classify_token(tokens[j - 1]) == TOKEN_WORD)
				has_command = 1;
		}
		j++;
	}
	return (has_command);
}

static int	check_pipe_commands(char **tokens)
{
	int	i;

	i = 0;
	while (tokens[i])
	{
		if (classify_token(tokens[i]) == TOKEN_PIPE && tokens[i + 1])
		{
			if (!has_valid_command_after_pipe(tokens, i))
				return (1);
		}
		i++;
	}
	return (0);
}

int	pipe_sequence_invalid(char **tokens)
{
	if (!tokens)
		return (1);
	if (has_consecutive_pipes(tokens))
		return (1);
	if (check_before_pipe(tokens))
		return (1);
	if (check_pipe_commands(tokens))
		return (1);
	return (0);
}
