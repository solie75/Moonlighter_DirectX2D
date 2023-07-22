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
//#define CBSLOT_PARTICLE		1
#define CBSLOT_GRID		2
#define CBSLOT_ANIMATION2D		3

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
	Grid,
	Animator,
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
	SolidBack,  // �ĸ��� �ﰢ���� �׸��� �ʴ´�.
	SolidFront, // ������ �ﰢ���� �׸��� �ʴ´�.
	SolidNone, // �׻� ��� �ﰢ���� �׸���.
	WireframeNone,
	End,
};

enum class eDSType
{
	Less, // turn on writes + ������ ���̰� ���� ���� ������ ���� ���� �� ī�޶�� ������ ���� �� ���� ���� �����Ѵ�.
	Greater, //  turn on writes + ������ ���� �� ���� ���� ������ ���� ���� �� ī�޶�� �ָ� ���� �� ���� ���� �����Ѵ�.
	NoWrite, // turn off writes + ���� ���� ī�޶� ����� �� ���̰� ����
	None, // turn off writes + ���� ���� ī�޶� �ֶ� ���� �� ����
	End,
};

enum class eBSType
{
	Default,
	AlphaBlend, // �Ϲ����� ���� ����
	OneOne, // Additive Blending; �ҽ��� ����� ��� ������ �ܼ��� ���ϴ� ������ ������ �����Ѵ�. 
	// ���, ������ ��Ⱑ �� ������� �Ǿ� ���̳� ���� ���� ȿ���� ���� �� �ִ�.
	End,
};

enum class eRenderingMode
{
	Opaque, // ������ : �Ϲ����� �������� ��ü ������ ǥ��
	CutOut, // �ƾƿ� : Alpha �� �̿��� ����, �������� ǥ���� (öâ, �ʴ��ʴ��� ��, õ ���� ǥ��)
	Transparent, // ���� : ���� �ݻ�Ǵ� �������� ������ (����)
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

CBUFFER(GridCB, CBSLOT_GRID)
{
	Vector4 CameraPosition;
	Vector2 CameraScale;
	Vector2 Resolution;
};