#include "ImageInterpolation.h"
#include "ColorSpaces.h"
#include <math.h>


void sampleAndHold(const uchar input[], int xSize, int ySize, uchar output[], int newXSize, int newYSize)
{
	
	/* TO DO */
	
	double horizontal_scale = (double)xSize / newXSize;
	double vertical_scale = (double)ySize / newYSize;
	int i, j, m, n;

	for (i = 0; i < newXSize; i++) {
		for (j = 0; j < newYSize; j++) {
			m = horizontal_scale*i;
			n = vertical_scale*j;

			if (m >= xSize) m = xSize - 1;
			if (n >= ySize) n = ySize - 1;

			output[3*i+ 3 * j*newXSize] = input[3 * m+ 3 * n*xSize];
			output[3 * i+1+ 3 * j*newXSize] = input[3 * m+1+ 3 * n*xSize];
			output[3 * i+2+ 3 * j*newXSize] = input[3 * m+2+ 3 * n*xSize];
		}
	}
}

void bilinearInterpolate(const uchar input[], int xSize, int ySize, uchar output[], int newXSize, int newYSize)
{
	/* TO DO */
	double horizontal_scale = (double)xSize / newXSize;
	double vertical_scale = (double)ySize / newYSize;
	int i, j, m, n;
	double a, b;
	for (i = 0; i < newXSize; i++) {
		for (j = 0; j < newYSize; j++) {
			m = horizontal_scale*i;
			n = vertical_scale*j;
			a = vertical_scale*j - floor(vertical_scale*j);
			b = horizontal_scale*i - floor(horizontal_scale*i);

			output[3 * i + j * newXSize * 3] = (1 - a) * (1 - b) * input[3 * m + n * xSize * 3] + (1 - a) * b * input[3 * (m + 1) + n * xSize * 3] + a * (1 - b) * input[3 * m + (n + 1) * xSize * 3] + a * b * input[3 * (m + 1) + (n + 1) * xSize * 3];
			output[3 * i + 1 + j * newXSize * 3] =(1 - a) * (1 - b) * input[3 * m + 1 + n * xSize * 3] +(1 - a) * b * input[3 * (m + 1) + 1 + n * xSize * 3] +a * (1 - b) * input[3 * m + 1 + (n + 1) * xSize * 3] +a * b * input[3 * (m + 1) + 1 + (n + 1) * xSize * 3];
			output[3 * i + 2 + j * newXSize * 3] =(1 - a) * (1 - b) * input[3 * m + 2 + n * xSize * 3] +(1 - a) * b * input[3 * (m + 1) + 2 + n * xSize * 3] +a * (1 - b) * input[3 * m + 2 + (n + 1) * xSize * 3] +a * b * input[3 * (m + 1) + 2 + (n + 1) * xSize * 3];

		}
	}
	
}


void bicubicInterpolate(const uchar input[], int xSize, int ySize, uchar output[], int newXSize, int newYSize)
{
	/* TO DO */
	 double horizontal_scale = (double)xSize / newXSize;
	 double vertical_scale = (double)ySize / newYSize;

	int m, n;
	double vertical_distance, horizontal_distance;

	for (int i = 0; i < newYSize; i++)
	{
		for (int j = 0; j < newXSize; j++)
		{
			m = round(i * vertical_scale);
			n = round(j * horizontal_scale);

			uchar red_vertical[4] = { 0 };
			uchar green_vertical[4] = {0 };
			uchar blue_vertical[4] = { 0};

			vertical_distance = 0;

			for (int p = -2; p < 2; p++)
			{
				if (p == -2) { 
					vertical_distance = abs(i * vertical_scale - (m + p)); 
				}

				uchar red_horizontal[4] = { 0 };
				uchar green_horizontal[4] = { 0 };
				uchar blue_horizontal[4] = { 0};

				horizontal_distance = 0;

				for (int q = -2; q < 2; q++)
				{
					if (q == -2) { 
						horizontal_distance = abs(j * horizontal_scale - (n + q)); 
					}

					if (m + p >= 0 && m + p < ySize && n + q >= 0 && n + q < xSize)
					{
						red_horizontal[q + 2] = input[3 * (m + p) * xSize + 3 * (n + q)];
						green_horizontal[q + 2] = input[3 * (m + p) * xSize + 3 * (n + q) + 1];
						blue_horizontal[q + 2] = input[3 * (m + p) * xSize + 3 * (n + q) + 2];
					}
					else
					{
						red_horizontal[q + 2] = 0;
						green_horizontal[q + 2] = 0;
						blue_horizontal[q + 2] = 0;
					}
				}

				red_vertical[p + 2] = cubicInterpolate(red_horizontal, horizontal_distance);
				green_vertical[p + 2] = cubicInterpolate(green_horizontal, horizontal_distance);
				blue_vertical[p + 2] = cubicInterpolate(blue_horizontal, horizontal_distance);
			}

			output[3 * i * newXSize + 3 * j] = cubicInterpolate(red_vertical, vertical_distance);
			output[3 * i * newXSize + 3 * j + 1] = cubicInterpolate(green_vertical, vertical_distance);
			output[3 * i * newXSize + 3 * j + 2] = cubicInterpolate(blue_vertical, vertical_distance);
		}
	}
}

void imageSwirl(const uchar input[], int xSize, int ySize, uchar output[], int m, int n, double k1)
{
	/* TO DO */
	int i, j, p, q;
	double dist_i, dist_j, radius, angle;
	for (i = 0; i < xSize; i++) {
		for (j = 0; j < ySize; j++) {
			dist_i = i - m;
			dist_j = j - n;
			radius = sqrt(pow(dist_i, 2) + pow(dist_j, 2));
			angle = PI*radius*k1;
			p = dist_i*cos(angle) - sin(angle)*dist_j + m;
			q = dist_i*sin(angle) + cos(angle)*dist_j + n;

			if (p >= 0 && q >= 0 && p < xSize && q < ySize) {
				output[3 * i + 3 * j*xSize] = input[3 * p + 3 * q*xSize];
				output[3 * i+1 + 3 * j*xSize] = input[3 * p+1 + 3 * q*xSize];
				output[3 * i+2 + 3 * j*xSize] = input[3 * p +2+ 3 * q*xSize];
			}
			else {
				output[3 * i + 3 * j*xSize] = 0;
				output[3 * i + 1 + 3 * j*xSize] = 0;
				output[3 * i + 2 + 3 * j*xSize] = 0;
			}
		}
	}
	

}

void imageSwirlBilinear(const uchar input[], int xSize, int ySize, uchar output[], int m, int n, double k1)
{
	/* TO DO */
	int i, j, p, q;
	double dist_i, dist_j, radius, angle, k, l,a , b;
	for (i = 0; i < xSize; i++) {
		for (j = 0; j < ySize; j++) {
			dist_i = i - m;
			dist_j = j - n;
			radius = sqrt(pow(dist_i, 2) + pow(dist_j, 2));
			angle = PI*radius*k1;
			k= dist_i*cos(angle) - sin(angle)*dist_j + m;
			l= dist_i*sin(angle) + cos(angle)*dist_j + n;

			p = floor(k);
			q = floor(l);
			a = l - q;
			b = k - p;

			if (p >= 0 && q >= 0 && p < xSize && q < ySize) {
				output[3 * i + j * xSize * 3] =(1 - a) * (1 - b) * input[3 * p + q * xSize * 3] +(1 - a) * b * input[3 * (p + 1) + q * xSize * 3] +a * (1 - b) * input[3 * p + (q + 1) * xSize * 3] +a * b * input[3 * (p + 1) + (q + 1) * xSize * 3];
				output[3 * i + 1 + j * xSize * 3] =(1 - a) * (1 - b) * input[3 * p + 1 + q * xSize * 3] +(1 - a) * b * input[3 * (p + 1) + 1 + q * xSize * 3] +a * (1 - b) * input[3 * p + 1 + (q + 1) * xSize * 3] +a * b * input[3 * (p + 1) + 1 + (q + 1) * xSize * 3];
				output[3 * i + 2 + j * xSize * 3] =(1 - a) * (1 - b) * input[3 * p + 2 + q * xSize * 3] +(1 - a) * b * input[3 * (p + 1) + 2 + q * xSize * 3] +a * (1 - b) * input[3 * p + 2 + (q + 1) * xSize * 3] +a * b * input[3 * (p + 1) + 2 + (q + 1) * xSize * 3];
			}
			else {
				output[3 * i + 3 * j*xSize] = 0;
				output[3 * i + 1 + 3 * j*xSize] = 0;
				output[3 * i + 2 + 3 * j*xSize] = 0;
			}

		}
	}
}

double w(double dist)
{
	if (fabs(dist) < 1)
	{
		return 1.5 * pow(fabs(dist), 3) - 2.5 * pow(fabs(dist), 2) + 1;
	}
	else if (fabs(dist) >= 1 && fabs(dist) < 2)
	{
		return -0.5 * pow(fabs(dist), 3) + 2.5 * pow(fabs(dist), 2) - 4 * fabs(dist) + 2;
	}
	else
	{
		return 0.0;
	}
}

double cubicInterpolate(uchar pixels[4], double dist)
{
	double new_dist;
	int output = 0;

	for (int i = 0; i < 4; i++)
	{
		new_dist = dist - i;
		output += pixels[i] * w(new_dist);
	}

	if (output > 255)
	{
		return 255;
	}
	else if (output < 0)
	{
		return 0;
	}
	else {
		return output;
	}
}