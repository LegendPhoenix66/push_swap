#include "push_swap.h"

// remove later, just to test if the stack was created correctly
void print_stacks(t_stack *stack_a, t_stack *stack_b)
{
	// print the stack to verify that it was created correctly
	printf("stack_a\n");
	if (stack_a == NULL) {
		printf("stack is empty\n");
	} else {
		t_stack *temp = stack_a;
		while (temp->next != stack_a) {
			printf("%ld\n", temp->value);
			temp = temp->next;
		}
		printf("%ld\n", temp->value);
		printf("end\n\n");
	}

	printf("stack_b\n");
	if (stack_b == NULL) {
		printf("stack is empty\n");
	} else {
		t_stack *temp = stack_b;
		while (temp->next != stack_b) {
			printf("%ld\n", temp->value);
			temp = temp->next;
		}
		printf("%ld\n", temp->value);
		printf("end\n\n");
	}
}

// initialize stacks, which are actually doubly linked lists
int main(int argc, char *argv[])
{
	t_stack *stack_a;
	t_stack *stack_b;

	validate_input(argc - 1, argv + 1);
	stack_a = NULL;
	stack_b = NULL;
	int i = argc - 1;
	while (i > 0) {
		push(&stack_a, create_node(ft_atoi(argv[i])));
		i--;
	}

	sort(&stack_a, &stack_b);
	while (stack_a) {
		free(pop(&stack_a));
	}
	return 0;
}
