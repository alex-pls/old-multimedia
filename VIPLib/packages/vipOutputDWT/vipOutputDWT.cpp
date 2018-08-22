/** @file vipOutputDWT.cpp
 *
 * File containing methods for the 'vipOutputDWT' class.
 * The header for this class can be found in vipOutputDWT.h, check that file
 * for class description.
 *
 *
 ****************************************************************************
 *  Class based on Package Studio template: vipOutputTemplate version 0.9.12
 ****************************************************************************
 * VIPLib Framework
 *  open source, founded by Alessandro Polo 2006
 *  http://mmlab.science.unitn.it/projects/VIPLib
 *
 *  maintained by MultiMedia Laboratory - DIT - University of Trento
 *
 ****************************************************************************/



#include "vipOutputDWT.h"


#include "../../source/vipUtility.h"
#include "../../source/codecs/vipCodec_BMP.h"
#include "../../source/math/vipMatrix.h"



/**
 * @brief  Default constructor initializes variables and canvas.
 *
 * @param[in]  mainWindow Main window's handle, if not NULL, it will be created.
 */
vipOutputDWT::vipOutputDWT() : vipOutput()
 {
	INFO("vipOutputDWT::vipOutputDWT() : vipOutput() [CONTRUCTOR]")


	height = VIPOUTPUTDWT_DEF_HEIGHT;
	width = VIPOUTPUTDWT_DEF_WIDTH;
	v_sleeptime = 0;
	iteration= 2;
	filter = 0;

	init();


 }


/**
 * @brief  Default constructor initializes variables.
 *
 * @param width Canvas' width.
 * @param height Canvas' height.
 *
 * @param[in]  mainWindow Main window's handle, if not NULL, it will be created.
 */
vipOutputDWT::vipOutputDWT(unsigned int w, unsigned int h) : vipOutput()
 {
	INFO("vipOutputDWT::vipOutputDWT() : vipOutput() [CONTRUCTOR]")


	height = h;
	width = w;
	v_sleeptime = 0;
	iteration = 2;
	filter = 0;

	init();
 }


/**
 * @brief  Default destructor, wait for pending events and flush.
 */
vipOutputDWT::~vipOutputDWT()
 {

 }


/**
 * @brief  Initialize canvas, create window if necessary.
 * @return VIPRET_OK
 */
VIPRESULT vipOutputDWT::init()
 {
	return VIPRET_NOT_IMPLEMENTED;
 }



/**
 * @brief  Set display frame rate (elaboration time is not subtracted).
 *
 * @param[in] frames per second (default is 0, no sleep)
 *
 * @return VIPRET_PARAM_ERR if fps is lower than 0, VIPRET_OK else.
 */
VIPRESULT vipOutputDWT::setFrameRate(float fps)
 {
	if (fps < 0.)
		return VIPRET_PARAM_ERR;

	if ( fps == 0 )
		v_sleeptime = 0;
	else
		v_sleeptime = (long)( (float)1000 / fps ); // milliseconds

	return VIPRET_OK;
 }



/**
 * @brief  Show canvas and if selected also main window.
 *
 * @return VIPRET_OK
 */
VIPRESULT vipOutputDWT::show()
 {
	return VIPRET_NOT_IMPLEMENTED;
 }



/**
 * @brief  Hide canvas and if selected also main window.
 *
 * @return VIPRET_OK
 */
VIPRESULT vipOutputDWT::hide()
 {
	return VIPRET_NOT_IMPLEMENTED;
 }



/**
 * @brief  Display frame, conversion to vipFrameRGB24 and data-copy routine.
 *
 * @param[in] img VIPLib Cache Frame to be displayed.
 *
 * @return VIPRET_OK if everything is fine, VIPRET_INTERNAL_ERR else.
 *
 * @note   Input operator (<<) call directly this function.
 * @see    operator << (vipFrameYUV420&)
 */
VIPRESULT vipOutputDWT::importFrom(vipFrameYUV420& img)
 {
	INFO("int vipOutputDWT::importFrom(vipFrameYUV420& img) [reading data]")

	vipUtility::vipSleep( v_sleeptime );    // milliseconds


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
 * @param[in] f filter to be applied (5/3 9/7)
 * 
 * @return filtered image
 */
vipMatrix<double>* img_horizontal_filter (vipMatrix<double>* img, int dim_f, double* f){
	int i,k;
	double p[3];

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
 * @brief Downsampling columns 
 *
 * @param[in] img image to be downsampled
 *
 * @return downsampled image 
 */
vipMatrix<double>* columns_downsampling (vipMatrix<double>* img){

	vipMatrix<double>* res= new vipMatrix<double>[3]; 
	for (int c=0; c<3; c++){
		res[c].setDim((img->getColumnsCount())/2, img->getRowsCount());
	}
	double p[3];
	for(int i=0; i<res->getColumnsCount(); i++){
		for(int k=0; k<res->getRowsCount(); k++){
			getPixel(img, 2*i+1, k, p);
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
 * @param[in] f filter to be applied (5/3 9/7)
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
			setPixel(res, i,k,p);
		}
	}

return res;

}



/**
 * @brief Downsampling rows 
 *
 * @param[in] img image to be downsampled
 *
 * @return downsampled image 
 */
vipMatrix<double>* rows_downsampling (vipMatrix<double>* img){

	vipMatrix<double>* res= new vipMatrix<double> [3];
	for (int c=0; c<3; c++){
		res[c].setDim((img->getColumnsCount()), img->getRowsCount()/2);
	}
	double p[3];
	for(int i=0; i<res->getColumnsCount(); i++){
		for(int k=0; k<res->getRowsCount(); k++){
			getPixel(img, i, 2*k+1, p);
			setPixel(res, i, k, p);	
		}
	}
	return res;
}



/**
 * @brief 
 *
 * @param[in, out] total Image to be joined 
 * @param[in] l_l image l_l to be copied 
 * @param[in] h_l image h_l to be copied 
 * @param[in] l_h image l_h to be copied
 * @param[in] h_h image h_h to be copied 
 */
void join_img (vipMatrix<double>* total, vipMatrix<double>* l_l, vipMatrix<double>* h_l, vipMatrix<double>* l_h, vipMatrix<double>* h_h){

	int w= l_l->getColumnsCount();
	int h= l_l->getRowsCount();
	double p[3];
	int r, c;

	for(c=0; c<w; c++){
		for(r=0; r<h; r++){
			getPixel(l_l, c, r, p);
			setPixel(total, c, r, p);

		}
	}

	for(c=w; c<2*w; c++){
		for(r=0; r<h; r++){
			getPixel(h_l, c-w, r, p);
			setPixel(total, c, r, p);
		}
	}

	for(c=0; c<w; c++){
		for(r=h; r<2*h; r++){
			getPixel(l_h, c, r-h, p);
			setPixel(total, c , r, p);
		}
	}

	for(c=w; c<2*w; c++){
		for(r=h; r<2*h; r++){
			getPixel(h_h, c-w, r-h, p);
			setPixel(total, c, r, p);
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
 * @brief  Display frame, data-copy routine. (optimized)
 *
 * @param[in] img VIPLib Cache24 Frame to be displayed.
 *
 * @return VIPRET_OK if everything is fine, VIPRET_INTERNAL_ERR else.
 *
 * @note   Input operator (<<) call directly this function.
 * @see    operator << (vipFrameRGB96&)
 */
VIPRESULT vipOutputDWT::importFrom(vipFrameRGB24& img)
 {
	INFO("int vipOutputDWT::importFrom(vipFrameRGB96& img) [reading data]")

		double *low;
		int dim_low;
		double *height;
		int dim_height;
		vipMatrix<double>* rgb;
		
		rgb= frame_to_matrix (&img);
		//rgb= (vipMatrix<double>) img;

		if (filter == 0){
			low = new double[5];
			low[0] = -1./8; low[1]=2./8;low[2] = 6./8; low[3] = 2./8; low[4] = -1./8;
			dim_low=5;

			height = new double[3];
			height[0] = -1./2; height[1] = 2./2; height[2] = -1./2;
			dim_height=3;

		} else {
			low = new double[9];
			low[0] = 0.026748757410; low[1] = -0.016864118442; low[2] = -0.078223266528;
			low[3] = 0.266864118442; low[4] = 0.602949018236; low[5] = 0.266864118442;
			low[6] = -0.078223266528; low[7] = -0.016864118442; low[8] = 0.026748757410;
			dim_low=9;

			height= new double[7];
			height[0] = 0.091271763114; height[1] = -0.057543526228; 
			height[2] = -0.591271763114; height[3] = 1.115087052456;
			height[4] = -0.591271763114; height[5] = -0.057543526228;
			height[6] = 0.091271763114;
			dim_height=7;
		}
		
		
		

	//creo img finale per salvare le 4 immagini filtrate, con img dispari diminuisco la dimensione di uno
		vipMatrix<double>* final_img= new vipMatrix<double> [3]; 

		for (int c=0; c<3; c++){
			final_img[c].setDim(img.width, img.height);
		}

		for (int i=0; i < iteration; i++){

	
			//calcolo L_L 
			vipMatrix<double>* low_horizontal=img_horizontal_filter(rgb, dim_low, low);
			vipMatrix<double>* low_downsampled=columns_downsampling(low_horizontal);
			vipMatrix<double>* low_low=img_vertical_filter(low_downsampled, dim_low, low);
			vipMatrix<double>* low_low_downsampled=rows_downsampling(low_low);
				

			//calcolo la L_H
			vipMatrix<double>* low_height=img_vertical_filter(low_downsampled, dim_height, height);			
			vipMatrix<double>* low_height_downsampled=rows_downsampling(low_height);
			

			//calcolo H_L
			vipMatrix<double>* height_horizontal=img_horizontal_filter(rgb, dim_height, height);
			vipMatrix<double>* height_downsampled=columns_downsampling(height_horizontal);
			vipMatrix<double>* height_low=img_vertical_filter(height_downsampled, dim_low, low);
			vipMatrix<double>* height_low_downsampled=rows_downsampling(height_low);
		

			//calcolo la H_H
			vipMatrix<double>* height_height=img_vertical_filter(height_downsampled, dim_height, height);			
			vipMatrix<double>* height_height_downsampled=rows_downsampling(height_height);
			
			
			join_img(final_img, low_low_downsampled, height_low_downsampled, low_height_downsampled, height_height_downsampled);

			
			delete []rgb;
			delete []low_horizontal;
			delete []low_downsampled;
			delete []low_low;
			delete []low_height;
			delete []low_height_downsampled;
			delete []height_horizontal;
			delete []height_downsampled;
			delete []height_low;
			delete []height_low_downsampled;
			delete []height_height;
			delete []height_height_downsampled;
			rgb = low_low_downsampled;
		}
		
		delete []low;
		delete []height;

		final_img[0].saveToFile("provaR.txt");
		final_img[1].saveToFile("provaG.txt");
		final_img[2].saveToFile("provaB.txt");
	
		vipFrameRGB24* stampa= matrix_to_frame (final_img);
		vipCodec_BMP::save(*stampa, "trasformata.bmp", vipCodec_BMP::FORMAT_BMP_24);

		

		
	return VIPRET_OK;
 }



/**
 * @brief  Display frame, conversion to vipFrameRGB24
 *         and single channel data-copy routine.
 *
 * @param[in] img VIPLib RGB Frame to be displayed.
 *
 * @return VIPRET_OK if everything is fine, VIPRET_INTERNAL_ERR else.
 *
 * @note   Input operator (<<) call directly this function.
 * @see    operator << (vipFrameRGB96&)
 */
VIPRESULT vipOutputDWT::importFrom(vipFrameRGB96& img)
 {
	INFO("int vipOutputDWT::importFrom(vipFrameRGB96& img) [reading data]")

// image displaying routine
	//	if ( v_sleeptime && v_sleeptime > (long)getElaborationTime())
	//		vipUtility::vipSleep( v_sleeptime - (long)getElaborationTime() );
	vipUtility::vipSleep( v_sleeptime );    // milliseconds

	return VIPRET_NOT_IMPLEMENTED;
 }



/**
 * @brief  Display frame, conversion to vipFrameRGB24
 *         and single channel data-copy routine.
 *
 * @param[in] img VIPLib Grey Frame to be displayed.
 *
 * @return VIPRET_OK if everything is fine, VIPRET_INTERNAL_ERR else.
 *
 * @note   Input operator (<<) call directly this function.
 * @see    operator << (vipFrameT<unsigned char>&)
 */
VIPRESULT vipOutputDWT::importFrom(vipFrameT<unsigned char>& img)
 {
	INFO("int vipOutputDWT::importFrom(vipFrameT<unsigned char>& img) [reading data]")

// image displaying routine


	//	if ( v_sleeptime && v_sleeptime > (long)getElaborationTime())
	//		vipUtility::vipSleep( v_sleeptime - (long)getElaborationTime() );
	vipUtility::vipSleep( v_sleeptime );    // milliseconds


	return VIPRET_NOT_IMPLEMENTED;
 }






