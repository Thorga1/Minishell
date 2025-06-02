/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quoted_count.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tordner <tordner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 00:36:34 by tordner           #+#    #+#             */
/*   Updated: 2025/06/03 00:36:43 by tordner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_escaped_in_double_quote(char *str, int i)
{
	if (str[i + 1] == '"' || str[i + 1] == '\\' || str[i + 1] == '$'
		|| str[i + 1] == '`' || str[i + 1] == '\n')
		return (1);
	return (0);
}

static int	is_escaped_in_single_quote(char *str, int i)
{
	if (str[i + 1] == '\'')
		return (1);
	return (0);
}

void	handle_quoted_count(char *str, int *i, char quote)
{
	(*i)++;
	while (str[*i])
	{
		if (str[*i] == '\\' && str[*i + 1])
		{
			if (quote == '"' && is_escaped_in_double_quote(str, *i))
			{
				(*i) += 2;
				continue ;
			}
			if (quote == '\'' && is_escaped_in_single_quote(str, *i))
			{
				(*i) += 2;
				continue ;
			}
		}
		if (str[*i] == quote)
		{
			(*i)++;
			break ;
		}
		(*i)++;
	}
}
