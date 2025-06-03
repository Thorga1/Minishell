/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tordner <tordner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 02:58:34 by tordner           #+#    #+#             */
/*   Updated: 2025/06/03 02:58:59 by tordner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*create_standard_prompt(char *dir_name, int exit_status)
{
	char	*prompt;
	char	*tmp;

	if (exit_status == 0)
	{
		tmp = ft_strjoin(GREEN "➜\001\033[0m\002  \001\033[1;36m\002", dir_name);
		if (!tmp)
			return (NULL);
		prompt = ft_strjoin(tmp, "\001\033[0m\002 ❯ ");
		free(tmp);
	}
	else
	{
		tmp = ft_strjoin(RED "➜\001\033[0m\002  \001\033[1;36m\002", dir_name);
		if (!tmp)
			return (NULL);
		prompt = ft_strjoin(tmp, "\001\033[0m\002 ❯ ");
		free(tmp);
	}
	return (prompt);
}

char	*generate_prompt(t_shell *shell)
{
	char	*dir_name;
	char	*prompt;

	dir_name = get_current_dir_name();
	if (!dir_name)
		return (ft_strdup("➜  ❯ "));
	else
		prompt = create_standard_prompt(dir_name, shell->exit_status);
	free(dir_name);
	if (prompt)
		return (prompt);
	else
		return (ft_strdup("➜  ❯ "));
}
