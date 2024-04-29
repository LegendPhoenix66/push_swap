/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhopp <lhopp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 11:22:00 by lhopp             #+#    #+#             */
/*   Updated: 2024/04/29 11:22:02 by lhopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

// initialize stacks, which are actually doubly linked lists
int main(int argc, char *argv[])
{
	t_stack *stack_a;
	t_stack *stack_b;
	char **numbers;
	int len;
	int i;

	stack_a = NULL;
	stack_b = NULL;

	if (argc == 2) {
		numbers = ft_split(argv[1], ' ');
		len = 0;
		while (numbers[len]) {
			len++;
		}
	} else {
		numbers = argv + 1;
		len = argc - 1;
	}

	validate_input(len, numbers);

	for (i = len - 1; i >= 0; i--) {
		push(&stack_a, create_node(ft_atoi(numbers[i])));
	}

	if (argc == 2) {
		i = 0;
		while (numbers[i]) {
			free(numbers[i]);
			i++;
		}
		free(numbers);
	}

	sort(&stack_a, &stack_b);
	while (stack_a) {
		free(pop(&stack_a));
	}
	return 0;
}
