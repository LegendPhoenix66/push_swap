/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhopp <lhopp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 11:22:00 by lhopp             #+#    #+#             */
/*   Updated: 2024/05/22 10:53:52 by lhopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

// initialize stacks, which are actually circular doubly linked lists
int	main(int argc, char *argv[])
{
	t_stack		*stack_a;
	t_stack		*stack_b;
	t_numbers	numbers;
	int			*integers;

	stack_a = NULL;
	stack_b = NULL;
	numbers = get_numbers(argc, argv);
	if (numbers.len == 0)
		return (0);
	integers = validate_input(numbers.len, numbers.numbers);
	populate_stack(&stack_a, numbers.len, integers);
	free_numbers(argc, numbers.numbers);
	free(integers);
	sort(&stack_a, &stack_b);
	while (stack_a)
	{
		free(pop(&stack_a));
	}
	return (0);
}
