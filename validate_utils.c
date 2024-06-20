/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhopp <lhopp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 10:57:54 by lhopp             #+#    #+#             */
/*   Updated: 2024/06/20 14:20:19 by lhopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	check_argument_count(unsigned int amount)
{
	if (amount < 1)
		exit(0);
}

int	calculate_num_len(int num)
{
	int	num_len;
	int	temp;

	num_len = 0;
	temp = num;
	while (temp)
	{
		num_len++;
		temp /= 10;
	}
	if (num <= 0)
		num_len++;
	return (num_len);
}

int	validate_num(int num, int str_len, int num_len, char *arr)
{
	if (num == 0 && arr[0] != '0')
	{
		ft_putendl_fd("Error\n", 2);
		return (-1);
	}
	if (num_len != str_len)
	{
		ft_putendl_fd("Error\n", 2);
		return (-1);
	}
	if ((arr[0] == '-' && num > 0) || (arr[0] != '-' && num < 0))
	{
		ft_putendl_fd("Error\n", 2);
		return (-1);
	}
	return (0);
}

int	convert_and_validate_input(t_params *params)
{
	unsigned int	i;
	int				num;
	int				result;

	i = 0;
	while (i < params->amount)
	{
		num = ft_atoi(params->arr[i]);
		result = validate_num(num, ft_strlen(params->arr[i]),
				calculate_num_len(num), params->arr[i]);
		if (result == -1)
			return (-1);
		params->numbers[i] = num;
		if (num < params->min)
			params->min = num;
		if (num > params->max)
			params->max = num;
		i++;
	}
	return (0);
}
