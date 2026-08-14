#pragma once

#include <DX3D/Core/Core.h>
//#include <DX3D/All.h>
#include <DX3D/Game/Component.h>
#include <DX3D/Component/TransformComponent.h>
#include <DX3D/Component/CubeComponent.h>
#include <DX3D/Component/SphereComponent.h>
#include <DX3D/Component/CapsuleComponent.h>
#include <unordered_map>
#include <DX3D/Game/GameObject.h>



//file reader headers
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

#include <json\json.h>

//math stuff
#include <DX3D/Math/Vec3.h>

#include <DX3D/Game/World.h>

namespace dx3d {
	class SceneMaster
	{
	public:
		SceneMaster();
		~SceneMaster();

	public:
		//Writer
		void saveScene(const std::unordered_map<size_t, std::vector<UniquePtr<GameObject>>>& Objlist);

		//Reader
		//void loadScene(const World& world);
		//component getter
		//dx3d::Component getComp(std::string _name);


		//Get file path
		std::string getFilePath();
		void setFilePath(string path);

	public:
		string curr_path;

	};
}

