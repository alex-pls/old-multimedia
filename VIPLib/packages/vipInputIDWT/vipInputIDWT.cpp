/** @file vipInputIDWT.cpp
 *
 * File containing methods for the 'vipInputIDWT' class.
 * The header for this class can be found in vipInputIDWT.h, check that file
 * for class description.
 *
 *
 ****************************************************************************
 *  Class based on Package Studio template: vipInputTemplate version 0.9.12
 ****************************************************************************
 * VIPLib Framework
 *  open source, founded by Alessandro Polo 2006
 *  http://mmlab.science.unitn.it/projects/VIPLib
 *
 *  maintained by MultiMedia Laboratory - DIT - University of Trento
 *
 ****************************************************************************/



#include "vipInputIDWT.h"

#include "../../source/vipUtility.h"
#include "../../source/codecs/vipCodec_BMP.h"
#include "../../source/math/vipMatrix.h"
#include "../vipOutputDWT/vipOutputDWT.h"
#include <math.h>


/**
 * @brief  Default constructor, frame rate
 *         is managed by vipInput class.
 *
 * @param[in] fps frame rate, default is 0: max possible
 */
vipInputIDWT::vipInputIDWT(float fps) : vipInput(fps)
 {
	INFO("vipInputIDWT::vipInputIDWT(float fps) : vipInput(fps) [CONTRUCTOR]")


	reset();

 }


/**
 * @brief  Default destructor, disconnect device and delete buffer.
 */
vipInputIDWT::~vipInputIDWT()
 {

 }



/**
 * @brief  Reset variables.
 *
 * @return VIPRET_OK
 */
VIPRESULT vipInputIDWT::reset()
 {

	bgRGB[0] = VIPPFG_DEF_COLOR_R;
	bgRGB[1] = VIPPFG_DEF_COLOR_G;
	bgRGB[2] = VIPPFG_DEF_COLOR_B;


	return VIPRET_OK;
 }



/**
 * @brief  Get the state of current data source.
 *
 * @return true is there are no more frames to load, false else.
 */
 bool vipInputIDWT::EoF()
 {
	 return false;
 }


/**
 * @brief  Create/capture a new frame with current settings.
 *
 * @param[out] img VIPLib Cache Frame to store data.
 *
 * @return VIPRET_OK if everything is fine, VIPRET_PARAM_ERR if frame
 *		   is not valid.
 *
 * @note   Ouput operator (>>) call directly this function.
 * @see    operator >> (vipFrameYUV420&)
 */
VIPRESULT vipInputIDWT::extractTo(vipFrameYUV420& img)
 {
	INFO("int vipInputIDWT::extractTo(vipFrameYUV420& img) [pushing data]")

	if ( &img == NULL )
		return VIPRET_PARAM_ERR;


//TODO memcpy instead

	/*for (unsigned int i = 0; i < img.height * img.width; i++)
		img.data[i] = bgRGB;*/


	return VIPRET_NOT_IMPLEMENTED;
 }


/**
 * @brief  Create/capture a new frame with current settings.
 *
 * @param[out] img VIPLib Cache Frame to store data.
 *
 * @return VIPRET_OK if everything is fine, VIPRET_PARAM_ERR if frame
 *		   is not valid.
 *
 * @note   Ouput operator (>>) call directly this function.
 * @see    operator >> (vipFrameYUV444&)
 */

VIPRESULT vipInputIDWT::extractTo(vipFrameYUV444& img)
 {
	INFO("int vipInputIDWT::extractTo(vipFrameYUV444& img) [pushing data]")

	if ( &img == NULL )
		return VIPRET_PARAM_ERR;


//TODO memcpy instead

	//for (unsigned int i = 0; i < img.height * img.width; i++)
	//	img.data[i] = bgRGB;s


	return VIPRET_NOT_IMPLEMENTED;
 }



/**
 * @brief Set specified pixel 
 *
 * @param[in,out] rgb image to be changed
 * @param[in] c x coordinate
 * @param[in] r y coordinate
 * @param[in] px value to set
 */
void setPixel(vipMatrix<double>* rgb, int c, int r, double* px){

	for (int i=0; i<3; i++){
		rgb[i].setValue(c,r,px[i]);
	}
}



/**
 * @brief Get specified pixel 
 *
 * @param[in,out] rgb image to be changed
 * @param[in] c x coordinate
 * @param[in] r y coordinate
 * @param[in] px value to set 
 */
void getPixel(vipMatrix<double>* rgb, int c, int r, double* px){

	for (int i=0; i<3; i++){
		px[i]=rgb[i].getValue(c,r);
	}
}

/**
 * @brief Upsampling rows 
 *
 * @param[in] img image to be upsampled
 *
 * @return upsampled image
 */
vipMatrix<double>* rows_upsampling (vipMatrix<double>* img){

	vipMatrix<double>* res= new vipMatrix<double> [3];
	for (int c=0; c<3; c++){
		res[c].setDim((img->getColumnsCount()), img->getRowsCount()*2);
	}
	double p[3];
	double zero[3]= {0, 0, 0};
	for(int i=0; i<res->getColumnsCount(); i++){
		for(int k=0; k<res->getRowsCount(); k++){
			if (k % 2 == 0){
				setPixel(res, i, k, zero);
			}else{
				getPixel(img, i, (k-1)/2, p);
				setPixel(res, i, k, p);	
			}
		}
	}
	return res;

}



/**
 * @brief Upsampling columns 
 *
 * @param[in] img image to be upsampled
 *
 * @return upsampled image 
 */
vipMatrix<double>* columns_upsampling (vipMatrix<double>* img){

	vipMatrix<double>* res= new vipMatrix<double> [3];
	for (int c=0; c<3; c++){
		res[c].setDim((img->getColumnsCount()*2), img->getRowsCount());
	}
	double p[3];
	double zero[3]= {0, 0, 0};
	for(int i=0; i<res->getColumnsCount(); i++){
		for(int k=0; k<res->getRowsCount(); k++){
			if (i % 2 == 0){
				setPixel(res, i, k, zero);
			}else{
				getPixel(img, (i-1)/2, k, p);
				setPixel(res, i, k, p);	
			}
		}
	}
	return res;

}


/**
 * @brief Apply horizontally the filter to the specified pixel 
 * 
 * @param[in] img image to be filtered 
 * @param[in] dim_f filter dimension 
 * @param[in] f filter to be applied
 * @param[in] x x coordinate
 * @param[in] y y coordinate
 * @param[out] p filtered pixel  
 */
void pixel_horizontal_filter (vipMatrix<double>* img, int dim_f, double* f, int x, int y, double* p) {
	
	int i, k;
	double* tmp[3]; 
	tmp[0]=new double [dim_f]; // red
	tmp[1]=new double [dim_f]; // green
	tmp[2]=new double [dim_f]; // blue

	int half= dim_f/2;
	for(i= -half; i<= half; i++){
		if(x+i<0){       
			getPixel(img, abs(x+i), y, p);
		} else if(x+i>(img->getColumnsCount())-1){
			getPixel(img, (2*img->getColumnsCount())-(x+i)-2, y, p);
		}else {
			getPixel(img, x+i, y, p);
		}
		for (k=0; k<3; k++){ 
				tmp[k][i+half]= p[k]*f[i+half];
		}	 
	}
	

	double t;
	for(k=0; k<3; k++){
		t=0;
		for(i=0; i<dim_f; i++){
			t= t + tmp[k][i];
		}
		p[k]= t;
	}

	delete tmp[0];
	delete tmp[1];
	delete tmp[2];
} 



/**
 * @brief Apply horizontally the filter to the specified image
 *
 * @param[in] img image to be filtered
 * @param[in] dim_f filter dimension
 * @param[in] f filter to be applied (3/5 7/9)
 * 
 * @return filtered image
 */
vipMatrix<double>* img_horizontal_filter (vipMatrix<double>* img, int dim_f, double* f){

	double p[3];
	int i,k;
	vipMatrix<double>* res= new vipMatrix<double>[3];
	for(i=0;i<3; i++){
		res[i].setDim(img->getColumnsCount(), img->getRowsCount());
	}
	for(i=0; i<img->getColumnsCount(); i++){
		for(k=0; k<img->getRowsCount(); k++){
			pixel_horizontal_filter(img, dim_f, f, i, k, p);
			setPixel(res, i, k, p);	
		}
	}
	
return res;

}



/**
 * @brief Apply vertically the filter to the specified pixel 
 * 
 * @param[in] img image to be filtered 
 * @param[in] dim_f filter dimension 
 * @param[in] f filter to be applied
 * @param[in] x x coordinate
 * @param[in] y y coordinate
 * @param[out] p filtered pixel  
 */
void pixel_vertical_filter (vipMatrix<double>* img, int dim_f, double* f, int x, int y, double* p) {
	
	int i, k;
	double* tmp[3]; 
	tmp[0]=new double [dim_f]; // red
	tmp[1]=new double [dim_f]; // green
	tmp[2]=new double [dim_f]; // blue

	int half= dim_f/2;
	for(i= -half; i<= half; i++){
		if(y+i<0){       
			getPixel(img, x, abs(y+i), p);
		} else if(y+i>(img->getRowsCount())-1){
			getPixel(img, x, (2*img->getRowsCount())-(y+i)-2, p);
		}else {
			getPixel(img, x, y+i, p);
		}
		for (k=0; k<3; k++){ 
				tmp[k][i+half]= p[k]*f[i+half];
		}	 
	}
	
	double t;
	for(k=0; k<3; k++){
		t=0;
		for(i=0; i<dim_f; i++){
			t= t + tmp[k][i];
		}
		p[k]= t;
	}

	delete tmp[0];
	delete tmp[1];
	delete tmp[2];
} 



/**
 * @brief Apply vertically the filter to the specified image
 *
 * @param[in] img image to be filtered
 * @param[in] dim_f filter dimension
 * @param[in] f filter to be applied (3/5 7/9)
 * 
 * @return filtered image
 */
vipMatrix<double>* img_vertical_filter (vipMatrix<double>* img, int dim_f, double* f){

	double p[3];

	vipMatrix<double>* res= new vipMatrix<double>[3];
	for (int c=0; c<3; c++){
		res[c].setDim((img->getColumnsCount()), img->getRowsCount());
	}
	for(int i=0; i<img->getColumnsCount(); i++){
		for(int k=0; k<img->getRowsCount(); k++){
			pixel_vertical_filter(img, dim_f, f, i, k, p);
			setPixel(res, i, k,p);
		}
	}

return res;

}



/**
 * @brief Sum two matrixes pixel by pixel
 *
 * @param[in] img1 first image
 * @param[in] img2 second image
 * 
 * @return the sum between first and second image
 */
vipMatrix<double>* sum (vipMatrix<double>* img1, vipMatrix<double>* img2){
	
	vipMatrix<double>* somma= new vipMatrix<double> [3];
	for (int b=0; b<3; b++){
		somma[b].setDim(img1->getColumnsCount(), img1->getRowsCount());
	}

	double p[3];
	double p1[3];
	double p2[3];
	int c, r;
	for (c=0; c<img1->getColumnsCount(); c++){
		for (r=0; r<img1->getRowsCount();r++){
			getPixel(img1, c, r, p1);
			getPixel(img2, c, r, p2);
			p[0]=p1[0] + p2[0];
			p[1]=p1[1] + p2[1];
			p[2]=p1[2] + p2[2];
			setPixel(somma, c, r, p); 
		}
	}
	return somma;
}



/**
 * @brief divide image in four subimages: LL, HL, LH, HH
 *
 * @param[in] img image to be divided
 * @param[in] num_iter number of iterations
 * @param[in, out] result vector with the four images: LL, HL, LH, HH
 */
void divide(vipMatrix<double>* img, int num_iter, vipMatrix<double>* result[4]){
	
	int c, r;
	double p[3];

	unsigned int dim_res_w= (img->getColumnsCount()/pow((double)2, (double)num_iter));
	unsigned int dim_res_h= (img->getRowsCount()/pow((double)2, (double)num_iter));
	
	for (int w=0; w<4; w++){
		result[w]= new vipMatrix<double> [3];
		result[w][0].setDim(dim_res_w, dim_res_h);
		result[w][1].setDim(dim_res_w, dim_res_h);
		result[w][2].setDim(dim_res_w, dim_res_h);
	}

	for(c=0; c<dim_res_w; c++){
		for(r=0; r<dim_res_h; r++){
			getPixel(img, c, r, p);
			setPixel(result[0], c, r, p);
		}
	}

	for(c=dim_res_w; c<2*dim_res_w; c++){
		for(r=0; r<dim_res_h; r++){
			getPixel(img, c, r, p);
			setPixel(result[1], c-dim_res_w, r, p);
		}
	}

	for(c=0; c<dim_res_w; c++){
		for(r=dim_res_h; r<2*dim_res_h; r++){
			getPixel(img, c, r, p);
			setPixel(result[2], c, r-dim_res_h, p);
		}
	}

	for(c=dim_res_w; c<2*dim_res_w; c++){
		for(r=dim_res_h; r<2*dim_res_h; r++){
			getPixel(img, c, r, p);
			setPixel(result[3], c-dim_res_w, r-dim_res_h, p);
		}
	}

}



/**
 * @brief Copy an image in the up-left corner of the other one 
 *
 * @param[in, out] img image to be modified 
 * @param[in] ll image to be copied 
 */
void copy (vipMatrix<double>* img, vipMatrix<double>* ll){
	
	double p[3];
	for (int i=0; i<ll->getColumnsCount(); i++){
		for (int j=0; j<ll->getRowsCount(); j++){
			getPixel(ll, i, j, p);
			setPixel(img, i, j, p);
		}
	}
}



/**
 * @brief Convert a vipMatrix<double> to a vipFrameRGB24
 *
 * @param[in] img image to be converted to vipFrameRGB24 
 * 
 * @return converted image 
 */
vipFrameRGB24*  matrix_to_frame (vipMatrix<double>* img){

	double p[3];
	PixelRGB24 px;
	
	vipFrameRGB24* result= new vipFrameRGB24(img[0].getColumnsCount(), img[0].getRowsCount());
	for(int c=0; c<img[0].getColumnsCount(); c++){
		for(int r=0; r<img[0].getRowsCount(); r++){
			getPixel(img, c, r, p);
			for (int k=0; k<3;k++){
				if (p[k]>255){
					p[k]=255;
				}else if(p[k]<0){
					p[k]=0;
				}
				px[k]=p[k];
			}
			result->setPixel(c,r,px);
		}
	}
	return result;
}



/**
 * @brief Convert a vipFrameRGB24 to a vipMatrix<double>
 *
 * @param[in] img image to be converted to vipMatrix<double> 
 * 
 * @return converted image 
 */
vipMatrix<double>*  frame_to_matrix (vipFrameRGB24* img){

	PixelRGB24 px;
	double tmp;
	int i;

	vipMatrix<double>* result= new vipMatrix<double>[3];
	for (i=0; i<3; i++){
		result[i].setDim(img->width, img->height);
	}
	
	for(i=0; i<3; i++){
		for(int c=0; c<result[i].getColumnsCount(); c++){
			for(int r=0; r<result[i].getRowsCount(); r++){
				img->getPixel(c,r,px);
				tmp = px[i];
				result[i].setValue(c,r,tmp);
			}
		}
	}
return result;


}


/**
 * @brief Perform the antitransform of the input image
 *
 * @param[in, out] img image to be antitransformed 
 *
 * @return VIPRET_OK if everything is fine, VIPRET_PARAM_ERR if frame
 *		   is not valid.
 */
VIPRESULT vipInputIDWT::extractTo(vipFrameRGB24& img)
 {
	INFO("int vipInputIDWT::extractTo(vipFrameRGB24& img) [pushing data]")

if ( &img == NULL )
		return VIPRET_PARAM_ERR;

		double *low;
		int dim_low;
		double *height;
		int dim_height;

		if (filter == 0){ 
			low = new double[3];
			low[0]= 1./2; low[1]= 2./2; low[2]= 1./2; 
			dim_low=3;

			height = new double[5];
			height[0]= -1./8; height[1]= -2./8; height[2]= 6./8;
			height[3]= -2./8; height[4]= -1./8 ;
			dim_height= 5;

		} else {
			low = new double[7];
			low[0] = -0.09127176311424948; low[1] = -0.05754352622849957; low[2] = 0.5912717631142470;
			low[3] = 1.115087052456994; low[4] = 0.5912717631142470; low[5] = -0.05754352622849957;
			low[6] = -0.09127176311424948; 
			dim_low= 7;

			height= new double[9];
			height[0] = 0.02674875741080976; height[1] = 0.01686411844287495; 
			height[2] = -0.07822326652898785; height[3] = -0.2668641184428723;
			height[4] = 0.6029490182363579; height[5] = -0.2668641184428723;
			height[6] = -0.07822326652898785; height[7] = 0.01686411844287495;
			height[8] = 0.02674875741080976;
			dim_height= 9;
		}

	int g;

	vipMatrix<double>* rgb= new vipMatrix<double> [3]; //QUI DEVO CARICARE IL FILE DI TESTO CON I COEFF.
	rgb[0].loadFromFile("provaR.txt");
	rgb[1].loadFromFile("provaG.txt");
	rgb[2].loadFromFile("provaB.txt");

	
	
	vipMatrix<double>* img_divide[4];
	vipMatrix<double>* upsampled_rows[4];
	vipMatrix<double>* upsampled_rows_filter[4];
	vipMatrix<double>* first_sum[2];
	vipMatrix<double>* upsampled_columns[2];
	vipMatrix<double>* upsampled_columns_filter[2];
	vipMatrix<double>* second_sum;

	img.reAllocCanvas(rgb[0].getColumnsCount(), rgb[0].getRowsCount());

// le iterazioni
	for (int z=iteration; z>=1; z--){

		divide(rgb, z, img_divide);
		
		for (g=0; g<4; g++){
			upsampled_rows[g]= rows_upsampling (img_divide[g]);
		}

		
		upsampled_rows_filter[0]= img_vertical_filter(upsampled_rows[0], dim_low, low);
		upsampled_rows_filter[1]= img_vertical_filter(upsampled_rows[1], dim_height, height);
		upsampled_rows_filter[2]= img_vertical_filter(upsampled_rows[2], dim_low, low);	
		upsampled_rows_filter[3]= img_vertical_filter(upsampled_rows[3], dim_height, height);
	
		
		first_sum[0]= sum(upsampled_rows_filter[0], upsampled_rows_filter[1]); 
		first_sum[1]= sum(upsampled_rows_filter[2], upsampled_rows_filter[3]); 
	
		
		for (g=0; g<2; g++){
			upsampled_columns[g]= columns_upsampling (first_sum[g]);
		}
	
		
		upsampled_columns_filter[0]= img_horizontal_filter(upsampled_columns[0], dim_low, low);
		upsampled_columns_filter[1]= img_horizontal_filter(upsampled_columns[1], dim_height, height);
	
		second_sum= sum (upsampled_columns_filter[0], upsampled_columns_filter[1]);
		copy(rgb, second_sum);
		

		for (g=0; g<4; g++){
			delete [](img_divide[g]);	
			delete [](upsampled_rows[g]);
			delete [](upsampled_rows_filter[g]);
		}
		for (g=0; g<2; g++){
			delete [](first_sum[g]);
			delete [](upsampled_columns[g]);
			delete [](upsampled_columns_filter[g]);
		}
		delete []second_sum;
	}

	delete []low;
	delete []height;

	img=*(matrix_to_frame(rgb));
	

	return VIPRET_OK;
	

	

 }







/**
 * @brief  Create a new image from DWT coefficients.
 *
 * @param[out] img Greyscale VIPLib Frame to store data.
 *
 * @return VIPRET_OK if everything is fine, VIPRET_PARAM_ERR if frame
 *		   is not valid.
 *
 * @note   Ouput operator (>>) call directly this function.
 * @see    operator >> (vipFrameT<unsigned char>&)
 */
VIPRESULT vipInputIDWT::extractTo(vipFrameT<unsigned char>& img)
 {
	INFO("int vipInputIDWT::extractTo(vipFrameT<unsigned char>& img) [pushing data]")

	if ( &img == NULL )
		return VIPRET_PARAM_ERR;



		return VIPRET_NOT_IMPLEMENTED;
 }









