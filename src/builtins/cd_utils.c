/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tordner <tordner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 21:31:25 by tordner           #+#    #+#             */
/*   Updated: 2025/06/01 21:35:44 by tordner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	handle_home_directory(t_shell *shell)
{
	char	*home;

	home = ft_get_env_var(shell->env, "HOME");
	if (home == NULL)
	{
		ft_putendl_fd("cd: HOME not set", STDERR_FILENO);
		return (1);
	}
	if (chdir(home) == -1)
	{
		ft_putstr_fd("cd: ", STDERR_FILENO);
		ft_putstr_fd(home, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
		perror("");
		return (1);
	}
	return (0);
}

int	handle_previous_directory(t_shell *shell)
{
	char	*oldpwd;

	oldpwd = ft_get_env_var(shell->env, "OLDPWD");
	if (oldpwd == NULL)
	{
		ft_putendl_fd("cd: OLDPWD not set", STDERR_FILENO);
		return (1);
	}
	ft_putendl_fd(oldpwd, STDOUT_FILENO);
	if (chdir(oldpwd) == -1)
	{
		ft_putstr_fd("cd: ", STDERR_FILENO);
		ft_putstr_fd(oldpwd, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
		perror("");
		return (1);
	}
	return (0);
}

char	*resolve_cd_path(char *path, t_shell *shell)
{
	char	*resolved_path;

	if (path[0] == '~')
		resolved_path = expand_tilde(path, shell);
	else if (path[0] == '$')
	{
		resolved_path = resolve_env_variables(path, shell);
		if (!resolved_path || ft_strlen(resolved_path) == 0)
		{
			ft_putstr_fd("cd: ", STDERR_FILENO);
			ft_putstr_fd(path, STDERR_FILENO);
			ft_putendl_fd(": No such file or directory", STDERR_FILENO);
			if (resolved_path)
				free(resolved_path);
			return (NULL);
		}
	}
	else
		resolved_path = ft_strdup(path);
	return (resolved_path);
}

int	execute_cd_change(char *resolved_path)
{
	if (chdir(resolved_path) == -1)
	{
		ft_putstr_fd("cd: ", STDERR_FILENO);
		ft_putstr_fd(resolved_path, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
		perror("");
		free(resolved_path);
		return (1);
	}
	free(resolved_path);
	return (0);
}
