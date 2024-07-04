/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauker <jkauker@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 12:18:59 by fschuber          #+#    #+#             */
/*   Updated: 2024/07/04 13:54:59 by jkauker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
#include <stdlib.h>

/*
	Garbage Collector (gc) has one dummy node at the start just as a reference.
	It's not a real garbage collector - just a list we append all elements to
	so we can easily free them all at once when we're done with the program.
*/

/*
	@brief	creates a new garbage collector
*/
t_list	*gc_create(void)
{
	t_list	*gc;

	gc = malloc(sizeof(t_list));
	if (!gc)
		return (NULL);
	gc->content = NULL;
	gc->next = NULL;
	return (gc);
}

/*
	@brief	appends a new non-duplicate element to the garbage collector
	@return	0 if successful,
			-1 if malloc fails,
			-2 if element is already in the list
*/
int	gc_append_element(void *content)
{
	t_list	*new_node;
	t_list	*selected_node;
	t_list	*garbage_col;

	if (!content)
		return (0);
	garbage_col = *gc();
	new_node = malloc(sizeof(t_list));
	if (!new_node)
		return (-1);
	new_node->content = content;
	new_node->next = NULL;
	selected_node = garbage_col;
	while (selected_node && selected_node->next && selected_node->content)
	{
		selected_node = selected_node->next;
		if (selected_node->content == content)
		{
			logger_v(LOGGER_WARNING, "Element already in gc.");
			return (free(new_node), -2);
		}
	}
	selected_node->next = new_node;
	return (0);
}

/*
	@brief	frees all elements in the garbage collector & resets it
*/
void	gc_cleanup_and_reinit(void)
{
	t_list	**garbage_col;

	garbage_col = gc();
	logger_v(LOGGER_INFO, "Cleaning up garbage collector.");
	ft_lstclear(garbage_col, free);
	*garbage_col = NULL;
	*garbage_col = gc_create();
}

void	gc_exit(int code)
{
	int			i;
	t_list		*ntt;
	t_list		*next;

	i = 2;
	while (++i < 1024)
		close(i);
	ntt = game()->entities;
	while (ntt)
	{
		next = ntt->next;
		if (ntt->content && ((t_entity *)ntt->content)->data)
		{
			free(((t_entity *)ntt->content)->data);
			((t_entity *)ntt->content)->data = NULL;
		}
		free(ntt->content);
		ntt->content = NULL;
		free(ntt);
		ntt = next;
	}
	gc_cleanup_and_reinit();
	free(*gc());
	exit(code);
}

/*
	@brief	allocates memory and appends it to the garbage collector
			exits the program by itself if malloc fails
			ptr1 is a pointer that will be freed if malloc fails
*/
void	*gc_malloc(size_t size)
{
	void	*new_mem;

	new_mem = malloc(size);
	if (!new_mem)
	{
		perror("Malloc failed");
		cub_exit("", -1);
	}
	ft_bzero(new_mem, size);
	if (gc_append_element(new_mem) == -1)
	{
		perror("Malloc failed");
		free(new_mem);
		cub_exit("", -1);
	}
	return (new_mem);
}
