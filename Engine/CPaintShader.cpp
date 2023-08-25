#include "CPaintShader.h"

void CPaintShader::Binds()
{
	mTarget->BindUnorderedAccessViews(0);

	mGroupX = mTarget->GetWidth() / mThreadGroupCountX + 1; // �� 1�� �����ִ°���?
	mGroupY = mTarget->GetHeight() / mThreadGroupCountY + 1;
	mGroupZ = 1;
}

void CPaintShader::Clear()
{
	mTarget->ClearUnorderedAccessViews(0);
}
