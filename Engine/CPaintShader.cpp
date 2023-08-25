#include "CPaintShader.h"

void CPaintShader::Binds()
{
	mTarget->BindUnorderedAccessViews(0);

	mGroupX = mTarget->GetWidth() / mThreadGroupCountX + 1; // 왜 1을 더해주는거지?
	mGroupY = mTarget->GetHeight() / mThreadGroupCountY + 1;
	mGroupZ = 1;
}

void CPaintShader::Clear()
{
	mTarget->ClearUnorderedAccessViews(0);
}
