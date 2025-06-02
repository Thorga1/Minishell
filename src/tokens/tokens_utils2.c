/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tordner <tordner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 03:25:24 by lfirmin           #+#    #+#             */
/*   Updated: 2025/06/03 00:20:43 by tordner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	extract_token_len(char *input, int *index, int *start)
{
	int		token_len;
	char	quote;

	while (input[*index] && (input[*index] == ' ' || input[*index] == '\t'))
		(*index)++;
	*start = *index;
	if (input[*index] == '\'' || input[*index] == '\"')
		token_len = handle_quoted_token(input, index, start);
	else if (is_special(input[*index]))
		token_len = handle_special_token(input, index);
	else
	{
		while (input[*index] && !is_delimiter(input[*index]) \
		&& !is_special(input[*index]))
		{
			if (input[*index] == '\'' || input[*index] == '\"')
			{
				quote = input[*index];
				(*index)++;
				while (input[*index] && input[*index] != quote)
					(*index)++;
				if (input[*index] == quote)
					(*index)++;
			}
			else
				(*index)++;
		}
		token_len = *index - *start;
	}
	return (token_len);
}

char	*extract_token(char *input, int *index, t_shell *shell)
{
	char	*token;
	int		start;
	int		token_len;
	int		temp_index;
	char	quote_char;

	shell->single_quoted_token = -1;
	temp_index = *index;
	while (input[temp_index] && (input[temp_index] == ' ' \
		|| input[temp_index] == '\t'))
		temp_index++;
	token_len = extract_token_len(input, index, &start);
	if (token_len == -1)
		return (NULL);
	if (input[temp_index] == '\'' || input[temp_index] == '\"')
	{
		if (input[temp_index] == '\'')
			shell->single_quoted_token = 1;
		quote_char = input[temp_index];
		token = extract_quoted_content(input, start, token_len, quote_char);
	}
	else
	{
		token = malloc(sizeof(char) * (token_len + 1));
		if (!token)
			return (NULL);
		ft_strlcpy(token, input + start, token_len + 1);
	}
	return (token);
}

int	check_quotes(char *input)
{
	bool	in_squote;
	bool	in_dquote;
	int		i;

	in_squote = false;
	in_dquote = false;
	i = 0;
	while (input[i])
	{
		if (input[i] == '\\' && input[i + 1])
		{
			i += 2;
			continue ;
		}
		if (input[i] == '\'' && !in_dquote)
			in_squote = !in_squote;
		else if (input[i] == '"' && !in_squote)
			in_dquote = !in_dquote;
		i++;
	}
	if (in_squote || in_dquote)
		return (1);
	return (0);
}

void	handle_word_count(char *str, int *i)
{
	char	quote;

	while (str[*i] && !is_delimiter(str[*i]) && !is_special(str[*i]))
	{
		if (str[*i] == '\'' || str[*i] == '\"')
		{
			quote = str[*i];
			(*i)++;
			while (str[*i] && str[*i] != quote)
				(*i)++;
			if (str[*i] == quote)
				(*i)++;
		}
		else
			(*i)++;
	}
}
