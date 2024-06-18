/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_best_move_b_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhopp <lhopp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 10:56:39 by lhopp             #+#    #+#             */
/*   Updated: 2024/05/22 10:58:40 by lhopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	optimize_move(t_move *move)
{
	int	rotate_a;
	int	rotate_b;

	if (move->direction_a == move->direction_b)
	{
		rotate_a = move->rotations_a;
		rotate_b = move->rotations_b;
		while (rotate_a > 0 && rotate_b > 0)
		{
			rotate_a--;
			rotate_b--;
			move->total_moves--;
		}
	}
}

int	count_rotations(const t_stack *node, t_stack *current, int direction)
{
	int	count;

	count = 0;
	while (!(node->value < current->value && node->value > current->prev->value)
		   && !(current->value < current->prev->value
				&& (node->value < current->value
					|| node->value > current->prev->value)))
	{
		if (direction)
			current = current->next;
		else
			current = current->prev;
		count++;
	}
	return (count);
}

void	update_move(t_move *move, int count, int direction)
{
	move->rotations_a = count;
	move->direction_a = direction;
	move->total_moves += count;
}

void	check_a_rotation(const t_stack *node, t_stack *stack_a, t_move *move)
{
	t_stack	*current;
	int		count_r;
	int		count_rr;

	current = stack_a;
	if (!current || current->next == current)
		return ;
	if (is_reverse_sorted(stack_a) && node->value > current->value)
		return ;
	count_r = count_rotations(node, current, 1);
	count_rr = count_rotations(node, current, 0);
	if (count_r <= count_rr)
		update_move(move, count_r, 1);
	else
		update_move(move, count_rr, 0);
	optimize_move(move);
}
