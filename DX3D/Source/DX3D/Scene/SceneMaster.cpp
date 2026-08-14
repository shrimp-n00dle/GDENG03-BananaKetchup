#include <DX3D/Scene/SceneMaster.h>


dx3d::SceneMaster::SceneMaster()
{
}

dx3d::SceneMaster::~SceneMaster()
{
}

void dx3d::SceneMaster::saveScene(const std::unordered_map<size_t, std::vector<UniquePtr<GameObject>>>& Objlist)
{

	//string filepath = this->getFilePath() + ".json";

	//TEST MUNA
	string filepath = "vingno_test_banana.json";

	ofstream myfile;
	myfile.open(filepath, std::ios::out);
	std::cout << "Selected filename is is " << filepath << std::endl;

	//PRIMITIVES
	//int i = 0;
	// for (const auto& [Listsize, obj] : Objlist) {
	//	 //name
	//	 myfile << obj[i]->objName << std::endl;

	//}
	
	// PRIMITIVES: Iterate through map, then iterate through each vector
	for (const auto& [listsize, objVector] : Objlist) {
		for (const auto& gameObj : objVector) {
			if (gameObj) { // Always good practice to check if the unique_ptr is valid
				myfile << gameObj->objName << std::endl;

				//POSITION
				myfile << "POSITION" <<
					gameObj->getTransform().getPosition().x << " " <<
					gameObj->getTransform().getPosition().y << " " <<
					gameObj->getTransform().getPosition().z << std::endl;


				//ROTATION
				myfile << "ROTATION" <<
					gameObj->getTransform().getRotation().x << " " <<
					gameObj->getTransform().getRotation().y << " " <<
					gameObj->getTransform().getRotation().z << std::endl;


				//SCALE
				myfile << "SCALE" <<
					gameObj->getTransform().getScale().x << " " <<
					gameObj->getTransform().getScale().y << " " <<
					gameObj->getTransform().getScale().z << std::endl;
			}
		}
	}


	//for (int i = 0; i < Objlist.size(); i++)
	//{
	//	//Object Name
	//	myfile << Objlist. << std::endl;
	//	Vec3 position = Objlist

	//}


	//OBJ/Mesh Objects

	//Physics Objects

	myfile.close();
	std::cout << "FILE NAMED " << filepath << " SAVED!" << std::endl;
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




