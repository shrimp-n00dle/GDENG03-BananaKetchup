#include "Spawner.h"
#include <iterator> // Required for std::next

catsup::Spawner::Spawner(const SpawnerDesc& desc) : Base(desc.base)
{
}

catsup::Spawner::~Spawner()
{
}

VertexBufferPtr catsup::Spawner::bakeShapes(int index, RenderSystem& device)
{
	VertexBufferPtr vb{};
	for (int i = 0; i < index; i++)
	{
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

		//Message prompt
		std::cout << "Shape number# " << i + 1 << " printed!" << std::endl;
	};

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

void catsup::Spawner::decoShapes(VertexBufferPtr vb,DeviceContext& context)
{
	//std::list<VertexBufferPtr>* listPtr = &bufferList;
	//std::list<VertexBufferPtr&>::iterator i = listPtr.begin();
	auto& copy = *vb;
	context.setVertexBuffer(copy);
	context.drawTriangleList(copy.getVertexListSize(), 0u);

	//for (const auto& index : bufferList)
	//{
	//	context.setVertexBuffer(*index);
	////	//context.drawTriangleList(&m_vb.getVertexListSize(), 0u);
	//	context.drawTriangleList((*index).getVertexListSize(), 0u);
	//}
}



