#pragma once

enum class eResourceType
{
	Texture,
	Shader,
	Material,
	Mesh,
	End,
};

enum class eComponentType
{
	None,
	Transform, // ���� ��ȯ
	Mesh, // Mesh ����
	Script, // object �� ��ȭ
	
	MeshRender, // World, View, Projection ��ȯ ��� ���۷� shader �� ����
	Particle,
	Camera, // view, Projection ��ȯ
	End,
};

enum class eLayerType
{
	Grid,
	Player,
	Monster,
	UI,
	Background,
	End,
};
