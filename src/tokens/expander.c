/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tordner <tordner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 22:59:57 by tordner           #+#    #+#             */
/*   Updated: 2025/06/02 01:19:06 by tordner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*append_status(char *res, t_shell *sh, int *i)
{
	char	*val;
	char	*tmp;

	val = ft_itoa(sh->exit_status);
	tmp = ft_strjoin(res, val);
	free(res);
	free(val);
	*i += 2;
	return (tmp);
}

static char	*append_env(char *res, char *str, t_shell *sh, int *i)
{
	int		start;
	char	*var;
	char	*val;
	char	*tmp;

	start = ++(*i);
	while (str[*i] && (ft_isalnum(str[*i]) || str[*i] == '_'))
		(*i)++;
	var = ft_substr(str, start, *i - start);
	val = get_env_value(var, sh);
	if (!val)
		val = "";
	tmp = ft_strjoin(res, val);
	free(res);
	free(var);
	return (tmp);
}

static char	*append_char(char *res, char c)
{
	char	buf[2];
	char	*tmp;

	buf[0] = c;
	buf[1] = '\0';
	tmp = ft_strjoin(res, buf);
	free(res);
	return (tmp);
}

char	*expand_variables(char *str, t_shell *sh)
{
	int		i;
	char	*res;

	i = 0;
	res = ft_calloc(1, 1);
	while (str && str[i])
	{
		if (str[i] == '$' && str[i + 1])
		{
			if (str[i + 1] == '?')
				res = append_status(res, sh, &i);
			else if (ft_isalnum(str[i + 1]) || str[i + 1] == '_')
				res = append_env(res, str, sh, &i);
			else
				res = append_char(res, str[i++]);
		}
		else
			res = append_char(res, str[i++]);
	}
	return (res);
}
