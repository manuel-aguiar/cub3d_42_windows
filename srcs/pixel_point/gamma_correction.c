/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gamma_correction.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 19:10:14 by marvin            #+#    #+#             */
/*   Updated: 2024/01/26 19:10:14 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "pixel_point.h"

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

float gamma22_pow(float x)
{
	return (0.8 * x * x + 0.2 * x * x * x);
}


//https://mimosa-pudica.net/fast-gamma/
// polynomial aproximation for inversegamma. x ^ (1.0 / 2.2f)
// using quake fast inverse square root for values between 0 and 1 (this case)
// symetrical to x ^ 2.2f around y = x;
// 0.8 * x ^ 1 / 2 + 0.2 * x ^ 1 / 3
// equally bad, one square root and on cube root
// (1.138 / x ^ 0.5 - 0.138) * x, good aprox and gets rid of the cube root

float inverse_gamma22_pow(float x)
{
	return ((1.138f * quake_fast_inverse_sqr_root(x) - 0.138f) * x);
}

int gamma_average(int start, int end, int num, int den)
{
    // Compute weighted average in sRGB color space
    float circleWeight = (float)num / (float)den;
    float squareWeight = 1.0f - circleWeight;

    // Apply gamma correction to linear RGB values
    //float gamma = 2.2f;
    //float invGamma = 1.0f / gamma;

    float blendedRed = inverse_gamma22_pow(gamma22_pow(rgb_r(start) / 255.0f) * circleWeight + gamma22_pow(rgb_r(end) / 255.0f) * squareWeight);
    float blendedGreen = inverse_gamma22_pow(gamma22_pow(rgb_g(start) / 255.0f) * circleWeight + gamma22_pow(rgb_g(end) / 255.0f) * squareWeight);
    float blendedBlue = inverse_gamma22_pow(gamma22_pow(rgb_b(start) / 255.0f) * circleWeight + gamma22_pow(rgb_b(end) / 255.0f) * squareWeight);

    // Convert back to integer values
    unsigned char blendedRedInt = (unsigned char)(blendedRed * 255.0f);
    unsigned char blendedGreenInt = (unsigned char)(blendedGreen * 255.0f);
    unsigned char blendedBlueInt = (unsigned char)(blendedBlue * 255.0f);

    // Set the pixel with the blended color
    return (rgba(blendedRedInt, blendedGreenInt, blendedBlueInt, 255));
}
