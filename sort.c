/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhopp <lhopp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 11:22:12 by lhopp             #+#    #+#             */
/*   Updated: 2024/04/29 16:59:20 by lhopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

// sorting 3 numbers in one stack with the fewest moves
void	sort_3_num(t_stack **stack)
{
	t_stack	*temp;
	t_stack	*next;
	t_stack	*prev;

	temp = *stack;
	next = temp->next;
	prev = temp->prev;
	if (temp->value > next->value && next->value > prev->value)
	{
		rotate(stack, 1);
		swap(stack);
		printf("ra\nsa\n");
	}
	else if (temp->value > prev->value && prev->value > next->value)
	{
		rotate(stack, 1);
		printf("ra\n");
	}
	else if (temp->value < next->value && temp->value > prev->value)
	{
		rotate(stack, 0);
		printf("rra\n");
	}
	else if (temp->value > next->value && temp->value < prev->value)
	{
		swap(stack);
		printf("sa\n");
	}
	else if (temp->value < next->value && next->value > prev->value)
	{
		rotate(stack, 0);
		swap(stack);
		printf("rra\nsa\n");
	}
}

int	stack_size(t_stack *stack)
{
	int		size;
	t_stack	*temp;

	if (!stack)
	{
		return (0);
	}
	size = 1;
	temp = stack;
	while (temp->next != stack)
	{
		size++;
		temp = temp->next;
	}
	return (size);
}

// sort the stack
void	sort(t_stack **stack_a, t_stack **stack_b)
{
	int		stack_a_size;
	t_move	best_move;
	int		count_r;
	int		count_rr;
	t_stack	*current;

	stack_a_size = stack_size(*stack_a);
	if (stack_a_size == 2)
	{
		if ((*stack_a)->value > (*stack_a)->next->value)
		{
			printf("sa\n");
		}
		return ;
	}
	if (is_sorted(*stack_a))
	{
		return ;
	}
	if (is_rotate_sorted(*stack_a))
	{
		rotate_sort(stack_a);
		return ;
	}
	while (stack_a_size > 3 && !is_rotate_sorted(*stack_a))
	{
		best_move = find_best_move(*stack_a, *stack_b);
		while (best_move.direction_a == best_move.direction_b
			&& best_move.rotations_a > 0 && best_move.rotations_b > 0)
		{
			if (best_move.direction_a)
			{
				rotate(stack_a, 1);
				rotate(stack_b, 1);
				printf("rr\n");
			}
			else
			{
				rotate(stack_a, 0);
				rotate(stack_b, 0);
				printf("rrr\n");
			}
			best_move.rotations_a--;
			best_move.rotations_b--;
		}
		while (best_move.rotations_a > 0)
		{
			if (best_move.direction_a)
			{
				rotate(stack_a, 1);
				printf("ra\n");
			}
			else
			{
				rotate(stack_a, 0);
				printf("rra\n");
			}
			best_move.rotations_a--;
		}
		while (best_move.rotations_b > 0)
		{
			if (best_move.direction_b)
			{
				rotate(stack_b, 1);
				printf("rb\n");
			}
			else
			{
				rotate(stack_b, 0);
				printf("rrb\n");
			}
			best_move.rotations_b--;
		}
		push(stack_b, pop(stack_a));
		printf("pb\n");
		stack_a_size--;
	}
	if (stack_a_size == 3)
	{
		sort_3_num(stack_a);
	}
	while (*stack_b)
	{
		count_r = 0;
		count_rr = 0;
		current = *stack_a;
		while (count_r < 1000)
		{
			if ((*stack_b)->value > current->prev->value
				&& (*stack_b)->value < current->value)
			{
				break ;
			}
			else if (current->value < current->prev->value
				&& (*stack_b)->value > current->prev->value)
			{
				break ;
			}
			else if (current->value < current->prev->value
				&& (*stack_b)->value < current->value)
			{
				break ;
			}
			current = current->next;
			count_r++;
		}
		current = *stack_a;
		while (count_rr < 1000)
		{
			if ((*stack_b)->value > current->prev->value
				&& (*stack_b)->value < current->value)
			{
				break ;
			}
			else if (current->value < current->prev->value
				&& (*stack_b)->value > current->prev->value)
			{
				break ;
			}
			else if (current->value < current->prev->value
				&& (*stack_b)->value < current->value)
			{
				break ;
			}
			current = current->prev;
			count_rr++;
		}
		if (count_r <= count_rr)
		{
			while (count_r--)
			{
				printf("ra\n");
				rotate(stack_a, 1);
			}
		}
		else
		{
			while (count_rr--)
			{
				printf("rra\n");
				rotate(stack_a, 0);
			}
		}
		push(stack_a, pop(stack_b));
		printf("pa\n");
	}
	while (!is_sorted(*stack_a))
	{
		count_r = 0;
		count_rr = 0;
		current = *stack_a;
		while (current->value > current->prev->value && count_r < 1000)
		{
			current = current->next;
			count_r++;
		}
		current = *stack_a;
		while (current->value >= current->prev->value && count_rr < 1000)
		{
			current = current->prev;
			count_rr++;
		}
		if (count_r <= count_rr)
		{
			while (count_r--)
			{
				printf("ra\n");
				rotate(stack_a, 1);
			}
		}
		else
		{
			while (count_rr--)
			{
				printf("rra\n");
				rotate(stack_a, 0);
			}
		}
	}
}
