/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crea <crea@student.42roma.it>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 02:35:30 by crea              #+#    #+#             */
/*   Updated: 2024/04/23 12:17:41 by crea             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

void	clean_list(t_list **list, t_list *new_head, char *buffer);
void	cpy_nodes(char *line, t_list *list);
int		len_to_newline(t_list *list);
int		find_newline(t_list *list);
t_list	*find_last_node(t_list *list);

static void	polish_list(t_list **list)
{
	t_list	*new_head;
	t_list	*last_node;
	char	*buffer;
	int		i;
	int		j;

	buffer = malloc(BUFFER_SIZE + 1);
	new_head = malloc(sizeof(t_list));
	if (!buffer || !new_head)
		return ;
	last_node = find_last_node(*list);
	i = 0;
	j = 0;
	while (last_node->data[i] && last_node->data[i] != '\n')
		i++;
	while (last_node->data[i] && last_node->data[i++])
		buffer[j++] = last_node->data[i];
	buffer[j] = '\0';
	new_head->data = buffer;
	new_head->next = NULL;
	clean_list(list, new_head, buffer);
}

static char	*extract_line(t_list *list)
{
	char	*line;
	int		len;

	len = len_to_newline(list);
	line = malloc(len + 1);
	if (!line)
		return (NULL);
	cpy_nodes(line, list);
	return (line);
}

static void	create_new_node(t_list **list, char *buffer)
{
	t_list	*new_node;
	t_list	*last_node;

	last_node = find_last_node(*list);
	new_node = malloc(sizeof(t_list));
	if (!new_node)
		return ;
	if (!last_node)
		*list = new_node;
	else
		last_node->next = new_node;
	new_node->data = buffer;
	new_node->next = NULL;
}

static void	create_buffer(t_list **list, int fd)
{
	ssize_t	bytes_read;
	char	*buffer;

	while (!(find_newline(*list)))
	{
		buffer = malloc(BUFFER_SIZE + 1);
		if (!buffer)
			return ;
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (!bytes_read)
		{
			free(buffer);
			return ;
		}
		buffer[bytes_read] = '\0';
		create_new_node(list, buffer);
	}
}

char	*get_next_line(int fd)
{
	static t_list	*list;
	char			*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, &line, 0) < 0)
		return (NULL);
	create_buffer(&list, fd);
	if (!list)
		return (NULL);
	line = extract_line(list);
	polish_list(&list);
	return (line);
}
