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
	VertexBufferPtr test{};
	bool bTesting = true;

	if (bTesting)
	{
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

			
			//Add it to the VertexBufferPtr
			//m_vb =

			test = device.createVertexBuffer({ vertextList, std::size(vertextList), sizeof(Vertex) });

			//Add to buffer list
			//bufferList.push_back(m_vb);

			//Message prompt
			std::cout << "Shape number# " << i + 1 << " printed!" << std::endl;
		}
	};

	return test;
}

void catsup::Spawner::addBuffer(VertexBufferPtr m_vb)
{
	bufferList.push_back(m_vb);
}

void catsup::Spawner::decoShapes(DeviceContext& context)
{
	//std::list<VertexBufferPtr>* listPtr = &bufferList;
	//std::list<VertexBufferPtr&>::iterator i = listPtr.begin();
	//auto& vb = bufferList.begin();//std::next(bufferList.begin(), 0);
	//context.setVertexBuffer(vb);
	//context.drawTriangleList(vb.getVertexListSize(), 0u);

	//for (const auto& index : bufferList)
	//{
	//	context.setVertexBuffer(*index);
	////	//context.drawTriangleList(&m_vb.getVertexListSize(), 0u);
	//	context.drawTriangleList((*index).getVertexListSize(), 0u);
	//}
}



