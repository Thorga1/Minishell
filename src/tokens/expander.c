/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tordner <tordner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 22:59:57 by tordner           #+#    #+#             */
/*   Updated: 2025/06/01 23:08:55 by tordner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand_variables(char *str, t_shell *shell)
{
	int		i = 0;
	char	*result = ft_calloc(1, 1);
	while (str && str[i])
	{
		if (str[i] == '$' && str[i + 1] && (ft_isalnum(str[i + 1]) || str[i + 1] == '_'))
		{
			int		start = ++i;
			while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
				i++;
			char	*var = ft_substr(str, start, i - start);
			char	*val = get_env_value(var, shell);
			char	*tmp = ft_strjoin(result, val);
			free(result);
			result = tmp;
			free(var);
		}
		else
		{
			char	buf[2] = {str[i++], 0};
			char	*tmp = ft_strjoin(result, buf);
			free(result);
			result = tmp;
		}
	}
	return (result);
}
