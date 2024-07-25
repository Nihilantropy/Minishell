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

# define EXIT_MAIN "User wrote exit\n"

# define ERR_ALLOC_ENV "Error. ENV allocation failed.\n"
# define ERR_ALLOC_NAME "Error. NAME allocation failed.\n"
# define ERR_ALLOC_VALUE "Error. VALUE allocation failed.\n"

# define ERR_NBR_ARG "Error. No argument should be provided.\n"
# define ERR_PIPE_INPUT "Error. Pipe input is not correct.\n"
# define ERR_ALLOC_STR "Error. STRING allocation failed.\n"
# define ERR_ALLOC_NEW_NODE "Error. NEW NODE allocation failed.\n"
# define ERR_ALLOC_QUOTE_NODE "Error. QUOTE NODE allocation failed.\n"
# define ERR_ALLOC_TOKEN_NODE "Error. TOKEN NODE allocation failed.\n"
# define ERR_ALLOC_ENV_STR "Error. FIRST ENV STR allocation failed.\n"
# define ERR_ALLOC_MATRIX "Error. MATRIX allocation failed.\n"
# define ERR_ALLOC_REDIR "Error. REDIR allocation failed.\n"

# define ERR_ALLOC_VAR "Error. VAR allocation failed.\n"
# define ERR_ALLOC_LINE_COPY "Error. LINE COPY allocation failed.\n"
# define ERR_ALLOC_PARSED_VAR "Error. PARSED VAR allocation failed.\n"
# define ERR_ALLOC_PARSED_VALUE "Error. PARSED VALUE allocation failed.\n"
# define ERR_ALLOC_PARSED_NAME "Error. PARSED NAME allocation failed.\n"
# define ERR_ALLOR_EXPORT "Error. EXPORT allocation failed.\n"
# define ERR_ALLOC_ARRAY "Error. ARRAY allocation failed.\n"

# define ERR_PWD "Error. PWD failed.\n"

# define ERR_ALLOC_MATRIX_COPY "Error. MATRIX COPY allocation failed.\n"

# define ERR_PIPE_FIRST_INDEX "-bash: syntax error near unexpected token `|'"
# define ERR_PIPE_LAST_INDEX "Error. Pipe at last index.\n"

# define ERR_PIPE "Error. Pipe error -1\n"
# define ERR_FORK "Error. Fork error -1\n"

# define ERROR_CHILD_OPEN "Error. Can't open file in child proc. Exit -1\n"
# define ERROR_PARENT_OPEN "Error. Can't open file in parent proc. Exit -1\n"

# define ERR_OPEN_FILE "Error on read file opening.\n"
# define ERR_WRITE_FILE "Error on write file creation.\n"

# define ERR_CMD_PATH "Error. Can't find command in PATH\n"
# define ERR_EXECVE "Error. Execve exit -1\n"

#endif