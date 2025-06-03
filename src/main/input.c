/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tordner <tordner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 17:17:15 by lfirmin           #+#    #+#             */
/*   Updated: 2025/06/03 04:15:00 by tordner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**parse_input(char *input, t_shell *shell)
{
	char	**tokens;
	int		i;

	tokens = tokenize_command(input, shell);
	if (!tokens)
	{
		printf(ERROR_TOKEN);
		shell->exit_status = 1;
		return (NULL);
	}
	if (validate_syntax(tokens))
	{
		i = 0;
		shell->exit_status = 2;
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
	t_cmd			*cmd_list;

	tokens = parse_input(input, shell);
	if (!tokens)
		return ;
	cmd_list = parse_tokens_to_list(tokens);
	if (cmd_list)
	{
		ret = execute_pipeline(cmd_list, shell);
		shell->exit_status = ret;
		free_cmd_list(cmd_list);
	}
	i = 0;
	while (tokens[i])
		free(tokens[i++]);
	free(tokens);
}
