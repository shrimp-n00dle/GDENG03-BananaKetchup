#include <DX3D/Scene/SceneMaster.h>


dx3d::SceneMaster::SceneMaster()
{
}

dx3d::SceneMaster::~SceneMaster()
{
}

void dx3d::SceneMaster::saveScene()
{

	std::cout << "CALLING WORKD" << std::endl;
	//string filepath = this->getFilePath() + ".json";

	//ofstream myfile;
	//myfile.open(filepath, std::ios::out);
	//std::cout << "Selected filename is is " << filepath << std::endl;

	////PRIMITIVES

	////OBJ/Mesh Objects

	////Physics Objects

	//myfile.close();
	//std::cout << "FILE NAMED " << filepath << " SAVED!" << std::endl;
}

void dx3d::SceneMaster::loadScene()
{
}

string dx3d::SceneMaster::getFilePath()
{
	return curr_path;
}

void dx3d::SceneMaster::setFilePath(string path)
{
	curr_path = path;
}




