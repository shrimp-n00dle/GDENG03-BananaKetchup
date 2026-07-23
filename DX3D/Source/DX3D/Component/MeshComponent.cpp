#include <DX3D/Component/MeshComponent.h>
#include <DX3D/Game/World.h>
#include <DX3D/Math/Vec3.h>
#include <DX3D/Math/Vec2.h>
#include <DX3D/Math/Mat4x4.h>
#include <DX3D/Graphics/GraphicsDevice.h>

#define TINYOBJLOADER_IMPLEMENTATION
#include <tiny_obj_loader.h>
#include <locale>
#include <codecvt>

dx3d::MeshComponent::MeshComponent(const ComponentDesc& data) : Component(data)
{
    tinyobj::attrib_t attribs;
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> materials;

    std::string warn;
    std::string err;

    std::string inputfile = std::wstring_convert<std::codecvt_utf8<wchar_t>>().to_bytes(path);
    bool res = tinyobj::LoadObj(&attribs, &shapes, &materials, &warn, &err, inputfile.c_str());

    if (!err.empty()) throw std::exception("MESH IS NOT CREATED #1");
    if (!res) throw std::exception("MESH IS NOT CREATED #2");
    if (shapes.size() > 1) throw std::exception("MESH IS NOT CREATED #3");

    struct Vertex
    {
        Vec3 position;
        Vec2 texCoord;
    };

    std::vector<Vertex> list_vertices;


    for (size_t s = 0; s < shapes.size(); s++)
    {
        size_t index_offset = 0;
        list_vertices.reserve(shapes[s].mesh.indices.size());

        for (size_t f = 0; f < shapes[s].mesh.num_face_vertices.size(); f++)
        {
            unsigned char num_face_verts = shapes[s].mesh.num_face_vertices[f];

            for (unsigned char v = 0; v < num_face_verts; v++)
            {
                tinyobj::index_t index = shapes[s].mesh.indices[index_offset + v];

                //Vertices
                tinyobj::real_t vx = attribs.vertices[index.vertex_index * 3 + 0];
                tinyobj::real_t vy = attribs.vertices[index.vertex_index * 3 + 1];
                tinyobj::real_t vz = attribs.vertices[index.vertex_index * 3 + 2];


                //Textures
                tinyobj::real_t tx = attribs.texcoords[index.texcoord_index * 2 + 0];
                tinyobj::real_t ty = attribs.texcoords[index.texcoord_index * 2 + 1];

                Vertex mesh_v(Vec3(vx, vy, vz), Vec2(tx, ty));
                list_vertices.push_back(mesh_v);
            }

            index_offset += num_face_verts;
        }
    }

	static const auto vb = m_context.device.createVertexBuffer({&list_vertices, std::size(list_vertices), sizeof(Vertex) });
	//static const auto ib = m_context.device.createIndexBuffer({ indexList, std::size(indexList) });

	m_vb = vb;
	//m_ib = ib;
}

void dx3d::MeshComponent::setMaterial(const RefPtr<MaterialResource>& material)
{
	m_material = material;
}

dx3d::MaterialResource* dx3d::MeshComponent::getMaterial()
{
	return m_material.get();
}

dx3d::VertexBuffer& dx3d::MeshComponent::getVertexBuffer()
{
	return *m_vb;
}

dx3d::IndexBuffer& dx3d::MeshComponent::getIndexBuffer()
{
	return *m_ib;
}
