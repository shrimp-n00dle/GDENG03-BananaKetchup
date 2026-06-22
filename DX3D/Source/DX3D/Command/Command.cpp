#include <DX3D/Command/Command.h>

void dx3d::Command::promptList()
{
	std::system("cls");
	std::cout << "COMMAND QUEUE" << std::endl;
	std::cout << "SIZE IS " << queueList.size() << std::endl;

	//print out queues here
	for (int i = 0; i < queueList.size(); i++)
	{
		std::cout << i+1 << ". " << queueList[i] << std::endl;
	}

}

void dx3d::SpawnCommand::execute(GraphicsEngine& g)
{
	g.callSpawn();
	

	//Command Queue
	queueList.push_back("[SPACEBAR] Cube summoned.");
	promptList();
}
void dx3d::SpawnCommand::undo(GraphicsEngine& g)
{
	g.removeRecent();

	//Command Queue
	queueList.push_back("[BACKSPACE] Cube removed.");
	promptList();
}

void dx3d::DeleteCommand::execute(GraphicsEngine& g)
{
	g.removeRecent();

	//Command Queue
	queueList.push_back("[BACKSPACE] Cube removed.");
	promptList();
}

void dx3d::DeleteCommand::undo(GraphicsEngine& g)
{
	promptList();
}

void dx3d::EndCommand::execute(GraphicsEngine& g)
{
	g.closeProgram();

	//Command Queue
	queueList.push_back("[ESCAPE] Program Terminated.");
	promptList();
	
}
void dx3d::EndCommand::undo(GraphicsEngine& g)
{
	promptList();
}
