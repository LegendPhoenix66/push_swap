/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhopp <lhopp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 11:22:12 by lhopp             #+#    #+#             */
/*   Updated: 2024/04/30 16:49:54 by lhopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

// sorting 3 numbers in one stack with the fewest moves
void	sort_3_num(t_stack **stack)
{
	t_stack	*node;
	t_stack	*next;
	t_stack	*prev;

	node = *stack;
	next = node->next;
	prev = node->prev;
	if (node->value > next->value && next->value > prev->value)
	{
		ra(stack);
		sa(stack);
	}
	else if (node->value > prev->value && prev->value > next->value)
		ra(stack);
	else if (node->value < next->value && node->value > prev->value)
		rra(stack);
	else if (node->value > next->value && node->value < prev->value)
		sa(stack);
	else if (node->value < next->value && next->value > prev->value)
	{
		rra(stack);
		sa(stack);
	}
}

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

t_stack *find_smallest_above(t_stack **stack, int value)
{
	t_stack *temp = *stack;
	t_stack *smallest_above = NULL;

	do {
		if (temp->value > value && (!smallest_above || temp->value < smallest_above->value)) {
			smallest_above = temp;
		}
		temp = temp->next;
	} while (temp != *stack);

	return smallest_above;
}

t_stack *find_smallest(t_stack **stack)
{
	t_stack *temp = *stack;
	t_stack *smallest = temp;

	do {
		if (temp->value < smallest->value) {
			smallest = temp;
		}
		temp = temp->next;
	} while (temp != *stack);

	return smallest;
}

int empty_stack_a(t_stack **stack_a, t_stack **stack_b, int stack_a_size)
{
	int temp;
	t_stack *temp_node = find_smallest(stack_a);
	for (int i = 0; i < stack_a_size / 2; i++) {
		temp_node = find_smallest_above(stack_a, temp_node->value);
	}

	temp = temp_node->value;
	while (stack_a_size > 3 && !is_rotate_sorted(*stack_a))
	{
		if ((*stack_a)->value > temp)
		{
			pb(stack_a, stack_b);
		}
		else {
			pb(stack_a, stack_b);
			rb(stack_b);
		}
		stack_a_size--;
	}
	return stack_a_size;
}

// sort the stack
void	sort(t_stack **stack_a, t_stack **stack_b)
{
	int	stack_a_size;

	stack_a_size = stack_size(*stack_a);
	if (stack_a_size == 2)
	{
		if ((*stack_a)->value > (*stack_a)->next->value)
			sa(stack_a);
	}
	else if (is_rotate_sorted(*stack_a))
		rotate_sort(stack_a);
	if (is_sorted(*stack_a))
		return ;
	stack_a_size = empty_stack_a(stack_a, stack_b, stack_a_size);
	if (stack_a_size == 3)
		sort_3_num(stack_a);
	while (*stack_b)
		perform_best_move(stack_a, stack_b);
	while (!is_sorted(*stack_a))
		rotate_sort(stack_a);
}
