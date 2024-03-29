/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leobarbo <leobarbo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 10:52:53 by leobarbo          #+#    #+#             */
/*   Updated: 2024/02/26 18:03:28 by leobarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minitalk.h"

/**
 * @brief Display a welcome message
 * @brief PID Get the process ID
 * @return void
*/
void	welcome_display(void)
{
	ft_printf(" _____                                         ");
	ft_printf("                                     _____\n");
	ft_printf("( ___ )-----------------------------------------", "");
	ft_printf("-----------------------------------( ___ )\n");
	ft_printf(" |   |                                         ", "");
	ft_printf("                                     |   |\n");
	ft_printf(" |   | ooo        ooooo  o8o               o8o ", "");
	ft_printf("     .             oooo  oooo        |   |\n");
	ft_printf(" |   | `88.       .888'  `*                `*  ", "");
	ft_printf("   .o8             `888  `888        |   |\n");
	ft_printf(" |   |  888b     d'888  oooo  ooo. .oo.   oooo ", "");
	ft_printf(" .o888oo  .oooo.    888   888  oooo  |   |\n");
	ft_printf(" |   |  8  `888'   888   888   888   888   888 ", "");
	ft_printf("   888    .oP'888   888   888888.    |   |\n");
	ft_printf(" |   |  8    Y     888   888   888   888   888 ", "");
	ft_printf("   888 . d8(  888   888   888 `88b.  |   |\n");
	ft_printf(" |   | o8o        o888o o888o o888o o888o o888o", "");
	ft_printf("   '888  `Y888''8o o888o o888o o888o |   |\n");
	ft_printf(" |___|                                         ", "");
	ft_printf("                                     |___|\n");
	ft_printf("(_____)-----------------------------------------", "");
	ft_printf("-----------------------------------(_____)\n");
	ft_printf("            ----- Welcome to Minitalk! ------ ");
	ft_printf("The PID number is: %d ------\n\n", getpid());
}

/**
 * @brief Handle the signals received
 * @brief siginfo Signal information
 * @brief info Signal information
 * @brief context Signal context
 * @brief convert SIGUSR1 and SIGUSR2 receveid to be printed
 * @return void
*/
static void	server_handler(int siginfo, siginfo_t *info, void *context)
{
	static char	c;
	static int	bit;

	(void)context;
	(void)info;
	if (siginfo == SIGUSR1)
		c = c | (1 << bit);
	bit++;
	kill(info->si_pid, SIGUSR2);
	if (bit == 8)
	{
		ft_printf("%c", c);
		c = 0;
		bit = 0;
		kill(info->si_pid, SIGUSR1);
	}
}

/**
 * @brief Configure the signals to be received by the server
 * @brief sa_newsignal New signal action
 * @brief sa_flags Special flags
 * @brief server_handler Signal handler
 * @brief SIGUSR1 User-defined signal 1
 * @brief SIGUSR2 User-defined signal 2
 * @return void
*/
static void	signal_config_server(void)
{
	struct sigaction	sa_newsignal;

	sa_newsignal.sa_sigaction = &server_handler;
	sa_newsignal.sa_flags = SA_SIGINFO;
	if (sigaction(SIGUSR1, &sa_newsignal, NULL) == -1
		|| sigaction(SIGUSR2, &sa_newsignal, NULL) == -1)
	{
		ft_putendl_fd("Error!", STDERR_FILENO);
		exit(1);
	}
}

/**
 * @brief Main function
 * @brief welcome_display Display a welcome message
 * @brief signal_config_server Configure the signals to be received by the server
 * @return 0
*/
int	main(void)
{
	welcome_display();
	while (1)
		signal_config_server();
	return (0);
}
