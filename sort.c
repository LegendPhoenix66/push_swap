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

int	calculate_rotation_count(t_stack **stack_a, t_stack **stack_b,
		int direction)
{
	int		count;
	t_stack	*current;

	count = 0;
	current = *stack_a;
	while (!((*stack_b)->value > current->prev->value
			&& (*stack_b)->value < current->value)
		&& !(current->value < current->prev->value
			&& ((*stack_b)->value > current->prev->value
				|| (*stack_b)->value < current->value)))
	{
		if (direction)
			current = current->next;
		else
			current = current->prev;
		count++;
	}
	return (count);
}

void	empty_stack_b(t_stack **stack_a, t_stack **stack_b)
{
	int	count_r;
	int	count_rr;

	while (*stack_b)
	{
		count_r = calculate_rotation_count(stack_a, stack_b, 1);
		count_rr = calculate_rotation_count(stack_a, stack_b, 0);
		if (count_r <= count_rr)
			while (count_r--)
				ra(stack_a);
		else
			while (count_rr--)
				rra(stack_a);
		pa(stack_a, stack_b);
	}
}

void	perform_common_rotations(t_move *best_move, t_stack **stack_a,
		t_stack **stack_b)
{
	while (best_move->direction_a == best_move->direction_b
		&& best_move->rotations_a > 0 && best_move->rotations_b > 0)
	{
		if (best_move->direction_a)
			rr(stack_a, stack_b);
		else
			rrr(stack_a, stack_b);
		best_move->rotations_a--;
		best_move->rotations_b--;
	}
}

void	perform_stack_a_rotations(t_move *best_move, t_stack **stack_a)
{
	while (best_move->rotations_a > 0)
	{
		if (best_move->direction_a)
			ra(stack_a);
		else
			rra(stack_a);
		best_move->rotations_a--;
	}
}

void	perform_stack_b_rotations(t_move *best_move, t_stack **stack_b)
{
	while (best_move->rotations_b > 0)
	{
		if (best_move->direction_b)
			rb(stack_b);
		else
			rrb(stack_b);
		best_move->rotations_b--;
	}
}

void	perform_best_move(t_stack **stack_a, t_stack **stack_b)
{
	t_move	best_move;

	best_move = find_best_move(*stack_a, *stack_b);
	perform_common_rotations(&best_move, stack_a, stack_b);
	perform_stack_a_rotations(&best_move, stack_a);
	perform_stack_b_rotations(&best_move, stack_b);
	pb(stack_a, stack_b);
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
	while (stack_a_size > 3 && !is_rotate_sorted(*stack_a))
	{
		perform_best_move(stack_a, stack_b);
		stack_a_size--;
	}
	if (stack_a_size == 3)
		sort_3_num(stack_a);
	empty_stack_b(stack_a, stack_b);
	while (!is_sorted(*stack_a))
		rotate_sort(stack_a);
}
