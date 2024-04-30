/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_best_move.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhopp <lhopp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 11:21:44 by lhopp             #+#    #+#             */
/*   Updated: 2024/04/30 16:53:24 by lhopp            ###   ########.fr       */
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

int count_rotations(const t_stack *node, t_stack *current, int direction)
{
	int count = 0;
	while (!(node->value > current->value && node->value < current->prev->value)
		   && !(current->value > current->prev->value
				&& (node->value > current->value
					|| node->value < current->prev->value)))
	{
		if	(direction)
			current = current->next;
		else
			current = current->prev;
		count++;
	}
	return count;
}

void update_move(t_move *move, int count, int direction)
{
	move->rotations_b = count;
	move->direction_b = direction;
	move->total_moves += count;
}

void	check_b_rotation(const t_stack *node, t_stack *stack_b, t_move *move)
{
	t_stack	*current;
	int		count_r;
	int		count_rr;

	current = stack_b;
	if (!current || current->next == current)
		return ;
	if (is_reverse_sorted(stack_b) && node->value > current->value)
		return ;
	count_r = count_rotations(node, current, 1);
	count_rr = count_rotations(node, current, 0);
	if (count_r <= count_rr)
		update_move(move, count_r, 1);
	else
		update_move(move, count_rr, 0);
	optimize_move(move);
}

t_move	check_next(t_stack *node, t_stack *stack_b, t_move prev_move,
		t_move best_move)
{
	t_move	move;
	t_move	best_move_next;

	move.total_moves = prev_move.rotations_a + 2;
	move.rotations_a = prev_move.rotations_a + 1;
	move.direction_a = 1;
	move.rotations_b = 0;
	move.direction_b = 1;
	if (best_move.total_moves < move.total_moves)
		return (best_move);
	check_b_rotation(node, stack_b, &move);
	if (move.total_moves < best_move.total_moves)
		best_move = move;
	best_move_next = check_next(node->next, stack_b, move, best_move);
	if (best_move_next.total_moves < best_move.total_moves)
		best_move = best_move_next;
	return (best_move);
}

t_move	check_previous(t_stack *node, t_stack *stack_b, t_move prev_move,
		t_move best_move)
{
	t_move	move;
	t_move	best_move_previous;

	move.total_moves = prev_move.rotations_a + 2;
	move.rotations_a = prev_move.rotations_a + 1;
	move.direction_a = 0;
	move.rotations_b = 0;
	move.direction_b = 1;
	if (best_move.total_moves < move.total_moves)
		return (best_move);
	check_b_rotation(node, stack_b, &move);
	if (move.total_moves < best_move.total_moves)
		best_move = move;
	best_move_previous = check_previous(node->prev, stack_b, move, best_move);
	if (best_move_previous.total_moves < best_move.total_moves)
		best_move = best_move_previous;
	return (best_move);
}

t_move	find_best_move(t_stack *stack_a, t_stack *stack_b)
{
	t_move	best_move;
	t_stack	*temp;
	t_move	temp_move;
	t_move	best_move_next;
	t_move	best_move_previous;

	temp = stack_a;
	temp_move.total_moves = 1;
	temp_move.rotations_a = 0;
	temp_move.direction_a = 0;
	temp_move.rotations_b = 0;
	temp_move.direction_b = 1;
	check_b_rotation(temp, stack_b, &temp_move);
	best_move = temp_move;
	best_move_next = check_next(stack_a->next, stack_b, temp_move, best_move);
	best_move_previous = check_previous(stack_a->prev, stack_b, temp_move,
			best_move);
	if (best_move_next.total_moves < best_move.total_moves)
		best_move = best_move_next;
	if (best_move_previous.total_moves < best_move.total_moves)
		best_move = best_move_previous;
	return (best_move);
}
