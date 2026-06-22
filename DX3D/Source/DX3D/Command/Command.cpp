#include <DX3D/Command/Command.h>

void dx3d::Command::promptList()
{
	std::system("cls");
	std::cout << "COMMAND QUEUE" << std::endl;

	//print out queues here

}

void dx3d::SpawnCommand::execute(GraphicsEngine& g)
{
	g.callSpawn();
	promptList();
}
void dx3d::SpawnCommand::undo(GraphicsEngine& g)
{
	g.removeRecent();
	promptList();
}

void dx3d::DeleteCommand::execute(GraphicsEngine& g)
{
	g.removeRecent();
	promptList();
}

void dx3d::DeleteCommand::undo(GraphicsEngine& g)
{
	promptList();
}

void dx3d::EndCommand::execute(GraphicsEngine& g)
{
	g.closeProgram();
	promptList();
}
void dx3d::EndCommand::undo(GraphicsEngine& g)
{
	promptList();
}
