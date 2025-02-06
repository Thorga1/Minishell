/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thorgal <thorgal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 17:21:22 by thorgal           #+#    #+#             */
/*   Updated: 2025/02/06 16:56:56 by thorgal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_delimiter(char c)
{
	return (c == ' ' || c == '\t' || c == '|' || c == '<'
		|| c == '>' || c == '\'' || c == '\"' || c == '\0');
}

static int	handle_quotes(char *input, int *index)
{
	char	quote_char;

	quote_char = input[*index];
	(*index)++;
	while (input[*index] && input[*index] != quote_char)
		(*index)++;
	if (input[*index] == quote_char)
		(*index)++;
	return (1);
}

static void extract_quoted_token(char *input, int *index, char quote_char)
{
    (*index)++;
    while (input[*index] && input[*index] != quote_char)
        (*index)++;
    if (input[*index] == quote_char)
        (*index)++;
}

char	*extract_token(char *input, int *index)
{
	char	*token;
	int		start;
	int		token_len;

	while (input[*index] && (input[*index] == ' ' || input[*index] == '\t'))
		(*index)++;
	start = *index;
	if (input[*index] == '\'' || input[*index] == '\"')
	{
		start = *index + 1;
		extract_quoted_token(input, index, input[*index]);
		token_len = (*index - 1) - start;
	}
	else
	{
		while (input[*index] && !is_delimiter(input[*index]))
			(*index)++;
		token_len = *index - start;
	}
	token = malloc(sizeof(char) * (token_len + 1));
	if (!token)
		return (NULL);
	ft_strlcpy(token, input + start, token_len + 1);
	return (token);
}

int	count_tokens(char *input)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	while (input[i])
	{
		while (input[i] && (input[i] == ' ' || input[i] == '\t'))
			i++;
		if (input[i] == '\'' || input[i] == '\"')
		{
			handle_quotes(input, &i);
			count++;
		}
		else if (input[i] && !is_delimiter(input[i]))
		{
			count++;
			while (input[i] && !is_delimiter(input[i]))
				i++;
		}
	}
	return (count);
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
		{
			// return (free_tokens(tokens, i));
			return (NULL);
		}
		i++;
	}
	tokens[i] = NULL;
	return (tokens);
}
