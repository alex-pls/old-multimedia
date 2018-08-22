/** @file PixelHSV.h
 *
 * File containing declarations for the 'PixelHSV' class.
 *
 * Class to store color pixel data: 3 channels: Hue, Sat, Val.
 *
 * Currently they are 3 int -> 3*32bits = 96bits
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


#ifndef PIXEL_HSV_H
#define PIXEL_HSV_H

#include <iostream>

using namespace std;

class PixelHSV
/**
 * A Single pixel consisting of Hue, Sat and Val fields
 *
 * The pixel is stored as an array of three ints which can be access as
 * seperate colour fields using the FieldSelector enum in the ImageHSV
 * class.
 */
{
	/**
	 * Outputs a pixel to the output stream
	 *
	 * This overlaoded operator inserts a representation of the
	 * pixel into the output stream (os) in the form '(h,s,v)'
	 * where h, s, v are the Hue, Sat and Val fields respectively.
	 *
	 * @param os The output stream.
	 * @param p  The pixel to output.
	 *
	 * @return A reference to the output stream for chained calls.
	 */
//	friend ostream& operator << (ostream& os, PixelHSV& p)
//	{
//		os << "(" << p[0] << "," << p[1] << "," << p[2] << ")";
//		return os;
//	}

public:
	 unsigned short int hue;	//16bit	|
	 unsigned char sat;			//8bit	|> 32bit
	 unsigned char val;			//8bit	|

public:
	/**
	 * The default constructor.
	 *
	 * This zero's the values of the Hue, Sat and Val colour fields.
	 */
	PixelHSV()
	 {  }


	/**
	 * Create a pixel with the specified values.
	 *
	 * This constructor creates a new pixel with the Hue, Sat and Val
	 * values specified as arguments.
	 */
	PixelHSV(unsigned short int h, unsigned char s, unsigned char v)
	{
		hue = h;
		sat = s;
		val = v;
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
	PixelHSV& operator = (PixelHSV& p)
	{
		hue = p.hue;
		sat = p.sat;
		val = p.val;

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
//	int& operator [] (int i)
//	{
//		return pixel[i];
//	}


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
//	const int& operator [] (int i) const
//	{
//		return pixel[i];
//	}


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
	bool operator == (PixelHSV& p)
	{
		return (   hue == p.hue
			&& sat == p.sat
			&& val == p.val);
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
	bool operator != (PixelHSV& p)
	{
		return (   hue != p.hue
			|| sat != p.sat
			|| val != p.val);
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
        PixelHSV& operator += (PixelHSV& p)
        {
                hue += p.hue;
                sat += p.sat;
                val += p.val;

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
        PixelHSV& operator -= (PixelHSV& p)
        {
				hue -= p.hue;
                sat -= p.sat;
                val -= p.val;

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
        PixelHSV& operator *= (double k)
        {
                hue = (int) (k*(double)hue);
                sat = (int) (k*(double)sat);
                val = (int) (k*(double)val);

                return *this;
        }


        PixelHSV& operator *= (PixelHSV& p)
        {
                hue *= p.hue;
                sat *= p.sat;
                val *= p.val;

                return *this;
        }

        PixelHSV& operator /= (PixelHSV& p)
        {
                hue /= p.hue;
                sat /= p.sat;
                val /= p.val;

                return *this;
        }

};


#endif	// PIXEL_HSV_H
