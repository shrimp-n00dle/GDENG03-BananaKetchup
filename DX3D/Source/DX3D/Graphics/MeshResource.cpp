#include <DX3D/Graphics/MeshResource.h>



dx3d::MeshResource::MeshResource(const MeshResourceDesc& desc) : Resource(desc.base)
{

}

dx3d::Mesh& dx3d::MeshResource::getMesh()
{
    return *m_mesh;
}
