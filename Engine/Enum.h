#pragma once

enum class eResourceType
{
	Texture,
	Shader,
	Material,
	Mesh,
	Animation,
	End,
};

enum class eComponentType
{
	None,
	Transform, // 월드 변환
	Mesh, // Mesh 생성
	MeshRender, // World, View, Projection 변환 상수 버퍼로 shader 에 전달
	Particle,
	Animator,
	Script, // object 의 변화
	Light,
	Camera, // view, Projection 변환
	End,
};

enum class eLayerType
{
	Grid,
	Player,
	Monster,
	Light,
	UI,
	Background,
	End,
};

enum class eLightType
{
	Directional,
	Point,
	Spot,
	End,
};