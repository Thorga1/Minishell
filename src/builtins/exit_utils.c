/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tordner <tordner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 11:41:05 by lfirmin           #+#    #+#             */
/*   Updated: 2025/06/01 21:35:36 by tordner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_valid_number(char *str)
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

int	check_positive_overflow(long long result, char digit)
{
	if (result > (LLONG_MAX - (digit - '0')) / 10)
		return (1);
	return (0);
}

int	check_negative_overflow(long long result, char digit)
{
	if (result > (-(LLONG_MIN + (digit - '0'))) / 10)
		return (1);
	return (0);
}
