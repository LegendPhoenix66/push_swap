
#include "push_swap.h"
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
