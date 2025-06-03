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

static long long	parse_digits(char *str, int *i, int sign, int *overflow)
{
	long long	result;

	result = 0;
	while (str[*i] >= '0' && str[*i] <= '9')
	{
		if (sign == 1 && check_positive_overflow(result, str[*i]))
		{
			*overflow = 1;
			return (LLONG_MAX);
		}
		if (sign == -1 && check_negative_overflow(result, str[*i]))
		{
			*overflow = 1;
			return (LLONG_MIN);
		}
		result = result * 10 + (str[*i] - '0');
		(*i)++;
	}
	return (result);
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
	result = parse_digits(str, &i, sign, overflow);
	return (result * sign);
}

static void	print_numeric_error(char *arg, t_shell *shell)
{
	ft_putstr_fd("minishell: exit: ", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd(": numeric argument required\n", 2);
	shell->exit_status = 2;
	shell->running = 0;
}

static int	handle_exit_argument(t_cmd *cmd, t_shell *shell, int *exit_code)
{
	long long	num;
	int			overflow;

	if (!is_valid_number(cmd->args[1]))
	{
		print_numeric_error(cmd->args[1], shell);
		return (2);
	}
	num = safe_atoll(cmd->args[1], &overflow);
	if (overflow)
	{
		print_numeric_error(cmd->args[1], shell);
		return (2);
	}
	*exit_code = (unsigned char)(num % 256);
	if (cmd->args[2])
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		return (1);
	}
	return (0);
}

int	ft_exit(t_cmd *cmd, t_shell *shell)
{
	int	exit_code;
	int	result;

	printf("exit\n");
	exit_code = shell->exit_status;
	if (cmd->args[1])
	{
		result = handle_exit_argument(cmd, shell, &exit_code);
		if (result != 0)
			return (result);
	}
	shell->exit_status = exit_code;
	shell->running = 0;
	return (exit_code);
}
