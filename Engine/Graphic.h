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

enum class eRSType
{
	SolidBack,  // 후면의 삼각형을 그리지 않는다.
	SolidFront, // 전면의 삼각혀을 그리지 않는다.
	SolidNone, // 항상 모든 삼각형을 그린다.
	WireframeNone,
	End,
};

enum class eDSType
{
	Less, // turn on writes + 기존의 깊이값 보다 현재 정점의 깊이 값이 더 카메라와 가까이 있을 때 깊이 값을 갱신한다.
	Greater, //  turn on writes + 기존의 깊이 값 보다 현재 정점의 깊이 값이 더 카메라와 멀리 있을 때 깊이 값을 갱신한다.
	NoWrite, // turn off writes + 기존 보다 카메라에 가까울 떄 깊이값 갱신
	None, // turn off writes + 기존 보다 카메라에 멀때 깊이 값 갱신
	End,
};

enum class eBSType
{
	Default,
	AlphaBlend, // 일반적인 알파 블랜드
	OneOne, // Additive Blending; 소스의 색상과 대상 색상을 단순히 더하는 것으로 블랜딩을 수행한다. 
	// 결과, 색상의 밝기가 더 밝아지게 되어 빛이나 광원 같은 효과를 만들 수 있다.
	End,
};

enum class eRenderingMode
{
	Opaque, // 불투명 : 일반적인 불투명한 고체 물질을 표현
	CutOut, // 컷아웃 : Alpha 를 이용한 투명, 불투명을 표현함 (철창, 너덜너덜한 잎, 천 등을 표현)
	Transparent, // 투명 : 빛이 반사되는 투명함을 포현함 (유리)
	End,
};

struct tVertex
{
	Vector3 pos;
	Vector4 color;
	Vector2 uv;
};

CBUFFER(TransformCB, CBSLOT_TRANSFORM)
{
	Matrix mWorld;
	Matrix mView;
	Matrix mProjection;
};