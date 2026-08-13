#include <DX3D/Component/CapsuleComponent.h>
#include <DX3D/Game/World.h>
#include <DX3D/Math/Vec3.h>
#include <DX3D/Math/Vec2.h>
#include <DX3D/Math/Mat4x4.h>
#include <DX3D/Graphics/GraphicsDevice.h>

#include <DirectXMath.h>

dx3d::CapsuleComponent::CapsuleComponent(const ComponentDesc& data) : Component(data)
{
	//CREATE CYLINDER
	std::vector<Vertex>  cy_list;
	std::vector<ui32> cy_indices;
	float height = 20, stackCount = 20, sliceCount = 20;
	float topRadius = 1.0f, bottomRadius = 1.0f;

	float stackHeight = height / stackCount;
	float radiusStep = (topRadius - bottomRadius) / stackCount;
	UINT ringCount = stackCount + 1;


	for (UINT i = 0; i < ringCount; ++i) {
		float y = -0.5f * height + i * stackHeight;
		float r = bottomRadius + i * radiusStep;


		float dTheta = 2.0f * DirectX::XM_PI / sliceCount;
		for (UINT j = 0; j <= sliceCount; ++j) {
			float c = cosf(j * dTheta);
			float s = sinf(j * dTheta);


			Vertex v;
			v.position = { r * c, y, r * s };
			// Normals and UVs can be calculated here for lighting and texturing
		   // v.Normal = DirectX::XMFLOAT3(c, 0.0f, s); // simplified
		   // v.TexCoord = DirectX::XMFLOAT2((float)j / sliceCount, (float)i / stackCount);
			//v.color = randomizeColor();


			cy_list.push_back(v);
		}
	}


	// Add indices for the cylinder body
	UINT ringVertexCount = sliceCount + 1;
	for (UINT i = 0; i < stackCount; ++i) {
		for (UINT j = 0; j < sliceCount; ++j) {
			cy_indices.push_back(i * ringVertexCount + j);
			cy_indices.push_back((i + 1) * ringVertexCount + j);
			cy_indices.push_back(i * ringVertexCount + j + 1);

			cy_indices.push_back(i * ringVertexCount + j + 1);
			cy_indices.push_back((i + 1) * ringVertexCount + j);
			cy_indices.push_back((i + 1) * ringVertexCount + j + 1);
		}
	}
	//BOTTOM AND TOP CAP
		 // --- BOTTOM CAP ---
	UINT bottomCapStartIndex = (UINT)cy_list.size();
	float yBottom = -0.5f * height;


	// 1. Center vertex for the bottom cap
	Vertex bottomCenter;
	bottomCenter.position = { 0.0f, yBottom, 0.0f };
	//bottomCenter.Normal = DirectX::XMFLOAT3(0.0f, -1.0f, 0.0f);
	//bottomCenter.TexCoord = DirectX::XMFLOAT2(0.5f, 0.5f);
	cy_list.push_back(bottomCenter);


	// 2. Ring vertices for the bottom cap
	float dTheta = 2.0f * DirectX::XM_PI / sliceCount;
	for (UINT i = 0; i <= sliceCount; ++i) {
		float c = cosf(i * dTheta);
		float s = sinf(i * dTheta);


		Vertex v;
		v.position = { bottomRadius * c, yBottom, bottomRadius * s };
		//v.color = randomizeColor();
		// v.Normal = DirectX::XMFLOAT3(0.0f, -1.0f, 0.0f);
		 // Map texture coordinates to a flat circle
		// v.TexCoord = DirectX::XMFLOAT2(0.5f + 0.5f * c, 0.5f + 0.5f * s);
		cy_list.push_back(v);
	}


	// 3. Bottom cap indices (Clockwise winding order looking from below)
	for (UINT i = 0; i < sliceCount; ++i) {
		cy_indices.push_back(bottomCapStartIndex);
		cy_indices.push_back(bottomCapStartIndex + 1 + i + 1);
		cy_indices.push_back(bottomCapStartIndex + 1 + i);
	}


	// --- TOP CAP ---
	UINT topCapStartIndex = (UINT)cy_list.size();
	float yTop = 0.5f * height;


	// 1. Center vertex for the top cap
	Vertex topCenter;
	topCenter.position = { 0.0f, yTop, 0.0f };
	//topCenter.color = randomizeColor();
	//topCenter.Normal = DirectX::XMFLOAT3(0.0f, 1.0f, 0.0f);
   // topCenter.TexCoord = DirectX::XMFLOAT2(0.5f, 0.5f);
	cy_list.push_back(topCenter);


	// 2. Ring vertices for the top cap
	for (UINT i = 0; i <= sliceCount; ++i) {
		float c = cosf(i * dTheta);
		float s = sinf(i * dTheta);


		Vertex v;
		v.position = { topRadius * c, yTop, topRadius * s };
		//v.color = randomizeColor();
		// v.Normal = DirectX::XMFLOAT3(0.0f, 1.0f, 0.0f);
		 // Map texture coordinates to a flat circle
		// v.TexCoord = DirectX::XMFLOAT2(0.5f + 0.5f * c, 0.5f + 0.5f * s);
		cy_list.push_back(v);
	}


	// 3. Top cap indices (Clockwise winding order looking from above)
	for (UINT i = 0; i < sliceCount; ++i) {
		cy_indices.push_back(topCapStartIndex);
		cy_indices.push_back(topCapStartIndex + 1 + i);
		cy_indices.push_back(topCapStartIndex + 1 + i + 1);
	}

	//std::cout << "CYLINDER SIZE IS " << cy_list.size() << std::endl;
	//std::cout << "CYLINDER INDCIDED SIZE IS " << cy_indices.size() << std::endl;


	Vertex cy_vertices[485];

	/* for (int i = 0; i < cy_list.size(); i++)
	 {
		 cy_vertices[i] = cy_list[i];
	 }*/

	ui32 cy_i[2520];

	/* for (int i = 0; i < cy_indices.size(); i++)
	 {
		 cy_i[i] = cy_indices[i];
	 }*/
	 //Cylinder Stuff
	 /*m_vb_cylinder = device.createVertexBuffer({ cy_vertices, std::size(cy_vertices), sizeof(Vertex) });
	 m_ib_cylinder = device.createIndexBuffer({ cy_i, std::size(cy_i) });*/


	static const auto vb = m_context.device.createVertexBuffer({ cy_vertices, std::size(cy_vertices), sizeof(Vertex) });
	static const auto ib = m_context.device.createIndexBuffer({ cy_i, std::size(cy_i) });

	m_vb = vb;
	m_ib = ib;


}

void dx3d::CapsuleComponent::setMaterial(const RefPtr<MaterialResource>& material)
{
	m_material = material;
}

dx3d::MaterialResource* dx3d::CapsuleComponent::getMaterial()
{
	return m_material.get();
}

dx3d::VertexBuffer& dx3d::CapsuleComponent::getVertexBuffer()
{
	return *m_vb;
}

dx3d::IndexBuffer& dx3d::CapsuleComponent::getIndexBuffer()
{
	return *m_ib;
}
