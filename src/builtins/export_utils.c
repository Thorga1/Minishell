/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tordner <tordner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 11:57:58 by lfirmin           #+#    #+#             */
/*   Updated: 2025/06/01 21:39:05 by tordner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

static int	handle_expansion_error(char *expanded_arg)
{
	if (!expanded_arg)
	{
		ft_putstr_fd("export: memory allocation error\n", 2);
		return (1);
	}
	return (0);
}

static int	handle_processing_error(char *expanded_arg, char *processed_arg)
{
	free(expanded_arg);
	if (!processed_arg)
	{
		ft_putstr_fd("export: memory allocation error\n", 2);
		return (1);
	}
	return (0);
}

static int	handle_update_result(t_shell *shell, char *processed_arg,
	int update_result)
{
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

int	handle_env_var(t_shell *shell, char *arg)
{
	int		update_result;
	char	*expanded_arg;
	char	*processed_arg;

	expanded_arg = expand_env_variables(arg, shell->env);
	if (handle_expansion_error(expanded_arg))
		return (1);
	processed_arg = handle_quotes_in_env_var(expanded_arg);
	if (handle_processing_error(expanded_arg, processed_arg))
		return (1);
	update_result = update_env_var(shell->env, processed_arg);
	return (handle_update_result(shell, processed_arg, update_result));
}
