#include "push_swap.h"

void optimize_move(t_move *move)
{
	if (move->direction_a == move->direction_b) {
		int rotate_a = move->rotations_a;
		int rotate_b = move->rotations_b;
		while (rotate_a > 0 && rotate_b > 0) {
			rotate_a--;
			rotate_b--;
			move->total_moves--;
		}
	}
}

void check_b_rotation(const t_stack *node, t_stack *stack_b, t_move *move)
{
	t_stack *current = stack_b;

	if (!current || current->next == current) {
		return;
	}
	if (is_reverse_sorted(stack_b) && node->value > current->value) {
		return;
	}
	int count_r = 0;
	while (count_r < 1000) {
		if (node->value > current->value && node->value < current->prev->value) {
			break;
		} else if (current->value > current->prev->value && node->value > current->value) {
			break;
		} else if (current->value > current->prev->value && node->value < current->prev->value) {
			break;
		}
		current = current->next;
		count_r++;
	}
	int count_rr = 0;
	current = stack_b;
	while (count_rr < 1000) {
		if (node->value > current->value && node->value < current->prev->value) {
			break;
		} else if (current->value > current->prev->value && node->value > current->value) {
			break;
		} else if (current->value > current->prev->value && node->value < current->prev->value) {
			break;
		}
		current = current->prev;
		count_rr++;
	}
	if (count_r == 1000) {
		printf("count_r: %d\n", count_r);
	}
	if (count_rr == 1000) {
		printf("count_rr: %d\n", count_rr);
	}
	if (count_r <= count_rr) {
		move->rotations_b = count_r;
		move->direction_b = 1;
		move->total_moves += count_r;
	} else {
		move->rotations_b = count_rr;
		move->direction_b = 0;
		move->total_moves += count_rr;
	}
	optimize_move(move);
}

t_move check_next(t_stack *node, t_stack *stack_b, t_move previous_move, t_move best_move)
{
	t_move move = {previous_move.rotations_a + 2, previous_move.rotations_a + 1, 1, 0, 1};
	if (best_move.total_moves < move.total_moves) {
		return best_move;
	}
	check_b_rotation(node, stack_b, &move);
	if (move.total_moves < best_move.total_moves) {
		best_move = move;
	}
	t_move best_move_next = check_next(node->next, stack_b, move, best_move);
	if (best_move_next.total_moves < best_move.total_moves) {
		best_move = best_move_next;
	}
	return best_move;
}

t_move check_previous(t_stack *node, t_stack *stack_b, t_move previous_move, t_move best_move)
{
	t_move move = {previous_move.rotations_a + 2, previous_move.rotations_a + 1, 0, 0, 1};
	if (best_move.total_moves < move.total_moves) {
		return best_move;
	}
	check_b_rotation(node, stack_b, &move);
	if (move.total_moves < best_move.total_moves) {
		best_move = move;
	}
	t_move best_move_previous = check_previous(node->prev, stack_b, move, best_move);
	if (best_move_previous.total_moves < best_move.total_moves) {
		best_move = best_move_previous;
	}
	return best_move;
}

t_move find_best_move(t_stack *stack_a, t_stack *stack_b)
{
	t_move best_move;
	t_stack *temp = stack_a;
	t_move temp_move = {1, 0, 0, 0, 1};
	check_b_rotation(temp, stack_b, &temp_move);
	best_move = temp_move;
	t_move best_move_next = check_next(stack_a->next, stack_b, temp_move, best_move);
	t_move best_move_previous = check_previous(stack_a->prev, stack_b, temp_move, best_move);

	if (best_move_next.total_moves < temp_move.total_moves) {
		best_move = best_move_next;
	} else if (best_move_previous.total_moves < temp_move.total_moves) {
		best_move = best_move_previous;
	} else {
		best_move = temp_move;
	}

	return best_move;
}