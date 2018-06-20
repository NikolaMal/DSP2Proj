
#ifndef IMAGEINTERPOLATION_H_
#define IMAGEINTERPOLATION_H_

#include <QString>
#include <QVector>
#include <QImage>

#define PI 3.141592653

void sampleAndHold(const uchar input[], int xSize, int ySize, uchar output[], int newXSize, int newYSize);

void bilinearInterpolate(const uchar input[], int xSize, int ySize, uchar output[], int newXSize, int newYSize);

void bicubicInterpolate(const uchar input[], int xSize, int ySize, uchar output[], int newXSize, int newYSize);

void imageSwirl(const uchar input[], int xSize, int ySize, uchar output[], int m, int n, double angle);

void imageSwirlBilinear(const uchar input[], int xSize, int ySize, uchar output[], int m, int n, double angle);

double w(double dist);

double cubicInterpolate(uchar pixels[4], double dist);

#endif // IMAGEINTERPOLATION_H_
