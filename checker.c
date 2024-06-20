/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhopp <lhopp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 14:19:37 by lhopp             #+#    #+#             */
/*   Updated: 2024/06/20 16:13:08 by lhopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

void	perform_rotate_operation(char *line, t_stack **stack_a,
		t_stack **stack_b)
{
	if (ft_strncmp(line, "rra", 3) == 0)
		rotate(stack_a, 0);
	else if (ft_strncmp(line, "rrb", 3) == 0)
		rotate(stack_b, 0);
	else if (ft_strncmp(line, "rrr", 3) == 0)
	{
		rotate(stack_a, 0);
		rotate(stack_b, 0);
	}
	else if (ft_strncmp(line, "ra", 2) == 0)
		rotate(stack_a, 1);
	else if (ft_strncmp(line, "rb", 2) == 0)
		rotate(stack_b, 1);
	else if (ft_strncmp(line, "rr", 2) == 0)
	{
		rotate(stack_a, 1);
		rotate(stack_b, 1);
	}
	else
		ft_error(stack_a, stack_b, line);
}

void	perform_operation(char *line, t_stack **stack_a, t_stack **stack_b)
{
	if (ft_strncmp(line, "sa", 2) == 0)
		swap(stack_a);
	else if (ft_strncmp(line, "sb", 2) == 0)
		swap(stack_b);
	else if (ft_strncmp(line, "ss", 2) == 0)
	{
		swap(stack_a);
		swap(stack_b);
	}
	else if (ft_strncmp(line, "pa", 2) == 0)
	{
		if (!*stack_b)
			return ;
		push(stack_a, pop(stack_b));
	}
	else if (ft_strncmp(line, "pb", 2) == 0)
	{
		if (!*stack_a)
			return ;
		push(stack_b, pop(stack_a));
	}
	else if (line[0] == 'r')
		perform_rotate_operation(line, stack_a, stack_b);
	else
		ft_error(stack_a, stack_b, line);
}

int	validate_and_populate_stack(t_stack **stack_a, t_numbers numbers)
{
	int	*integers;

	integers = validate_input(numbers.len, numbers.numbers);
	if (!integers)
	{
		free_numbers(numbers.len, numbers.numbers);
		return (1);
	}
	populate_stack(stack_a, numbers.len, integers);
	free_numbers(numbers.len, numbers.numbers);
	free(integers);
	return (0);
}

int	main(int argc, char *argv[])
{
	t_stack		*stack_a;
	t_stack		*stack_b;
	t_numbers	numbers;
	char		*line;

	stack_a = NULL;
	stack_b = NULL;
	numbers = get_numbers(argc, argv);
	if (numbers.len == 0)
		return (0);
	if (validate_and_populate_stack(&stack_a, numbers) == 1)
		return (1);
	line = get_next_line(1);
	while (line)
	{
		perform_operation(line, &stack_a, &stack_b);
		free(line);
		line = get_next_line(1);
	}
	free(line);
	finish(stack_a, stack_b);
}
