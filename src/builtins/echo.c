/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfirmin <lfirmin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 17:17:08 by thorgal           #+#    #+#             */
/*   Updated: 2025/04/22 15:55:46 by lfirmin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*get_env_value(char *var_name, t_shell *shell)
{
	int	i;
	int	var_len;

	if (!var_name || !shell || !shell->env)
		return (NULL);
	if (var_name[0] == '$')
		var_name++;
	if (var_name[0] == '?')
	{
		printf("%d", shell->exit_status);
		return (0);
	}
	var_len = ft_strlen(var_name);
	i = 0;
	while (shell->env[i])
	{
		if (ft_strncmp(shell->env[i], var_name, var_len) == 0
			&& shell->env[i][var_len] == '=')
			return (shell->env[i] + var_len + 1);
		i++;
	}
	return (NULL);
}

static int	is_env_var(char *str)
{
	return (str && str[0] == '$' && str[1] != '\0');
}

int	ft_echo(t_cmd *cmd, t_shell *shell)
{
	int		print_newline;
	int		i;
	char	**args;
	// int		original_stdout;
	int		ret;
	char	*env_value;

	i = 1;
	print_newline = 1;
	args = cmd->args;
	// original_stdout = 0;
	ret = 0;
	if (args[i] && strcmp(args[i], "-n") == 0)
	{
		print_newline = 0;
		i++;
	}
	int first = 1;
	while (args[i])
	{
		if (!first)
			printf(" ");

		if (is_env_var(args[i]))
		{
			env_value = get_env_value(args[i], shell);
			if (env_value)
				printf("%s", env_value);
		}
		else
		{
			printf("%s", args[i]);
		}
		first = 0;
		i++;
	}
	if (print_newline)
		printf("\n");
	return (ret);
}
