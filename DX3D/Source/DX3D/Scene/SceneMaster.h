#pragma once

//#include <DX3D/Core/Core.h>
//#include <DX3D/All.h>
//#include <unordered_map>
//#include <DX3D/Game/GameObject.h>

//file reader headers
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

//math stuff
#include <DX3D/Math/Vec3.h>

namespace dx3d {
	class SceneMaster
	{
	public:
		SceneMaster();
		~SceneMaster();

	public:
		//Writer
		void saveScene(/*const std::unordered_map<size_t, std::vector<UniquePtr<GameObject>>>& Objlist*/);

		//Reader
		void loadScene();


		//Get file path
		string getFilePath();
		void setFilePath(string path);

	public:
		string curr_path;

	};
}

