/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfirmin <lfirmin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 11:57:58 by lfirmin           #+#    #+#             */
/*   Updated: 2025/04/23 12:01:08 by lfirmin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_env_var(t_shell *shell, char *arg)
{
	int	update_result;

	update_result = update_env_var(shell->env, arg);
	if (update_result == 0)
	{
		shell->env = add_env_var(shell->env, arg);
		if (!shell->env)
			return (printf("export: memory allocation error\n"), 1);
	}
	else if (update_result == -1)
		return (printf("export: memory allocation error\n"), 1);
	return (0);
}
