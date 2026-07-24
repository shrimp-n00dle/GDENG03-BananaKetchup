#pragma once
#pragma once
#include <DX3D/Core/Core.h>
#include <DX3D/Game/Component.h>
#include <DX3D/Graphics/MeshBuffer.h>
#include <DX3D/Graphics/GraphicsDevice.h>



namespace dx3d
{
	class MeshComponent final : public Component
	{
		dx3d_typeid(MeshComponent)
	public:
		explicit MeshComponent(const ComponentDesc& data);

		void setMaterial(const RefPtr<MaterialResource>& material);
		void assignMesh(const RefPtr<MeshBuffer>& mesh) noexcept;
		MaterialResource* getMaterial();

		VertexBuffer& getVertexBuffer();
		IndexBuffer& getIndexBuffer();

		RefPtr<dx3d::VertexBuffer> callVertexBuffer(GraphicsDevice& _device);
		RefPtr<dx3d::IndexBuffer> callIndexBuffer(GraphicsDevice& _device);

	private:
		RefPtr<MaterialResource> m_material{};
		RefPtr<VertexBuffer> m_vb;
		RefPtr<IndexBuffer> m_ib;

		RefPtr<MeshBuffer> m_mesh;
	};
}
