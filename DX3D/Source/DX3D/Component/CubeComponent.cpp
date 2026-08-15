#include <DX3D/Component/CubeComponent.h>
#include <DX3D/Game/World.h>
#include <DX3D/Math/Vec3.h>
#include <DX3D/Math/Vec2.h>
#include <DX3D/Math/Mat4x4.h>
#include <DX3D/Graphics/GraphicsDevice.h>


dx3d::CubeComponent::CubeComponent(const ComponentDesc& data) : Component(data)
{

	static const Vertex vertexList[] =
	{
		// Front (+Z)
		{{-0.5f, -0.5f,  0.5f}},
		{{-0.5f,  0.5f,  0.5f}},
		{{ 0.5f,  0.5f,  0.5f}},
		{{ 0.5f, -0.5f,  0.5f}},

		// Back (-Z)
		{{ 0.5f, -0.5f, -0.5f}},
		{{ 0.5f,  0.5f, -0.5f}},
		{{-0.5f,  0.5f, -0.5f}},
		{{-0.5f, -0.5f, -0.5f}},

		// Left (-X)
		{{-0.5f, -0.5f, -0.5f}},
		{{-0.5f,  0.5f, -0.5f}},
		{{-0.5f,  0.5f,  0.5f}},
		{{-0.5f, -0.5f,  0.5f}},

		// Right (+X)
		{{ 0.5f, -0.5f,  0.5f}},
		{{ 0.5f,  0.5f,  0.5f}},
		{{ 0.5f,  0.5f, -0.5f}},
		{{ 0.5f, -0.5f, -0.5f}},

		// Top (+Y)
		{{-0.5f,  0.5f,  0.5f}},
		{{-0.5f,  0.5f, -0.5f}},
		{{ 0.5f,  0.5f, -0.5f}},
		{{ 0.5f,  0.5f,  0.5f}},

		// Bottom (-Y)
		{{-0.5f, -0.5f, -0.5f}},
		{{-0.5f, -0.5f,  0.5f}},
		{{ 0.5f, -0.5f,  0.5f}},
		{{ 0.5f, -0.5f, -0.5f}},
	};

	static const ui32 indexList[] =
	{
		 0,  2,  1,   0,  3,  2,   // Front
		 4,  6,  5,   4,  7,  6,   // Back
		 8, 10,  9,   8, 11, 10,   // Left
		12, 14, 13,  12, 15, 14,   // Right
		16, 18, 17,  16, 19, 18,   // Top
		20, 22, 21,  20, 23, 22    // Bottom
	};


	static const auto vb = m_context.device.createVertexBuffer({ vertexList, std::size(vertexList), sizeof(Vertex) });
	static const auto ib = m_context.device.createIndexBuffer({ indexList, std::size(indexList) });

	m_vb = vb;
	m_ib = ib;
}

void dx3d::CubeComponent::setMaterial(const RefPtr<MaterialResource>& material)
{
	m_material = material;
}

dx3d::MaterialResource* dx3d::CubeComponent::getMaterial()
{
	return m_material.get();
}

dx3d::VertexBuffer& dx3d::CubeComponent::getVertexBuffer()
{
	return *m_vb;
}

dx3d::IndexBuffer& dx3d::CubeComponent::getIndexBuffer()
{
	return *m_ib;
}
