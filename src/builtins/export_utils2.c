/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tordner <tordner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 21:39:14 by tordner           #+#    #+#             */
/*   Updated: 2025/06/01 21:40:08 by tordner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_valid_identifier(char *str)
{
	int	i;

	if (!str || !*str)
		return (0);
	if (str[0] == '-')
		return (-1);
	if (!((str[0] >= 'a' && str[0] <= 'z')
			|| (str[0] >= 'A' && str[0] <= 'Z')
			|| str[0] == '_'))
		return (0);
	i = 1;
	while (str[i] && str[i] != '=')
	{
		if (!((str[i] >= 'a' && str[i] <= 'z')
				|| (str[i] >= 'A' && str[i] <= 'Z')
				|| (str[i] >= '0' && str[i] <= '9')
				|| str[i] == '_'))
			return (0);
		i++;
	}
	return (1);
}

char	*process_single_var(char *result, char *var_start, char *var_end,
	char **env)
{
	char	*var_name;
	char	*var_value;
	char	*new_result;

	var_name = extract_var_name(result, var_start, var_end);
	if (!var_name)
		return (free(result), NULL);
	var_value = get_env_value_for_expansion(env, var_name);
	if (!var_value)
		var_value = "";
	new_result = build_expanded_string(result, var_start, var_end, var_value);
	free(var_name);
	free(result);
	return (new_result);
}

char	*expand_env_variables(char *str, char **env)
{
	char	*result;
	char	*var_start;
	char	*var_end;

	if (!str)
		return (NULL);
	result = ft_strdup(str);
	if (!result)
		return (NULL);
	while (find_next_var(result, &var_start, &var_end) && var_start)
	{
		result = process_single_var(result, var_start, var_end, env);
		if (!result)
			return (NULL);
	}
	return (result);
}

void	handle_quote_char(char *var_value, int *i, int *in_quotes,
	char *quote_type)
{
	if (!*in_quotes && (var_value[*i] == '\'' || var_value[*i] == '"'))
	{
		*in_quotes = 1;
		*quote_type = var_value[*i];
		(*i)++;
	}
	else if (*in_quotes && var_value[*i] == *quote_type)
	{
		*in_quotes = 0;
		*quote_type = 0;
		(*i)++;
	}
}

char	*process_quotes(char *var_value, char *clean_value)
{
	int		i;
	int		j;
	int		in_quotes;
	char	quote_type;

	i = 0;
	j = 0;
	in_quotes = 0;
	quote_type = 0;
	while (var_value[i])
	{
		if ((var_value[i] == '\'' || var_value[i] == '"'))
			handle_quote_char(var_value, &i, &in_quotes, &quote_type);
		else
			clean_value[j++] = var_value[i++];
	}
	clean_value[j] = '\0';
	return (clean_value);
}
// char	**add_env_var(char **env, char *new_var) in utils.c
