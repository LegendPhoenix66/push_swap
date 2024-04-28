#include "push_swap.h"

typedef struct s_params
{
	unsigned amount;
	char **arr;
	int *numbers;
	int min;
	int max;
} t_params;

void check_argument_count(unsigned amount)
{
	if (amount < 1) {
		printf("Error: Invalid amount of arguments\n");
		exit(1);
	}
}

void convert_and_validate_input(t_params *params)
{
	unsigned i;
	int num;

	i = 0;
	while (i < params->amount) {
		num = ft_atoi(params->arr[i]);
		if (num == 0 && params->arr[i][0] != '0') {
			printf("Error: Invalid input (NaN)\n");
			exit(1);
		}
		if ((params->arr[i][0] == '-' && num > 0) || (params->arr[i][0] != '-' && num < 0)) {
			printf("Error: Invalid input (overflow)\n");
			exit(1);
		}
		params->numbers[i] = num;
		if (num < params->min) params->min = num;
		if (num > params->max) params->max = num;
		i++;
	}
}

void check_duplicates(const t_params *params, t_list **hash, int size)
{
	for (unsigned i = 0; i < params->amount; i++) {
		int num = params->numbers[i];
		int hash_index = num % size - params->min;
		if (hash_index < 0) {
			hash_index = -hash_index;
		}

		t_list *list = hash[hash_index];
		while (list) {
			if (!list->content) {
				break;
			}
			int *content = (int *) list->content;
			if (*(content) == num) {
				printf("Error: Duplicate input\n");
				exit(1);
			}
			list = list->next;
		}
		int *pnum = malloc(sizeof(int));
		*pnum = num;
		t_list *new_node = ft_lstnew(pnum);
		ft_lstadd_front(&hash[hash_index], new_node);
	}
}

void validate_input(unsigned amount, char **arr)
{
	t_params params;
	params.amount = amount;
	params.arr = arr;
	params.numbers = (int *) malloc(sizeof(int) * amount);
	if (!params.numbers) {
		printf("Error: Memory allocation failed\n");
		exit(1);
	}
	params.min = INT_MAX;
	params.max = INT_MIN;

	check_argument_count(params.amount);
	convert_and_validate_input(&params);

	int size = params.max - params.min + 1;
	if (size > 1000 || size <= 0) {
		size = 1000;
	}
	t_list **hash = (t_list **) malloc(sizeof(t_list) * size);
	if (!hash) {
		printf("Error: Memory allocation failed\n");
		exit(1);
	}
	for (int i = 0; i < size; i++) {
		hash[i] = NULL;
	}
	ft_memset(hash, 0, sizeof(t_list) * size);
	check_duplicates(&params, hash, size);
	free(params.numbers);
	for (int i = 0; i < size; i++) {
		ft_lstclear(&hash[i], free);
	}
	free(hash);
}
