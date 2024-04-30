/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhopp <lhopp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 11:22:00 by lhopp             #+#    #+#             */
/*   Updated: 2024/04/30 16:53:43 by lhopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

// get t_numbers struct with numbers as string and its length from argv
t_numbers get_numbers(int argc, char *argv[])
{
	t_numbers result;
	if (argc == 2)
	{
		result.numbers = ft_split(argv[1], ' ');
		result.len = 0;
		while (result.numbers[result.len])
			result.len++;
	}
	else
	{
		result.numbers = argv + 1;
		result.len = argc - 1;
	}
	return result;
}

void free_numbers(int argc, char **numbers)
{
	if (argc == 2)
	{
		int i = 0;
		while (numbers[i])
		{
			free(numbers[i]);
			i++;
		}
		free(numbers);
	}
}

void populate_stack(t_stack **stack_a, int len, int *integers)
{
	int i = len - 1;
	while (i >= 0)
	{
		push(stack_a, create_node(integers[i]));
		i--;
	}
}

// initialize stacks, which are actually circular doubly linked lists
int	main(int argc, char *argv[])
{
	t_stack	*stack_a = NULL;
	t_stack	*stack_b = NULL;
	t_numbers numbers = get_numbers(argc, argv);
	int		*integers = validate_input(numbers.len, numbers.numbers);

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
