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
    //tinyobj::attrib_t attribs;
    //std::vector<tinyobj::shape_t> shapes;
    //std::vector<tinyobj::material_t> materials;

    //std::string warn;
    //std::string err;

    ////PATH
    //if (desc.base.path == nullptr) std::cout << "PARH IS NULL" << std::endl;

    ////OPTION 2
    //size_t convertedChars = 0;
    //size_t bufferSize = 0;
    //wcstombs_s(&bufferSize, nullptr, 0, desc.base.path, _TRUNCATE);
    //std::vector<char> buffer(bufferSize);
    //wcstombs_s(&convertedChars, buffer.data(), bufferSize, desc.base.path, _TRUNCATE);
    //std::string resultStr = std::string(buffer.data());
    //std::cout << "PATH IS " + resultStr << std::endl;
    //bool res = tinyobj::LoadObj(&attribs, &shapes, &materials, &warn, &err, resultStr.c_str());
    //if (!res)
    //{
    //    DX3DLogThrowError("LoadObj did not work", resultStr.c_str());
    //}

    //if (!err.empty()) throw std::exception("MESH IS NOT CREATED #1");

    //if (shapes.size() > 1) throw std::exception("MESH IS NOT CREATED #2");

    std::vector<ui32> indices_count;

    int index = 0;
    std::ifstream file(desc.base.path);
    if (!file.is_open()) return;

    std::vector<Vec3> vectors;
    std::vector<ui32> indices;


    std::string line;
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string prefix;
        ss >> prefix;

        if (prefix == "v") {
            float x, y, z;
            ss >> x >> y >> z;
            vectors.push_back({ x, y, z });
        }

        else if (prefix == "f")
        {
            std::string vStr;
            for (int i = 0; i < 3; i++)
            {
                ss >> vStr;
                if (!vStr.empty())
                {
                    size_t slash = vStr.find('/');
                    int vIndex = std::stoi(vStr.substr(0,slash));
                    indices.push_back(static_cast<ui32>(vIndex - 1));
                }
            }
        }

    }


    std::vector<Vertex> vertices_count;
    for (auto& coords : vectors)
    {
        Vertex v{};
        v.position = coords;
        vertices_count.push_back(v);

    }

    m_mesh_buffer = desc.graphicsDevice.createMesh({vertices_count, indices});
}