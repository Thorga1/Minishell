/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_quoted_content.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tordner <tordner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 00:39:01 by tordner           #+#    #+#             */
/*   Updated: 2025/06/03 01:08:06 by tordner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handle_double_quote_escape(t_escape_handler *m, int i)
{
	if (m->input[i + 1] == '"' || m->input[i + 1] == '\\' \
		|| m->input[i + 1] == '$' || m->input[i + 1] == '`' \
		|| m->input[i + 1] == '\n')
	{
		m->content[m->j++] = m->input[i + 1];
		return (2);
	}
	m->content[m->j++] = m->input[i];
	return (1);
}

static int	handle_single_quote_escape(t_escape_handler *m, int i)
{
	if (m->input[i + 1] == '\'')
	{
		m->content[m->j++] = '\'';
		return (2);
	}
	m->content[m->j++] = m->input[i];
	return (1);
}

static int	handle_escapes(t_escape_handler *mini_data, char quote)
{
	if (quote == '"')
		return (handle_double_quote_escape(mini_data, mini_data->i));
	else if (quote == '\'')
		return (handle_single_quote_escape(mini_data, mini_data->i));
	mini_data->content[mini_data->j++] = mini_data->input[mini_data->i + 1];
	return (2);
}

char	*extract_quoted_content(char *input, int start, \
	int len, char quote_char)
{
	char				*content;
	t_escape_handler	mini_data;

	content = malloc(sizeof(char) * (len + 1));
	if (!content)
		return (NULL);
	mini_data = (t_escape_handler){input, content, start, 0};
	while (mini_data.i < start + len)
	{
		if (input[mini_data.i] == '\\' && mini_data.i + 1 < start + len)
			mini_data.i += handle_escapes(&mini_data, quote_char);
		else
			mini_data.content[mini_data.j++] = mini_data.input[mini_data.i++];
	}
	mini_data.content[mini_data.j] = '\0';
	return (content);
}
