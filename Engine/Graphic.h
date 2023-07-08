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

enum class CBType
{
	Transform,
	End,
};

struct Vertex
{
	Vector3 pos;
	Vector4 Color;
};

struct Transform
{
	Vector4 pos;
	Vector4 scale;
	Vector4 color;
};