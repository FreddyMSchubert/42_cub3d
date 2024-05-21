/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschuber <fschuber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 12:18:59 by fschuber          #+#    #+#             */
/*   Updated: 2024/05/21 09:26:49 by fschuber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

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
int	gc_append_element(t_list *gc, void *content)
{
	t_list	*new_node;
	t_list	*selected_node;

	new_node = malloc(sizeof(t_list));
	if (!new_node)
		return (-1);
	new_node->content = content;
	new_node->next = NULL;
	selected_node = gc;
	while (selected_node->next != NULL)
	{
		selected_node = selected_node->next;
		if (selected_node->content == content)
		{
			verbose_logger('w', "Element already in garbage collector.");
			return (free(new_node), -2);
		}
	}
	selected_node->next = new_node;
	return (0);
}

/*
	@brief	frees all elements in the garbage collector & resets it
*/
void	gc_cleanup_and_reinit(t_list **gc)
{
	verbose_logger('i', "Cleaning up garbage collector.");
	ft_lstclear(gc, free);
	*gc = NULL;
	*gc = gc_create();
}

static void	gc_exit_error(t_list **gc, void *ptr1)
{
	gc_cleanup_and_reinit(gc);
	free(*gc);
	if (ptr1)
		free(ptr1);
	exit(EXIT_FAILURE);
}

/*
	@brief	allocates memory and appends it to the garbage collector
			exits the program by itself if malloc fails
			ptr1 is a pointer that will be freed if malloc fails
*/
void	*gc_malloc(size_t size, t_list **gc, void *ptr1)
{
	void	*new_mem;

	new_mem = malloc(size);
	if (!new_mem)
	{
		perror("Malloc failed");
		gc_exit_error(gc, ptr1);
	}
	ft_bzero(new_mem, size);
	if (gc_append_element(*gc, new_mem) == -1)
	{
		perror("Malloc failed");
		free(new_mem);
		gc_exit_error(gc, ptr1);
	}
	return (new_mem);
}
