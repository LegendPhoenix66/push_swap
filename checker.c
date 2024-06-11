
#include "checker.h"

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

void sort(t_stack **stack_a, t_stack **stack_b)
{
	stack_b = stack_b;
	stack_a = stack_a;
	//
}

int	main(int argc, char *argv[])
{
	t_stack	*stack_a = NULL;
	t_stack	*stack_b = NULL;
	t_numbers numbers = get_numbers(argc, argv);
	int		*integers = validate_input(numbers.len, numbers.numbers);

	populate_stack(&stack_a, numbers.len, integers);
	free_numbers(argc, numbers.numbers);
	free(integers);
	char *line = get_next_line(1);
	while (line) {
		if (ft_strncmp(line, "sa", 2) == 0)
			sa(&stack_a);
		else if (ft_strncmp(line, "sb", 2) == 0)
			sb(&stack_b);
		else if (ft_strncmp(line, "ss", 2) == 0)
			ss(&stack_a, &stack_b);
		else if (ft_strncmp(line, "pa", 2) == 0)
			pa(&stack_a, &stack_b);
		else if (ft_strncmp(line, "pb", 2) == 0)
			pb(&stack_a, &stack_b);
		else if (ft_strncmp(line, "ra", 2) == 0)
			ra(&stack_a);
		else if (ft_strncmp(line, "rb", 2) == 0)
			rb(&stack_b);
		else if (ft_strncmp(line, "rr", 2) == 0)
			rr(&stack_a, &stack_b);
		else if (ft_strncmp(line, "rra", 3) == 0)
			rra(&stack_a);
		else if (ft_strncmp(line, "rrb", 3) == 0)
			rrb(&stack_b);
		else if (ft_strncmp(line, "rrr", 3) == 0)
			rrr(&stack_a, &stack_b);
		free(line);
		line = get_next_line(1);
	}
	if (is_sorted(stack_a) && !stack_b)
		ft_putendl_fd("OK", 1);
	else
		ft_putendl_fd("KO", 1);
	while (stack_a)
	{
		free(pop(&stack_a));
	}
	stack_b = stack_b;
	return (0);
}