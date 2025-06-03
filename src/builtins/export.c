/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tordner <tordner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 11:54:38 by lfirmin           #+#    #+#             */
/*   Updated: 2025/06/01 21:30:55 by tordner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	update_env_var(char **env, char *var)
{
	int		i;
	char	*equal_sign;
	int		var_name_len;

	equal_sign = ft_strchr(var, '=');
	if (!equal_sign)
		return (0);
	var_name_len = equal_sign - var;
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], var, var_name_len) == 0
			&& (env[i][var_name_len] == '=' || env[i][var_name_len] == '\0'))
		{
			free(env[i]);
			env[i] = ft_strdup(var);
			if (!env[i])
				return (-1);
			return (1);
		}
		i++;
	}
	return (0);
}

int	handle_export_validation(char *arg)
{
	int	validity;

	validity = is_valid_identifier(arg);
	if (validity <= 0)
	{
		ft_putstr_fd("export: '", 2);
		ft_putstr_fd(arg, 2);
		if (validity == -1)
		{
			ft_putstr_fd("': option invalide\n", 2);
			return (2);
		}
		else
			ft_putstr_fd("': not a valid identifier\n", 2);
		return (1);
	}
	return (0);
}

int	process_single_export_arg(t_shell *shell, char *arg)
{
	int	validation_result;
	int	status;

	validation_result = handle_export_validation(arg);
	if (validation_result > 0)
	{
		if (validation_result == 2)
			return (2);
		return (1);
	}
	if (ft_strchr(arg, '='))
	{
		status = handle_env_var(shell, arg);
		if (status != 0)
			return (status);
	}
	return (0);
}

int	process_export_args(t_shell *shell, char **args, int i)
{
	int	ret;
	int	status;
	int	success;

	ret = 1;
	success = 0;
	while (args[i])
	{
		status = process_single_export_arg(shell, args[i]);
		if (status == 2)
			return (2);
		if (status == 1)
		{
			i++;
			continue ;
		}
		if (status == 0)
			success = 1;
		i++;
	}
	if (success)
		ret = 0;
	return (ret);
}

int	ft_export(t_shell *shell, t_cmd *cmd)
{
	int	i;

	if (!cmd->args[1])
	{
		i = 0;
		while (shell->env[i])
		{
			printf("declare -x %s\n", shell->env[i]);
			i++;
		}
		return (0);
	}
	return (process_export_args(shell, cmd->args, 1));
}
