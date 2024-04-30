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
		exit(0);
}

int calculate_num_len(int num)
{
    int num_len = 0;
    int temp = num;
    while (temp)
    {
        num_len++;
        temp /= 10;
    }
    if (num <= 0)
        num_len++;
    return num_len;
}

void validate_num(int num, int str_len, int num_len, char *arr)
{
    if (num == 0 && arr[0] != '0')
    {
        ft_putendl_fd("Error\n", 2);
        exit(1);
    }
    if (num_len != str_len)
    {
        ft_putendl_fd("Error\n", 2);
        exit(1);
    }
    if ((arr[0] == '-' && num > 0) || (arr[0] != '-' && num < 0))
    {
        ft_putendl_fd("Error\n", 2);
        exit(1);
    }
}

void convert_and_validate_input(t_params *params)
{
    unsigned int i;
    int num;

    i = 0;
    while (i < params->amount)
    {
        num = ft_atoi(params->arr[i]);
        validate_num(num, ft_strlen(params->arr[i]),
					 calculate_num_len(num), params->arr[i]);
        params->numbers[i] = num;
        if (num < params->min)
            params->min = num;
        if (num > params->max)
            params->max = num;
        i++;
    }
}

int calculate_hash_index(int num, int min, int size)
{
    int hash_index = (num - min) % size;
    if (hash_index < 0)
        hash_index = -hash_index;
    return hash_index;
}

void check_list_content(t_list *list, int num)
{
    int *content;
    while (list)
    {
        if (!list->content)
            break;
        content = (int *)list->content;
        if (*(content) == num)
        {
            ft_putendl_fd("Error\n", 2);
            exit(1);
        }
        list = list->next;
    }
}

void check_duplicates(const t_params *params, t_list **hash, int size)
{
    int num;
    int hash_index;
    int *pnum;
    unsigned int i;

    i = 0;
    while (i < params->amount)
    {
        num = params->numbers[i];
        hash_index = calculate_hash_index(num, params->min, size);
        check_list_content(hash[hash_index], num);
        pnum = malloc(sizeof(int));
        *pnum = num;
        ft_lstadd_front(&hash[hash_index],  ft_lstnew(pnum));
        i++;
    }
}

void initialize_params(t_params *params, unsigned int amount, char **arr)
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
    convert_and_validate_input(params);
}

t_list **allocate_hash(int size)
{
    t_list **hash;
    int i;

    hash = (t_list **)malloc(sizeof(t_list) * size);
    if (!hash)
    {
        ft_putendl_fd("Error: Memory allocation failed\n", 2);
        exit(1);
    }
    i = 0;
    while (i < size)
    {
        hash[i] = NULL;
        i++;
    }
    ft_memset(hash, 0, sizeof(t_list) * size);
    return hash;
}

void clear_hash(t_list **hash, int size)
{
    int i = 0;
    while (i < size)
    {
        ft_lstclear(&hash[i], free);
        i++;
    }
    free(hash);
}

int *validate_input(unsigned int amount, char **arr)
{
    t_params params;
    int size;
    t_list **hash;

    initialize_params(&params, amount, arr);
    size = params.max - params.min + 1;
    if (size > 1000 || size <= 0)
        size = 1000;
    hash = allocate_hash(size);
    check_duplicates(&params, hash, size);
    clear_hash(hash, size);
    return params.numbers;
}
