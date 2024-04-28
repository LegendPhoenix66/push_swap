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
	char **numbers;
	int len;
	int i;

	stack_a = NULL;
	stack_b = NULL;

	if (argc == 2) {
		numbers = ft_split(argv[1], ' ');
		len = 0;
		while (numbers[len]) {
			len++;
		}
	} else {
		numbers = argv + 1;
		len = argc - 1;
	}

	validate_input(len, numbers);

	for (i = len - 1; i >= 0; i--) {
		push(&stack_a, create_node(ft_atoi(numbers[i])));
	}

	if (argc == 2) {
		i = 0;
		while (numbers[i]) {
			free(numbers[i]);
			i++;
		}
		free(numbers);
	}

	sort(&stack_a, &stack_b);
	while (stack_a) {
		free(pop(&stack_a));
	}
	return 0;
}