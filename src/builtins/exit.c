/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tordner <tordner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 10:00:00 by lfirmin           #+#    #+#             */
/*   Updated: 2025/06/01 21:30:31 by tordner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <limits.h>
#include <errno.h>

static int	is_valid_number(char *str)
{
	int	i;

	i = 0;
	if (!str || !str[0])
		return (0);
	if (str[i] == '-' || str[i] == '+')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

static long long	safe_atoll(char *str, int *overflow)
{
	long long	result;
	int			sign;
	int			i;

	result = 0;
	sign = 1;
	i = 0;
	*overflow = 0;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (sign == 1)
		{
			if (result > (LLONG_MAX - (str[i] - '0')) / 10)
			{
				*overflow = 1;
				return (LLONG_MAX);
			}
		}
		else
		{
			if (result > (-(LLONG_MIN + (str[i] - '0'))) / 10)
			{
				*overflow = 1;
				return (LLONG_MIN);
			}
		}
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (result * sign);
}

int	ft_exit(t_cmd *cmd, t_shell *shell)
{
	int			exit_code;
	long long	num;
	int			overflow;

	printf("exit\n");
	exit_code = shell->exit_status;
	if (cmd->args[1])
	{
		if (!is_valid_number(cmd->args[1]))
		{
			ft_putstr_fd("minishell: exit: ", 2);
			ft_putstr_fd(cmd->args[1], 2);
			ft_putstr_fd(": numeric argument required\n", 2);
			shell->exit_status = 2;
			shell->running = 0;
			return (2);
		}
		num = safe_atoll(cmd->args[1], &overflow);
		if (overflow)
		{
			ft_putstr_fd("minishell: exit: ", 2);
			ft_putstr_fd(cmd->args[1], 2);
			ft_putstr_fd(": numeric argument required\n", 2);
			shell->exit_status = 2;
			shell->running = 0;
			return (2);
		}
		exit_code = (unsigned char)(num % 256);
		if (cmd->args[2])
		{
			ft_putstr_fd("minishell: exit: too many arguments\n", 2);
			return (1);
		}
	}
	shell->exit_status = exit_code;
	shell->running = 0;
	return (exit_code);
}
