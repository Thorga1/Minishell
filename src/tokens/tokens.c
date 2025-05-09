/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfirmin <lfirmin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 17:47:48 by thorgal           #+#    #+#             */
/*   Updated: 2025/04/23 03:07:26 by lfirmin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	extract_quoted_token(char *input, int *index, char quote_char)
{
	int	count;

	count = 0;
	(*index)++;
	while (input[*index] && input[*index] != quote_char)
	{
		(*index)++;
		count++;
	}
	if (input[*index] == quote_char)
		(*index)++;
	else if (input[*index] == '\0' || count == 0)
		return (1);
	return (0);
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
