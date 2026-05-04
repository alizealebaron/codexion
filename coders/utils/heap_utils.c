/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heap_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alebaron <alebaron@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/02 11:46:45 by alebaron          #+#    #+#             */
/*   Updated: 2026/05/04 16:53:01 by alebaron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../codexion.h"

static void			heap_reorganize(t_heap *heap, int value);
static long long	get_index_time(t_heap *heap, int index);

void	heap_insert(t_heap *heap, t_coder *coder)
{
	int			i;
	long long	coder_time;

	pthread_mutex_lock(&coder->lock);
	coder_time = coder->last_compile_time;
	pthread_mutex_unlock(&coder->lock);
	i = heap->size;
	heap->binary_tree[i] = coder;
	while (i != 0)
	{
		int parent_i = (i - 1) / 2;
		long long parent_time;
		pthread_mutex_lock(&heap->binary_tree[parent_i]->lock);
		parent_time = heap->binary_tree[parent_i]->last_compile_time;
		pthread_mutex_unlock(&heap->binary_tree[parent_i]->lock);
		if (parent_time <= coder_time)
			break;
		t_coder *temp = heap->binary_tree[parent_i];
		heap->binary_tree[parent_i] = heap->binary_tree[i];
		heap->binary_tree[i] = temp;
		i = parent_i;
	}
	heap->size++;
}

t_coder	*heap_remove_first(t_heap *heap)
{
	t_coder *first_value = heap->binary_tree[0];
	heap->binary_tree[0] = heap->binary_tree[heap->size - 1];
	heap->size--;
	heap_reorganize(heap, 0);
	return first_value;
}

static void	heap_reorganize(t_heap *heap, int index)
{
	int	left_child_index;
	int	right_child_index;
	int	smallest;
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
		if (get_index_time(heap, right_child_index) < get_index_time(heap, smallest))
			smallest = right_child_index;
	if (smallest != index)
	{
		t_coder *temp = heap->binary_tree[index];
        heap->binary_tree[index] = heap->binary_tree[smallest];
        heap->binary_tree[smallest] = temp;
		heap_reorganize(heap, smallest);
	}
}

static long long get_index_time(t_heap *heap, int index)
{
	long long	time;

	pthread_mutex_lock(&heap->binary_tree[index]->lock);
	time = heap->binary_tree[index]->last_compile_time;
	pthread_mutex_unlock(&heap->binary_tree[index]->lock);
	return (time);
}
