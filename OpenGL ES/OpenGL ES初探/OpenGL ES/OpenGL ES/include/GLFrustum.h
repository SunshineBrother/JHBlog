// GLFrustum.h
// Code by Richard S. Wright Jr.
// Encapsulates a frustum... works in conjunction
// with GLFrame
/* Copyright (c) 2005-2009, Richard S. Wright Jr.
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
#include "math3d.h"
#include "GLFrame.h"

#ifndef __GL_FRAME_CLASS
#define __GL_FRAME_CLASS


///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
class GLFrustum
    {
    public:
        GLFrustum(void)       // Set some Reasonable Defaults
            { SetOrthographic(-1.0f, 1.0f, -1.0f, 1.0f, -1.0f, 1.0f); }

        // Set the View Frustum
        GLFrustum(GLfloat fFov, GLfloat fAspect, GLfloat fNear, GLfloat fFar)
            { SetPerspective(fFov, fAspect, fNear, fFar); }

		GLFrustum(GLfloat xMin, GLfloat xMax, GLfloat yMin, GLfloat yMax, GLfloat zMin, GLfloat zMax)
			{ SetOrthographic(xMin, xMax, yMin, yMax, zMin, zMax); }

		// Get the projection matrix for this guy
		const M3DMatrix44f& GetProjectionMatrix(void) { return projMatrix; }

        // Calculates the corners of the Frustum and sets the projection matrix.
		// Orthographics Matrix Projection    
		void SetOrthographic(GLfloat xMin, GLfloat xMax, GLfloat yMin, GLfloat yMax, GLfloat zMin, GLfloat zMax)
			{
			m3dMakeOrthographicMatrix(projMatrix, xMin, xMax, yMin, yMax, zMin, zMax);
			projMatrix[15] = 1.0f;


			// Fill in values for untransformed Frustum corners
            // Near Upper Left
            nearUL[0] = xMin; nearUL[1] = yMax; nearUL[2] = zMin; nearUL[3] = 1.0f;

            // Near Lower Left
            nearLL[0] = xMin; nearLL[1] = yMin; nearLL[2] = zMin; nearLL[3] = 1.0f;

            // Near Upper Right
            nearUR[0] = xMax; nearUR[1] = yMax; nearUR[2] = zMin; nearUR[3] = 1.0f;

            // Near Lower Right
            nearLR[0] = xMax; nearLR[1] = yMin; nearLR[2] = zMin; nearLR[3] = 1.0f;

            // Far Upper Left
            farUL[0] = xMin; farUL[1] = yMax; farUL[2] = zMax; farUL[3] = 1.0f;

            // Far Lower Left
            farLL[0] = xMin; farLL[1] = yMin; farLL[2] = zMax; farLL[3] = 1.0f;

            // Far Upper Right
            farUR[0] = xMax; farUR[1] = yMax; farUR[2] = zMax; farUR[3] = 1.0f;

            // Far Lower Right
            farLR[0] = xMax; farLR[1] = yMin; farLR[2] = zMax; farLR[3] = 1.0f;
			}


        // Calculates the corners of the Frustum and sets the projection matrix.
		// Perspective Matrix Projection
		void SetPerspective(float fFov, float fAspect, float fNear, float fFar)
            {
            float xmin, xmax, ymin, ymax;       // Dimensions of near clipping plane
            float xFmin, xFmax, yFmin, yFmax;   // Dimensions of far clipping plane

            // Do the Math for the near clipping plane
            ymax = fNear * float(tan( fFov * M3D_PI / 360.0 ));
            ymin = -ymax;
            xmin = ymin * fAspect;
            xmax = -xmin;
              
			// Construct the projection matrix
            m3dLoadIdentity44(projMatrix);
            projMatrix[0] = (2.0f * fNear)/(xmax - xmin);
            projMatrix[5] = (2.0f * fNear)/(ymax - ymin);
            projMatrix[8] = (xmax + xmin) / (xmax - xmin);
            projMatrix[9] = (ymax + ymin) / (ymax - ymin);
            projMatrix[10] = -((fFar + fNear)/(fFar - fNear));
            projMatrix[11] = -1.0f;
            projMatrix[14] = -((2.0f * fFar * fNear)/(fFar - fNear));
			projMatrix[15] = 0.0f;
          
            // Do the Math for the far clipping plane
            yFmax = fFar * float(tan(fFov * M3D_PI / 360.0));
            yFmin = -yFmax;
            xFmin = yFmin * fAspect;
            xFmax = -xFmin;


            // Fill in values for untransformed Frustum corners
            // Near Upper Left
            nearUL[0] = xmin; nearUL[1] = ymax; nearUL[2] = -fNear; nearUL[3] = 1.0f;

            // Near Lower Left
            nearLL[0] = xmin; nearLL[1] = ymin; nearLL[2] = -fNear; nearLL[3] = 1.0f;

            // Near Upper Right
            nearUR[0] = xmax; nearUR[1] = ymax; nearUR[2] = -fNear; nearUR[3] = 1.0f;

            // Near Lower Right
            nearLR[0] = xmax; nearLR[1] = ymin; nearLR[2] = -fNear; nearLR[3] = 1.0f;

            // Far Upper Left
            farUL[0] = xFmin; farUL[1] = yFmax; farUL[2] = -fFar; farUL[3] = 1.0f;

            // Far Lower Left
            farLL[0] = xFmin; farLL[1] = yFmin; farLL[2] = -fFar; farLL[3] = 1.0f;

            // Far Upper Right
            farUR[0] = xFmax; farUR[1] = yFmax; farUR[2] = -fFar; farUR[3] = 1.0f;

            // Far Lower Right
            farLR[0] = xFmax; farLR[1] = yFmin; farLR[2] = -fFar; farLR[3] = 1.0f;
            }


        // Builds a transformation matrix and transforms the corners of the Frustum,
        // then derives the plane equations
        void Transform(GLFrame& Camera)
            {
            // Workspace
   			M3DMatrix44f rotMat;
            M3DVector3f vForward, vUp, vCross;
            M3DVector3f   vOrigin;

            ///////////////////////////////////////////////////////////////////
            // Create the transformation matrix. This was the trickiest part
            // for me. The default view from OpenGL is down the negative Z
            // axis. However, building a transformation axis from these 
            // directional vectors points the frustum the wrong direction. So
            // You must reverse them here, or build the initial frustum
            // backwards - which to do is purely a matter of taste. I chose to
            // compensate here to allow better operability with some of my other
            // legacy code and projects. RSW
            Camera.GetForwardVector(vForward);
            vForward[0] = -vForward[0];
            vForward[1] = -vForward[1];
            vForward[2] = -vForward[2];

            Camera.GetUpVector(vUp);
            Camera.GetOrigin(vOrigin);
   
	   		// Calculate the right side (x) vector
            m3dCrossProduct3(vCross, vUp, vForward);

            // The Matrix
   			// X Column
	   		memcpy(rotMat, vCross, sizeof(float)*3);
            rotMat[3] = 0.0f;
           
            // Y Column
		   	memcpy(&rotMat[4], vUp, sizeof(float)*3);
            rotMat[7] = 0.0f;       
                                    
            // Z Column
		   	memcpy(&rotMat[8], vForward, sizeof(float)*3);
            rotMat[11] = 0.0f;

            // Translation
			rotMat[12] = vOrigin[0];
            rotMat[13] = vOrigin[1];
            rotMat[14] = vOrigin[2];
            rotMat[15] = 1.0f;

            ////////////////////////////////////////////////////
            // Transform the frustum corners
            m3dTransformVector4(nearULT, nearUL, rotMat);
            m3dTransformVector4(nearLLT, nearLL, rotMat);
            m3dTransformVector4(nearURT, nearUR, rotMat);
            m3dTransformVector4(nearLRT, nearLR, rotMat);
            m3dTransformVector4(farULT, farUL, rotMat);
            m3dTransformVector4(farLLT, farLL, rotMat);
            m3dTransformVector4(farURT, farUR, rotMat);
            m3dTransformVector4(farLRT, farLR, rotMat);

            ////////////////////////////////////////////////////
            // Derive Plane Equations from points... Points given in
            // counter clockwise order to make normals point inside 
            // the Frustum
            // Near and Far Planes
            m3dGetPlaneEquation(nearPlane, nearULT, nearLLT, nearLRT);
            m3dGetPlaneEquation(farPlane, farULT, farURT, farLRT);
            
            // Top and Bottom Planes
            m3dGetPlaneEquation(topPlane, nearULT, nearURT, farURT);
            m3dGetPlaneEquation(bottomPlane, nearLLT, farLLT, farLRT);

            // Left and right planes
            m3dGetPlaneEquation(leftPlane, nearLLT, nearULT, farULT);
            m3dGetPlaneEquation(rightPlane, nearLRT, farLRT, farURT);
            }

        

        // Allow expanded version of sphere test
        bool TestSphere(float x, float y, float z, float fRadius)
            {
            M3DVector3f vPoint;
            vPoint[0] = x;
            vPoint[1] = y;
            vPoint[2] = z;

            return TestSphere(vPoint, fRadius);
            }

        // Test a point against all frustum planes. A negative distance for any
        // single plane means it is outside the frustum. The radius value allows
        // to test for a point (radius = 0), or a sphere. Possibly there might
        // be some gain in an alternative function that saves the addition of 
        // zero in this case.
        // Returns false if it is not in the frustum, true if it intersects
        // the Frustum.
        bool TestSphere(M3DVector3f vPoint, float fRadius)
            {
            float fDist;

            // Near Plane - See if it is behind me
            fDist = m3dGetDistanceToPlane(vPoint, nearPlane);
            if(fDist + fRadius <= 0.0)
                return false;

            // Distance to far plane
            fDist = m3dGetDistanceToPlane(vPoint, farPlane);
            if(fDist + fRadius <= 0.0)
                return false;

            fDist = m3dGetDistanceToPlane(vPoint, leftPlane);
            if(fDist + fRadius <= 0.0)
                return false;

            fDist = m3dGetDistanceToPlane(vPoint, rightPlane);
            if(fDist + fRadius <= 0.0)
                return false;

            fDist = m3dGetDistanceToPlane(vPoint, bottomPlane);
            if(fDist + fRadius <= 0.0)
                return false;

            fDist = m3dGetDistanceToPlane(vPoint, topPlane);
            if(fDist + fRadius <= 0.0)
                return false;

            return true;
            }

    protected:
		// The projection matrix for this frustum
		M3DMatrix44f projMatrix;	

        // Untransformed corners of the frustum
        M3DVector4f  nearUL, nearLL, nearUR, nearLR;
        M3DVector4f  farUL,  farLL,  farUR,  farLR;

        // Transformed corners of Frustum
        M3DVector4f  nearULT, nearLLT, nearURT, nearLRT;
        M3DVector4f  farULT,  farLLT,  farURT,  farLRT;

        // Base and Transformed plane equations
        M3DVector4f nearPlane, farPlane, leftPlane, rightPlane;
        M3DVector4f topPlane, bottomPlane;
    };



#endif
