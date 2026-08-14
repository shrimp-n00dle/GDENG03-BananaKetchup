#pragma once

//file reader headers
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

namespace dx3d {
	class SceneMaster
	{
	public:
		SceneMaster();
		~SceneMaster();

	public:
		//Writer
		void saveScene();

		//Reader
		void loadScene();


		//Get file path
		string getFilePath();
		void setFilePath(string path);

	public:
		string curr_path;

	};
}

