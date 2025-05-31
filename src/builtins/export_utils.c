/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfirmin <lfirmin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 11:57:58 by lfirmin           #+#    #+#             */
/*   Updated: 2025/05/31 14:46:41 by lfirmin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_env_value_for_expansion(char **env, char *var_name)
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

static char	*extract_var_name(char *result, char *var_start, char *var_end)
{
	return (ft_substr(result, var_start - result + 1, var_end - var_start - 1));
}

static char	*build_expanded_string(char *result, char *var_start, char *var_end,
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

static char	*find_next_var(char *result, char **var_start, char **var_end)
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

static char	*process_single_var(char *result, char *var_start, char *var_end,
	char **env)
{
	char	*var_name;
	char	*var_value;
	char	*new_result;

	var_name = extract_var_name(result, var_start, var_end);
	if (!var_name)
		return (free(result), NULL);
	var_value = get_env_value_for_expansion(env, var_name);
	if (!var_value)
		var_value = "";
	new_result = build_expanded_string(result, var_start, var_end, var_value);
	free(var_name);
	free(result);
	return (new_result);
}

static char	*expand_env_variables(char *str, char **env)
{
	char	*result;
	char	*var_start;
	char	*var_end;

	if (!str)
		return (NULL);
	result = ft_strdup(str);
	if (!result)
		return (NULL);
	while (find_next_var(result, &var_start, &var_end) && var_start)
	{
		result = process_single_var(result, var_start, var_end, env);
		if (!result)
			return (NULL);
	}
	return (result);
}

static char	*process_quotes(char *var_value, char *clean_value)
{
	int		i;
	int		j;
	int		in_quotes;
	char	quote_type;

	i = 0;
	j = 0;
	in_quotes = 0;
	quote_type = 0;
	while (var_value[i])
	{
		if (!in_quotes && (var_value[i] == '\'' || var_value[i] == '"'))
		{
			in_quotes = 1;
			quote_type = var_value[i];
			i++;
		}
		else if (in_quotes && var_value[i] == quote_type)
		{
			in_quotes = 0;
			quote_type = 0;
			i++;
		}
		else
			clean_value[j++] = var_value[i++];
	}
	clean_value[j] = '\0';
	return (clean_value);
}

char	*handle_quotes_in_env_var(char *arg)
{
	char	*equal_sign;
	char	*var_name;
	char	*var_value;
	char	*clean_value;
	char	*result;

	equal_sign = ft_strchr(arg, '=');
	if (!equal_sign)
		return (ft_strdup(arg));
	var_name = ft_substr(arg, 0, equal_sign - arg + 1);
	if (!var_name)
		return (NULL);
	var_value = equal_sign + 1;
	clean_value = malloc(ft_strlen(var_value) + 1);
	if (!clean_value)
		return (free(var_name), NULL);
	process_quotes(var_value, clean_value);
	result = ft_strjoin(var_name, clean_value);
	free(var_name);
	free(clean_value);
	return (result);
}

int	handle_env_var(t_shell *shell, char *arg)
{
	int		update_result;
	char	*expanded_arg;
	char	*processed_arg;

	expanded_arg = expand_env_variables(arg, shell->env);
	if (!expanded_arg)
	{
		ft_putstr_fd("export: memory allocation error\n", 2);
		return (1);
	}
	processed_arg = handle_quotes_in_env_var(expanded_arg);
	free(expanded_arg);
	if (!processed_arg)
	{
		ft_putstr_fd("export: memory allocation error\n", 2);
		return (1);
	}
	update_result = update_env_var(shell->env, processed_arg);
	if (update_result == 0)
	{
		shell->env = add_env_var(shell->env, processed_arg);
		free(processed_arg);
		if (!shell->env)
		{
			ft_putstr_fd("export: memory allocation error\n", 2);
			return (1);
		}
	}
	else if (update_result == -1)
	{
		free(processed_arg);
		ft_putstr_fd("export: memory allocation error\n", 2);
		return (1);
	}
	else
		free(processed_arg);
	return (0);
}
