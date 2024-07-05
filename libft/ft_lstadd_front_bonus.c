/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasal <dasal@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 13:49:16 by dasal             #+#    #+#             */
/*   Updated: 2024/04/30 14:49:26 by dasal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (!lst || !new)
		return ;
	new->next = *lst;
	*lst = new;
}

/* int	main(void)
{
	t_list *list = NULL;

	ft_lstadd_front(&list, ft_lstnew("hello"));
	ft_lstadd_front(&list, ft_lstnew("world"));
	ft_lstadd_front(&list, ft_lstnew("!"));

	t_list *temp = list;
	while (temp != NULL)
	{
		printf("%s\n", (char *)temp->content);
		temp = temp->next;
	}
	return (0);
}
 */