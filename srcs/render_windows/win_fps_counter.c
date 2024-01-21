/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fps_counter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 12:10:53 by marvin            #+#    #+#             */
/*   Updated: 2024/01/21 12:10:53 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "render_windows.h"

void    set_fps_start(t_fps_counter *fps)
{
    GetSystemTime(&fps->start);
}


//static void	putcountint_fps(int nb, char    str[12])
//{
//	char	print;
//	int		i;
//	char	sign;
//
//	sign = 1;
//	i = 12;  //sizeof str blabla
//	if (nb < 0)
//		sign = -1;
//	if (nb == 0)
//		str[--i] = '0';
//	while (nb != 0)
//	{
//		print = nb % 10;
//		if (print < 0)
//			print *= -1;
//		str[--i] = print + '0';
//		nb /= 10;
//	}
//	if (sign == -1)
//		str[--i] = '-';
//    str[12 - i] = '\0';  //sizeof str blabla
//}

void    fps_calc_print(t_fps_counter *fps)
{
    GetSystemTime(&fps->end);
    FILETIME fileTime1, fileTime2;

    // Convert SYSTEMTIME to FILETIME
    SystemTimeToFileTime(&fps->start, &fileTime1);
    SystemTimeToFileTime(&fps->end, &fileTime2);

    // Subtract FILETIME values
    ULARGE_INTEGER uli1, uli2;
    uli1.LowPart = fileTime1.dwLowDateTime;
    uli1.HighPart = fileTime1.dwHighDateTime;
    uli2.LowPart = fileTime2.dwLowDateTime;
    uli2.HighPart = fileTime2.dwHighDateTime;


    long long int res = (long long int)((long long)(1000 * 10000) / (long long)(uli2.QuadPart - uli1.QuadPart));  // Convert 100-nanosecond intervals to milliseconds, 1000/ number to get fps
	fps->count = (long int)res;

	fps->start = fps->end;
	//ft_memcpy(&fps->start, &fps->end, sizeof(fps->start));
	//ft_memset(&fps->end, 0, sizeof(fps->end));
    //ft_memset(fps->fps, 0, sizeof(fps->fps));
    //putcountint_fps(fps->count, fps->fps);

	printf("fps: %ld\n", fps->count);

}