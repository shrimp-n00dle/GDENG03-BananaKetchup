#include "Spawner.h"

catsup::Spawner::Spawner(const SpawnerDesc& desc) : Base(desc.base)
{
}

catsup::Spawner::~Spawner()
{
}

void catsup::Spawner::bakeShapes(int index, RenderSystem& device)
{
	for (int i = 0; i < index; i++)
	{
	//Create the shape
	//const Vertex vertextList[] =
	//{
	//	//Position            //Color
	//	{ {-0.25f,-0.25f,0.0f}, {1,0,0,1} },
	//	{ {-0.25f,0.25f,0.0f},  {0,1,0,1} },
	//	{ {0.25f,0.25f,0.0f},   {0,0,1,1} },

	//	
	//	{ {0.25f,0.25f,0.0f},   {0,0,1,1} },
	//	{ {0.25f,-0.25f,0.0f},  {0,0,1,1} },
	//	{ {-0.25f,-0.25f,0.0f}, {1,0,0,1} }
	//};

	//Add it to the VertexBufferPtr
	//m_vb = device.createVertexBuffer({ vertextList, std::size(vertextList), sizeof(Vertex) });

	//Add to buffer list
	//bufferList.push_back(m_vb);

	//Message prompt
	std::cout << "Shape number# " << i + 1 << " printed!" << std::endl;
	}
}



