#pragma once

enum class eResourceType
{
	Texture,
	Shader,
	Material,
	Mesh,
	Animation,
	ComputeShader,
	End,
};

enum class eComponentType
{
	None,
	Transform, // ���� ��ȯ
	Mesh, // Mesh ����
	Collider2D,
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
	Projectile,
	Light,
	UI,
	Background,
	Camera,
	Weapon,
	PlayerProjectile,
	Portal,
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

enum class eCreatureType
{
	Player,
	Monster,
	NPC,
	End,
};