/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_token_len.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tordner <tordner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 00:28:00 by tordner           #+#    #+#             */
/*   Updated: 2025/06/03 00:28:37 by tordner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	skip_whitespace(char *input, int *index)
{
	while (input[*index] && (input[*index] == ' ' || input[*index] == '\t'))
		(*index)++;
	return (*index);
}

static int	handle_quotes_in_token(char *input, int *index)
{
	char	quote;

	quote = input[*index];
	(*index)++;
	while (input[*index] && input[*index] != quote)
		(*index)++;
	if (input[*index] == quote)
		(*index)++;
	return (0);
}

static int	handle_normal_token(char *input, int *index)
{
	while (input[*index] && !is_delimiter(input[*index]) && \
	!is_special(input[*index]))
	{
		if (input[*index] == '\'' || input[*index] == '\"')
			handle_quotes_in_token(input, index);
		else
			(*index)++;
	}
	return (*index);
}

int	extract_token_len(char *input, int *index, int *start)
{
	int	token_len;

	skip_whitespace(input, index);
	*start = *index;
	if (input[*index] == '\'' || input[*index] == '\"')
		token_len = handle_quoted_token(input, index, start);
	else if (is_special(input[*index]))
		token_len = handle_special_token(input, index);
	else
	{
		handle_normal_token(input, index);
		token_len = *index - *start;
	}
	return (token_len);
}
