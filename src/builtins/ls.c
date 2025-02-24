/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thorgal <thorgal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 15:49:05 by thorgal           #+#    #+#             */
/*   Updated: 2025/02/20 17:50:24 by thorgal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <dirent.h>

int ft_ls(void)
{
    DIR             *dir;
    struct dirent   *entry;
    char            *current_dir;

    current_dir = ".";
    dir = opendir(current_dir);
    if (!dir)
    {
        perror("ls");
        return (1);
    }

    while ((entry = readdir(dir)) != NULL)
    {
        // Skip les fichiers cachés (commençant par .)
        if (entry->d_name[0] != '.')
            printf("%s  ", entry->d_name);
    }
    printf("\n");

    closedir(dir);
    return (0);
} 