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

#include <cwchar>
#include <clocale>
#include <cstdlib> 

dx3d::MeshResource::MeshResource(const MeshResourceDesc& desc) : Resource(desc.base)
{
    tinyobj::attrib_t attribs;
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> materials;

    std::string warn;
    std::string err;

    //PATH
    if (desc.base.path == nullptr) std::cout << "PARH IS NULL" << std::endl;


    //OPTION 1
    //// Step 1: Calculate the buffer size needed (passing nullptr as the destination)
    //size_t requiredSize = 0;
    //errno_t err = wcstombs_s(&requiredSize, nullptr, 0, desc.base.path, 0);

    //if (err != 0 || requiredSize == 0) {
    //    std::cout << "Conversion failed or string is empty" << std::endl;
    //    //return ""; // Conversion failed or string is empty
    //}

    //// Step 2: Allocate a temporary buffer for the narrow character data
    //std::string resultStr;
    //resultStr.resize(requiredSize - 1); // Size includes null terminator, std::string handles it automatically

    //// Step 3: Perform the actual conversion into the std::string buffer space
    //size_t convertedChars = 0;
    //err = wcstombs_s(&convertedChars, &resultStr[0], requiredSize, desc.base.path, _TRUNCATE);

    //if (err != 0) {
    //    std::cout << "Conversion failed" << std::endl;
    //   //return ""; // Conversion failed
    //}

    //OPTION 2
      // Determine the required buffer size
    size_t convertedChars = 0;
    size_t bufferSize = 0;
    wcstombs_s(&bufferSize, nullptr, 0, desc.base.path, _TRUNCATE);

    // Allocate buffer for the multibyte string
    std::vector<char> buffer(bufferSize);

    // Convert wide-character string to multibyte
    wcstombs_s(&convertedChars, buffer.data(), bufferSize, desc.base.path, _TRUNCATE);

    std::string resultStr = std::string(buffer.data());


    std::cout << "PATH IS " + resultStr << std::endl;

    bool res = tinyobj::LoadObj(&attribs, &shapes, &materials, &warn, &err, resultStr.c_str());
    if (!res)
    {
        DX3DLogThrowError("LoadObj did not work", resultStr.c_str());
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

    int index = 0;


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
                std::cout << index << std::endl;
                index++;

                tinyobj::index_t index = shapes[s].mesh.indices[index_offset + v];

                //Vertices
                tinyobj::real_t vx = attribs.vertices[index.vertex_index * 3 + 0];
                tinyobj::real_t vy = attribs.vertices[index.vertex_index * 3 + 1];
                tinyobj::real_t vz = attribs.vertices[index.vertex_index * 3 + 2];


                //Textures
                tinyobj::real_t tx = attribs.texcoords[index.texcoord_index * 2 + 0];
                tinyobj::real_t ty = attribs.texcoords[index.texcoord_index * 2 + 1];

                Vertex mesh_v(Vec3(vx, vy, vz), Vec2(0, 0));
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