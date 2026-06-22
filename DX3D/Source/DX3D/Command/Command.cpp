#include <DX3D/Command/Command.h>

void dx3d::SpawnCommand::execute(GraphicsEngine& g)
{
	g.callSpawn();
}

void dx3d::DeleteCommand::execute(GraphicsEngine& g)
{
	g.removeRecent();
}
