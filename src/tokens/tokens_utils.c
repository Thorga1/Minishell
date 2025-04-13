/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thorgal <thorgal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 17:21:22 by thorgal           #+#    #+#             */
/*   Updated: 2025/03/10 17:56:27 by thorgal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_tokens(char *str)
{
	int		i;
	int		count;
	char	quote;

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
		{
			quote = str[i++];
			while (str[i] && str[i] != quote)
				i++;
			if (str[i] == quote)
				i++;
		}
		else if (is_special(str[i]))
		{
			if ((str[i] == '<' && str[i + 1] == '<')
				|| (str[i] == '>' && str[i + 1] == '>'))
				i += 2;
			else
				i++;
		}
		else
		{
			while (str[i] && !is_delimiter(str[i]) && !is_special(str[i])
				&& str[i] != '\'' && str[i] != '\"')
				i++;
		}
	}
	return (count);
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
		if (extract_quoted_token(input, index, input[*index]) == 1)
			return (NULL);
		token_len = (*index - 1) - start;
	}
	else if (is_special(input[*index]))
	{
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

int	check_quotes(char *input)
{
	int	i;
	int	count_single;
	int	count_double;

	i = 0;
	count_double = 0;
	count_single = 0;
	while (input[i])
	{
		if (input[i] == '\"')
			count_double++;
		else if (input[i] == '\'')
			count_single++;
		i++;
	}
	if (count_double % 2 != 0 || count_single % 2 != 0)
		return (1);
	else
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