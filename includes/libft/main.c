/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgreau <lgreau@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 10:05:37 by lgreau            #+#    #+#             */
/*   Updated: 2024/04/15 11:39:08 by lgreau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

// void	leaks(void)
// {
// 	system("leaks main");
// }

void	print_item(void *item)
{
	printf("  |- %s\n", (char *)item);
}

int	main(void)
{
	// atexit(leaks);
	char	**operators = get_operators();
	char	str[] = "cmd1 && (cmd2 || cmd3) >> out";
	int		token_count = 0;
	t_token	*token = ft_tokenize(str, &token_count);

	printf("Found %d tokens\n", token_count);
	for(int i = 0; i < token_count; i++)
		printf("  |- %s\t: (%s)\n", operators[token[i].op], token[i].value);

	printf("\nGenerating the syntax tree:\n");

	t_btree	*syntax_tree = ft_btree_create_node((void *)ft_strdup(operators[token[0].op]));
	ft_btree_traverse(syntax_tree, print_item, INFIX, NULL);

	char	*tmp = ft_substr(str, 0, token[0].value - str);
	printf("tmp: %s\n", tmp);
	free(tmp);
	tmp = ft_substr(str, (token[0].value - str) + ft_strlen(operators[token[0].op]), ft_strlen(str) - (token[0].value - str) + ft_strlen(operators[token[0].op]));
	printf("tmp: %s\n", tmp);
	free(tmp);

	free(token);
	exit(*get_errno() != 0);
}
