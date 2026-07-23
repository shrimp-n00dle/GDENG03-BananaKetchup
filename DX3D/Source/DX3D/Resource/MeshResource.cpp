#include <DX3D/Resource/MeshResource.h>
#include <DX3D/Graphics/GraphicsDevice.h>

#include <DX3D/Math/Vec3.h>
#include <DX3D/Math/Vec2.h>

#define TINYOBJLOADER_DISABLE_FAST_FLOAT
#define TINYOBJLOADER_IMPLEMENTATION
#include <tiny_obj_loader.h>
#include <locale>
#include <codecvt>

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

dx3d::MeshResource::MeshResource(const MeshResourceDesc& desc) : Resource(desc.base)
{
    tinyobj::attrib_t attribs;
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> materials;

    std::string warn;
    std::string err;

    //PATH
    std::ifstream file(desc.base.path);

    if (!file.is_open()) std::cout << "OBJ PATH NOT FOUND" << std::endl;
    else  std::cout << "HELLO MESH" << std::endl;


   std::stringstream buffer;
   buffer << file.rdbuf(); // Read the file buffer into the stringstream

    std::string path = buffer.str(); // Convert to std::string
    //std::string path = "Game/Assets/Models/teapot.obj";

    //std::string inputfile = std::wstring_convert<std::codecvt_utf8<wchar_t>>().to_bytes(path);
    bool res = tinyobj::LoadObj(&attribs, &shapes, &materials, &warn, &err, path.c_str());
    if (!res)
    {
        DX3DLogThrowError("LoadObj did not work", path.c_str());
    }

    if (!err.empty()) throw std::exception("MESH IS NOT CREATED #1");

    if (shapes.size() > 1) throw std::exception("MESH IS NOT CREATED #2");


    struct Vertex
    {
        Vec3 position;
        Vec2 texCoord;
    };

    std::vector<Vertex> vertices_count;
    std::vector<ui32> indices_count;


    for (size_t s = 0; s < shapes.size(); s++)
    {
        size_t index_offset = 0;
        vertices_count.reserve(shapes[s].mesh.indices.size());
        indices_count.reserve(shapes[s].mesh.indices.size());

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
                vertices_count.push_back(mesh_v);

                indices_count.push_back(index_offset + v);
            }

            index_offset += num_face_verts;
        }
    }


    std::cout << "VERICTES COUNT IS " + vertices_count.size() << std::endl;
    std::cout << "INDICES COUNT IS " + indices_count.size() << std::endl;

    Vertex mesh_vertices[2503];

    for (int i = 0; i < vertices_count.size(); i++)
    {
        mesh_vertices[i] = vertices_count[i];
    }

    ui32 mesh_indices[4968];
    for (int i = 0; i < indices_count.size(); i++)
    {
        mesh_indices[i] = indices_count[i];
    }


    m_vertex_buffer = desc.graphicsDevice.createVertexBuffer({mesh_vertices, std::size(mesh_vertices), sizeof(Vertex)});
    m_index_buffer = desc.graphicsDevice.createIndexBuffer({ mesh_indices, std::size(mesh_indices) });


}