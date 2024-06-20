/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhopp <lhopp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 13:00:13 by lhopp             #+#    #+#             */
/*   Updated: 2024/06/20 13:00:47 by lhopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	stack_size(t_stack *stack)
{
	int		size;
	t_stack	*temp;

	if (!stack)
		return (0);
	size = 1;
	temp = stack;
	while (temp->next != stack)
	{
		size++;
		temp = temp->next;
	}
	return (size);
}

t_stack	*find_smallest_above(t_stack **stack, int value)
{
	t_stack	*temp;
	t_stack	*smallest_above;

	temp = *stack;
	smallest_above = NULL;
	while (temp != *stack || smallest_above == NULL)
	{
		if (temp->value > value && (!smallest_above
				|| temp->value < smallest_above->value))
		{
			smallest_above = temp;
		}
		temp = temp->next;
	}
	return (smallest_above);
}

t_stack	*find_smallest(t_stack **stack)
{
	t_stack	*temp;
	t_stack	*smallest;

	temp = *stack;
	smallest = temp;
	while (temp != *stack || smallest == temp)
	{
		if (temp->value < smallest->value)
		{
			smallest = temp;
		}
		temp = temp->next;
	}
	return (smallest);
}
