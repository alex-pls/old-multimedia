/**
 *  @class   vipTrajectory
 *
 *  @brief   This Class is a simple trajectory (fully inline) implementation.
 *
 *  @bug     could use better interface: private/protected members and public access methods
 *  @warning not completely tested.
 *  @todo	 could use better interface (private/protected members and public access methods); implement transform.
 *
 *  @version 0.1
 *  @date    22/07/2008 - //2008
 *  @author  Marco Verza
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

/*	How this is meant to be used:

	vipTrajectory<unsigned int> image_traj(10);			// to express a trajectory inside image (pixels)
	vipTrajectory<float>		world_traj(10);			// to express a world trajectory (meters..)
	unsigned int x=2,y=3,z=4;
	traj.addPoint( &x, &y, &z );						// add one point
	vipMatrix<float> H(3,3);							// create transform core matrix (then fill it with values)
	transformTrajectory(&image_traj, &world_traj, H);	// transform trajectory using 3x3 matrix as core (i.e. for homography)

*/

#ifndef _VIP_TRAJECTORY_UTIL_H
#define _VIP_TRAJECTORY_UTIL_H

#include <stdio.h>
#include <vipdefs.h>
#include <math/vipMatrix.h>
#include <time.h>


template <class T> class vipTrajectory
{
public:
	vipTrajectory()
	{
		data_x = NULL;
		data_y = NULL;
		data_z = NULL;
		data_t = NULL;
		m_uiCurrLen = 0;
		m_uiFirstFreePos = 0;
	}
	vipTrajectory( unsigned int len, bool useX = true, bool useY = true, bool useZ = true, bool useT = true )
	{
		m_uiCurrLen = len;
		m_uiFirstFreePos = 0;
		data_x	= useX ?	(new T[len])		: NULL;
		data_y	= useY ?	(new T[len])		: NULL;
		data_z	= useZ ?	(new T[len])		: NULL;
		data_t	= useT ?	(new time_t[len])	: NULL;
	}
	~vipTrajectory()
	{
		reset();
	}
public:
	T		*data_x;
	T		*data_y;
	T		*data_z;
	time_t	*data_t;
	unsigned int m_uiCurrLen;
	unsigned int m_uiFirstFreePos;

public:
	void copyFrom( vipTrajectory *traj )	// copy all data from traj. no referencing to traj data
	{
		bool use_x = ( traj->data_x != NULL ) ? true : false;
		bool use_y = ( traj->data_y != NULL ) ? true : false;
		bool use_z = ( traj->data_z != NULL ) ? true : false;
		bool use_t = ( traj->data_t != NULL ) ? true : false;

		reAlloc( traj->m_uiCurrLen, use_x, use_y, use_z, use_t );
		m_uiFirstFreePos	= traj->m_uiFirstFreePos;

		if( m_uiFirstFreePos > 0 )
		{
			if( use_x )
				memcpy( data_x, traj->data_x, sizeof(T)*m_uiFirstFreePos );
			if( use_y )
				memcpy( data_y, traj->data_y, sizeof(T)*m_uiFirstFreePos );
			if( use_z )
				memcpy( data_z, traj->data_z, sizeof(T)*m_uiFirstFreePos );
			if( use_t )
				memcpy( data_t, traj->data_t, sizeof(time_t)*m_uiFirstFreePos );
		}
	}

	void reset()
	{
		if( data_x != NULL )
			delete[] data_x;
		if( data_y != NULL )
			delete[] data_y;
		if( data_z != NULL )
			delete[] data_z;
		if( data_t != NULL )
			delete[] data_t;

		data_x = NULL;
		data_y = NULL;
		data_z = NULL;
		data_t = NULL;
		m_uiCurrLen = 0;
		m_uiFirstFreePos = 0;
	}

	void reAlloc(unsigned int newLen, bool useX = true, bool useY = true, bool useZ = true, bool useT = false )
	{
		reset();
		m_uiCurrLen = newLen;
		m_uiFirstFreePos = 0;
		data_x = useX ? (new T[newLen])			: NULL;
		data_y = useY ? (new T[newLen])			: NULL;
		data_z = useZ ? (new T[newLen])			: NULL;
		data_t = useT ? (new time_t[newLen])	: NULL;
	}

	void printDebugUint()
	{
		printf("vipTrajectory [%h] printDebug():\n", this );
		printf("Currently allocated: %i positions\n", m_uiCurrLen );
		printf("Currently used: %i positions\n", m_uiFirstFreePos );
		printf("data:\n", m_uiFirstFreePos );
		for( unsigned int i=0; i<m_uiFirstFreePos; i++ )
		{
			printf("\t[%i]:", i);

			if( data_x == NULL )	// x
				printf("{N/A,");
			else
				printf("{%i,", (int)data_x[i] );

			if( data_y == NULL )	// y
				printf("N/A,");
			else
				printf("%i,", (int)data_y[i] );

			if( data_z == NULL )	// z
				printf("N/A}");
			else
				printf("%i}", (int)data_z[i] );

			printf("");
		}
	}

	void printDebugFloat()
	{
		printf("vipTrajectory [%h] printDebug():\n", this );
		printf("Currently allocated: %i positions\n", m_uiCurrLen );
		printf("Currently used: %i positions\n", m_uiFirstFreePos );
		printf("data:\n", m_uiFirstFreePos );
		for( unsigned int i=0; i<m_uiFirstFreePos; i++ )
		{
			printf("\t[%i]:", i);

			if( data_x == NULL )	// x
				printf("{N/A,");
			else
				printf("{%f,", (float)data_x[i] );

			if( data_y == NULL )	// y
				printf("N/A,");
			else
				printf("%f,", (float)data_y[i] );

			if( data_z == NULL )	// z
				printf("N/A}");
			else
				printf("%f}", (float)data_z[i] );

			printf("");
		}
	}

	VIPRESULT	addPoint( T *entry_x, T *entry_y = NULL, T *entry_z = NULL, time_t *entry_t = NULL )
	{
		if( m_uiFirstFreePos == m_uiCurrLen )	// this traj is FULL
		{ //realloc
			//printf("vipTrajectory: realloc of data, from %i to %i pos.\n", m_uiCurrLen, m_uiCurrLen*2);
			if( entry_x != NULL )	// check if x is in use 
			{
				T *tmp_x = new T[m_uiCurrLen*2];
				memcpy( tmp_x, data_x, sizeof(T)*m_uiCurrLen );
				delete[] data_x;
				data_x = tmp_x;
			}
			if( entry_y != NULL )	// check if y is in use 
			{
				T *tmp_y = new T[m_uiCurrLen*2];
				memcpy( tmp_y, data_y, sizeof(T)*m_uiCurrLen );
				delete[] data_y;
				data_y = tmp_y;
			}
			if( entry_z != NULL )	// check if z is in use 
			{
				T *tmp_z = new T[m_uiCurrLen*2];
				memcpy( tmp_z, data_z, sizeof(T)*m_uiCurrLen );
				delete[] data_z;
				data_z = tmp_z;
			}
			if( entry_t != NULL )	// check if z is in use 
			{
				time_t *tmp_t = new time_t[m_uiCurrLen*2];
				memcpy( tmp_t, data_t, sizeof(time_t)*m_uiCurrLen );
				delete[] data_t;
				data_t = tmp_t;
			}

			m_uiCurrLen *= 2;	// update current length

			//printDebug();

		}
		else if( m_uiFirstFreePos > m_uiCurrLen )
		{
			printf("vipTrajectory: improper use / data corruption! debug this. press enter\n");
			getchar();
		}

		if( (entry_x!=NULL && data_x==NULL) || (entry_y!=NULL && data_y==NULL) || (entry_z!=NULL && data_z==NULL) || (entry_t!=NULL && data_t==NULL) )
			return VIPRET_PARAM_ERR;

		if( entry_x != NULL )
			data_x[m_uiFirstFreePos] = *entry_x;	// NOTE: entry is COPIED to this object, not referenced.
		if( entry_y != NULL )
			data_y[m_uiFirstFreePos] = *entry_y;
		if( entry_z != NULL )
			data_z[m_uiFirstFreePos] = *entry_z;

		if( entry_t != NULL )
			data_t[m_uiFirstFreePos] = *entry_t;
		else if( data_t != NULL )
			data_t[m_uiFirstFreePos] = time(NULL);	// if null input time, but time's used, set timestamp to NOW


		m_uiFirstFreePos++;

		//if( m_uiFirstFreePos >= m_uiCurrLen )
		//	printf("**WARNING** vipTrajectory: last free position just filled.\n");

		return VIPRET_OK;
	}

	int appendFrom( vipTrajectory *traj )	// append from another trajectory
	{
		int	count = 0;
		T	*x,*y,*z;
		time_t *t;
		for( unsigned int i=0; i<traj->m_uiFirstFreePos; i++ )
		{
			if( data_x != NULL )
				x = &traj->data_x[i];
			else
				x = NULL;

			if( data_y != NULL )
				y = &traj->data_y[i];
			else
				y = NULL;

			if( data_z != NULL )
				z = &traj->data_z[i];
			else
				z = NULL;

			if( data_t != NULL )
				t = &traj->data_t[i];
			else
				t = NULL;

			this->addPoint( x, y, z, t );
			count++;
		}
		return count;
	}

};	// end of vipTrajectory template

// todo: doxy comments
// input:	image_traj must point to a non empty 3D trajectory (homoegeneous coords).
//			world_traj must point to an already correctly allocated 3D vipTrajectory<float>
static VIPRESULT transformTrajectory( vipTrajectory<unsigned int> *image_traj, vipTrajectory<float> *world_traj, vipMatrix<float> *transfCore, bool doNormalizeByZ = true, bool copyTimestamps = true )
{
	// check input traj pointer
	if( image_traj == NULL )	// invalid input pointer
		return VIPRET_PARAM_ERR;
	
	if( image_traj->m_uiCurrLen == 0 )	// empty input traj
		return VIPRET_PARAM_ERR;

	if( image_traj->data_x == NULL || image_traj->data_y == NULL || image_traj->data_z == NULL )	// support only 3D homogeneous coords at the moment
		return VIPRET_PARAM_ERR;

	if( image_traj->m_uiFirstFreePos == 0 )	// empty input traj
		return VIPRET_OK;	// nothing to do

	int offset = 0;
	vipMatrix<float> vmTempIn(1,3);
	vipMatrix<float> vmTempOut(1,3);
	float x,z,y;
	time_t *t = NULL;

	bool useT = ( image_traj->data_t != NULL ) ? copyTimestamps : false; 

	// check output pointer
	if( world_traj == NULL )
		return VIPRET_PARAM_ERR;
	else // pointer to already created output traj is supplied
	{ // check output traj
		if( world_traj->m_uiFirstFreePos != 0 )	// output traj not empty. we will only compute and append new data
			offset = world_traj->m_uiFirstFreePos;
		if( world_traj->data_x == NULL || world_traj->data_y == NULL || world_traj->data_z == NULL || (world_traj->data_t==NULL && useT) )	// supplied output traj is not (correctly) initialized.
		{
			printf("** Warning ** transformTrajectory(): reallocating supplied output traj. could eat data.\npress Enter to continue\n");
			getchar();
			world_traj->reAlloc( image_traj->m_uiCurrLen, true, true, true, useT );
		}
	}

	for( unsigned int i=offset; i < image_traj->m_uiFirstFreePos; i++ )
	{
		// Transform and save each coordinate
		//for( unsigned int i=offset; i<image_traj->m_uiFirstFreePos; i++ )
		//{
			x = (float)image_traj->data_x[i];	// prepare input 3x1 matrix
			vmTempIn.setValue(0,0, x );
			y = (float)image_traj->data_y[i];
			vmTempIn.setValue(0,1, y );
			z = (float)image_traj->data_z[i];
			vmTempIn.setValue(0,2, z );
			vipMatrix<float>::multiply_3x3_3x1( transfCore, &vmTempIn, &vmTempOut );	// do transform

			// prepare result, with or without normalizing by z
			x = (doNormalizeByZ) ? (vmTempOut.getValue(0,0)/vmTempOut.getValue(0,2))	: (vmTempOut.getValue(0,0));
			y = (doNormalizeByZ) ? (vmTempOut.getValue(0,1)/vmTempOut.getValue(0,2))	: (vmTempOut.getValue(0,1));
			z = (doNormalizeByZ) ? (1.0)												: (vmTempOut.getValue(0,2));
			
			t = ( useT )		 ? ( &image_traj->data_t[i] ) : NULL;	// copy over timestamp if exists

			world_traj->addPoint( &x, &y, &z, t ); // save point (hoprefully to the correct location, it should always be first free pos)
		//}
		
	}

	return VIPRET_OK;
}

// Distance between two 1/2/3D points, in the case of unsigned int trajectory
static float getDistance( vipTrajectory<unsigned int> *tr1, unsigned int pos1, vipTrajectory<unsigned int> *tr2, unsigned int pos2 )
{
	if( tr1 == NULL || tr2 == NULL || pos1 >= tr1->m_uiFirstFreePos || pos2 >= tr2->m_uiFirstFreePos )
		return -1;	// input parameters error

	float dist;

	bool useX = ( tr1->data_x!=0 && tr2->data_x!=0 );
	bool useY = ( tr1->data_y!=0 && tr2->data_y!=0 );
	bool useZ = ( tr1->data_z!=0 && tr2->data_z!=0 );

	if( useX )
		dist = ((float)tr1->data_x[pos1]) - ((float)tr2->data_x[pos2]);
	if( useY )
		dist += ((float)tr1->data_y[pos1]) - ((float)tr2->data_y[pos2]);
	if( useZ )
		dist += ((float)tr1->data_z[pos1]) - ((float)tr2->data_z[pos2]);

	return ( sqrt(dist) );
}

// Distance between two 1/2/3D points, in the case of float trajectory
static float getDistance( vipTrajectory<float> *tr1, unsigned int pos1, vipTrajectory<float> *tr2, unsigned int pos2 )
{
	if( tr1 == NULL || tr2 == NULL || pos1 >= tr1->m_uiFirstFreePos || pos2 >= tr2->m_uiFirstFreePos )
		return -1;	// input parameters error

	float dist;

	bool useX = ( tr1->data_x!=0 && tr2->data_x!=0 );
	bool useY = ( tr1->data_y!=0 && tr2->data_y!=0 );
	bool useZ = ( tr1->data_z!=0 && tr2->data_z!=0 );

	if( useX )
		dist = pow( (tr1->data_x[pos1]) - (tr2->data_x[pos2]), 2 );
	if( useY )
		dist += pow( (tr1->data_y[pos1]) - (tr2->data_y[pos2]), 2 );
	if( useZ )
		dist += pow( (tr1->data_z[pos1]) - (tr2->data_z[pos2]), 2 );

	return ( sqrt(dist) );
}


#endif _VIP_TRAJECTORY_UTIL_H