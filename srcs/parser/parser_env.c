/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcantell <mcantell@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 13:58:23 by mcantell          #+#    #+#             */
/*   Updated: 2024/09/23 13:58:24 by mcantell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*handle_exit_status_var(char *str, char *end);
char	*hanlde_env_var(t_shell *shell, char *str, char *start, char *end);

/*	handle env var:
**	Function that loops to replace all $VAR
**	with the correct variables.
**	If the string is parsed, point at the new string
**	and restart the loop until all '$' are correctly parsed.
*/

void	handle_env_var(t_shell *shell, t_arg *new_node)
{
	int		i;
	char	*old_str;
	char	*new_str;

	i = 0;
	while (new_node->str[i])
	{
		if (new_node->str[i + 1] && new_node->str[i] == '$')
		{
			old_str = new_node->str;
			new_str = parse_env_var(shell, new_node->str);
			if (!new_str)
				break ;
			new_node->str = new_str;
			free(old_str);
			i = 0;
		}
		else
			i++;
	}
}

/*	parse env var:
**	search for the variable name, save it in 
**	a string, and use getenv to retrieve its value.
**	temp should take the value of the last character + 1 (if any)
**	of the main string, taken up to the $, attached to the value
**	of the environment variable.
**	Handle $? expander status.
*/
char	*parse_env_var(t_shell *shell, char *str)
{
	char		*start;
	char		*end;
	char		*new_str;

	start = ft_strnstr(str, "$", ft_strlen(str));
	end = start + 1;
	if (!*end)
		return (NULL);
	if (*end == '?')
	{
		end++;
		new_str = handle_exit_status_var(str, end);
	}
	else
		new_str = hanlde_env_var(shell, str, start, end);
	return (new_str);
}
