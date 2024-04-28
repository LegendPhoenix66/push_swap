#include "push_swap.h"

int is_sorted(t_stack *stack)
{
	t_stack *temp = stack;
	while (temp->next != stack) {
		if (temp->value > temp->next->value) {
			return 0;
		}
		temp = temp->next;
	}
	return 1;
}

int is_rotate_sorted(t_stack *stack)
{
	t_stack *temp = stack;
	int jump_flag = 0; // flag to allow one jump in the sequence

	while (temp->next != stack) {
		if (temp->value > temp->next->value) {
			if (jump_flag) {
				return 0; // if we already had a jump, return 0
			} else {
				jump_flag = 1; // if it's the first jump, set the flag
			}
		}
		temp = temp->next;
	}

	// check for a jump at the boundary
	if (jump_flag && temp->value > stack->value) {
		return 0;
	}

	return 1;
}

int is_reverse_sorted(t_stack *stack)
{
	t_stack *temp = stack;
	while (temp->next != stack) {
		if (temp->value < temp->next->value) {
			return 0;
		}
		temp = temp->next;
	}
	return 1;
}