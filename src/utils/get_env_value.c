/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env_value.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tordner <tordner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 23:59:04 by tordner           #+#    #+#             */
/*   Updated: 2025/06/03 00:02:52 by tordner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*handle_special_vars(char *var_name, t_shell *shell)
{
	if (!var_name || !shell)
		return (NULL);
	if (var_name[0] == '$')
		var_name++;
	if (var_name[0] == '?')
	{
		printf("%d", shell->exit_status);
		return (NULL);
	}
	return (var_name);
}

static int	get_var_name_length(char *var_name)
{
	int	len;

	len = 0;
	while (var_name[len] && (ft_isalnum(var_name[len]) || var_name[len] == '_'))
		len++;
	return (len);
}

static char	*search_env(char *var_name, int var_len, char **env)
{
	int	i;

	i = 0;
	while (env && env[i])
	{
		if (ft_strncmp(env[i], var_name, var_len) \
		== 0 && env[i][var_len] == '=')
			return (env[i] + var_len + 1);
		i++;
	}
	return (NULL);
}

char	*get_env_value(char *var_name, t_shell *shell)
{
	char	*clean_var_name;
	int		var_len;

	if (!var_name || !shell || !shell->env)
		return (NULL);
	clean_var_name = handle_special_vars(var_name, shell);
	if (!clean_var_name)
		return (NULL);
	var_len = get_var_name_length(clean_var_name);
	if (var_len == 0)
		return (NULL);
	return (search_env(clean_var_name, var_len, shell->env));
}
