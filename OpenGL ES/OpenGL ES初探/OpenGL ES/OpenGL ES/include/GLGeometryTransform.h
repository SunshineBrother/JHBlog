// GLGeometryTransform
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

#ifndef __GLT_GEOMETRY_PIPELINE
#define __GLT_GEOMETRY_PIPELINE


#include "GLTools.h"

class GLGeometryTransform
	{
	public:
		GLGeometryTransform(void) {}

		inline void SetModelViewMatrixStack(GLMatrixStack& mModelView) { _mModelView = &mModelView; }

		inline void SetProjectionMatrixStack(GLMatrixStack& mProjection) { _mProjection = &mProjection; }

		inline void SetMatrixStacks(GLMatrixStack& mModelView, GLMatrixStack& mProjection) {
			_mModelView = &mModelView;
			_mProjection = &mProjection;
			}

		const M3DMatrix44f& GetModelViewProjectionMatrix(void)
			{
			m3dMatrixMultiply44(_mModelViewProjection, _mProjection->GetMatrix(), _mModelView->GetMatrix());
			return _mModelViewProjection;
			}

		inline const M3DMatrix44f& GetModelViewMatrix(void) { return _mModelView->GetMatrix(); }
		inline const M3DMatrix44f& GetProjectionMatrix(void) { return _mProjection->GetMatrix(); }

		const M3DMatrix33f& GetNormalMatrix(bool bNormalize = false)
			{
			m3dExtractRotationMatrix33(_mNormalMatrix, GetModelViewMatrix());

			if(bNormalize) {
				m3dNormalizeVector3(&_mNormalMatrix[0]);
				m3dNormalizeVector3(&_mNormalMatrix[3]);
				m3dNormalizeVector3(&_mNormalMatrix[6]);
				}

			return _mNormalMatrix;
			}

	protected:
		M3DMatrix44f	_mModelViewProjection;
		M3DMatrix33f	_mNormalMatrix;

		GLMatrixStack*  _mModelView;
		GLMatrixStack* _mProjection;
};

#endif
