/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tordner <tordner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 15:49:05 by thorgal           #+#    #+#             */
/*   Updated: 2025/06/01 21:28:22 by tordner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_env(t_shell *shell, t_cmd *cmd)
{
	int	i;

	i = 0;
	if (!shell->env)
		return (1);
	if (cmd && cmd->args && cmd->args[1])
	{
		ft_putstr_fd("env: '", 2);
		ft_putstr_fd(cmd->args[1], 2);
		ft_putstr_fd("': No such file or directory\n", 2);
		return (127);
	}
	while (shell->env[i])
	{
		printf("%s\n", shell->env[i]);
		i++;
	}
	return (0);
}
