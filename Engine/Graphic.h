#pragma once
#include "Header.h"
#include <wrl.h>
#include <d3d11.h>
#include <d3dcompiler.h>

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")

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

struct tTransform
{
	Vector4 pos;
	Vector4 scale;
	Vector4 color;
};