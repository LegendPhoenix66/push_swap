/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhopp <lhopp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 11:22:05 by lhopp             #+#    #+#             */
/*   Updated: 2024/05/22 10:53:55 by lhopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include "libft/libft.h"

typedef struct s_stack
{
	long			value;
	struct s_stack	*next;
	struct s_stack	*prev;
}					t_stack;

typedef struct s_move
{
	int				total_moves;
	int				rotations_a;
	int				direction_a;
	int				rotations_b;
	int				direction_b;
}					t_move;

typedef struct s_params
{
	unsigned int	amount;
	char			**arr;
	int				*numbers;
	int				min;
	int				max;
}					t_params;

typedef struct s_numbers
{
	char			**numbers;
	int				len;
}					t_numbers;

t_stack				*create_node(long value);
void				push(t_stack **stack, t_stack *new_node);
t_stack				*pop(t_stack **stack);
void				rotate(t_stack **stack, int direction);
void				swap(t_stack **stack);

void				sa(t_stack **stack_a);
void				pa(t_stack **stack_a, t_stack **stack_b);
void				pb(t_stack **stack_a, t_stack **stack_b);
void				ra(t_stack **stack_a);
void				rb(t_stack **stack_b);
void				rr(t_stack **stack_a, t_stack **stack_b);
void				rra(t_stack **stack_a);
void				rrb(t_stack **stack_b);
void				rrr(t_stack **stack_a, t_stack **stack_b);

int					*validate_input(unsigned int amount, char **arr);
void				sort(t_stack **stack_a, t_stack **stack_b);
void				rotate_sort(t_stack **stack_a);
int					is_sorted(t_stack *stack);
int					is_rotate_sorted(t_stack *stack);
int					is_reverse_sorted(t_stack *stack);
t_move				find_best_move(t_stack *stack_a, t_stack *stack_b);
int					stack_size(t_stack *stack);
void				check_b_rotation(const t_stack *node, t_stack *stack_b,
						t_move *move);
void				perform_best_move(t_stack **stack_a, t_stack **stack_b);
t_list				**allocate_hash(int size);
int					calculate_hash_index(int num, int min, int size);
void				clear_hash(t_list **hash, int size);
void				convert_and_validate_input(t_params *params);
void				check_argument_count(unsigned int amount);

#endif // PUSH_SWAP_H
