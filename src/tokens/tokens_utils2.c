/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tordner <tordner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 03:25:24 by lfirmin           #+#    #+#             */
/*   Updated: 2025/06/02 21:33:48 by tordner          ###   ########.fr       */
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

char	*ft_strjoin_free(char *s1, char *s2)
{
	char	*res;

	res = ft_strjoin(s1, s2);
	free(s1);
	free(s2);
	return (res);
}

char	*extract_token(char *input, int *index, t_shell *shell)
{
	char		*token;
	char		*segment;
	int			start;
	int			token_len;
	char		quote_char;

	shell->single_quoted_token = -1;
	while (input[*index] == ' ' || input[*index] == '\t')
		(*index)++;
	token = ft_calloc(1, 1);
	if (!token)
		return (NULL);
	while (input[*index] && !is_delimiter(input[*index]) \
	&& !is_special(input[*index]))
	{
		if (input[*index] == '\'' || input[*index] == '"')
		{
			quote_char = input[*index];
			start = ++(*index);
			while (input[*index] && input[*index] != quote_char)
				(*index)++;
			token_len = *index - start;
			segment = extract_quoted_content(input, start, token_len, \
				quote_char);
			if (!segment)
				return (free(token), NULL);
			if (quote_char == '\'')
				shell->single_quoted_token = 1;
			token = ft_strjoin_free(token, segment);
		}
		else
		{
			start = *index;
			while (input[*index] && !is_delimiter(input[*index]) \
			&& !is_special(input[*index]) \
			&& input[*index] != '\'' && input[*index] != '"')
				(*index)++;
			token_len = *index - start;
			segment = ft_substr(input, start, token_len);
			if (!segment)
				return (free(token), NULL);
			token = ft_strjoin_free(token, segment);
		}
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

char	**tokenize_command(char *input, t_shell *shell)
{
	char	**tokens;
	int		count;
	int		i;
	int		index;
	char	*expanded;

	count = count_tokens(input);
	tokens = malloc(sizeof(char *) * (count + 1));
	if (!tokens)
		return (NULL);
	i = 0;
	index = 0;
	while (i < count)
	{
		tokens[i] = extract_token(input, &index, shell);
		if (!tokens[i])
			return (free_tokens(tokens, i));
		if (shell->single_quoted_token != 1)
		{
			expanded = expand_variables(tokens[i], shell);
			free(tokens[i]);
			tokens[i] = expanded;
			shell->single_quoted_token = -1;
		}
		i++;
	}
	tokens[i] = NULL;
	if (check_quotes(input) == 1)
		return (free_tokens(tokens, i));
	return (tokens);
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
