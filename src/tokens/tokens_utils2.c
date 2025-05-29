/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfirmin <lfirmin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 03:25:24 by lfirmin           #+#    #+#             */
/*   Updated: 2025/05/29 14:35:33 by lfirmin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	extract_token_len(char *input, int *index, int *start)
{
	int	token_len;

	while (input[*index] && (input[*index] == ' ' || input[*index] == '\t'))
		(*index)++;
	*start = *index;
	if (input[*index] == '\'' || input[*index] == '\"')
		token_len = handle_quoted_token(input, index, start); 
	else if (is_special(input[*index]))
		token_len = handle_special_token(input, index);
	else
	{
		while (input[*index] && !is_delimiter(input[*index]) && !is_special(input[*index]))
		{
			if (input[*index] == '\'' || input[*index] == '\"')
			{
				char quote = input[*index];
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

char	*extract_token(char *input, int *index)
{
	char	*token;
	int		start;
	int		token_len;
	int		temp_index;
	char	quote_char;

	temp_index = *index;
	// Skip delimiters to find the actual start of the token
	while (input[temp_index] && (input[temp_index] == ' ' || input[temp_index] == '\t'))
		temp_index++;
	
	token_len = extract_token_len(input, index, &start);
	if (token_len == -1)
		return (NULL);
	
	// Check if this was a quoted token
	if (input[temp_index] == '\'' || input[temp_index] == '\"')
	{
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

char	**tokenize_command(char *input)
{
	char	**tokens;
	int		count;
	int		i;
	int		index;

	count = count_tokens(input);
	tokens = malloc(sizeof(char *) * (count + 1));
	if (!tokens)
		return (NULL);
	i = 0;
	index = 0;
	while (i < count)
	{
		tokens[i] = extract_token(input, &index);
		if (!tokens[i])
			return (free_tokens(tokens, i));
		i++;
	}
	tokens[i] = NULL;
	if (check_quotes(input) == 1)
		return (free_tokens(tokens, i));
	return (tokens);
}

void	handle_word_count(char *str, int *i)
{
	while (str[*i] && !is_delimiter(str[*i]) && !is_special(str[*i]))
	{
		if (str[*i] == '\'' || str[*i] == '\"')
		{
			char quote = str[*i];
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
