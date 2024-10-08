/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crea <crea@student.42roma.it>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 13:43:55 by crea              #+#    #+#             */
/*   Updated: 2024/09/23 13:55:31 by crea             ###   ########.fr       */
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
