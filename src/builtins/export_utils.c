/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 11:57:58 by lfirmin           #+#    #+#             */
/*   Updated: 2025/05/19 10:55:48 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Traite les guillemets dans les variables d'environnement
 * 
 * Gère les guillemets simples (') et doubles (") dans la valeur
 * d'une variable d'environnement en créant une nouvelle chaîne sans guillemets.
 * 
 * @param arg Variable au format "nom=valeur" où valeur peut contenir des guillemets
 * @return char* Nouvelle chaîne au format "nom=valeur" sans guillemets ou NULL si erreur
 */
char	*handle_quotes_in_env_var(char *arg)
{
	char	*equal_sign;
	char	*var_name;
	char	*var_value;
	char	*result;
	char	*clean_value;
	int		i;
	int		j;
	int		in_quotes;
	char	quote_type;

	equal_sign = ft_strchr(arg, '=');
	if (!equal_sign)
		return (ft_strdup(arg));

	var_name = ft_substr(arg, 0, equal_sign - arg + 1);
	if (!var_name)
		return (NULL);

	var_value = equal_sign + 1;
	clean_value = malloc(ft_strlen(var_value) + 1);
	if (!clean_value)
	{
		free(var_name);
		return (NULL);
	}

	i = 0;
	j = 0;
	in_quotes = 0;
	quote_type = 0;
	
	while (var_value[i])
	{
		if (!in_quotes && (var_value[i] == '\'' || var_value[i] == '"'))
		{
			in_quotes = 1;
			quote_type = var_value[i];
			i++;
		}
		else if (in_quotes && var_value[i] == quote_type)
		{
			in_quotes = 0;
			quote_type = 0;
			i++;
		}
		else
		{
			clean_value[j++] = var_value[i++];
		}
	}
	clean_value[j] = '\0';

	result = ft_strjoin(var_name, clean_value);
	free(var_name);
	free(clean_value);
	
	return (result);
}

int	handle_env_var(t_shell *shell, char *arg)
{
	int		update_result;
	char	*processed_arg;

	processed_arg = handle_quotes_in_env_var(arg);
	if (!processed_arg)
	{
		ft_putstr_fd("export: memory allocation error\n", 2);
		return (1);
	}

	update_result = update_env_var(shell->env, processed_arg);
	if (update_result == 0)
	{
		shell->env = add_env_var(shell->env, processed_arg);
		free(processed_arg);
		if (!shell->env)
		{
			ft_putstr_fd("export: memory allocation error\n", 2);
			return (1);
		}
	}
	else if (update_result == -1)
	{
		free(processed_arg);
		ft_putstr_fd("export: memory allocation error\n", 2);
		return (1);
	}
	else
	{
		free(processed_arg);
	}
	
	return (0);
}
