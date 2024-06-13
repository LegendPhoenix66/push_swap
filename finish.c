/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   finish.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhopp <lhopp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 15:16:38 by lhopp             #+#    #+#             */
/*   Updated: 2024/06/13 15:16:40 by lhopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

void	ft_error(t_stack **stack_a, t_stack **stack_b)
{
	ft_putendl_fd("Error", 1);
	while (*stack_a)
		free(pop(stack_a));
	while (*stack_b)
		free(pop(stack_b));
	exit(1);
}

void	finish(t_stack *stack_a, t_stack *stack_b)
{
	if (is_sorted(stack_a) && !stack_b)
		ft_putendl_fd("OK", 1);
	else
		ft_putendl_fd("KO", 1);
	while (stack_a)
		free(pop(&stack_a));
	exit(1);
}
