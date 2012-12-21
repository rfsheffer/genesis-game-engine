//
//  math_matrix.h
//  Matrix Classes
//
//  Created by Ryan Sheffer on 2012-11-10.
//  Copyright (c) 2012 Ryan Sheffer. All rights reserved.
//

namespace MathLib
{

//-----------------------------------------------------------------------------
// Purpose: Multiplies Matrix in1 by Matrix in2 and puts the result in out
//-----------------------------------------------------------------------------
void MatrixMultiply(matrix4x4 &in1, matrix4x4 &in2, matrix4x4 &out)
{
	out.m_elms[0] = (in1.m_elms[0] * in2.m_elms[0]) + (in1.m_elms[1] * in2.m_elms[4]) + (in1.m_elms[2] * in2.m_elms[8]) + (in1.m_elms[3] * in2.m_elms[12]);
	out.m_elms[1] = (in1.m_elms[0] * in2.m_elms[1]) + (in1.m_elms[1] * in2.m_elms[5]) + (in1.m_elms[2] * in2.m_elms[9]) + (in1.m_elms[3] * in2.m_elms[13]);
	out.m_elms[2] = (in1.m_elms[0] * in2.m_elms[2]) + (in1.m_elms[1] * in2.m_elms[6]) + (in1.m_elms[2] * in2.m_elms[10]) + (in1.m_elms[3] * in2.m_elms[14]);
	out.m_elms[3] = (in1.m_elms[0] * in2.m_elms[3]) + (in1.m_elms[1] * in2.m_elms[7]) + (in1.m_elms[2] * in2.m_elms[11]) + (in1.m_elms[3] * in2.m_elms[15]);

	out.m_elms[4] = (in1.m_elms[4] * in2.m_elms[0]) + (in1.m_elms[5] * in2.m_elms[4]) + (in1.m_elms[6] * in2.m_elms[8]) + (in1.m_elms[7] * in2.m_elms[12]);
	out.m_elms[5] = (in1.m_elms[4] * in2.m_elms[1]) + (in1.m_elms[5] * in2.m_elms[5]) + (in1.m_elms[6] * in2.m_elms[9]) + (in1.m_elms[7] * in2.m_elms[13]);
	out.m_elms[6] = (in1.m_elms[4] * in2.m_elms[2]) + (in1.m_elms[5] * in2.m_elms[6]) + (in1.m_elms[6] * in2.m_elms[10]) + (in1.m_elms[7] * in2.m_elms[14]);
	out.m_elms[7] = (in1.m_elms[4] * in2.m_elms[3]) + (in1.m_elms[5] * in2.m_elms[7]) + (in1.m_elms[6] * in2.m_elms[11]) + (in1.m_elms[7] * in2.m_elms[15]);

	out.m_elms[8] = (in1.m_elms[8] * in2.m_elms[0]) + (in1.m_elms[9] * in2.m_elms[4]) + (in1.m_elms[10] * in2.m_elms[8]) + (in1.m_elms[11] * in2.m_elms[12]);
	out.m_elms[9] = (in1.m_elms[8] * in2.m_elms[1]) + (in1.m_elms[9] * in2.m_elms[5]) + (in1.m_elms[10] * in2.m_elms[9]) + (in1.m_elms[11] * in2.m_elms[13]);
	out.m_elms[10] = (in1.m_elms[8] * in2.m_elms[2]) + (in1.m_elms[9] * in2.m_elms[6]) + (in1.m_elms[10] * in2.m_elms[10]) + (in1.m_elms[11] * in2.m_elms[14]);
	out.m_elms[11] = (in1.m_elms[8] * in2.m_elms[3]) + (in1.m_elms[9] * in2.m_elms[7]) + (in1.m_elms[10] * in2.m_elms[11]) + (in1.m_elms[11] * in2.m_elms[15]);

	out.m_elms[12] = (in1.m_elms[12] * in2.m_elms[0]) + (in1.m_elms[13] * in2.m_elms[4]) + (in1.m_elms[14] * in2.m_elms[8]) + (in1.m_elms[15] * in2.m_elms[12]);
	out.m_elms[13] = (in1.m_elms[12] * in2.m_elms[1]) + (in1.m_elms[13] * in2.m_elms[5]) + (in1.m_elms[14] * in2.m_elms[9]) + (in1.m_elms[15] * in2.m_elms[13]);
	out.m_elms[14] = (in1.m_elms[12] * in2.m_elms[2]) + (in1.m_elms[13] * in2.m_elms[6]) + (in1.m_elms[14] * in2.m_elms[10]) + (in1.m_elms[15] * in2.m_elms[14]);
	out.m_elms[15] = (in1.m_elms[12] * in2.m_elms[3]) + (in1.m_elms[13] * in2.m_elms[7]) + (in1.m_elms[14] * in2.m_elms[11]) + (in1.m_elms[15] * in2.m_elms[15]);
}

//-----------------------------------------------------------------------------
// Purpose: Returns the basic vectors, where Forward = Z, Left = X, and Up = Y
//-----------------------------------------------------------------------------
void matrix4x4::GetBasisVectors(Vector3 &vLeft, Vector3 &vUp, Vector3 &vForward) const
{
	// Left == X
	vLeft.x = m_elms[0];
	vLeft.y = m_elms[1];
	vLeft.z = m_elms[2];

	// Up == Y
	vUp.x = m_elms[4];
	vUp.y = m_elms[5];
	vUp.z = m_elms[6];
    
    // Forward == Z
	vForward.x = m_elms[8];
	vForward.y = m_elms[9];
	vForward.z = m_elms[10];
}

//-----------------------------------------------------------------------------
// Purpose: Comparison of this matrix vs src matrix
//-----------------------------------------------------------------------------
bool matrix4x4::operator==(const matrix4x4& src) const
{
	return !memcmp(src.m_elms, m_elms, sizeof(m_elms));
}

}