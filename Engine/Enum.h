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
	Transform, // ���� ��ȯ
	Mesh, // Mesh ����
	MeshRender, // World, View, Projection ��ȯ ��� ���۷� shader �� ����
	Particle,
	Animator,
	Script, // object �� ��ȭ
	Light,
	Camera, // view, Projection ��ȯ
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

enum class eColliderType
{
	Rect,
	Circle,
	Sphere,
	Cube,
	End,
};

enum class eCameraType
{
	Main,
	UI,
	End,
};