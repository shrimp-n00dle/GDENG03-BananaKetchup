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
	int yes = 0;
		//Create the shape
		const Vertex vertextList[] =
		{
			//Position            //Color
			{ {-0.25f,-0.25f,0.0f}, {1,0,0,1} },
			{ {-0.25f,0.25f,0.0f},  {0,1,0,1} },
			{ {0.25f,0.25f,0.0f},   {0,0,1,1} },


			{ {0.25f,0.25f,0.0f},   {0,0,1,1} },
			{ {0.25f,-0.25f,0.0f},  {0,0,1,1} },
			{ {-0.25f,-0.25f,0.0f}, {1,0,0,1} }
		};

		vb = device.createVertexBuffer({ vertextList, std::size(vertextList), sizeof(Vertex) });

		for (int i = 0; i < indexList.size(); i++)
		{
			indexList.at(i) = device.createVertexBuffer({ vertextList, std::size(vertextList), sizeof(Vertex) });
		}

		//Message prompt
		std::cout << "List size is# " << indexList.size()  << " printed!" << std::endl;

		copyData data;
		data.newPos = DirectX::XMFLOAT3(0.01, 0.0, 0.0);

		Microsoft::WRL::ComPtr<ID3D11Resource> copyBuffer = indexList.at(0)->getBuffer().Get();
		context.getContext()->UpdateSubresource(copyBuffer.Get(), 0, nullptr, &data, 0, 0);
		context.getContext()->VSSetConstantBuffers(0, 1, indexList.at(0)->getBuffer().GetAddressOf());

	return vb;
}

void catsup::Spawner::addBuffer(VertexBufferPtr m_vb)
{
	bufferList.push_back(m_vb);
	std::cout << "LIST SIZE IS " << bufferList.size() << std::endl;
}

VertexBufferPtr catsup::Spawner::getList()
{
	return bufferList[0];
}

void catsup::Spawner::decoShapes(VertexBufferPtr vb,DeviceContext& context, std::vector<VertexBufferPtr> indexList)
{
	auto& copyA = *vb;
	context.setVertexBuffer(copyA);
	context.drawTriangleList(copyA.getVertexListSize(), 0u);

	auto& copyB = *indexList.at(0);
	context.setVertexBuffer(copyB);
	context.drawTriangleList(copyB.getVertexListSize(), 0u);
}



