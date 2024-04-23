/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_export.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klamprak <klamprak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 13:45:22 by klamprak          #+#    #+#             */
/*   Updated: 2024/04/23 20:06:20 by klamprak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
	Edge cases:
		export test
			- test not exist (just add "test" and export it, but not on env)
			- test exists and has a value already (just export it "test=value")
				- "value" for export and value for env without ""
		export test=
			- add 'test=""' even if test already exists with a value
				- add "test=" at env but without quotes
				- add test="" at export
		export test=value
			- test not exist (export it 'test="value"'))
			- test exists and has a value already (export it "test="new_value""))
			- value is not a valid name_value
			- in all cases should add on env whithout "" and on export with ""
		export test="value"
			- same with test=value
		export
			- just print env and exported vars but sorted
 */

/**
 * @brief reproduce the behavior of export with no options
 *
 * @param argv a list like ["echo", "-n", "string1", "string2", NULL]
 * @param envp environment variables
 * @return int, 0 on success, -1 on error
 */
int	b_export(char *const argv[], char *envp[])
{
	argv = NULL;
	envp = NULL;
	return (0);
}
