/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_stacks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhopp <lhopp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 13:41:54 by lhopp             #+#    #+#             */
/*   Updated: 2024/06/20 13:55:43 by lhopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

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
