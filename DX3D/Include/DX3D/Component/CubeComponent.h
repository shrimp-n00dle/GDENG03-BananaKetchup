#pragma once
#include <DX3D/Core/Core.h>
#include <DX3D/Game/Component.h>

namespace dx3d
{
	class CubeComponent final : public Component
	{
		dx3d_typeid(CubeComponent)
	public:
		explicit CubeComponent(const ComponentDesc& data);
		

		void setMaterial(const RefPtr<MaterialResource>& material);
		MaterialResource* getMaterial();

		VertexBuffer& getVertexBuffer();
		IndexBuffer& getIndexBuffer();

	private:
		RefPtr<MaterialResource> m_material{};
		RefPtr<VertexBuffer> m_vb{};
		RefPtr<IndexBuffer> m_ib{};
	};
}
