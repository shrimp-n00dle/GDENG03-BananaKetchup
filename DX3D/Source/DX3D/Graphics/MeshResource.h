#pragma once
#include <DX3D/Resource/Resource.h>

namespace dx3d
{
	class MeshResource : public Resource
	{
	public:
		explicit MeshResource(const MeshResourceDesc& desc);
		dx3d::Mesh& getMesh();
	private:
		RefPtr<Mesh> m_mesh{};
	};
}
