/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_btree.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgreau <lgreau@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 11:39:24 by lgreau            #+#    #+#             */
/*   Updated: 2024/04/14 15:05:23 by lgreau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_BTREE_H
# define FT_BTREE_H

# include "../ft_error/ft_error.h"
# include "../ft_queue/ft_queue.h"
# include <stdlib.h> // malloc, free, NULL

typedef struct s_btree
{
	struct s_btree	*left;
	struct s_btree	*right;
	void			*item;
}					t_btree;

typedef enum e_traversal_order
{
	PREFIX,
	INFIX,
	POSTFIX,
	BREADTH,
	DEPTH,
	ORDER_COUNT
}					t_traversal_order;

t_btree				*ft_btree_create_node(void *item);

void				ft_btree_iter_prefix(t_btree *root, void (*f)(void *));
void				ft_btree_iter_infix(t_btree *root, void (*f)(void *));
void				ft_btree_iter_postfix(t_btree *root, void (*f)(void *));
void				ft_btree_iter_breadth(t_btree *root, void (*f)(void *),
						void (*del)(void *));
void				ft_btree_iter_depth(t_btree *root, void (*f)(void *));
void				ft_btree_traverse(t_btree *root, void (*f)(void *),
						t_traversal_order order, void (*del)(void *));

void				ft_clear_btree(t_btree *root, void (*del)(void *));

t_btree				*ft_sbtree_find_last(t_btree *root, void *ref,
						int (*cmp)(void *, void *));
void				ft_sbtree_insert(t_btree **root, void *item,
						int (*cmp)(void *, void *));

#endif
