/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfirmin <lfirmin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 03:25:24 by lfirmin           #+#    #+#             */
/*   Updated: 2025/04/23 03:31:49 by lfirmin          ###   ########.fr       */
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
		while (input[*index] && !is_delimiter(input[*index]))
			(*index)++;
		token_len = *index - *start;
	}
	return (token_len);
}

char	*extract_token(char *input, int *index)
{
	char	*token;
	int		start;
	int		token_len;

	token_len = extract_token_len(input, index, &start);
	if (token_len == -1)
		return (NULL);
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

void	handle_word_count(char *str, int *i)
{
	while (str[*i] && !is_delimiter(str[*i]) && !is_special(str[*i])
		&& str[*i] != '\'' && str[*i] != '\"')
		(*i)++;
}
