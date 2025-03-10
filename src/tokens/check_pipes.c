/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_pipes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thorgal <thorgal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 16:55:42 by tordner           #+#    #+#             */
/*   Updated: 2025/03/10 17:45:16 by thorgal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_before_pipe(char **tokens)
{
	int	i;

	i = 0;
	while (tokens[i])
	{
		if (classify_token(tokens[i]) == TOKEN_PIPE
			&& (classify_token(tokens[i - 1]) == TOKEN_REDIRECTION_IN
				|| classify_token(tokens[i - 1]) == TOKEN_REDIRECTION_OUT
				|| classify_token(tokens[i - 1]) == TOKEN_APPEND
				|| classify_token(tokens[i - 1]) == TOKEN_HEREDOC))
			return (1);
		i++;
	}
	return (0);
}

int	validate_pipes(char **tokens)
{
	int	i;

	i = 0;
	while (tokens[i + 1] != NULL)
		i++;
	if (classify_token(tokens[0]) == TOKEN_PIPE
		|| classify_token(tokens[i]) == TOKEN_PIPE)
		return (1);
	i = 0;
	while (tokens[i])
	{
		if (classify_token(tokens[i]) == TOKEN_PIPE && tokens[i + 1]
			&& classify_token(tokens[i + 1]) == TOKEN_PIPE)
			return (1);
		i++;
	}
	i = 0;
	if (check_before_pipe(tokens))
		return (1);
	while (tokens[i])
	{
		if (classify_token(tokens[i]) == TOKEN_PIPE
			&& tokens[i + 1] && (classify_token(tokens[i + 1]) != TOKEN_WORD))
			return (1);
		i++;
	}
	return (0);
}
