/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tordner <tordner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 11:41:05 by lfirmin           #+#    #+#             */
/*   Updated: 2025/06/01 21:35:36 by tordner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	update_pwd_env(t_shell *shell)
{
	char	cwd[PATH_MAX];
	char	*old_pwd;
	char	*new_pwd;

	old_pwd = ft_get_env_var(shell->env, "PWD");
	if (old_pwd)
	{
		new_pwd = ft_strjoin("OLDPWD=", old_pwd);
		if (new_pwd)
		{
			update_env_var(shell->env, new_pwd);
			free(new_pwd);
		}
	}
	if (getcwd(cwd, PATH_MAX) != NULL)
	{
		new_pwd = ft_strjoin("PWD=", cwd);
		if (new_pwd)
		{
			update_env_var(shell->env, new_pwd);
			free(new_pwd);
		}
		return (0);
	}
	return (1);
}

char	*resolve_env_variables(char *path, t_shell *shell)
{
	char	*env_value;
	char	*var_name;
	int		i;
	int		start;

	if (!path || !path[0] || !shell)
		return (ft_strdup(path));
	if (path[0] != '$')
		return (ft_strdup(path));
	start = 1;
	i = start;
	while (path[i] && path[i] != '/' && path[i] != ' ')
		i++;
	var_name = ft_substr(path, start, i - start);
	if (!var_name)
		return (NULL);
	env_value = ft_get_env_var(shell->env, var_name);
	free(var_name);
	if (!env_value)
		return (ft_strdup(""));
	if (path[i])
		return (ft_strjoin(env_value, &path[i]));
	return (ft_strdup(env_value));
}

char	*expand_tilde(char *path, t_shell *shell)
{
	char	*home;
	char	*result;

	if (!path || path[0] != '~')
		return (ft_strdup(path));
	home = ft_get_env_var(shell->env, "HOME");
	if (!home)
		return (ft_strdup(path));
	if (path[1] == '\0')
		return (ft_strdup(home));
	if (path[1] == '/')
	{
		result = ft_strjoin(home, path + 1);
		return (result);
	}
	return (ft_strdup(path));
}

int	validate_cd_args(t_cmd *cmd, t_shell *shell)
{
	if (!cmd || !cmd->args)
		return (1);
	if (!cmd->args[1] || ft_strlen(cmd->args[1]) == 0)
		return (handle_home_directory(shell));
	if (ft_strcmp(cmd->args[1], "-") == 0)
		return (handle_previous_directory(shell));
	if (ft_strcmp(cmd->args[1], "~") == 0)
		return (handle_home_directory(shell));
	if (cmd->args[1] && cmd->args[2])
	{
		ft_putendl_fd("cd: too many arguments", STDERR_FILENO);
		return (1);
	}
	return (0);
}

int	ft_cd(t_cmd *cmd, t_shell *shell)
{
	char	*path;
	char	*resolved_path;
	int		validation_result;
	int		status;

	validation_result = validate_cd_args(cmd, shell);
	if (validation_result != 0)
		return (validation_result);
	path = cmd->args[1];
	resolved_path = resolve_cd_path(path, shell);
	if (!resolved_path)
		return (1);
	if (execute_cd_change(resolved_path) != 0)
		return (1);
	status = update_pwd_env(shell);
	return (status);
}
