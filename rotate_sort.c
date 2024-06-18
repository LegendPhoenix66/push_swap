/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate_sort.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhopp <lhopp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 11:22:08 by lhopp             #+#    #+#             */
/*   Updated: 2024/04/30 14:22:15 by lhopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	calculate_rotations(t_stack **stack_a, int *rotate_r, int *rotate_l)
{
	t_stack	*temp_r;
	t_stack	*temp_l;

	temp_r = *stack_a;
	temp_l = *stack_a;
	*rotate_r = 1;
	*rotate_l = 1;
	while (temp_r->value < temp_r->next->value)
	{
		temp_r = temp_r->next;
		(*rotate_r)++;
	}
	while (temp_l->value > temp_l->prev->value)
	{
		temp_l = temp_l->prev;
		(*rotate_l)++;
	}
}

int	determine_direction(int rotate_r, int rotate_l)
{
	return (rotate_r < rotate_l);
}

void	perform_rotation(t_stack **stack_a, int direction)
{
	while (!is_sorted(*stack_a))
	{
		if (direction)
			ra(stack_a);
		else {
			rra(stack_a);
		}
	}
}

void	rotate_sort(t_stack **stack_a)
{
	int	direction;
	int	rotate_r;
	int	rotate_l;

	calculate_rotations(stack_a, &rotate_r, &rotate_l);
	direction = determine_direction(rotate_r, rotate_l);
	perform_rotation(stack_a, direction);
}
