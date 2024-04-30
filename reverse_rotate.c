/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_rotate.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhopp <lhopp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 14:04:08 by lhopp             #+#    #+#             */
/*   Updated: 2024/04/30 14:04:09 by lhopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	rra(t_stack **stack_a)
{
	rotate(stack_a, 0);
	ft_putendl_fd("rra", 1);
}

void	rrb(t_stack **stack_b)
{
	rotate(stack_b, 0);
	ft_putendl_fd("rrb", 1);
}

void	rrr(t_stack **stack_a, t_stack **stack_b)
{
	rotate(stack_a, 0);
	rotate(stack_b, 0);
	ft_putendl_fd("rrr", 1);
}
