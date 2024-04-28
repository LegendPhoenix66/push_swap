# include "push_swap.h"

t_stack *create_node(long value)
{
	t_stack *new_node = malloc(sizeof(t_stack));
	if (!new_node) {
		return NULL;
	}
	new_node->value = value;
	new_node->next = NULL;
	new_node->prev = NULL;
	return new_node;
}

void push(t_stack **stack, t_stack *new_node)
{
	if (!*stack) {
		new_node->next = new_node;
		new_node->prev = new_node;
		*stack = new_node;
	} else {
		t_stack *last = (*stack)->prev;

		new_node->next = *stack;
		(*stack)->prev = new_node;
		new_node->prev = last;
		last->next = new_node;
		*stack = new_node;
	}
}

t_stack *pop(t_stack **stack)
{
	if (!*stack) {
		return NULL;
	}

	t_stack *last = (*stack)->prev;
	t_stack *first = *stack;

	if (first == last) {
		*stack = NULL;
	} else {
		last->next = first->next;
		first->next->prev = last;
		*stack = last->next;
	}

	first->next = NULL;
	first->prev = NULL;
	return first;
}

void rotate(t_stack **stack, int direction)
{
	if (!*stack || !(*stack)->next) {
		return;
	}

	if (direction == 1) {
		*stack = (*stack)->next;
	} else {
		*stack = (*stack)->prev;
	}
}

void swap(t_stack **stack)
{
	if (!*stack || !(*stack)->next) {
		return;
	}

	t_stack *first = *stack;
	t_stack *second = first->next;

	first->next = second->next;
	second->next->prev = first;
	second->prev = first->prev;
	first->prev->next = second;
	first->prev = second;
	second->next = first;

	*stack = second;
}

