/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_sorted.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhopp <lhopp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 11:21:47 by lhopp             #+#    #+#             */
/*   Updated: 2024/04/29 11:21:50 by lhopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	int jump_flag = 0;

	while (temp->next != stack) {
		if (temp->value > temp->next->value) {
			if (jump_flag) {
				return 0;
			} else {
				jump_flag = 1;
			}
		}
		temp = temp->next;
	}

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