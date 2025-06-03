/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tordner <tordner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 17:47:48 by thorgal           #+#    #+#             */
/*   Updated: 2025/06/03 02:42:27 by tordner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_delimiter(char c)
{
	return (c == ' ' || c == '\t' || c == '\0');
}

int	is_special(char c)
{
	return (c == '|' || c == '<' || c == '>');
}

void	skip_delimiters(char *str, int *i)
{
	while (str[*i] && is_delimiter(str[*i]))
		(*i)++;
}

static int	handle_escape_in_quote(char *input, int *i, int *count, char quote)
{
	if (quote == '"' && (input[*i + 1] == '"' || input[*i + 1] == '\\'
			|| input[*i + 1] == '$' || input[*i + 1] == '`'
			|| input[*i + 1] == '\n'))
	{
		*i += 2;
		*count += 2;
		return (1);
	}
	else if (quote == '\'' && input[*i + 1] == '\'')
	{
		*i += 2;
		*count += 2;
		return (1);
	}
	return (0);
}

int	extract_quoted_token(char *input, int *index, char quote_char)
{
	int	count;

	count = 0;
	(*index)++;
	while (input[*index])
	{
		if (input[*index] == '\\' && input[*index + 1] && \
			handle_escape_in_quote(input, index, &count, quote_char))
			continue ;
		if (input[*index] == quote_char)
		{
			(*index)++;
			return (0);
		}
		(*index)++;
		count++;
	}
	return (1);
}
