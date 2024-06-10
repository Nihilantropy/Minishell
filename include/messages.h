/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   messages.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crea <crea@student.42roma.it>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 15:59:34 by crea              #+#    #+#             */
/*   Updated: 2024/06/04 21:50:12 by crea             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MESSAGES_H
# define MESSAGES_H

# define ERR_NBR_ARG "Error. No argument should be provided.\n"
# define PIPE_ERROR "Error. Pipe error -1\n"
# define FORK_ERROR "Error. Fork error -1\n"

# define ERROR_CHILD_OPEN "Error. Can't open file in child proc. Exit -1\n"
# define ERROR_PARENT_OPEN "Error. Can't open file in parent proc. Exit -1\n"

# define ERROR_OPEN_FILE "Error on read file opening.\n"
# define ERROR_WRITE_FILE "Error on write file creation.\n"

# define ERROR_CMD_PATH "Error. Can't find command in PATH\n"
# define ERROR_EXECVE "Error. Execve exit -1\n"

#endif