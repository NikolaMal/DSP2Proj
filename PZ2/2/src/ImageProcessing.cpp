
#include "ImageProcessing.h"
#include "ImageInterpolation.h"

#include <QDebug>

void imageProcessingFun(const QString& progName, QImage* const outImgs, const QImage* const inImgs, const QVector<double>& params) 
{
	int X_SIZE = inImgs->width();
	int Y_SIZE = inImgs->height();

	/* NOTE: Calculate output image resolution and construct output image object */

	if(progName == "Sample and hold") 
	{	
		/* Input image data in RGB format can be obtained with inImgs->bits() */
		/* Vertical scale factor is params[0] */
		/* Horizontal scale factor is params[1] */
		int Y_NEW_SIZE = (int)(params[0] * Y_SIZE) - (int)(Y_SIZE*params[0]) % 4;
		int X_NEW_SIZE = (int)(params[1] * X_SIZE) - (int)(X_SIZE*params[0]) % 4;
		new(outImgs) QImage(X_NEW_SIZE, Y_NEW_SIZE, inImgs->format());
		sampleAndHold(inImgs->bits(), X_SIZE, Y_SIZE, outImgs->bits(), X_NEW_SIZE, Y_NEW_SIZE);

		/* TO DO: Calculate output image resolution and construct output image object */

		/* TO DO: Perform Sample and hold interpolation  */


	}
	else if (progName == "Bilinear") 
	{
		/* Input image data in RGB format can be obtained with inImgs->bits() */
		/* Vertical scale factor is params[0] */
		/* Horizontal scale factor is params[1] */

		int Y_NEW_SIZE = (int)(params[0] * Y_SIZE) - (int)(Y_SIZE*params[0]) % 4;
		int X_NEW_SIZE = (int)(params[1] * X_SIZE) - (int)(X_SIZE*params[0]) % 4;
		new(outImgs) QImage(X_NEW_SIZE, Y_NEW_SIZE, inImgs->format());
		bilinearInterpolate(inImgs->bits(), X_SIZE, Y_SIZE, outImgs->bits(), X_NEW_SIZE, Y_NEW_SIZE);


		/* TO DO: Calculate output image resolution and construct output image object */

		/* TO DO: Perform Bilinear interpolation  */
	}
	else if(progName == "Swirl") 
	{	
		/* Input image data in RGB format can be obtained with inImgs->bits() */
		/* k1 factor is params[0]*/
		/* Center of rotation coordinates are (XSIZE/2, YSIZE/2) */

		/* TO DO: Construct output image object */

		/* TO DO: Perform image rotation */
	
	}
	else if (progName == "Swirl Bilinear") 
	{
		/* Input image data in RGB format can be obtained with inImgs->bits() */
		/* k1 factor is params[0]*/
		/* Center of rotation coordinates are (XSIZE/2, YSIZE/2) */

		/* TO DO: Construct output image object */

		/* TO DO: Perform image rotation with bilinear interpolation */
	}

}

