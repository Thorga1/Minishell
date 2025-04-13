/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thorgal <thorgal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 15:49:05 by thorgal           #+#    #+#             */
/*   Updated: 2025/02/20 17:50:24 by thorgal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int ft_env(t_shell *shell)
{
    int i;

    i = 0;
    if (!shell->env)
        return (1);
    while (shell->env[i])
    {
        printf("%s\n", shell->env[i]);
        i++;
    }
    return (0);
}