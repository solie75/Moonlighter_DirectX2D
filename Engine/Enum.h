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
	Transform,
	Mesh,
	MeshRender,
	Particle,
	Script,
	Camera,
	End,
};