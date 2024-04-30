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
