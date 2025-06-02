/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tordner <tordner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 17:47:48 by thorgal           #+#    #+#             */
/*   Updated: 2025/06/03 00:40:59 by tordner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	extract_quoted_token(char *input, int *index, char quote_char)
{
	int	count;

	count = 0;
	(*index)++;
	while (input[*index])
	{
		if (input[*index] == '\\' && input[*index + 1])
		{
			if (quote_char == '"')
			{
				if (input[*index + 1] == '"' || input[*index + 1] == '\\' || \
					input[*index + 1] == '$' || input[*index + 1] == '`' || \
					input[*index + 1] == '\n')
				{
					(*index) += 2;
					count += 2;
					continue ;
				}
			}
			else if (quote_char == '\'' && input[*index + 1] == '\'')
			{
				(*index) += 2;
				count += 2;
				continue ;
			}
		}
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
