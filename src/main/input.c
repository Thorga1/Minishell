/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfirmin <lfirmin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 17:17:15 by lfirmin           #+#    #+#             */
/*   Updated: 2025/04/13 17:32:16 by lfirmin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**parse_input(char *input, t_shell *shell)
{
	char	**tokens;
	int		i;

	tokens = tokenize_command(input);
	if (!tokens)
	{
		printf(ERROR_TOKEN);
		shell->exit_status = 1;
		return (NULL);
	}
	if (validate_syntax(tokens))
	{
		i = 0;
		while (tokens[i])
			free(tokens[i++]);
		free(tokens);
		return (NULL);
	}
	return (tokens);
}

void	process_input(char *input, t_shell *shell)
{
	char			**tokens;
	int				i;
	int				ret;
	t_smd			*cmd_list;

	tokens = parse_input(input, shell);
	if (!tokens)
		return ;
	cmd_list = parse_tokens_to_list(tokens);
	if (cmd_list)
	{
		ret = execute_builtin(cmd_list, shell);
		if (ret == -1)
		{
			printf(ERROR_NOT_FOUND, cmd_list->args[0]);
			shell->exit_status = 127;
		}
		else
			shell->exit_status = ret;
		free_cmd_list(cmd_list);
	}
	i = 0;
	while (tokens[i])
		free(tokens[i++]);
	free(tokens);
}
