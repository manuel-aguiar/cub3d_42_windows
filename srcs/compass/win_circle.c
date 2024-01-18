/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   win_circle.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 11:32:07 by marvin            #+#    #+#             */
/*   Updated: 2024/01/15 11:32:07 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "compass.h"

/*Midpoint Circle algorithm, by calculating 1/8 of a circle, one can render the
full object by projecting coordinates

i will have to use a hashtable to store the circles coordinates to make collision
detection easier. inner circle will not be moveable so the coordinates will always
be valid. if the circle has atmost 200 height, i'll be storing 1600 bytes,
so it is a very small table and not drain much memory

hashtable for the square as well, for each single frame the square will be the same for everyone except
the offset from where it starts off, with a couple of lookups i can check the boundaries for
each scanline and print only what is needed

*/

// must be visible

void	draw_horizontal_line(t_win_glfw *win, int min_x, int max_x, int y, int color)
{
	while (min_x <= max_x)
		win->set_pixel(win, min_x++, y, color);
}		


void	win_full_circle(t_win_glfw *win, t_pixel centre, int radius, int color)
{
    int x;
    int y;
    int decision;


	if (centre.x - radius < 0 || centre.y - radius < 0 || centre.x + radius > win->win_width || centre.y + radius > win->win_height)
		return ;
	x = radius;
	y = 0;
	decision = 1 - radius;
	while (y <= x)
	{
		draw_horizontal_line(win, -y + centre.x, y + centre.x, x + centre.y, color);
		draw_horizontal_line(win, -x + centre.x, x + centre.x, y + centre.y, color);
		draw_horizontal_line(win, -x + centre.x, x + centre.x, -y + centre.y, color);
		draw_horizontal_line(win, -y + centre.x, y + centre.x, -x + centre.y, color);
		y++;
		if (decision <= 0)
			decision += 2 * y + 1;
		else
		{
			x--;
			decision += 2 * (y - x) + 1;
		}
	}
}


void	win_drawcircle_wo_antialiasing(t_win_glfw *win, t_pixel centre, int radius, int color, int width)
{
    int x;
    int y;
    int decision;
	int count;

	if (centre.x - radius < 0 || centre.y - radius < 0 || centre.x + radius > win->win_width || centre.y + radius > win->win_height)
		return ;

	count = 0;
	while (count < width)
	{
		x = radius - count;
		y = 0;
		decision = 1 - radius;

		while (y <= x)
		{
			win->set_pixel(win, x + centre.x, y + centre.y, color);
			win->set_pixel(win, -x + centre.x, y + centre.y, color);
			win->set_pixel(win, x + centre.x, -y + centre.y, color);
			win->set_pixel(win, -x + centre.x, -y + centre.y, color);
			win->set_pixel(win, y + centre.x, x + centre.y, color);
			win->set_pixel(win, -y + centre.x, x + centre.y, color);
			win->set_pixel(win, y + centre.x, -x + centre.y, color);
			win->set_pixel(win, -y + centre.x, -x + centre.y, color);
			y++;
			if (decision <= 0)
				decision += 2 * y + 1;
			else
			{
				x--;
				decision += 2 * (y - x) + 1;
			}
		}
		count++;
	}
}

void	win_drawcircle_wo_antialiasing_clean(t_win_glfw *win, t_pixel centre, int radius, int color)
{
    int x;
    int y;
    int decision;

	x = radius;
	y = 0;
	decision = 1 - radius;

	while (y <= x)
	{
		win->set_pixel(win, x + centre.x, y + centre.y, color);
		win->set_pixel(win, -x + centre.x, y + centre.y, color);
		win->set_pixel(win, x + centre.x, -y + centre.y, color);
		win->set_pixel(win, -x + centre.x, -y + centre.y, color);
		win->set_pixel(win, y + centre.x, x + centre.y, color);
		win->set_pixel(win, -y + centre.x, x + centre.y, color);
		win->set_pixel(win, y + centre.x, -x + centre.y, color);
		win->set_pixel(win, -y + centre.x, -x + centre.y, color);
		y++;
		if (decision <= 0)
			decision += 2 * y + 1;
		else
		{
			x--;
			decision += 2 * (y - x) + 1;
		}
	}
}

//chatgpt xiaolin_wu circle

//(t_win_glfw *win, t_pixel centre, int radius, int color)



void	flood_fill(t_win_glfw *win, int x, int y, int color)
{
	if (win->get_pixel(win, x, y) != 0)
		return ;
	win->set_pixel(win, x, y, color);
	flood_fill(win, x + 1, y, color);
	flood_fill(win, x, y + 1, color);
	flood_fill(win, x - 1, y, color);
	flood_fill(win, x, y - 1, color);
}

# define RGB_R(rgba) ((rgba >> 16) & 0xff)
# define RGB_G(rgba) ((rgba >> 8) & 0xff)
# define RGB_B(rgba) ((rgba) & 0xff)
# define RGB_A(rgba) ((rgba >> 24) & 0xff)

// gamma correction instead of linear average of pixels when antialiasing



// turn these into hash tables...? the inverse pow becoming 2 sqrrts.....

//quake fast inverse square root of doom
float quake_fast_inverse_sqr_root(float number)
{
  long i;
  float x2, y;
  const float threehalfs = 1.5F;

  x2 = number * 0.5F;
  y  = number;
  i  = * ( long * ) &y;                       // evil floating point bit level hacking
  i  = 0x5f3759df - ( i >> 1 );               // what the fuck?
  y  = * ( float * ) &i;
  y  = y * ( threehalfs - ( x2 * y * y ) );   // 1st iteration
  // y  = y * ( threehalfs - ( x2 * y * y ) );   // 2nd iteration, this can be removed

  return (y);
}

//https://stackoverflow.com/questions/48903716/fast-image-gamma-correction
// replace pow(float x, float 2.2f) with this
//it is a polinomial aproximation for the function x^2.2 when 0 < x < 1
// function is simetrical around the function y = x

float gamma22_pow(float x)
{
	return (0.8 * x * x + 0.2 * x * x * x);
}


//https://mimosa-pudica.net/fast-gamma/
// polynomial aproximation for inversegamma
// using quake fast inverse square root for values between 0 and 1 (this case)

float inverse_gamma22_pow(float x)
{
	return ((1.138 * quake_fast_inverse_sqr_root(x) - 0.138) * x);
}

int gamma_average(int start, int end, int num, int den)
{
    // Compute weighted average in sRGB color space
    float circleWeight = (float)num / (float)den;
    float squareWeight = 1.0f - circleWeight;

    // Apply gamma correction to linear RGB values
    //float gamma = 2.2f;
    //float invGamma = 1.0f / gamma;

    float blendedRed = inverse_gamma22_pow(gamma22_pow(RGB_R(start) / 255.0f) * circleWeight + gamma22_pow(RGB_R(end) / 255.0f) * squareWeight);
    float blendedGreen = inverse_gamma22_pow(gamma22_pow(RGB_G(start) / 255.0f) * circleWeight + gamma22_pow(RGB_G(end) / 255.0f) * squareWeight);
    float blendedBlue = inverse_gamma22_pow(gamma22_pow(RGB_B(start) / 255.0f) * circleWeight + gamma22_pow(RGB_B(end) / 255.0f) * squareWeight);

    // Convert back to integer values
    unsigned char blendedRedInt = (unsigned char)(blendedRed * 255.0f);
    unsigned char blendedGreenInt = (unsigned char)(blendedGreen * 255.0f);
    unsigned char blendedBlueInt = (unsigned char)(blendedBlue * 255.0f);

    // Set the pixel with the blended color
    return (RGBA(blendedRedInt, blendedGreenInt, blendedBlueInt, 255));
}

void setPixel4(t_win_glfw *win, int centreX, int centreY, int deltaX, int deltaY, int color, int num, int den, bool line)
{
    win->set_pixel(win, centreX + deltaX, centreY + deltaY, gamma_average(win->get_pixel(win, centreX + deltaX, centreY + deltaY), color, num, den));
    win->set_pixel(win, centreX - deltaX, centreY + deltaY, gamma_average(win->get_pixel(win, centreX - deltaX, centreY + deltaY), color, num, den));
	
    win->set_pixel(win, centreX + deltaX, centreY - deltaY, gamma_average(win->get_pixel(win, centreX + deltaX, centreY - deltaY), color, num, den));
    win->set_pixel(win, centreX - deltaX, centreY - deltaY, gamma_average(win->get_pixel(win, centreX - deltaX, centreY - deltaY), color, num, den));

	if (line)
	{
		draw_horizontal_line(win, centreX - deltaX, centreX + deltaX, centreY + deltaY, color);
		draw_horizontal_line(win, centreX - deltaX, centreX + deltaX, centreY - deltaY, color);
	}
}

void chatgpt_anticircle(t_win_glfw *win, t_pixel centre, int radius, int color)
{
	//win_full_circle(win, centre, radius, color);

	int centreX = centre.x;
	int centreY = centre.y;
    int radius2 = radius * radius;
    static const int maxTransparency = 127;

    // Upper and lower halves
    int quarter = round(radius2 / sqrt(radius2 + radius2));
    for (int x = 0; x <= quarter; x++) {
        float y = radius * sqrt(1 - x * x / (float)radius2);
        float error = y - (int)(y);
        int transparency = (int)(error * maxTransparency);

        setPixel4(win, centreX, centreY, x, (int)(y), color, transparency, maxTransparency, true);
		setPixel4(win, centreX, centreY, (int)(y), x, color, transparency, maxTransparency, true);
        setPixel4(win, centreX, centreY, x, (int)(y) + 1, color, (maxTransparency - transparency), maxTransparency, false);
		setPixel4(win, centreX, centreY, (int)(y) + 1, x, color, (maxTransparency - transparency), maxTransparency, false);
    }

   // for (int y = 0; y <= quarter; y++) {
   //     float x = radius * sqrt(1 - y * y / (float)radius2);
   //     float error = x - (int)(x);
   //     int transparency = (int)(error * maxTransparency);
//
	//	int alpha = avg_colour(0, color, transparency, maxTransparency);
	//	int alpha2 = avg_colour(0, color, (maxTransparency - transparency), maxTransparency);
//
   //     //setPixel4(win, centreX, centreY, (int)(x), y, color, alpha, true);
   //     //setPixel4(win, centreX, centreY, (int)(x) + 1, y, color, alpha2, false);
   // }
	//flood_fill(win, centre.x, centre.y + radius - 1, color);
}
