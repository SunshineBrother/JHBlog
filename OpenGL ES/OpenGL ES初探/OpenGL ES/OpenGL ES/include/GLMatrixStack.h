// GLMatrixStack.h
// Matrix stack functionality
/*
Copyright (c) 2009, Richard S. Wright Jr.
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

#ifndef __GLT_MATRIX_STACK
#define __GLT_MATRIX_STACK

#include "GLTools.h"
#include "math3d.h"
#include "GLFrame.h"

enum GLT_STACK_ERROR { GLT_STACK_NOERROR = 0, GLT_STACK_OVERFLOW, GLT_STACK_UNDERFLOW }; 

class GLMatrixStack
	{
	public:
		GLMatrixStack(int iStackDepth = 64) {
			stackDepth = iStackDepth;
			pStack = new M3DMatrix44f[iStackDepth];
			stackPointer = 0;
			m3dLoadIdentity44(pStack[0]);
			lastError = GLT_STACK_NOERROR;
			}
		
		
		~GLMatrixStack(void) {
			delete [] pStack;
			}

		
		inline void LoadIdentity(void) { 
			m3dLoadIdentity44(pStack[stackPointer]); 
			}
		
		inline void LoadMatrix(const M3DMatrix44f mMatrix) { 
			m3dCopyMatrix44(pStack[stackPointer], mMatrix); 
			}
            
        inline void LoadMatrix(GLFrame& frame) {
            M3DMatrix44f m;
            frame.GetMatrix(m);
            LoadMatrix(m);
            }
            
		inline void MultMatrix(const M3DMatrix44f mMatrix) {
			M3DMatrix44f mTemp;
			m3dCopyMatrix44(mTemp, pStack[stackPointer]);
			m3dMatrixMultiply44(pStack[stackPointer], mTemp, mMatrix);
			}
            
        inline void MultMatrix(GLFrame& frame) {
            M3DMatrix44f m;
            frame.GetMatrix(m);
            MultMatrix(m);
            }
            				
		inline void PushMatrix(void) {
			if(stackPointer < stackDepth) {
				stackPointer++;
				m3dCopyMatrix44(pStack[stackPointer], pStack[stackPointer-1]);
				}
			else
				lastError = GLT_STACK_OVERFLOW;
			}
		
		inline void PopMatrix(void) {
			if(stackPointer > 0)
				stackPointer--;
			else
				lastError = GLT_STACK_UNDERFLOW;
			}
			
		void Scale(GLfloat x, GLfloat y, GLfloat z) {
			M3DMatrix44f mTemp, mScale;
			m3dScaleMatrix44(mScale, x, y, z);
			m3dCopyMatrix44(mTemp, pStack[stackPointer]);
			m3dMatrixMultiply44(pStack[stackPointer], mTemp, mScale);
			}
			
			
		void Translate(GLfloat x, GLfloat y, GLfloat z) {
			M3DMatrix44f mTemp, mScale;
			m3dTranslationMatrix44(mScale, x, y, z);
			m3dCopyMatrix44(mTemp, pStack[stackPointer]);
			m3dMatrixMultiply44(pStack[stackPointer], mTemp, mScale);			
			}
            			
		void Rotate(GLfloat angle, GLfloat x, GLfloat y, GLfloat z) {
			M3DMatrix44f mTemp, mRotate;
			m3dRotationMatrix44(mRotate, float(m3dDegToRad(angle)), x, y, z);
			m3dCopyMatrix44(mTemp, pStack[stackPointer]);
			m3dMatrixMultiply44(pStack[stackPointer], mTemp, mRotate);
			}
		
		
		// I've always wanted vector versions of these
		void Scalev(const M3DVector3f vScale) {
			M3DMatrix44f mTemp, mScale;
			m3dScaleMatrix44(mScale, vScale);
			m3dCopyMatrix44(mTemp, pStack[stackPointer]);
			m3dMatrixMultiply44(pStack[stackPointer], mTemp, mScale);
			}
			
        void Translatev(const M3DVector3f vTranslate) {
			M3DMatrix44f mTemp, mTranslate;
			m3dLoadIdentity44(mTranslate);
            memcpy(&mTranslate[12], vTranslate, sizeof(M3DVector3f));
			m3dCopyMatrix44(mTemp, pStack[stackPointer]);
			m3dMatrixMultiply44(pStack[stackPointer], mTemp, mTranslate);
            }
        
			
		void Rotatev(GLfloat angle, M3DVector3f vAxis) {
			M3DMatrix44f mTemp, mRotation;
			m3dRotationMatrix44(mRotation, float(m3dDegToRad(angle)), vAxis[0], vAxis[1], vAxis[2]);
			m3dCopyMatrix44(mTemp, pStack[stackPointer]);
			m3dMatrixMultiply44(pStack[stackPointer], mTemp, mRotation);
			}
			
		
		// I've also always wanted to be able to do this
		void PushMatrix(const M3DMatrix44f mMatrix) {
		 	if(stackPointer < stackDepth) {
				stackPointer++;
				m3dCopyMatrix44(pStack[stackPointer], mMatrix);
				}
			else
				lastError = GLT_STACK_OVERFLOW;
			}
			
        void PushMatrix(GLFrame& frame) {
            M3DMatrix44f m;
            frame.GetMatrix(m);
            PushMatrix(m);
            }
            
		// Two different ways to get the matrix
		const M3DMatrix44f& GetMatrix(void) { return pStack[stackPointer]; }
		void GetMatrix(M3DMatrix44f mMatrix) { m3dCopyMatrix44(mMatrix, pStack[stackPointer]); }


		inline GLT_STACK_ERROR GetLastError(void) {
			GLT_STACK_ERROR retval = lastError;
			lastError = GLT_STACK_NOERROR;
			return retval; 
			}
	
	protected:
		GLT_STACK_ERROR		lastError;
		int					stackDepth;
		int					stackPointer;
		M3DMatrix44f		*pStack;
	};

#endif
