/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhopp <lhopp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 11:22:05 by lhopp             #+#    #+#             */
/*   Updated: 2024/04/29 11:22:06 by lhopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
#define PUSH_SWAP_H

#include "libft/libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct s_stack
{
	long value;
	struct s_stack *next;
	struct s_stack *prev;
} t_stack;

typedef struct s_move
{
	int total_moves;
	int rotations_a;
	int direction_a;
	int rotations_b;
	int direction_b;
} t_move;

t_stack *create_node(long value);
void push(t_stack **stack, t_stack *new_node);
t_stack *pop(t_stack **stack);
void rotate(t_stack **stack, int direction);
void swap(t_stack **stack);
void validate_input(unsigned amount, char **arr);
void sort(t_stack **stack_a, t_stack **stack_b);
void rotate_sort(t_stack **stack_a);
int is_sorted(t_stack *stack);
int is_rotate_sorted(t_stack *stack);
int is_reverse_sorted(t_stack *stack);
t_move find_best_move(t_stack *stack_a, t_stack *stack_b);
int stack_size(t_stack *stack);

#endif //PUSH_SWAP_H
