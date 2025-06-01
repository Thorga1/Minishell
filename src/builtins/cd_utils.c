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
