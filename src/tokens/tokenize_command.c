/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_command.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tordner <tordner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 00:05:01 by tordner           #+#    #+#             */
/*   Updated: 2025/06/03 00:05:13 by tordner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*process_token(char *token, t_shell *shell)
{
	char	*expanded;

	expanded = NULL;
	if (shell->single_quoted_token != 1)
	{
		expanded = expand_variables(token, shell);
		free(token);
		shell->single_quoted_token = -1;
		return (expanded);
	}
	return (token);
}

static char	**allocate_tokens(int count)
{
	char	**tokens;

	tokens = malloc(sizeof(char *) * (count + 1));
	if (!tokens)
		return (NULL);
	return (tokens);
}

char	**tokenize_command(char *input, t_shell *shell)
{
	char	**tokens;
	int		count;
	int		i;
	int		index;

	count = count_tokens(input);
	tokens = allocate_tokens(count);
	if (!tokens)
		return (NULL);
	i = 0;
	index = 0;
	while (i < count)
	{
		tokens[i] = extract_token(input, &index, shell);
		if (!tokens[i])
			return (free_tokens(tokens, i));
		tokens[i] = process_token(tokens[i], shell);
		i++;
	}
	tokens[i] = NULL;
	if (check_quotes(input) == 1)
		return (free_tokens(tokens, i));
	return (tokens);
}
