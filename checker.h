/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhopp <lhopp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 14:20:15 by lhopp             #+#    #+#             */
/*   Updated: 2024/06/20 13:55:26 by lhopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHECKER_H
# define CHECKER_H

# include "libft/libft.h"

typedef struct s_stack
{
	long			value;
	struct s_stack	*next;
	struct s_stack	*prev;
}					t_stack;

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
void				sb(t_stack **stack_b);
void				ss(t_stack **stack_a, t_stack **stack_b);
void				pa(t_stack **stack_a, t_stack **stack_b);
void				pb(t_stack **stack_a, t_stack **stack_b);
void				ra(t_stack **stack_a);
void				rb(t_stack **stack_b);
void				rr(t_stack **stack_a, t_stack **stack_b);
void				rra(t_stack **stack_a);
void				rrb(t_stack **stack_b);
void				rrr(t_stack **stack_a, t_stack **stack_b);

int					*validate_input(unsigned int amount, char **arr);
int					is_sorted(t_stack *stack);
char				*get_next_line(int fd);
void				ft_error(t_stack **stack_a, t_stack **stack_b);
void				finish(t_stack *stack_a, t_stack *stack_b);
t_numbers			get_numbers(int argc, char *argv[]);
void				free_numbers(int argc, char **numbers);
void				populate_stack(t_stack **stack_a, int len, int *integers);

#endif // CHECKER_H
