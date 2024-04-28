#include "push_swap.h"

// sorting 3 numbers in one stack with the fewest moves
void sort_3_num(t_stack **stack)
{
	t_stack const *temp = *stack;
	t_stack const *next = temp->next;
	t_stack const *prev = temp->prev;

	if (temp->value > next->value && next->value > prev->value) {
		rotate(stack, 1);
		swap(stack);
		printf("ra\nsa\n");
	} else if (temp->value > prev->value && prev->value > next->value) {
		rotate(stack, 1);
		printf("ra\n");
	} else if (temp->value < next->value && temp->value > prev->value) {
		rotate(stack, 0);
		printf("rra\n");
	} else if (temp->value > next->value && temp->value < prev->value) {
		swap(stack);
		printf("sa\n");
	} else if (temp->value < next->value && next->value > prev->value) {
		rotate(stack, 0);
		swap(stack);
		printf("rra\nsa\n");
	}
}

int stack_size(t_stack *stack)
{
	if (!stack) {
		return 0;
	}
	int size = 1;
	t_stack *temp = stack;
	while (temp->next != stack) {
		size++;
		temp = temp->next;
	}
	return size;
}

// sort the stack
void sort(t_stack **stack_a, t_stack **stack_b)
{
	int stack_a_size = stack_size(*stack_a);
	if (stack_a_size == 2) {
		if ((*stack_a)->value > (*stack_a)->next->value) {
			printf("sa\n");
		}
		return;
	}
	if (is_sorted(*stack_a)) {
		return;
	}
	if (is_rotate_sorted(*stack_a)) {
		rotate_sort(stack_a);
		return;
	}
	while (stack_a_size > 3 && !is_rotate_sorted(*stack_a)) {
		t_move bestMove = find_best_move(*stack_a, *stack_b);
		while (bestMove.direction_a == bestMove.direction_b && bestMove.rotations_a > 0 && bestMove.rotations_b > 0) {
			if (bestMove.direction_a) {
				rotate(stack_a, 1);
				rotate(stack_b, 1);
				printf("rr\n");
			} else {
				rotate(stack_a, 0);
				rotate(stack_b, 0);
				printf("rrr\n");
			}
			bestMove.rotations_a--;
			bestMove.rotations_b--;
		}
		while (bestMove.rotations_a > 0) {
			if (bestMove.direction_a) {
				rotate(stack_a, 1);
				printf("ra\n");
			} else {
				rotate(stack_a, 0);
				printf("rra\n");
			}
			bestMove.rotations_a--;
		}
		while (bestMove.rotations_b > 0) {
			if (bestMove.direction_b) {
				rotate(stack_b, 1);
				printf("rb\n");
			} else {
				rotate(stack_b, 0);
				printf("rrb\n");
			}
			bestMove.rotations_b--;
		}
		push(stack_b, pop(stack_a));
		printf("pb\n");
		stack_a_size--;
	}
	if (stack_a_size == 3) {
		sort_3_num(stack_a);
	}
	while (*stack_b) {
		int count_r = 0;
		int count_rr = 0;
		t_stack *current = *stack_a;

		// Check clockwise direction
		while (count_r < 1000) {
			if ((*stack_b)->value > current->prev->value && (*stack_b)->value < current->value) {
				break;
			} else if (current->value < current->prev->value && (*stack_b)->value > current->prev->value) {
				break;
			} else if (current->value < current->prev->value && (*stack_b)->value < current->value) {
				break;
			}
			current = current->next;
			count_r++;
		}

		current = *stack_a;

		// Check counter-clockwise direction
		while (count_rr < 1000) {
			if ((*stack_b)->value > current->prev->value && (*stack_b)->value < current->value) {
				break;
			} else if (current->value < current->prev->value && (*stack_b)->value > current->prev->value) {
				break;
			} else if (current->value < current->prev->value && (*stack_b)->value < current->value) {
				break;
			}
			current = current->prev;
			count_rr++;
		}

		// Choose the direction with the shortest distance
		if (count_r <= count_rr) {
			while (count_r--) {
				printf("ra\n");
				rotate(stack_a, 1);
			}
		} else {
			while (count_rr--) {
				printf("rra\n");
				rotate(stack_a, 0);
			}
		}

		// Insert the top element of stack_b into stack_a
		push(stack_a, pop(stack_b));
		printf("pa\n");
	}
	while (!is_sorted(*stack_a)) {
		int count_r = 0;
		int count_rr = 0;
		t_stack *current = *stack_a;

		// Check clockwise direction
		while (current->value > current->prev->value && count_r < 1000) {
			current = current->next;
			count_r++;
		}

		current = *stack_a;

		// Check counter-clockwise direction
		while (current->value >= current->prev->value && count_rr < 1000) {
			current = current->prev;
			count_rr++;
		}

		// Choose the direction with the shortest distance
		if (count_r <= count_rr) {
			while (count_r--) {
				printf("ra\n");
				rotate(stack_a, 1);
			}
		} else {
			while (count_rr--) {
				printf("rra\n");
				rotate(stack_a, 0);
			}
		}
	}
}