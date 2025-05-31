/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_pipes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfirmin <lfirmin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 16:55:42 by tordner           #+#    #+#             */
/*   Updated: 2025/06/01 01:06:39 by lfirmin          ###   ########.fr       */
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

int	pipe_sequence_invalid(char **tokens)
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
	if (check_before_pipe(tokens))
		return (1);
	i = 0;
	while (tokens[i])
	{
		if (classify_token(tokens[i]) == TOKEN_PIPE && tokens[i + 1])
		{
			// Après un pipe, on peut avoir des redirections suivies d'une commande
			// Il faut juste s'assurer qu'il y a au moins une commande dans le segment
			int j = i + 1;
			int has_command = 0;
			
			// Parcourir le segment après le pipe pour vérifier qu'il y a une commande
			while (tokens[j] && classify_token(tokens[j]) != TOKEN_PIPE)
			{
				if (classify_token(tokens[j]) == TOKEN_WORD)
				{
					// Vérifier que ce n'est pas juste un argument de redirection
					if (j == i + 1 || classify_token(tokens[j - 1]) == TOKEN_WORD)
						has_command = 1;
				}
				j++;
			}
			
			if (!has_command)
				return (1);
		}
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
