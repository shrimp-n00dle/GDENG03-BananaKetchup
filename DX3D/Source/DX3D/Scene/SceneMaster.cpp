#include <DX3D/Scene/SceneMaster.h>

dx3d::SceneMaster::SceneMaster()
{
}

dx3d::SceneMaster::~SceneMaster()
{
}

void dx3d::SceneMaster::saveScene(const std::unordered_map<size_t, std::vector<UniquePtr<GameObject>>>& Objlist)
{
    std::string filepath = "DX11_Scene.json";
    std::cout << "Selected filename is " << filepath << std::endl;


    Json::Value root;
    Json::Value objectsArray(Json::arrayValue);


    for (const auto& [listsize, objVector] : Objlist) {
        for (const auto& gameObj : objVector) {
            if (gameObj) { 
                Json::Value objJson;


                objJson["name"] = gameObj->objName;
                
                //GETTING GAMEOBJECT TYPE
                if (gameObj->isPhysics)
                {
                    gameObj->objName = gameObj->objName + "_Physics";
                } 

                // POSITION
                Json::Value position(Json::objectValue);
                position["x"] = gameObj->getTransform().getPosition().x;
                position["y"] = gameObj->getTransform().getPosition().y;
                position["z"] = gameObj->getTransform().getPosition().z;
                objJson["position"] = position;

                // ROTATION
                Json::Value rotation(Json::objectValue);
                rotation["x"] = gameObj->getTransform().getRotation().x;
                rotation["y"] = gameObj->getTransform().getRotation().y;
                rotation["z"] = gameObj->getTransform().getRotation().z;
                objJson["rotation"] = rotation;

                // SCALE
                Json::Value scale(Json::objectValue);
                scale["x"] = gameObj->getTransform().getScale().x;
                scale["y"] = gameObj->getTransform().getScale().y;
                scale["z"] = gameObj->getTransform().getScale().z;
                objJson["scale"] = scale;

 
                objectsArray.append(objJson);
            }
        }
    }


    root["objects"] = objectsArray;


    std::ofstream myfile(filepath, std::ios::out);
    if (myfile.is_open()) {
        Json::StreamWriterBuilder builder;
        builder["indentation"] = "  "; 
        std::unique_ptr<Json::StreamWriter> writer(builder.newStreamWriter());

        writer->write(root, &myfile);
        myfile.close();
        std::cout << "SCENE NAME " << filepath << " DONE!" << std::endl;
    }
    else {
        std::cerr << "Error: Could not open file " << filepath << " for writing." << std::endl;
    }
}

//dx3d::Component dx3d::SceneMaster::getComp(std::string objName)
//{
//    switch (objName)
//    {
//        case "Cube":
//            return dx3d::CubeComponent;
//        break;
//
//    }
//}


std::string dx3d::SceneMaster::getFilePath()
{
    return curr_path;
}

void dx3d::SceneMaster::setFilePath(std::string path)
{
    curr_path = path;
}