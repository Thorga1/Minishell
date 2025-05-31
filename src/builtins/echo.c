/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfirmin <lfirmin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 17:17:08 by thorgal           #+#    #+#             */
/*   Updated: 2025/05/31 14:37:37 by lfirmin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*get_env_value(char *var_name, t_shell *shell)
{
	int	i;
	int	var_len;

	if (!var_name || !shell || !shell->env)
		return (NULL);
	if (var_name[0] == '$')
		var_name++;
	if (var_name[0] == '?')
	{
		printf("%d", shell->exit_status);
		return (0);
	}
	var_len = 0;
	// Calculer la longueur du nom de variable valide (lettres, chiffres, underscore)
	while (var_name[var_len] && (ft_isalnum(var_name[var_len]) || var_name[var_len] == '_'))
		var_len++;
	if (var_len == 0)
		return (NULL);
	i = 0;
	while (shell->env[i])
	{
		if (ft_strncmp(shell->env[i], var_name, var_len) == 0
			&& shell->env[i][var_len] == '=')
			return (shell->env[i] + var_len + 1);
		i++;
	}
	return (NULL);
}


void	print_with_expansion(char *str, t_shell *shell)
{
	int		i;
	int		start;
	char	*env_value;
	char	temp_var[256];
	int		var_len;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1] && (ft_isalnum(str[i + 1]) || str[i + 1] == '_' || str[i + 1] == '?'))
		{
			start = i + 1;
			if (str[start] == '?')
			{
				printf("%d", shell->exit_status);
				i += 2;
			}
			else
			{
				var_len = 0;
				while (str[start + var_len] && (ft_isalnum(str[start + var_len]) || str[start + var_len] == '_'))
					var_len++;
				if (var_len > 0 && var_len < 255)
				{
					ft_strlcpy(temp_var, &str[start], var_len + 1);
					env_value = get_env_value(temp_var, shell);
					if (env_value)
						printf("%s", env_value);
				}
				i = start + var_len;
			}
		}
		else
		{
			printf("%c", str[i]);
			i++;
		}
	}
}

int	is_env_var(char *str)
{
	int	i;
	
	if (!str || str[0] != '$')
		return (0);
	i = 1;
	while (str[i])
	{
		if (str[i] == '$')
			return (1); // Contient au moins une variable
		i++;
	}
	return (str[1] != '\0'); // Simple variable si pas d'autres caractères après $
}

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

void	print_echo_args(char **args, int i, t_shell *shell, int first)
{
	while (args[i])
	{
		if (!first)
			printf(" ");
		print_with_expansion(args[i], shell);
		first = 0;
		i++;
	}
}

int	ft_echo(t_cmd *cmd, t_shell *shell)
{
	int		print_newline;
	int		i;
	char	**args;
	int		first;

	i = 1;
	print_newline = 1;
	args = cmd->args;
	
	// Traiter tous les arguments -n consécutifs
	while (args[i] && is_valid_n_option(args[i]))
	{
		print_newline = 0;
		i++;
	}
	
	first = 1;
	print_echo_args(args, i, shell, first);
	if (print_newline)
		printf("\n");
	return (0);
}