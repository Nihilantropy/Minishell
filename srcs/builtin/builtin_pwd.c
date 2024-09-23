/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcantell <mcantell@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 13:57:20 by mcantell          #+#    #+#             */
/*   Updated: 2024/09/23 13:57:21 by mcantell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*	handle builtin pwd:
**	use the getcwd() function to find the current folder path.
*/
void	handle_builtin_pwd(void)
{
	char	pwd[2048];

	if (getcwd(pwd, 2048) != NULL)
	{
		printf("%s\n", pwd);
		g_exit_status = EXIT_STATUS_SUCCESS;
	}
	else
	{
		g_exit_status = EXIT_STATUS_ERROR;
		ft_putstr_fd(ERR_PWD, 2);
	}

}
