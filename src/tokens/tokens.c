/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfirmin <lfirmin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 17:47:48 by thorgal           #+#    #+#             */
/*   Updated: 2025/05/26 17:42:37 by lfirmin          ###   ########.fr       */
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
				// Dans les double quotes, on peut échapper: " \ $ ` newline
				if (input[*index + 1] == '"' || input[*index + 1] == '\\' || 
					input[*index + 1] == '$' || input[*index + 1] == '`' || 
					input[*index + 1] == '\n')
				{
					(*index) += 2;
					count += 2;
					continue ;
				}
			}
			else if (quote_char == '\'' && input[*index + 1] == '\'')
			{
				// Dans les single quotes, seul \' peut être échappé
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

char	*extract_quoted_content(char *input, int start, int len, char quote_char)
{
	char	*content;
	int		i;
	int		j;

	content = malloc(sizeof(char) * (len + 1));
	if (!content)
		return (NULL);
	i = start;
	j = 0;
	while (i < start + len)
	{
		if (input[i] == '\\' && i + 1 < start + len)
		{
			if (quote_char == '"')
			{
				// Dans les double quotes, on peut échapper: " \ $ ` newline
				if (input[i + 1] == '"' || input[i + 1] == '\\' || 
					input[i + 1] == '$' || input[i + 1] == '`' || 
					input[i + 1] == '\n')
				{
					content[j++] = input[i + 1];
					i += 2;
				}
				else
				{
					// Si ce n'est pas un caractère échappable, on garde le backslash
					content[j++] = input[i];
					i++;
				}
			}
			else if (quote_char == '\'')
			{
				// Dans les single quotes, seul \' peut être échappé
				if (input[i + 1] == '\'')
				{
					content[j++] = '\'';
					i += 2;
				}
				else
				{
					content[j++] = input[i];
					i++;
				}
			}
		}
		else
		{
			content[j++] = input[i];
			i++;
		}
	}
	content[j] = '\0';
	return (content);
}

void	skip_delimiters(char *str, int *i)
{
	while (str[*i] && is_delimiter(str[*i]))
		(*i)++;
}
