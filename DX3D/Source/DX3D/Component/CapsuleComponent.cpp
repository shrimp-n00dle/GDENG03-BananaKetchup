#include <DX3D/Component/CapsuleComponent.h>
#include <DX3D/Game/World.h>
#include <DX3D/Math/Vec3.h>
#include <DX3D/Math/Vec2.h>
#include <DX3D/Math/Mat4x4.h>
#include <DX3D/Graphics/GraphicsDevice.h>

#include <DirectXMath.h>
#include <iostream>

dx3d::CapsuleComponent::CapsuleComponent(const ComponentDesc& data) : Component(data)
{
    float totalHeight = 6.0f;
    float radius = 1.5f;
    uint32_t sliceCount = 24;
    uint32_t stackCount = 12;

    std::vector<Vertex> vertices;
    std::vector<uint32_t> indices;

    float cylinderHeight = totalHeight - 2.0f * radius;
    if (cylinderHeight < 0.0f) cylinderHeight = 0.0f;

    float dTheta = 2.0f * DirectX::XM_PI / sliceCount;
    float dPhi = DirectX::XM_PIDIV2 / stackCount;

    // --- 1. Bottom Hemisphere ---
    float yBottomCenter = -0.5f * cylinderHeight;
    for (uint32_t i = 0; i <= stackCount; ++i) {
        float phi = DirectX::XM_PIDIV2 + i * dPhi;
        float sinPhi = sinf(phi);
        float cosPhi = cosf(phi);

        float y = yBottomCenter + radius * cosPhi;
        float r = radius * sinPhi;

        for (uint32_t j = 0; j <= sliceCount; ++j) {
            float theta = j * dTheta;
            float c = cosf(theta);
            float s = sinf(theta);

            Vertex v;
            v.position = { r * c, y, r * s };
            vertices.push_back(v);
        }
    }

    // --- 2. Cylinder Top Ring ---
    float yTopCenter = 0.5f * cylinderHeight;
    for (uint32_t j = 0; j <= sliceCount; ++j) {
        float theta = j * dTheta;
        float c = cosf(theta);
        float s = sinf(theta);

        Vertex v;
        v.position = { radius * c, yTopCenter, radius * s };
        vertices.push_back(v);
    }

    // --- 3. Top Hemisphere ---
    for (uint32_t i = 1; i <= stackCount; ++i) {
        float phi = DirectX::XM_PIDIV2 - i * dPhi;
        float sinPhi = sinf(phi);
        float cosPhi = cosf(phi);

        float y = yTopCenter + radius * cosPhi;
        float r = radius * sinPhi;

        for (uint32_t j = 0; j <= sliceCount; ++j) {
            float theta = j * dTheta;
            float c = cosf(theta);
            float s = sinf(theta);

            Vertex v;
            v.position = { r * c, y, r * s };;
            vertices.push_back(v);
        }
    }

    // --- 4. Indices Generation ---
    uint32_t ringVertexCount = sliceCount + 1;
    uint32_t totalRings = (stackCount + 1) + 1 + stackCount;
    uint32_t totalSegments = totalRings - 1;

    for (uint32_t i = 0; i < totalSegments; ++i) {
        for (uint32_t j = 0; j < sliceCount; ++j) {
            uint32_t i0 = i * ringVertexCount + j;
            uint32_t i1 = (i + 1) * ringVertexCount + j;
            uint32_t i2 = i * ringVertexCount + j + 1;
            uint32_t i3 = (i + 1) * ringVertexCount + j + 1;

            indices.push_back(i0); indices.push_back(i1); indices.push_back(i2);
            indices.push_back(i2); indices.push_back(i1); indices.push_back(i3);
        }
    }

    Vertex cy_vertices[650];

    int cyCount = 0;
    int inCount = 0;
    for (int i = 0; i < vertices.size(); i++)
     {
        cy_vertices[i] = vertices[i];
        cyCount++;
     }

    ui32 cy_i[3600];

    for (int i = 0; i < indices.size(); i++)
     {
         cy_i[i] = indices[i];
        inCount++;
     }

    std::cout << "TOTAL CYCOUNT IS " << cyCount << " AND TOTAL INCOUNT IS " << inCount << std::endl;

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
