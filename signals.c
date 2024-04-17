/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klamprak <klamprak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 09:56:54 by klamprak          #+#    #+#             */
/*   Updated: 2024/04/17 10:07:57 by klamprak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
info:
	- we can not pass any data to signal handler(its forbitten at task description) so we need to clean everything each time a command is finished
	so we will be ready to terminate the program as soon as we get a ctrl+D signal
	- its ok if you don't free some things like envp[][] before you exit as soon as you have not access to main variables

Shell:
	- https://stackoverflow.com/questions/18530572/how-to-execute-a-command-from-c-and-terminate-it: send signal to proccess after fork
	- ctrl + C(SIGINT):
		- if you run a command, send SIGINT to it and stop the rest of the command. Then just print another prommt
		- if you don't run a command, don't do anything, just print another prommt
	- ctrl + D(SIGQUIT):
		- if you run a command, just send this signal to the command
		- if you dont run a command
			- if rl_buffer is empty terminate the shell (everything should be already cleaned every time you finish command execution)
			- else do nothing
	- ctrl + \
		- just ignore it, but handle it in order not to stop the program

Built-ins functs:
	- should handle ctrl + D as the original behavior (most likely ignore it)
	- should handle ctrl + C to clean and terminated

- General
	- ctrl-C
		- SIGINT
		- while a program is running, you're telling it to interrupt what it's doing and stop
		- SIGINT is the signal sent when we press Ctrl+C. The default action is to terminate the process.
		However, some programs override this action and handle it differently. One common example is the bash interpreter.
		When we press Ctrl+C it doesn’t quit, instead, it prints a new and empty prompt line.
	- ctrl-D
		- SIGQUIT
		- Many programs won't respond to a SIGQUIT (some might, it's up to them) but bash itself will.
		If you're in a bash prompt and it want it to exit (like if you're remotely connected to a bash server for example),
		if you hit CTRL + D it'll tell the bash session to end. You also could close the window or just type exit and it'll
		exit too.
		- SIGQUIT also generates a core dump before exiting and terminated if used for a program
	- ctrl-\
		- SIGQUIT
		- but they said on interactive not to do anything
 */
