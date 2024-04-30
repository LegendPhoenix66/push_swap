
#include "push_swap.h"

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

int calculate_hash_index(int num, int min, int size)
{
	int hash_index = (num - min) % size;
	if (hash_index < 0)
		hash_index = -hash_index;
	return hash_index;
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
