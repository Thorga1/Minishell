/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfirmin <lfirmin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 17:17:08 by thorgal           #+#    #+#             */
/*   Updated: 2025/06/02 00:22:51 by lfirmin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_valid_n_option(char *str)
{
	int	i;

	if (!str || str[0] != '-' || str[1] != 'n')
		return (0);
	i = 2;
	while (str[i])
	{
		if (str[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

void	print_echo_args(char **args, int i, int first)
{
	if (!args)
		return ;
	while (args[i])
	{
		if (!args[i])
			i++;
		else
		{
			if (!first)
				printf(" ");
			printf("%s", args[i]);
			first = 0;
			i++;
		}
	}
}

int	ft_echo(t_cmd *cmd, t_shell *shell)
{
	int		print_newline;
	int		i;
	char	**args;
	int		first;

	(void)shell;
	if (!cmd || !cmd->args)
		return (1);
	i = 1;
	print_newline = 1;
	args = cmd->args;
	while (args[i] && is_valid_n_option(args[i]))
	{
		print_newline = 0;
		i++;
	}
	first = 1;
	print_echo_args(args, i, first);
	if (print_newline)
		printf("\n");
	return (0);
}
