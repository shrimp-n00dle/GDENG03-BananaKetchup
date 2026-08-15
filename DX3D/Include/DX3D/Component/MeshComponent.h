#pragma once
#pragma once
#include <DX3D/Core/Core.h>
#include <DX3D/Game/Component.h>
#include <DX3D/Component/TransformComponent.h>
#include <DX3D/Graphics/MeshBuffer.h>
#include <DX3D/Graphics/GraphicsDevice.h>
#include <DX3D/Input/InputSystem.h>
#include <DX3D/Game/GameObject.h>


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
		float meshScale = 1.0f;
		dx3d::InputSystem& input;
		dx3d::TransformComponent& modelScale;
		RefPtr<MaterialResource> m_material{};
		RefPtr<VertexBuffer> m_vb;
		RefPtr<IndexBuffer> m_ib;

		RefPtr<MeshBuffer> m_mesh;
	};
}
