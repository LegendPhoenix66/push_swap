/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhopp <lhopp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 11:21:36 by lhopp             #+#    #+#             */
/*   Updated: 2024/06/20 14:01:56 by lhopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	check_list_content(t_list *list, int num)
{
	int	*content;

	while (list)
	{
		if (!list->content)
			break ;
		content = (int *)list->content;
		if (*(content) == num)
			return (-1);
		list = list->next;
	}
	return (0);
}

void	check_duplicates(const t_params *params, t_list **hash, int size)
{
	int				num;
	int				hash_index;
	int				*pnum;
	unsigned int	i;

	i = 0;
	while (i < params->amount)
	{
		num = params->numbers[i];
		hash_index = calculate_hash_index(num, params->min, size);
		if (check_list_content(hash[hash_index], num) == -1)
		{
			clear_hash(hash, size);
			free(params->numbers);
			ft_putendl_fd("Error\n", 2);
			exit(1);
		}
		pnum = malloc(sizeof(int));
		*pnum = num;
		ft_lstadd_front(&hash[hash_index], ft_lstnew(pnum));
		i++;
	}
}

int	initialize_params(t_params *params, unsigned int amount, char **arr)
{
	params->amount = amount;
	params->arr = arr;
	params->numbers = (int *)malloc(sizeof(int) * amount);
	if (!params->numbers)
	{
		ft_putendl_fd("Error: Memory allocation failed\n", 2);
		exit(1);
	}
	params->min = INT_MAX;
	params->max = INT_MIN;
	check_argument_count(params->amount);
	return (convert_and_validate_input(params));
}

int	*validate_input(unsigned int amount, char **arr)
{
	t_params	params;
	int			size;
	t_list		**hash;
	int			init_result;

	init_result = initialize_params(&params, amount, arr);
	if (init_result == -1)
	{
		free(params.numbers);
		return (NULL);
	}
	size = params.max - params.min + 1;
	if (size > 1000 || size <= 0)
		size = 1000;
	hash = allocate_hash(size);
	check_duplicates(&params, hash, size);
	clear_hash(hash, size);
	return (params.numbers);
}
