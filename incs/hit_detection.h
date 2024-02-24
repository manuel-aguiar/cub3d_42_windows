/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_detection.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 09:15:13 by marvin            #+#    #+#             */
/*   Updated: 2024/02/24 09:15:13 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HIT_DETECTION_H

# define HIT_DETECTION_H

# include "libft.h"
# include "vector.h"

typedef struct s_hitnode t_hitnode;
typedef struct s_sprite  t_sprite;

typedef struct s_hitnode
{
	t_sprite	*sprite;
	t_hitnode	*next;
}	t_hitnode;

typedef struct s_hitlist
{
	t_hitnode	*head;
	size_t		len;
}	t_hitlist;

typedef struct s_lb_hit
{
	float		p1;
	float		p2;
	float		p3;
	float		p4;
	float		q1;
	float		q2;
	float		q3;
	float		q4;
	float	    posarr[5];
	float	    negarr[5];
	int		    posind;
	int		    negind;
	float	    r1;
	float	    r2;
	float	    r3;
	float	    r4;
	float	    xn1;
	float	    yn1;
	float	    xn2;
	float	    yn2;
	float	    rn1;
	float	    rn2;
}	t_lb_hit;

int	    liang_barsky_hit(t_vector low_bot, t_vector hi_top, t_vector start, t_vector end);
void	hitlist_in_head(t_hitlist *list, t_hitnode *insert);

#endif