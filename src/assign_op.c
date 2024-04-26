/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign_op.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klamprak <klamprak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 18:57:49 by klamprak          #+#    #+#             */
/*   Updated: 2024/04/26 19:11:11 by klamprak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
	- Cases:
		- name=
			- if exists empty its value, else coninue
		- name="     value  a"
			- same as name = "value a"
		- name=value
			- create the name with this value
		- name+=value
			- if name not exists it create it, else add value at its end
		- name=$name2
			- just replace $name2 with its content and run the initial assigment
	- Errors
		-$name=value
			- replace $name with its content and execute the whole command
			content=value: command not found
		-"name"=value
			- name=value: command not found

*/

void	check_for_assigments(char *str)
{
	int	i;

	if (!str)
		return ;
	i = -1;
	while (str[++i])
	{

	}
}
