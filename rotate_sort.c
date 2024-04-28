#include "push_swap.h"

void calculate_rotations(t_stack **stack_a, int *rotate_r, int *rotate_l)
{
	t_stack *temp_r = *stack_a;
	t_stack *temp_l = *stack_a;
	*rotate_r = 1;
	*rotate_l = 1;
	while (temp_r->value < temp_r->next->value) {
		temp_r = temp_r->next;
		(*rotate_r)++;
	}
	while (temp_l->value > temp_l->prev->value) {
		temp_l = temp_l->prev;
		(*rotate_l)++;
	}
}

int determine_direction(int rotate_r, int rotate_l)
{
	if (rotate_r < rotate_l) {
		return 1;
	} else {
		return 0;
	}
}

void perform_rotation(t_stack **stack_a, int direction)
{
	while (!is_sorted(*stack_a)) {
		rotate(stack_a, direction);
		if (direction) {
			printf("ra\n");
		} else {
			printf("rra\n");
		}
	}
}

void rotate_sort(t_stack **stack_a)
{
	int rotate_r, rotate_l;
	calculate_rotations(stack_a, &rotate_r, &rotate_l);
	int direction = determine_direction(rotate_r, rotate_l);
	perform_rotation(stack_a, direction);
}
