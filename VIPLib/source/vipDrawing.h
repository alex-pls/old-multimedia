/*
*	Drawing component draft
*		by MV
*	- no subpixel support
*	- no subsampled planes support (yuv444/hsv/rgb supported, no yuv4:2:0 etc.)
*	- not buffer-safe
*	- no error checking
*	- use with common sense
*/

#ifndef _VIP_DRAWING_H
#define _VIP_DRAWING_H

class vipDrawingTool
{
	// Members
private:
	unsigned char	*p1;		// Pointer to output plane 1 (Y, usually; H for HSV, etc.). MEMORY NOT HANDLED HERE! JUST REFERENCED!
	unsigned char	*p2;		// Pointer to output plane 2 (U for yuv, S for HSV, etc.)
	unsigned char	*p3;		// Pointer to output plane 3 (V for yuv, V for HSV, etc.)
	unsigned int	img_w;		// Output frame width. Setting this incorrectly will cause memory access exceptions.
	unsigned int	img_h;		// Output frame height. Setting this incorrectly will cause memory access exceptions.
	unsigned int	brushSize;	// Size of "brush" side (use odd numbers! no subpixel support)
	unsigned char	brushClr1;	// Brush color component 1 (for plane1)
	unsigned char	brushClr2;	// Brush color component 1 (for plane1)
	unsigned char	brushClr3;	// Brush color component 1 (for plane1)

	// Default constructor and destructor
public:
	vipDrawingTool()
	{
		p1 = NULL;
		p2 = NULL;
		p3 = NULL;
		img_w = 0;
		img_h = 0;
		brushClr1 = 0;
		brushClr2 = 0;
		brushClr3 = 0;
		brushSize = 0;
	}
	~vipDrawingTool() {}	// nothing! planes' buffers are obviously not to be deleted. they're output buffers

	// Member access methods
public:
	void setOutputPlanes( unsigned char *ptrPlane1, unsigned char *ptrPlane2, unsigned char *ptrPlane3, unsigned int planeWidth, unsigned int planeHeight )
		{ p1=ptrPlane1; p2=ptrPlane2; p3=ptrPlane3; img_w=planeWidth; img_h=planeHeight; }

	void setBrushSize( unsigned int sidePixels )
	{ brushSize=(sidePixels%2==0)?(sidePixels+1):(sidePixels); }	// we want non-zero odd number here.

	void setBrushColor( unsigned char colorComp1, unsigned char colorComp2, unsigned char colorComp3 )
		{ brushClr1=colorComp1; brushClr2=colorComp2; brushClr3=colorComp3; }

	void setBrushSizeAndColor( unsigned int sizePixels, unsigned char colorComp1, unsigned char colorComp2, unsigned char colorComp3 )
	{
		setBrushSize( sizePixels );
		setBrushColor( colorComp1, colorComp2, colorComp3 );
	}

	// Private (internal) helper methods
private:
	inline bool writePix( unsigned int x, unsigned int y )
	{
		if( !isInBounds(x,y) )
			return false;
		p1[ y*img_w + x ] = brushClr1;
		p2[ y*img_w + x ] = brushClr2;
		p3[ y*img_w + x ] = brushClr3;
		return true;
	}
	inline bool isInBounds( unsigned int x, unsigned int y )
		{ return !( x<0 || y<0 || x>=img_w || y>= img_h ); }

	// Public drawing methods
public:
	inline unsigned int drawDot( unsigned int x, unsigned int y )
	{
		unsigned int retCount = 0;
		unsigned int delta = (brushSize>1) ? (brushSize-1)/2 : 0;
		// Cycle nearby pixels
		unsigned int wleft = (delta>x) ? 0 : (x-delta);	// w starting point, to avoid unsigned underflow
		unsigned int htop = (delta>y) ? 0 : (y-delta);	// h starting point, to avoid unsigned underflow
		for( unsigned int w=wleft; w<=x+delta; w++ )
		{
			for( unsigned int h=htop; h<=y+delta; h++ )
			{ // and try to write there
				retCount += writePix(w,h);
			}
		}
		return retCount;
	}
	inline unsigned int drawLine( unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2 )
	{ // note : highly computationally inefficient. 
		unsigned int retCount = 0;
		unsigned int xmin = (x1<x2) ? x1 : x2;
		unsigned int xmax = (x1<x2) ? x2 : x1;
		unsigned int ymin = (y1<y2) ? y1 : y2;
		unsigned int ymax = (y1<y2) ? y2 : y1;
		unsigned int delta = (brushSize>1) ? (brushSize-1)/2 : 1;
		bool zerodivx, zerodivy, ind_y, ind_x;
		float err, yratio, xratio;
		float errThres = 0.01;
		for( unsigned int x=xmin; x<=xmax; x++ )	// restrict check area to min/max boundaries area
		{
			for( unsigned int y=ymin; y<=ymax; y++ )
			{
				// check equation
				zerodivy = ( ((float)y2)-((float)y1) == 0 ) ? true : false;		// handle some divide by 0 stuff
				zerodivx = ( ((float)x2)-((float)x1) == 0 ) ? true : false;
				ind_y = ( zerodivy && (((float)y)-((float)y1) ==0) ) ? true : false; // handle some 0/0 stuff
				ind_x = ( zerodivx && (((float)x)-((float)x1) ==0) ) ? true : false;
				yratio = ( ((float)y)-((float)y1) ) / ( ((float)y2)-((float)y1) ) ;
				xratio = ( ((float)x)-((float)x1) ) / ( ((float)x2)-((float)x1) ) ;
				if( (zerodivy&&zerodivx) || (ind_y) || (ind_x) )
					err = 0;
				else
					err = yratio - xratio;
				if( abs(err) <= errThres )
					retCount+=drawDot(x,y);
			}
		}
		return retCount;
	}

};



#endif // _VIP_DRAWING_H