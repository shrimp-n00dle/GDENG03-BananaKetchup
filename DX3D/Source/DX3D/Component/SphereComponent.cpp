#include <DX3D/Component/SphereComponent.h>
#include <DX3D/Game/World.h>
#include <DX3D/Math/Vec3.h>
#include <DX3D/Math/Vec2.h>
#include <DX3D/Math/Mat4x4.h>
#include <DX3D/Graphics/GraphicsDevice.h>

#include <iostream>
#include <DirectXMath.h>


dx3d::SphereComponent::SphereComponent(const ComponentDesc& data) : Component(data)
{

	std::vector<Vertex>  sphere_list;
	std::vector<ui32> sphere_indices;
	float radius = 0.1f;
	int numSlices = 20;
	int numStacks = 20;

	for (int i = 0; i <= numStacks; ++i) {
		float phi = i * DirectX::XM_PI / numStacks;


		for (int j = 0; j <= numSlices; ++j) {
			float theta = j * (2.0f * DirectX::XM_PI) / numSlices;


			Vertex sphere;
			sphere.position = { (radius * sinf(phi) * cosf(theta)),
								 (radius * cosf(phi)),
								(radius * sinf(phi) * sinf(theta)) };




			//sphere.color = randomizeColor();


			sphere_list.push_back(sphere);
		}
	}


	std::cout << "SPHERE LIST SIZE IS: " << sphere_list.size() << std::endl;


	//Sphere Indices
	for (int i = 0; i < numStacks; ++i) {
		for (int j = 0; j < numSlices; ++j) {
			int current = i * (numSlices + 1) + j;
			int next = current + numSlices + 1;


			// Triangle 1
			sphere_indices.push_back(current);
			sphere_indices.push_back(next);
			sphere_indices.push_back(current + 1);


			// Triangle 2
			sphere_indices.push_back(current + 1);
			sphere_indices.push_back(next);
			sphere_indices.push_back(next + 1);
		}
	}


	std::cout << "SPHERE LIST SIZE IS: " << sphere_indices.size() << std::endl;



	Vertex sphere_vertices[441];


	for (int i = 0; i < sphere_list.size(); i++)
	{
		sphere_vertices[i] = sphere_list[i];
	}


	ui32 spheres_i[2400];


	for (int i = 0; i < sphere_indices.size(); i++)
	{
		spheres_i[i] = sphere_indices[i];
	}
	//Sphere Stuff
	//m_vb_sphere = device.createVertexBuffer({ sphere_vertices, std::size(sphere_vertices), sizeof(Vertex) });
	//m_ib_sphere = device.createIndexBuffer({ spheres_i, std::size(spheres_i) });




	//static const Vertex vertexList[] =
	//{
	//	// Front (+Z)
	//	{{-0.5f, -0.5f,  0.5f}},
	//	{{-0.5f,  0.5f,  0.5f}},
	//	{{ 0.5f,  0.5f,  0.5f}},
	//	{{ 0.5f, -0.5f,  0.5f}},

	//	// Back (-Z)
	//	{{ 0.5f, -0.5f, -0.5f}},
	//	{{ 0.5f,  0.5f, -0.5f}},
	//	{{-0.5f,  0.5f, -0.5f}},
	//	{{-0.5f, -0.5f, -0.5f}},

	//	// Left (-X)
	//	{{-0.5f, -0.5f, -0.5f}},
	//	{{-0.5f,  0.5f, -0.5f}},
	//	{{-0.5f,  0.5f,  0.5f}},
	//	{{-0.5f, -0.5f,  0.5f}},

	//	// Right (+X)
	//	{{ 0.5f, -0.5f,  0.5f}},
	//	{{ 0.5f,  0.5f,  0.5f}},
	//	{{ 0.5f,  0.5f, -0.5f}},
	//	{{ 0.5f, -0.5f, -0.5f}},

	//	// Top (+Y)
	//	{{-0.5f,  0.5f,  0.5f}},
	//	{{-0.5f,  0.5f, -0.5f}},
	//	{{ 0.5f,  0.5f, -0.5f}},
	//	{{ 0.5f,  0.5f,  0.5f}},

	//	// Bottom (-Y)
	//	{{-0.5f, -0.5f, -0.5f}},
	//	{{-0.5f, -0.5f,  0.5f}},
	//	{{ 0.5f, -0.5f,  0.5f}},
	//	{{ 0.5f, -0.5f, -0.5f}},
	//};

	//static const ui32 indexList[] =
	//{
	//	 0,  2,  1,   0,  3,  2,   // Front
	//	 4,  6,  5,   4,  7,  6,   // Back
	//	 8, 10,  9,   8, 11, 10,   // Left
	//	12, 14, 13,  12, 15, 14,   // Right
	//	16, 18, 17,  16, 19, 18,   // Top
	//	20, 22, 21,  20, 23, 22    // Bottom
	//};


	static const auto vb = m_context.device.createVertexBuffer({ sphere_vertices, std::size(sphere_vertices), sizeof(Vertex) });
	static const auto ib = m_context.device.createIndexBuffer({ spheres_i, std::size(spheres_i) });

	m_vb = vb;
	m_ib = ib;
}

void dx3d::SphereComponent::setMaterial(const RefPtr<MaterialResource>& material)
{
	m_material = material;
}

dx3d::MaterialResource* dx3d::SphereComponent::getMaterial()
{
	return m_material.get();
}

dx3d::VertexBuffer& dx3d::SphereComponent::getVertexBuffer()
{
	return *m_vb;
}

dx3d::IndexBuffer& dx3d::SphereComponent::getIndexBuffer()
{
	return *m_ib;
}
