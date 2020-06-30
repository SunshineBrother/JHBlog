// Math3d.h
// Math3D Library, version 0.95

/* Copyright (c) 2009, Richard S. Wright Jr.
All rights reserved.

Redistribution and use in source and binary forms, with or without modification, 
are permitted provided that the following conditions are met:

Redistributions of source code must retain the above copyright notice, this list 
of conditions and the following disclaimer.

Redistributions in binary form must reproduce the above copyright notice, this list 
of conditions and the following disclaimer in the documentation and/or other 
materials provided with the distribution.

Neither the name of Richard S. Wright Jr. nor the names of other contributors may be used 
to endorse or promote products derived from this software without specific prior 
written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY 
EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES 
OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT 
SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, 
INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED 
TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR 
BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN 
CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN 
ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

// Header file for the Math3d library. The C-Runtime has math.h, this file and the
// accompanying math3d.cpp are meant to suppliment math.h by adding geometry/math routines
// useful for graphics, simulation, and physics applications (3D stuff).
// This library is meant to be useful on Win32, Mac OS X, various Linux/Unix distros,
// and mobile platforms. Although designed with OpenGL in mind, there are no OpenGL 
// dependencies. Other than standard math routines, the only other outside routine
// used is memcpy (for faster copying of vector arrays).
// Richard S. Wright Jr.

#ifndef _MATH3D_LIBRARY__
#define _MATH3D_LIBRARY__

#include <math.h>
#include <string.h>	// Memcpy lives here on most systems

///////////////////////////////////////////////////////////////////////////////
// Data structures and containers
// Much thought went into how these are declared. Many libraries declare these
// as structures with x, y, z data members. However structure alignment issues
// could limit the portability of code based on such structures, or the binary
// compatibility of data files (more likely) that contain such structures across
// compilers/platforms. Arrays are always tightly packed, and are more efficient 
// for moving blocks of data around (usually).
// Sigh... yes, I probably should use GLfloat, etc. But that requires that we
// always include OpenGL. Since this library is also useful for non-graphical
// applications, I shall risk the wrath of the portability gods...

typedef float	M3DVector2f[2];		// 3D points = 3D Vectors, but we need a 
typedef double	M3DVector2d[2];		// 2D representations sometimes... (x,y) order

typedef float	M3DVector3f[3];		// Vector of three floats (x, y, z)
typedef double	M3DVector3d[3];		// Vector of three doubles (x, y, z)

typedef float	M3DVector4f[4];		// Lesser used... Do we really need these?
typedef double	M3DVector4d[4];		// Yes, occasionaly we do need a trailing w component



// 3x3 matrix - column major. X vector is 0, 1, 2, etc.
//		0	3	6	
//		1	4	7
//		2	5	8
typedef float	M3DMatrix33f[9];		// A 3 x 3 matrix, column major (floats) - OpenGL Style
typedef double	M3DMatrix33d[9];		// A 3 x 3 matrix, column major (doubles) - OpenGL Style


// 4x4 matrix - column major. X vector is 0, 1, 2, etc.
//	0	4	8	12
//	1	5	9	13
//	2	6	10	14
//	3	7	11	15
typedef float M3DMatrix44f[16];		// A 4 X 4 matrix, column major (floats) - OpenGL style
typedef double M3DMatrix44d[16];	// A 4 x 4 matrix, column major (doubles) - OpenGL style


///////////////////////////////////////////////////////////////////////////////
// Useful constants
#define M3D_PI (3.14159265358979323846)
#define M3D_2PI (2.0 * M3D_PI)
#define M3D_PI_DIV_180 (0.017453292519943296)
#define M3D_INV_PI_DIV_180 (57.2957795130823229)


///////////////////////////////////////////////////////////////////////////////
// Useful shortcuts and macros
// Radians are king... but we need a way to swap back and forth for programmers and presentation.
// Leaving these as Macros instead of inline functions, causes constants
// to be evaluated at compile time instead of run time, e.g. m3dDegToRad(90.0)
#define m3dDegToRad(x)	((x)*M3D_PI_DIV_180)
#define m3dRadToDeg(x)	((x)*M3D_INV_PI_DIV_180)

// Hour angles
#define m3dHrToDeg(x)	((x) * (1.0 / 15.0))
#define m3dHrToRad(x)	m3dDegToRad(m3dHrToDeg(x))

#define m3dDegToHr(x)	((x) * 15.0))
#define m3dRadToHr(x)	m3dDegToHr(m3dRadToDeg(x))


// Returns the same number if it is a power of
// two. Returns a larger integer if it is not a 
// power of two. The larger integer is the next
// highest power of two.
inline unsigned int m3dIsPOW2(unsigned int iValue)
    {
    unsigned int nPow2 = 1;
    
    while(iValue > nPow2)
        nPow2 = (nPow2 << 1);
    
    return nPow2;
    }


///////////////////////////////////////////////////////////////////////////////
// Inline accessor functions (Macros) for people who just can't count to 3 or 4
// Really... you should learn to count before you learn to program ;-)
// 0 = x
// 1 = y
// 2 = z
// 3 = w
#define	m3dGetVectorX(v) (v[0])
#define m3dGetVectorY(v) (v[1])
#define m3dGetVectorZ(v) (v[2])
#define m3dGetVectorW(v) (v[3])

#define m3dSetVectorX(v, x)	((v)[0] = (x))
#define m3dSetVectorY(v, y)	((v)[1] = (y))
#define m3dSetVectorZ(v, z)	((v)[2] = (z))
#define m3dSetVectorW(v, w)	((v)[3] = (w))

///////////////////////////////////////////////////////////////////////////////
// Inline vector functions
// Load Vector with (x, y, z, w).
inline void m3dLoadVector2(M3DVector2f v, const float x, const float y)
    { v[0] = x; v[1] = y; }
inline void m3dLoadVector2(M3DVector2d v, const float x, const float y)
    { v[0] = x; v[1] = y; }
inline void m3dLoadVector3(M3DVector3f v, const float x, const float y, const float z) 
	{ v[0] = x; v[1] = y; v[2] = z; }
inline void m3dLoadVector3(M3DVector3d v, const double x, const double y, const double z)
	{ v[0] = x; v[1] = y; v[2] = z; }
inline void m3dLoadVector4(M3DVector4f v, const float x, const float y, const float z, const float w) 
	{ v[0] = x; v[1] = y; v[2] = z; v[3] = w;}
inline void m3dLoadVector4(M3DVector4d v, const double x, const double y, const double z, const double w)
	{ v[0] = x; v[1] = y; v[2] = z; v[3] = w;}


////////////////////////////////////////////////////////////////////////////////
// Copy vector src into vector dst
inline void	m3dCopyVector2(M3DVector2f dst, const M3DVector2f src) { memcpy(dst, src, sizeof(M3DVector2f)); }
inline void	m3dCopyVector2(M3DVector2d dst, const M3DVector2d src) { memcpy(dst, src, sizeof(M3DVector2d)); }

inline void	m3dCopyVector3(M3DVector3f dst, const M3DVector3f src) { memcpy(dst, src, sizeof(M3DVector3f)); }
inline void	m3dCopyVector3(M3DVector3d dst, const M3DVector3d src) { memcpy(dst, src, sizeof(M3DVector3d)); }

inline void	m3dCopyVector4(M3DVector4f dst, const M3DVector4f src) { memcpy(dst, src, sizeof(M3DVector4f)); }
inline void	m3dCopyVector4(M3DVector4d dst, const M3DVector4d src) { memcpy(dst, src, sizeof(M3DVector4d)); }


////////////////////////////////////////////////////////////////////////////////
// Add Vectors (r, a, b) r = a + b
inline void m3dAddVectors2(M3DVector2f r, const M3DVector2f a, const M3DVector2f b)
	{ r[0] = a[0] + b[0];	r[1] = a[1] + b[1];  }
inline void m3dAddVectors2(M3DVector2d r, const M3DVector2d a, const M3DVector2d b)
	{ r[0] = a[0] + b[0];	r[1] = a[1] + b[1];  }

inline void m3dAddVectors3(M3DVector3f r, const M3DVector3f a, const M3DVector3f b)
	{ r[0] = a[0] + b[0];	r[1] = a[1] + b[1]; r[2] = a[2] + b[2]; }
inline void m3dAddVectors3(M3DVector3d r, const M3DVector3d a, const M3DVector3d b)
	{ r[0] = a[0] + b[0];	r[1] = a[1] + b[1]; r[2] = a[2] + b[2]; }

inline void m3dAddVectors4(M3DVector4f r, const M3DVector4f a, const M3DVector4f b)
	{ r[0] = a[0] + b[0];	r[1] = a[1] + b[1]; r[2] = a[2] + b[2]; r[3] = a[3] + b[3]; }
inline void m3dAddVectors4(M3DVector4d r, const M3DVector4d a, const M3DVector4d b)
	{ r[0] = a[0] + b[0];	r[1] = a[1] + b[1]; r[2] = a[2] + b[2]; r[3] = a[3] + b[3]; }

////////////////////////////////////////////////////////////////////////////////
// Subtract Vectors (r, a, b) r = a - b
inline void m3dSubtractVectors2(M3DVector2f r, const M3DVector2f a, const M3DVector2f b)
	{ r[0] = a[0] - b[0]; r[1] = a[1] - b[1];  }
inline void m3dSubtractVectors2(M3DVector2d r, const M3DVector2d a, const M3DVector2d b)
	{ r[0] = a[0] - b[0]; r[1] = a[1] - b[1]; }

inline void m3dSubtractVectors3(M3DVector3f r, const M3DVector3f a, const M3DVector3f b)
	{ r[0] = a[0] - b[0]; r[1] = a[1] - b[1]; r[2] = a[2] - b[2]; }
inline void m3dSubtractVectors3(M3DVector3d r, const M3DVector3d a, const M3DVector3d b)
	{ r[0] = a[0] - b[0]; r[1] = a[1] - b[1]; r[2] = a[2] - b[2]; }

inline void m3dSubtractVectors4(M3DVector4f r, const M3DVector4f a, const M3DVector4f b)
	{ r[0] = a[0] - b[0]; r[1] = a[1] - b[1]; r[2] = a[2] - b[2]; r[3] = a[3] - b[3]; }
inline void m3dSubtractVectors4(M3DVector4d r, const M3DVector4d a, const M3DVector4d b)
	{ r[0] = a[0] - b[0]; r[1] = a[1] - b[1]; r[2] = a[2] - b[2]; r[3] = a[3] - b[3]; }



///////////////////////////////////////////////////////////////////////////////////////
// Scale Vectors (in place)
inline void m3dScaleVector2(M3DVector2f v, const float scale) 
	{ v[0] *= scale; v[1] *= scale; }
inline void m3dScaleVector2(M3DVector2d v, const double scale) 
	{ v[0] *= scale; v[1] *= scale; }

inline void m3dScaleVector3(M3DVector3f v, const float scale) 
	{ v[0] *= scale; v[1] *= scale; v[2] *= scale; }
inline void m3dScaleVector3(M3DVector3d v, const double scale) 
	{ v[0] *= scale; v[1] *= scale; v[2] *= scale; }

inline void m3dScaleVector4(M3DVector4f v, const float scale) 
	{ v[0] *= scale; v[1] *= scale; v[2] *= scale; v[3] *= scale; }
inline void m3dScaleVector4(M3DVector4d v, const double scale) 
	{ v[0] *= scale; v[1] *= scale; v[2] *= scale; v[3] *= scale; }


//////////////////////////////////////////////////////////////////////////////////////
// Cross Product
// u x v = result
// 3 component vectors only.
inline void m3dCrossProduct3(M3DVector3f result, const M3DVector3f u, const M3DVector3f v)
	{
	result[0] = u[1]*v[2] - v[1]*u[2];
	result[1] = -u[0]*v[2] + v[0]*u[2];
	result[2] = u[0]*v[1] - v[0]*u[1];
	}

inline void m3dCrossProduct3(M3DVector3d result, const M3DVector3d u, const M3DVector3d v)
	{
	result[0] = u[1]*v[2] - v[1]*u[2];
	result[1] = -u[0]*v[2] + v[0]*u[2];
	result[2] = u[0]*v[1] - v[0]*u[1];
	}

//////////////////////////////////////////////////////////////////////////////////////
// Dot Product, only for three component vectors
// return u dot v
inline float m3dDotProduct3(const M3DVector3f u, const M3DVector3f v)
	{ return u[0]*v[0] + u[1]*v[1] + u[2]*v[2]; }

inline double m3dDotProduct3(const M3DVector3d u, const M3DVector3d v)
	{ return u[0]*v[0] + u[1]*v[1] + u[2]*v[2]; }

//////////////////////////////////////////////////////////////////////////////////////
// Angle between vectors, only for three component vectors. Angle is in radians...
inline float m3dGetAngleBetweenVectors3(const M3DVector3f u, const M3DVector3f v)
    {
    float dTemp = m3dDotProduct3(u, v);
    return float(acos(double(dTemp)));	// Double cast just gets rid of compiler warning, no real need
    }

inline double m3dGetAngleBetweenVectors3(const M3DVector3d u, const M3DVector3d v)
    {
    double dTemp = m3dDotProduct3(u, v);
    return acos(dTemp);
    }

//////////////////////////////////////////////////////////////////////////////////////
// Get Square of a vectors length
// Only for three component vectors
inline float m3dGetVectorLengthSquared3(const M3DVector3f u)
	{ return (u[0] * u[0]) + (u[1] * u[1]) + (u[2] * u[2]); }

inline double m3dGetVectorLengthSquared3(const M3DVector3d u)
	{ return (u[0] * u[0]) + (u[1] * u[1]) + (u[2] * u[2]); }

//////////////////////////////////////////////////////////////////////////////////////
// Get lenght of vector
// Only for three component vectors.
inline float m3dGetVectorLength3(const M3DVector3f u)
	{ return sqrtf(m3dGetVectorLengthSquared3(u)); }

inline double m3dGetVectorLength3(const M3DVector3d u)
	{ return sqrt(m3dGetVectorLengthSquared3(u)); }

//////////////////////////////////////////////////////////////////////////////////////
// Normalize a vector
// Scale a vector to unit length. Easy, just scale the vector by it's length
inline void m3dNormalizeVector3(M3DVector3f u)
	{ m3dScaleVector3(u, 1.0f / m3dGetVectorLength3(u)); }

inline void m3dNormalizeVector3(M3DVector3d u)
	{ m3dScaleVector3(u, 1.0 / m3dGetVectorLength3(u)); }


//////////////////////////////////////////////////////////////////////////////////////
// Get the distance between two points. The distance between two points is just
// the magnitude of the difference between two vectors
// Located in math.cpp
float m3dGetDistanceSquared3(const M3DVector3f u, const M3DVector3f v);
double m3dGetDistanceSquared3(const M3DVector3d u, const M3DVector3d v);

inline double m3dGetDistance3(const M3DVector3d u, const M3DVector3d v)
{ return sqrt(m3dGetDistanceSquared3(u, v)); }

inline float m3dGetDistance3(const M3DVector3f u, const M3DVector3f v)
{ return sqrtf(m3dGetDistanceSquared3(u, v)); }

inline float m3dGetMagnitudeSquared3(const M3DVector3f u) { return u[0]*u[0] + u[1]*u[1] + u[2]*u[2]; }
inline double m3dGetMagnitudeSquared3(const M3DVector3d u) { return u[0]*u[0] + u[1]*u[1] + u[2]*u[2]; }

inline float m3dGetMagnitude3(const M3DVector3f u) { return sqrtf(m3dGetMagnitudeSquared3(u)); }
inline double m3dGetMagnitude3(const M3DVector3d u) { return sqrt(m3dGetMagnitudeSquared3(u)); }

	

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Matrix functions
// Both floating point and double precision 3x3 and 4x4 matricies are supported.
// No support is included for arbitrarily dimensioned matricies on purpose, since
// the 3x3 and 4x4 matrix routines are the most common for the purposes of this
// library. Matrices are column major, like OpenGL matrices.
// Unlike the vector functions, some of these are going to have to not be inlined,
// although many will be.

// Copy Matrix
// Brain-dead memcpy
inline void m3dCopyMatrix33(M3DMatrix33f dst, const M3DMatrix33f src)
	{ memcpy(dst, src, sizeof(M3DMatrix33f)); }

inline void m3dCopyMatrix33(M3DMatrix33d dst, const M3DMatrix33d src)
	{ memcpy(dst, src, sizeof(M3DMatrix33d)); }

inline void m3dCopyMatrix44(M3DMatrix44f dst, const M3DMatrix44f src)
	{ memcpy(dst, src, sizeof(M3DMatrix44f)); }

inline void m3dCopyMatrix44(M3DMatrix44d dst, const M3DMatrix44d src)
	{ memcpy(dst, src, sizeof(M3DMatrix44d)); }

// LoadIdentity
// Implemented in Math3d.cpp
void m3dLoadIdentity33(M3DMatrix33f m);
void m3dLoadIdentity33(M3DMatrix33d m);
void m3dLoadIdentity44(M3DMatrix44f m);
void m3dLoadIdentity44(M3DMatrix44d m);

/////////////////////////////////////////////////////////////////////////////
// Get/Set Column.
inline void m3dGetMatrixColumn33(M3DVector3f dst, const M3DMatrix33f src, const int column)
	{ memcpy(dst, src + (3 * column), sizeof(float) * 3); }

inline void m3dGetMatrixColumn33(M3DVector3d dst, const M3DMatrix33d src, const int column)
	{ memcpy(dst, src + (3 * column), sizeof(double) * 3); }

inline void m3dSetMatrixColumn33(M3DMatrix33f dst, const M3DVector3f src, const int column)
	{ memcpy(dst + (3 * column), src, sizeof(float) * 3); }

inline void m3dSetMatrixColumn33(M3DMatrix33d dst, const M3DVector3d src, const int column)
	{ memcpy(dst + (3 * column), src, sizeof(double) * 3); }

inline void m3dGetMatrixColumn44(M3DVector4f dst, const M3DMatrix44f src, const int column)
	{ memcpy(dst, src + (4 * column), sizeof(float) * 4); }

inline void m3dGetMatrixColumn44(M3DVector4d dst, const M3DMatrix44d src, const int column)
	{ memcpy(dst, src + (4 * column), sizeof(double) * 4); }

inline void m3dSetMatrixColumn44(M3DMatrix44f dst, const M3DVector4f src, const int column)
	{ memcpy(dst + (4 * column), src, sizeof(float) * 4); }

inline void m3dSetMatrixColumn44(M3DMatrix44d dst, const M3DVector4d src, const int column)
	{ memcpy(dst + (4 * column), src, sizeof(double) * 4); }


///////////////////////////////////////////////////////////////////////////////
// Extract a rotation matrix from a 4x4 matrix
// Extracts the rotation matrix (3x3) from a 4x4 matrix
inline void m3dExtractRotationMatrix33(M3DMatrix33f dst, const M3DMatrix44f src)
	{	
	memcpy(dst, src, sizeof(float) * 3); // X column
	memcpy(dst + 3, src + 4, sizeof(float) * 3); // Y column
	memcpy(dst + 6, src + 8, sizeof(float) * 3); // Z column
	}

// Ditto above, but for doubles
inline void m3dExtractRotationMatrix33(M3DMatrix33d dst, const M3DMatrix44d src)
	{
	memcpy(dst, src, sizeof(double) * 3); // X column
	memcpy(dst + 3, src + 4, sizeof(double) * 3); // Y column
	memcpy(dst + 6, src + 8, sizeof(double) * 3); // Z column
	}

// Inject Rotation (3x3) into a full 4x4 matrix...
inline void m3dInjectRotationMatrix44(M3DMatrix44f dst, const M3DMatrix33f src)
	{
	memcpy(dst, src, sizeof(float) * 4);
	memcpy(dst + 4, src + 4, sizeof(float) * 4);
	memcpy(dst + 8, src + 8, sizeof(float) * 4);
	}

// Ditto above for doubles
inline void m3dInjectRotationMatrix44(M3DMatrix44d dst, const M3DMatrix33d src)
	{
	memcpy(dst, src, sizeof(double) * 4);
	memcpy(dst + 4, src + 4, sizeof(double) * 4);
	memcpy(dst + 8, src + 8, sizeof(double) * 4);
	}

////////////////////////////////////////////////////////////////////////////////
// MultMatrix
// Implemented in Math.cpp
void m3dMatrixMultiply44(M3DMatrix44f product, const M3DMatrix44f a, const M3DMatrix44f b);
void m3dMatrixMultiply44(M3DMatrix44d product, const M3DMatrix44d a, const M3DMatrix44d b);
void m3dMatrixMultiply33(M3DMatrix33f product, const M3DMatrix33f a, const M3DMatrix33f b);
void m3dMatrixMultiply33(M3DMatrix33d product, const M3DMatrix33d a, const M3DMatrix33d b);


// Transform - Does rotation and translation via a 4x4 matrix. Transforms
// a point or vector.
// By-the-way __inline means I'm asking the compiler to do a cost/benefit analysis. If 
// these are used frequently, they may not be inlined to save memory. I'm experimenting
// with this....
// Just transform a 3 compoment vector
__inline void m3dTransformVector3(M3DVector3f vOut, const M3DVector3f v, const M3DMatrix44f m)
    {
    vOut[0] = m[0] * v[0] + m[4] * v[1] + m[8] *  v[2] + m[12];// * v[3];	// Assuming 1 
    vOut[1] = m[1] * v[0] + m[5] * v[1] + m[9] *  v[2] + m[13];// * v[3];	
    vOut[2] = m[2] * v[0] + m[6] * v[1] + m[10] * v[2] + m[14];// * v[3];	
	//vOut[3] = m[3] * v[0] + m[7] * v[1] + m[11] * v[2] + m[15] * v[3];
    }

// Ditto above, but for doubles
__inline void m3dTransformVector3(M3DVector3d vOut, const M3DVector3d v, const M3DMatrix44d m)
    {
    vOut[0] = m[0] * v[0] + m[4] * v[1] + m[8] *  v[2] + m[12];// * v[3];	 
    vOut[1] = m[1] * v[0] + m[5] * v[1] + m[9] *  v[2] + m[13];// * v[3];	
    vOut[2] = m[2] * v[0] + m[6] * v[1] + m[10] * v[2] + m[14];// * v[3];	
	//vOut[3] = m[3] * v[0] + m[7] * v[1] + m[11] * v[2] + m[15] * v[3];
    }

// Full four component transform
__inline void m3dTransformVector4(M3DVector4f vOut, const M3DVector4f v, const M3DMatrix44f m)
    {
    vOut[0] = m[0] * v[0] + m[4] * v[1] + m[8] *  v[2] + m[12] * v[3];	 
    vOut[1] = m[1] * v[0] + m[5] * v[1] + m[9] *  v[2] + m[13] * v[3];	
    vOut[2] = m[2] * v[0] + m[6] * v[1] + m[10] * v[2] + m[14] * v[3];	
	vOut[3] = m[3] * v[0] + m[7] * v[1] + m[11] * v[2] + m[15] * v[3];
    }

// Ditto above, but for doubles
__inline void m3dTransformVector4(M3DVector4d vOut, const M3DVector4d v, const M3DMatrix44d m)
    {
    vOut[0] = m[0] * v[0] + m[4] * v[1] + m[8] *  v[2] + m[12] * v[3];	 
    vOut[1] = m[1] * v[0] + m[5] * v[1] + m[9] *  v[2] + m[13] * v[3];	
    vOut[2] = m[2] * v[0] + m[6] * v[1] + m[10] * v[2] + m[14] * v[3];	
	vOut[3] = m[3] * v[0] + m[7] * v[1] + m[11] * v[2] + m[15] * v[3];
    }



// Just do the rotation, not the translation... this is usually done with a 3x3
// Matrix.
__inline void m3dRotateVector(M3DVector3f vOut, const M3DVector3f p, const M3DMatrix33f m)
	{
    vOut[0] = m[0] * p[0] + m[3] * p[1] + m[6] * p[2];	
    vOut[1] = m[1] * p[0] + m[4] * p[1] + m[7] * p[2];	
    vOut[2] = m[2] * p[0] + m[5] * p[1] + m[8] * p[2];	
	}

// Ditto above, but for doubles
__inline void m3dRotateVector(M3DVector3d vOut, const M3DVector3d p, const M3DMatrix33d m)
	{
    vOut[0] = m[0] * p[0] + m[3] * p[1] + m[6] * p[2];	
    vOut[1] = m[1] * p[0] + m[4] * p[1] + m[7] * p[2];	
    vOut[2] = m[2] * p[0] + m[5] * p[1] + m[8] * p[2];	
	}


// Create a Scaling Matrix
inline void m3dScaleMatrix33(M3DMatrix33f m, float xScale, float yScale, float zScale)
	{ m3dLoadIdentity33(m); m[0] = xScale; m[4] = yScale; m[8] = zScale; }
	
inline void m3dScaleMatrix33(M3DMatrix33f m, const M3DVector3f vScale)
	{ m3dLoadIdentity33(m); m[0] = vScale[0]; m[4] = vScale[1]; m[8] = vScale[2]; }
	
inline void m3dScaleMatrix33(M3DMatrix33d m, double xScale, double yScale, double zScale)
	{ m3dLoadIdentity33(m); m[0] = xScale; m[4] = yScale; m[8] = zScale; }
	
inline void m3dScaleMatrix33(M3DMatrix33d m, const M3DVector3d vScale)
	{ m3dLoadIdentity33(m); m[0] = vScale[0]; m[4] = vScale[1]; m[8] = vScale[2]; }

inline void m3dScaleMatrix44(M3DMatrix44f m, float xScale, float yScale, float zScale)
	{ m3dLoadIdentity44(m); m[0] = xScale; m[5] = yScale; m[10] = zScale; }
	
inline void m3dScaleMatrix44(M3DMatrix44f m, const M3DVector3f vScale)
	{ m3dLoadIdentity44(m); m[0] = vScale[0]; m[5] = vScale[1]; m[10] = vScale[2]; }
	
inline void m3dScaleMatrix44(M3DMatrix44d m, double xScale, double yScale, double zScale)
	{ m3dLoadIdentity44(m); m[0] = xScale; m[5] = yScale; m[10] = zScale; }
	
inline void m3dScaleMatrix44(M3DMatrix44d m, const M3DVector3d vScale)
	{ m3dLoadIdentity44(m); m[0] = vScale[0]; m[5] = vScale[1]; m[10] = vScale[2]; }

	
void m3dMakePerspectiveMatrix(M3DMatrix44f mProjection, float fFov, float fAspect, float zMin, float zMax);
void m3dMakeOrthographicMatrix(M3DMatrix44f mProjection, float xMin, float xMax, float yMin, float yMax, float zMin, float zMax);


// Create a Rotation matrix
// Implemented in math3d.cpp
void m3dRotationMatrix33(M3DMatrix33f m, float angle, float x, float y, float z);
void m3dRotationMatrix33(M3DMatrix33d m, double angle, double x, double y, double z);
void m3dRotationMatrix44(M3DMatrix44f m, float angle, float x, float y, float z);
void m3dRotationMatrix44(M3DMatrix44d m, double angle, double x, double y, double z);

// Create a Translation matrix. Only 4x4 matrices have translation components
inline void m3dTranslationMatrix44(M3DMatrix44f m, float x, float y, float z)
{ m3dLoadIdentity44(m); m[12] = x; m[13] = y; m[14] = z; }

inline void m3dTranslationMatrix44(M3DMatrix44d m, double x, double y, double z)
{ m3dLoadIdentity44(m); m[12] = x; m[13] = y; m[14] = z; }

void m3dInvertMatrix44(M3DMatrix44f mInverse, const M3DMatrix44f m);
void m3dInvertMatrix44(M3DMatrix44d mInverse, const M3DMatrix44d m);

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
// Other Miscellaneous functions

// Find a normal from three points
// Implemented in math3d.cpp
void m3dFindNormal(M3DVector3f result, const M3DVector3f point1, const M3DVector3f point2, 
							const M3DVector3f point3);
void m3dFindNormal(M3DVector3d result, const M3DVector3d point1, const M3DVector3d point2, 
							const M3DVector3d point3);


// Calculates the signed distance of a point to a plane
inline float m3dGetDistanceToPlane(const M3DVector3f point, const M3DVector4f plane)
           { return point[0]*plane[0] + point[1]*plane[1] + point[2]*plane[2] + plane[3]; }

inline double m3dGetDistanceToPlane(const M3DVector3d point, const M3DVector4d plane)
           { return point[0]*plane[0] + point[1]*plane[1] + point[2]*plane[2] + plane[3]; }


// Get plane equation from three points
void m3dGetPlaneEquation(M3DVector4f planeEq, const M3DVector3f p1, const M3DVector3f p2, const M3DVector3f p3);
void m3dGetPlaneEquation(M3DVector4d planeEq, const M3DVector3d p1, const M3DVector3d p2, const M3DVector3d p3);

// Determine if a ray intersects a sphere
// Return value is < 0 if the ray does not intersect
// Return value is 0.0 if ray is tangent
// Positive value is distance to the intersection point
double m3dRaySphereTest(const M3DVector3d point, const M3DVector3d ray, const M3DVector3d sphereCenter, double sphereRadius);
float m3dRaySphereTest(const M3DVector3f point, const M3DVector3f ray, const M3DVector3f sphereCenter, float sphereRadius);


///////////////////////////////////////////////////////////////////////////////////////////////////////
// Faster (and one shortcut) replacements for gluProject
void m3dProjectXY( M3DVector2f vPointOut, const M3DMatrix44f mModelView, const M3DMatrix44f mProjection, const int iViewPort[4], const M3DVector3f vPointIn);    
void m3dProjectXYZ(M3DVector3f vPointOut, const M3DMatrix44f mModelView, const M3DMatrix44f mProjection, const int iViewPort[4], const M3DVector3f vPointIn);


//////////////////////////////////////////////////////////////////////////////////////////////////
// This function does a three dimensional Catmull-Rom "spline" interpolation between p1 and p2
void m3dCatmullRom(M3DVector3f vOut, const M3DVector3f vP0, const M3DVector3f vP1, const M3DVector3f vP2, const M3DVector3f vP3, float t);
void m3dCatmullRom(M3DVector3d vOut, const M3DVector3d vP0, const M3DVector3d vP1, const M3DVector3d vP2, const M3DVector3d vP3, double t);

//////////////////////////////////////////////////////////////////////////////////////////////////
// Compare floats and doubles... 
inline bool m3dCloseEnough(const float fCandidate, const float fCompare, const float fEpsilon)
    {
    return (fabs(fCandidate - fCompare) < fEpsilon);
    }
    
inline bool m3dCloseEnough(const double dCandidate, const double dCompare, const double dEpsilon)
    {
    return (fabs(dCandidate - dCompare) < dEpsilon);
    }    
 
////////////////////////////////////////////////////////////////////////////
// Used for normal mapping. Finds the tangent bases for a triangle...
// Only a floating point implementation is provided. This has no practical use as doubles.
void m3dCalculateTangentBasis(M3DVector3f vTangent, const M3DVector3f pvTriangle[3], const M3DVector2f pvTexCoords[3], const M3DVector3f N);

////////////////////////////////////////////////////////////////////////////
// Smoothly step between 0 and 1 between edge1 and edge 2
double m3dSmoothStep(const double edge1, const double edge2, const double x);
float m3dSmoothStep(const float edge1, const float edge2, const float x);

/////////////////////////////////////////////////////////////////////////////
// Planar shadow Matrix
void m3dMakePlanarShadowMatrix(M3DMatrix44d proj, const M3DVector4d planeEq, const M3DVector3d vLightPos);
void m3dMakePlanarShadowMatrix(M3DMatrix44f proj, const M3DVector4f planeEq, const M3DVector3f vLightPos);

/////////////////////////////////////////////////////////////////////////////
// Closest point on a ray to another point in space
double m3dClosestPointOnRay(M3DVector3d vPointOnRay, const M3DVector3d vRayOrigin, const M3DVector3d vUnitRayDir, 
							const M3DVector3d vPointInSpace);

float m3dClosestPointOnRay(M3DVector3f vPointOnRay, const M3DVector3f vRayOrigin, const M3DVector3f vUnitRayDir, 
							const M3DVector3f vPointInSpace);

#endif
