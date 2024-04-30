
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
