#include "Spawner.h"
#include <iterator>


catsup::Spawner::Spawner(const SpawnerDesc& desc) : Base(desc.base)
{
}

catsup::Spawner::~Spawner()
{
}

VertexBufferPtr catsup::Spawner::bakeShapes(int index, RenderSystem& device, std::vector<VertexBufferPtr> indexList,
	DeviceContext& context)
{
	VertexBufferPtr vb{};
		

		for (int i = 0; i < indexList.size(); i++)
		{
			indexList.at(i) = device.createVertexBuffer({ vertextList, std::size(vertextList), sizeof(Vertex) });
		}

		//Message prompt
		std::cout << "List size is# " << indexList.size()  << " printed!" << std::endl;

		copyData data;
		data.newPos = DirectX::XMFLOAT3(0.1, 0.1, 0.0);
		D3D11_MAPPED_SUBRESOURCE mappedResource;
		Microsoft::WRL::ComPtr<ID3D11Resource> copyBuffer = indexList.at(0)->getBuffer().Get();
		context.getContext()->Map(copyBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
		CopyMemory(mappedResource.pData, &data, sizeof(copyData));
		context.getContext()->Unmap(cBuffer.m_buffer.Get(),0);

		//Microsoft::WRL::ComPtr<ID3D11Resource> copyBuffer = indexList.at(0)->getBuffer().Get();
		//context.getContext()->UpdateSubresource(copyBuffer.Get(), 0, nullptr, &data, 0, 0);
		context.getContext()->VSSetConstantBuffers(0, 1, cBuffer.m_buffer.GetAddressOf());

	return vb;
}

void catsup::Spawner::decoShapes(VertexBufferPtr vb,DeviceContext& context, std::vector<VertexBufferPtr> indexList)
{
	auto& copyA = *vb;
	context.setVertexBuffer(copyA);
	context.drawTriangleList(copyA.getVertexListSize(), 0u);

	auto& copyB = *cBuffer;
	context.setVertexBuffer(copyB);
	context.drawTriangleList(copyB.getVertexListSize(), 0u);
}



