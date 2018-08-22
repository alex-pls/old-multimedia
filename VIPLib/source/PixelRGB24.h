/** @file PixelRGB24.h
 *
 * File containing declarations for the 'PixelRGB24' class.
 *
 * Class to store color pixel data: 3 channels: Red, Green, Blue.
 *
 * Currently they are 3 char -> 3*8bits = 24bits
 *
 *
 * @see vipFilter
 *
 *
 ****************************************************************************
 * VIPLib Framework
 *  open source, founded by Alessandro Polo 2006
 *  http://mmlab.disi.unitn.it/projects/VIPLib
 *
 *  maintained by MultiMedia Laboratory - DISI - University of Trento
 *
 ****************************************************************************/


#ifndef PIXEL_RGB24_H
#define PIXEL_RGB24_H
class PixelRGB24;
//#include "PixelRGB32.h"
#include <iostream>

using namespace std;

class PixelRGB24
/**
 * A Single pixel consisting of red, green and blue fields
 *
 * The pixel is stored as an array of three ints which can be access as
 * seperate colour fields using the FieldSelector enum in the ImageRGB24
 * class.
 */
{
	/**
	 * Outputs a pixel to the output stream
	 *
	 * This overlaoded operator inserts a representation of the
	 * pixel into the output stream (os) in the form '(r,g,b)'
	 * where r, g, b are the red, green and blue fields respectively.
	 *
	 * @param os The output stream.
	 * @param p  The pixel to output.
	 *
	 * @return A reference to the output stream for chained calls.
	 */
	friend ostream& operator << (ostream& os, PixelRGB24& p)
	{
		os << "(" << p[0] << "," << p[1] << "," << p[2] << ")";
		return os;
	}

protected:
	unsigned char pixel[3];	///< The pixels data as an array of uchar (0-255)


public:

	//unsigned char pixel[3];	///< The pixels data as an array of uchar (0-255)
	/**
	 * The default constructor.
	 *
	 * This zero's the values of the red, green and blue colour fields.
	 */
	PixelRGB24()
	 { pixel[0] = pixel[1] = pixel[2] = 0; }


	/**
	 * Create a pixel with the specified values.
	 *
	 * This constructor creates a new pixel with the red, green and
	 * blue values specified as arguments.
	 */
	PixelRGB24(unsigned char red, unsigned char green, unsigned char blue)
	{
		pixel[0] = red;
		pixel[1] = green;
		pixel[2] = blue;
	}


	/**
	 * Overloaded assignment operator.
	 *
	 * Assign the values of the pixel specified to the fields
	 * of this pixel.
	 *
	 * @param p The pixel to assign the values from.
	 *
	 * @return A reference to this object.
	 */
	PixelRGB24& operator = (PixelRGB24& p)
	{
		pixel[0] = p[0];
		pixel[1] = p[1];
		pixel[2] = p[2];

		return *this;
	}


	/**
	 * Overloaded array operator.
	 *
	 * This operator allows easy access to the data of the pixel as
	 * if you were refering to the data directly.
	 *
	 * @param i The index of the field to return.
	 *
	 * @return The value of the field.
	 */
	unsigned char& operator [] (int i)
	{
		return pixel[i];
	}

	/**
	 * Overloaded array operator.
	 *
	 * This operator allows easy access to the data of the pixel as
	 * if you were refering to the data directly.
	 *
	 * @param i The index of the field to return.
	 *
	 * @return The value of the field.
	 */
	const unsigned char& operator [] (int i) const
	{
		return pixel[i];
	}

	/**
	 * Overloaded Cast operator.
	 *
	 * This operator allows the pixel to be easily cast to an int
	 * pointer. Since the pixel data is just an array of ints, this
	 * operator allows the pixel to be treated as such.
	 */
	operator unsigned char* ()
	{
		return (unsigned char*) pixel;
	}

	/**
	 * Overloaded equality operator.
	 *
	 * This tests whether this pixel and the one specified are equal
	 * i.e. have the same values for all fields.
	 *
	 * @param p The pixel to test equality with.
	 *
	 * @return true  - if pixels are equal.
	 *         false - if pixels differ in any fields.
	 */
	bool operator == (PixelRGB24& p)
	{
		return (   pixel[0] == p.pixel[0]
			&& pixel[1] == p.pixel[1]
			&& pixel[2] == p.pixel[2]);
	}


	/**
	 * Overloaded test for none equality
	 *
	 * This tests whether the pixel and the one specified are not
	 * equal i.e. they have at least one field in which their values
	 * differ.
	 *
	 * @param p The pixel to test none-equality with.
	 *
	 * @return true  - if pixels are different
	 *         false - if all fields are the same.
	 */
	bool operator != (PixelRGB24& p)
	{
		return (   pixel[0] != p.pixel[0]
			|| pixel[1] != p.pixel[1]
			|| pixel[2] != p.pixel[2]);
	}

        /**
         * Overloaded addition operator.
         *
         * Add the values of the pixel specified to the fields
         * of this pixel. Note NO checking that values are within
         * range 0-255 is done.
         *
         * @param p The pixel to add the values from.
         *
         * @return A reference to this object.
         */
        PixelRGB24& operator += (PixelRGB24& p)
        {
                pixel[0] += p[0];
                pixel[1] += p[1];
                pixel[2] += p[2];

                return *this;
        }

        /**
         * Overloaded subtraction(difference) operator.
         *
         * Assign the difference of the values of the pixel specified
         * and this pixel to the fields of this pixel.
         *
         * @param p The pixel to difference the values with.
         *
         * @return A reference to this object.
         */
        PixelRGB24& operator -= (PixelRGB24& p)
        {
                pixel[0] -= p[0];
                pixel[1] -= p[1];
                pixel[2] -= p[2];

                return *this;
        }

        /**
         * Overloaded multiplication operator.
         *
         * Multiply the fields of this pixel by a scalar value.
         *
         * @param k The scalar to multiply by.
         *
         * @return A reference to this object.
         */
        PixelRGB24& operator *= (double k)
        {
                pixel[0] = (int) (k*(double)pixel[0]);
                pixel[1] = (int) (k*(double)pixel[1]);
                pixel[2] = (int) (k*(double)pixel[2]);

                return *this;
        }

        PixelRGB24& operator *= (PixelRGB24& p)
        {
                pixel[0] *= p[0];
                pixel[1] *= p[1];
                pixel[2] *= p[2];

                return *this;
        }

        PixelRGB24& operator /= (PixelRGB24& p)
        {
                pixel[0] /= p[0];
                pixel[1] /= p[1];
                pixel[2] /= p[2];

                return *this;
        }

};


#endif	// PIXEL_RGB24_H
