#pragma once
#include "Header.h"
#include "Enum.h"
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
#define CBSLOT_DEBUGCOLOR		4
#define CBSLOT_PARTICLE		5

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
	Particle,
	Grid,
	Animator,
	DebugColor,
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
	LessEqual, // ������ ���� ������ ���� ������ ���� ���� ���ų� ������ ���� �� ���� ���� ����
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

//enum class eSRVType
//{
//	None,
//	End,
//};

enum class eViewType
{
	None,
	SRV,
	UAV,
	End,
};

struct tVertex
{
	Vector3 pos;
	Vector4 color;
	Vector2 uv;
};

struct LightAttribute
{
	Vector4 color;
	Vector4 position;
	Vector4 direction;

	eLightType type;
	float radius;
	float angle;
	int pad;
};

struct DebugMesh
{
	eColliderType type;
	Vector3 position;
	Vector3 rotation;
	Vector3 scale;

	float radius;
	float duration;
	float time;

	bool IsCollider; // true: �浹 ����, false: �浹 ���� �ƴ�
};

struct Particle
{
	Vector4 position;
	Vector4 direction;

	float endTime;
	float time;
	float speed;
	UINT active;
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

CBUFFER(AnimatorCB, CBSLOT_ANIMATION2D)
{
	//Vector2 spriteLeftTop;
	//Vector2 spriteSize;
	//Vector2 spriteOffset;
	//Vector2 atlasSize;

	Vector2 SpriteSize;
	Vector2 Offset;

	//UINT printSpriteIndex;
	UINT AnimationType;
};

CBUFFER(DebugColorCB, CBSLOT_DEBUGCOLOR)
{
	Vector4 DebugColor;
};

CBUFFER(ParticleCB, CBSLOT_PARTICLE)
{
	UINT elementCount;
	float elpasedTime;
	int padd;
	int padd2;
};