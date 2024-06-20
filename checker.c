/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhopp <lhopp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 14:19:37 by lhopp             #+#    #+#             */
/*   Updated: 2024/06/13 15:15:03 by lhopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

t_numbers	get_numbers(int argc, char *argv[])
{
	t_numbers	result;

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
	return (result);
}

void	free_numbers(int argc, char **numbers)
{
	int	i;

	if (argc == 2)
	{
		i = 0;
		while (numbers[i])
		{
			free(numbers[i]);
			i++;
		}
		free(numbers);
	}
}

void	populate_stack(t_stack **stack_a, int len, int *integers)
{
	int	i;

	i = len - 1;
	while (i >= 0)
	{
		push(stack_a, create_node(integers[i]));
		i--;
	}
}

void	perform_operation(char *line, t_stack **stack_a, t_stack **stack_b)
{
	if (ft_strncmp(line, "sa", 2) == 0)
		sa(stack_a);
	else if (ft_strncmp(line, "sb", 2) == 0)
		sb(stack_b);
	else if (ft_strncmp(line, "ss", 2) == 0)
		ss(stack_a, stack_b);
	else if (ft_strncmp(line, "pa", 2) == 0)
		pa(stack_a, stack_b);
	else if (ft_strncmp(line, "pb", 2) == 0)
		pb(stack_a, stack_b);
	else if (ft_strncmp(line, "ra", 2) == 0)
		ra(stack_a);
	else if (ft_strncmp(line, "rb", 2) == 0)
		rb(stack_b);
	else if (ft_strncmp(line, "rr", 2) == 0)
		rr(stack_a, stack_b);
	else if (ft_strncmp(line, "rra", 3) == 0)
		rra(stack_a);
	else if (ft_strncmp(line, "rrb", 3) == 0)
		rrb(stack_b);
	else if (ft_strncmp(line, "rrr", 3) == 0)
		rrr(stack_a, stack_b);
	else
		ft_error(stack_a, stack_b);
}

int	main(int argc, char *argv[])
{
	t_stack		*stack_a;
	t_stack		*stack_b;
	t_numbers	numbers;
	int			*integers;
	char		*line;

	stack_a = NULL;
	stack_b = NULL;
	numbers = get_numbers(argc, argv);
	integers = validate_input(numbers.len, numbers.numbers);
	populate_stack(&stack_a, numbers.len, integers);
	free_numbers(argc, numbers.numbers);
	free(integers);
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
