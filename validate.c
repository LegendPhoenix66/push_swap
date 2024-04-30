/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhopp <lhopp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 11:21:36 by lhopp             #+#    #+#             */
/*   Updated: 2024/04/30 16:54:17 by lhopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	check_argument_count(unsigned int amount)
{
	if (amount < 1)
	{
		exit(1);
	}
}

// too many lines
void	convert_and_validate_input(t_params *params)
{
	unsigned int	i;
	int				num;
	int				str_len;
	int				num_len;
	int				temp;

	i = 0;
	while (i < params->amount)
	{
		str_len = ft_strlen(params->arr[i]);
		num = ft_atoi(params->arr[i]);
		num_len = 0;
		temp = num;
		while (temp)
		{
			num_len++;
			temp /= 10;
		}
		if (num <= 0)
		{
			num_len++;
		}
		if (num == 0 && params->arr[i][0] != '0')
		{
			fprintf(stderr, "Error\n");
			exit(1);
		}
		if (num_len != str_len)
		{
			fprintf(stderr, "Error\n");
			exit(1);
		}
		if ((params->arr[i][0] == '-' && num > 0) || (params->arr[i][0] != '-'
				&& num < 0))
		{
			fprintf(stderr, "Error\n");
			exit(1);
		}
		params->numbers[i] = num;
		if (num < params->min)
			params->min = num;
		if (num > params->max)
			params->max = num;
		i++;
	}
}

// too many lines
void	check_duplicates(const t_params *params, t_list **hash, int size)
{
	int				num;
	int				hash_index;
	t_list			*list;
	int				*content;
	int				*pnum;
	t_list			*new_node;
	unsigned int	i;

	i = 0;
	while (i < params->amount)
	{
		num = params->numbers[i];
		hash_index = (num - params->min) % size;
		if (hash_index < 0)
		{
			hash_index = -hash_index;
		}
		list = hash[hash_index];
		while (list)
		{
			if (!list->content)
			{
				break ;
			}
			content = (int *)list->content;
			if (*(content) == num)
			{
				fprintf(stderr, "Error\n");
				exit(1);
			}
			list = list->next;
		}
		pnum = malloc(sizeof(int));
		*pnum = num;
		new_node = ft_lstnew(pnum);
		ft_lstadd_front(&hash[hash_index], new_node);
		i++;
	}
}

// too many lines
int	*validate_input(unsigned int amount, char **arr)
{
	t_params	params;
	int			size;
	t_list		**hash;
	int			i;

	params.amount = amount;
	params.arr = arr;
	params.numbers = (int *)malloc(sizeof(int) * amount);
	if (!params.numbers)
	{
		fprintf(stderr, "Error: Memory allocation failed\n");
		exit(1);
	}
	params.min = INT_MAX;
	params.max = INT_MIN;
	check_argument_count(params.amount);
	convert_and_validate_input(&params);
	size = params.max - params.min + 1;
	if (size > 1000 || size <= 0)
	{
		size = 1000;
	}
	hash = (t_list **)malloc(sizeof(t_list) * size);
	if (!hash)
	{
		fprintf(stderr, "Error: Memory allocation failed\n");
		exit(1);
	}
	i = 0;
	while (i < size)
	{
		hash[i] = NULL;
		i++;
	}
	ft_memset(hash, 0, sizeof(t_list) * size);
	check_duplicates(&params, hash, size);
	i = 0;
	while (i < size)
	{
		ft_lstclear(&hash[i], free);
		i++;
	}
	free(hash);
	return (params.numbers);
}
