/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfirmin <lfirmin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 17:21:22 by thorgal           #+#    #+#             */
/*   Updated: 2025/04/23 03:31:04 by lfirmin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_quoted_count(char *str, int *i, char quote)
{
	(*i)++;
	while (str[*i] && str[*i] != quote)
		(*i)++;
	if (str[*i] == quote)
		(*i)++;
}

void	handle_special_count(char *str, int *i)
{
	if ((str[*i] == '<' && str[*i + 1] == '<')
		|| (str[*i] == '>' && str[*i + 1] == '>'))
		(*i) += 2;
	else
		(*i)++;
}

int	count_tokens(char *str)
{
	int		i;
	int		count;

	i = 0;
	count = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		skip_delimiters(str, &i);
		if (!str[i])
			break ;
		count++;
		if (str[i] == '\'' || str[i] == '\"')
			handle_quoted_count(str, &i, str[i]);
		else if (is_special(str[i]))
			handle_special_count(str, &i);
		else
			handle_word_count(str, &i);
	}
	return (count);
}

int	handle_quoted_token(char *input, int *index, int *start)
{
	*start = *index + 1;
	if (extract_quoted_token(input, index, input[*index]) == 1)
		return (-1);
	return ((*index - 1) - *start);
}

int	handle_special_token(char *input, int *index)
{
	int	token_len;

	if ((input[*index] == '<' && input[*index + 1] == '<')
		|| (input[*index] == '>' && input[*index + 1] == '>'))
	{
		(*index) += 2;
		token_len = 2;
	}
	else
	{
		(*index)++;
		token_len = 1;
	}
	return (token_len);
}
