/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tordner <tordner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 21:39:14 by tordner           #+#    #+#             */
/*   Updated: 2025/06/01 21:40:08 by tordner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env_value_for_expansion(char **env, char *var_name)
{
	int		i;
	int		var_len;
	char	*equal_pos;

	if (!env || !var_name)
		return (NULL);
	var_len = ft_strlen(var_name);
	i = 0;
	while (env[i])
	{
		equal_pos = ft_strchr(env[i], '=');
		if (equal_pos && (equal_pos - env[i]) == var_len
			&& ft_strncmp(env[i], var_name, var_len) == 0)
			return (equal_pos + 1);
		i++;
	}
	return (NULL);
}

char	*extract_var_name(char *result, char *var_start, char *var_end)
{
	return (ft_substr(result, var_start - result + 1, var_end - var_start - 1));
}

char	*build_expanded_string(char *result, char *var_start, char *var_end,
	char *var_value)
{
	char	*before_var;
	char	*after_var;
	char	*temp;
	char	*final_result;

	before_var = ft_substr(result, 0, var_start - result);
	after_var = ft_strdup(var_end);
	if (!before_var || !after_var)
	{
		free(before_var);
		free(after_var);
		return (NULL);
	}
	temp = ft_strjoin(before_var, var_value);
	free(before_var);
	if (!temp)
	{
		free(after_var);
		return (NULL);
	}
	final_result = ft_strjoin(temp, after_var);
	free(temp);
	free(after_var);
	return (final_result);
}

char	*find_next_var(char *result, char **var_start, char **var_end)
{
	char	*temp;

	*var_start = ft_strchr(result, '$');
	if (!*var_start)
		return (result);
	*var_end = *var_start + 1;
	while (**var_end && (ft_isalnum(**var_end) || **var_end == '_'))
		(*var_end)++;
	if (*var_end == *var_start + 1)
	{
		temp = ft_strchr(*var_start + 1, '$');
		if (!temp)
			return (result);
		*var_start = temp;
		return (find_next_var(result, var_start, var_end));
	}
	return (result);
}
