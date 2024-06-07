/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crea <crea@student.42roma.it>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 02:35:27 by crea              #+#    #+#             */
/*   Updated: 2024/04/23 12:17:25 by crea             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

void	clean_list(t_list **list, t_list *new_head, char *buffer)
{
	t_list	*temp;

	if (!*list)
		return ;
	while (*list)
	{
		temp = (*list)->next;
		free((*list)->data);
		free(*list);
		*list = temp;
	}
	*list = NULL;
	if (new_head->data[0])
		(*list) = new_head;
	else
	{
		free(buffer);
		free(new_head);
	}
}

void	cpy_nodes(char *line, t_list *list)
{
	int	i;
	int	j;

	j = 0;
	while (list)
	{
		i = 0;
		while (list->data[i])
		{
			if (list->data[i] == '\n')
			{
				line[j++] = list->data[i];
				line[j] = '\0';
				return ;
			}
			line[j++] = list->data[i++];
		}
		list = list->next;
	}
	line[j] = '\0';
	return ;
}

int	len_to_newline(t_list *list)
{
	int	i;
	int	len;

	len = 0;
	while (list)
	{
		i = 0;
		while (list->data[i])
		{
			if (list->data[i] == '\n')
			{
				len++;
				return (len);
			}
			i++;
			len++;
		}
		list = list->next;
	}
	return (len);
}

int	find_newline(t_list *list)
{
	int	i;

	if (!list)
		return (0);
	while (list)
	{
		i = 0;
		while (list->data[i] && i < BUFFER_SIZE)
		{
			if (list->data[i] == '\n')
				return (1);
			i++;
		}
		list = list->next;
	}
	return (0);
}

t_list	*find_last_node(t_list *list)
{
	if (!list)
		return (NULL);
	while (list->next)
		list = list->next;
	return (list);
}
