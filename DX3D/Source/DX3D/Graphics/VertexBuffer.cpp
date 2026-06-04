#include <DX3D/Graphics/VertexBuffer.h>

dx3d::VertexBuffer::VertexBuffer(const VertexBufferDesc& desc, const GraphicsResourceDesc& gDesc) :
	GraphicsResource(gDesc), m_vertexSize(desc.vertexSize), m_vertextListSize(desc.vertexListSize)
{
	if (!desc.vertexList) DX3DLogThrowInvalidArg("No vertex list provided. From VB.cpp");
	if (!desc.vertexListSize) DX3DLogThrowInvalidArg("Vertex list size must be non-zero. From VB.cpp");
	if (!desc.vertexSize)DX3DLogThrowInvalidArg("Vertex size must be non-zero. From VB.cpp");
	
	D3D11_BUFFER_DESC buffDesc{};
	buffDesc.ByteWidth = desc.vertexListSize * desc.vertexSize;
	buffDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

	D3D11_SUBRESOURCE_DATA initData{};
	initData.pSysMem = desc.vertexList;

	DX3DGraphicsLogErrorAndThrow(
		m_device.CreateBuffer(&buffDesc, &initData, &m_buffer),
		"CreateBuffer() failed  from VertexeBUffer.cpp");
}

dx3d::ui32 dx3d::VertexBuffer::getVertexListSize() const noexcept
{
	return m_vertextListSize;
}

Microsoft::WRL::ComPtr<ID3D11Buffer> dx3d::VertexBuffer::getBuffer()
{
	return m_buffer;
}

int dx3d::VertexBuffer::TEST()
{
	return 0;
}

