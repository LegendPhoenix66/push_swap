/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhopp <lhopp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 14:02:32 by lhopp             #+#    #+#             */
/*   Updated: 2024/04/30 14:03:39 by lhopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ra(t_stack **stack_a)
{
	rotate(stack_a, 1);
	ft_putendl_fd("ra", 1);
}

void	rb(t_stack **stack_b)
{
	rotate(stack_b, 1);
	ft_putendl_fd("rb", 1);
}

void	rr(t_stack **stack_a, t_stack **stack_b)
{
	rotate(stack_a, 1);
	rotate(stack_b, 1);
	ft_putendl_fd("rr", 1);
}
