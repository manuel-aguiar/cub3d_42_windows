/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   liang-barsky.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 17:34:55 by marvin            #+#    #+#             */
/*   Updated: 2024/01/12 17:34:55 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIANG_BARSKY_H

# define LIANG_BARSKY_H



typedef struct s_lbclip
{
	int		p1;
	int		p2;
	int		p3;
	int		p4;
	int		q1;
	int		q2;
	int		q3;
	int		q4;
	float	posarr[5];
	float	negarr[5];
	int		posind;
	int		negind;
	float	r1;
	float	r2;
	float	r3;
	float	r4;
	int		xn1;
	int		yn1;
	int		xn2;
	int		yn2;
	float	rn1;
	float	rn2;
}	t_lbclip;



#endif