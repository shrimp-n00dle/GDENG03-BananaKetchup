#include <DX3D/Graphics/MeshResource.h>


#define TINYOBJLOADER_IMPLEMENTATION
#include <tiny_obj_loader.h>
#include <locale>
#include <codecvt>

#include <DX3D/Graphics/GraphicsDevice.h>

dx3d::MeshResource::MeshResource(const wchar_t* path)
//dx3d::MeshResource::MeshResource(const MeshResourceDesc& desc) : Resource(desc.base)
{
    tinyobj::attrib_t attribs;
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> materials;

    std::string warn;
    std::string err;

    std::string inputfile = std::wstring_convert<std::codecvt_utf8<wchar_t>>().to_bytes(path);
    bool res =  tinyobj::LoadObj(&attribs,&shapes, &materials, &warn,&err, inputfile.c_str());

   if (!err.empty()) throw std::exception("MESH IS NOT CREATED #1");
   if (!res) throw std::exception("MESH IS NOT CREATED #2");
   if (shapes.size() > 1) throw std::exception("MESH IS NOT CREATED #3");

   for (size_t s = 0; s < shapes.size(); s++)
   {
       size_t index_offset = 0;
       
       for (size_t f = 0; f < shapes[s].mesh.num_face_vertices.size(); f++)
       {
           unsigned char num_face_verts = shapes[s].mesh.num_face_vertices[f];

           for (unsigned char v = 0; v < num_face_verts; v++)
           {
               tinyobj::index_t index = shapes[s].mesh.indices[index_offset + v];

               //Vertices
               tinyobj::real_t vx = attribs.vertices[index.vertex_index*3 + 0];
               tinyobj::real_t vy = attribs.vertices[index.vertex_index*3 + 1];
               tinyobj::real_t vz = attribs.vertices[index.vertex_index*3 + 2];


               //Textures
               tinyobj::real_t tx = attribs.texcoords[index.texcoord_index * 2 + 0];
               tinyobj::real_t ty = attribs.texcoords[index.texcoord_index * 2 + 1];
           }

           index_offset += num_face_verts;
       }
   }

   GraphicsDevice::createVertexBuffer();
}




dx3d::Mesh& dx3d::MeshResource::getMesh()
{
    return *m_mesh;
}

//void dx3d::MeshResource::setPath(std::string _path)
//{
//  // std::string inputfile = std::wstring_convert<std::codecvt_utf8<wchar_t>>().to_bytes(_path);
//   // path = inputfile;
//}
