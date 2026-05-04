/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heap_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alebaron <alebaron@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/02 11:46:45 by alebaron          #+#    #+#             */
/*   Updated: 2026/05/04 18:05:01 by alebaron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../codexion.h"

static void			heap_reorganize(t_heap *heap, int value);
static long long	get_index_time(t_heap *heap, int index);
static void			swap_coder(t_heap *heap, int parent_i, int i);

void	heap_insert(t_heap *heap, t_coder *coder)
{
	int			i;
	long long	coder_time;
	int			parent_i;
	long long	parent_time;

	pthread_mutex_lock(&coder->lock);
	coder_time = coder->last_compile_time;
	pthread_mutex_unlock(&coder->lock);
	i = heap->size;
	heap->binary_tree[i] = coder;
	parent_i = ((i - 1) / 2);
	parent_time = get_index_time(heap, parent_i);
	while (i != 0)
	{
		parent_time = get_index_time(heap, parent_i);
		if (parent_time <= coder_time)
			break ;
		swap_coder(heap, parent_i, i);
		i = parent_i;
	}
	heap->size++;
}

static void	swap_coder(t_heap *heap, int parent_i, int i)
{
	t_coder	*tmp;

	tmp = heap->binary_tree[parent_i];
	heap->binary_tree[parent_i] = heap->binary_tree[i];
	heap->binary_tree[i] = tmp;
}

t_coder	*heap_remove_first(t_heap *heap)
{
	t_coder	*first_value;

	first_value = heap->binary_tree[0];
	heap->binary_tree[0] = heap->binary_tree[heap->size - 1];
	heap->size--;
	heap_reorganize(heap, 0);
	return (first_value);
}

static void	heap_reorganize(t_heap *heap, int index)
{
	int			left_child_index;
	int			right_child_index;
	int			smallest;
	long long	index_time;

	left_child_index = 2 * index + 1;
	right_child_index = 2 * index + 2;
	smallest = index;
	index_time = get_index_time(heap, index);
	if (left_child_index < heap->size)
	{
		if (get_index_time(heap, left_child_index) < index_time)
			smallest = left_child_index;
	}
	if (right_child_index < heap->size)
		if (get_index_time(heap, right_child_index)
			< get_index_time(heap, smallest))
			smallest = right_child_index;
	if (smallest != index)
	{
		swap_coder(heap, index, smallest);
		heap_reorganize(heap, smallest);
	}
}

static long long	get_index_time(t_heap *heap, int index)
{
	long long	time;

	pthread_mutex_lock(&heap->binary_tree[index]->lock);
	time = heap->binary_tree[index]->last_compile_time;
	pthread_mutex_unlock(&heap->binary_tree[index]->lock);
	return (time);
}
