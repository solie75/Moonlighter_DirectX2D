#pragma once
#include "Header.h"
#include <wrl.h>
#include <d3d11.h>
#include <d3dcompiler.h>

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")

#define CB_GETBINDSLOT(name) __CBUFFERBINDSLOT__##name##__
#define CBUFFER(name, slot) static const int CB_GETBINDSLOT(name) = slot; struct alignas(16) name 
#define CBSLOT_TRANSFORM		0

enum class eShaderStage
{
	VS,
	HS,
	DS,
	GS,
	PS,
	CS,
	End,
};

enum class eCBType
{
	Transform,
	End,
};

enum class eSamplerType
{
	Point,
	Anisotropic,
	End,
};


struct tVertex
{
	Vector3 pos;
	Vector4 color;
	Vector2 uv;
};

//struct tTransform
//{
//	Vector4 pos;
//	Vector4 scale;
//	Vector4 color;
//};

CBUFFER(TransformCB, CBSLOT_TRANSFORM)
{
	Matrix mWorld;
	Matrix mView;
	Matrix mProjection;
};