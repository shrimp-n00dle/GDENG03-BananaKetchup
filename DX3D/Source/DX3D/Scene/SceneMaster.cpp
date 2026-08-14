#include <DX3D/Scene/SceneMaster.h>

dx3d::SceneMaster::SceneMaster()
{
}

dx3d::SceneMaster::~SceneMaster()
{
}

void dx3d::SceneMaster::saveScene(const std::unordered_map<size_t, std::vector<UniquePtr<GameObject>>>& Objlist)
{
    std::string filepath = "test.json";
    std::cout << "Selected filename is " << filepath << std::endl;

    // Root JSON object for Unity compatibility
    Json::Value root;
    Json::Value objectsArray(Json::arrayValue);

    // Iterate through map and vectors
    for (const auto& [listsize, objVector] : Objlist) {
        for (const auto& gameObj : objVector) {
            if (gameObj) { // Check if unique_ptr is valid
                Json::Value objJson;

                // Optional: If your GameObject has a name property, uncomment/adjust this:
              //  objJson["name"] = gameObj->getObjName();

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

                // Append the object to our JSON array
                objectsArray.append(objJson);
            }
        }
    }

    // Attach the array to the root object
    root["objects"] = objectsArray;

    // Write to file using JsonCpp's StreamWriterBuilder
    std::ofstream myfile(filepath, std::ios::out);
    if (myfile.is_open()) {
        Json::StreamWriterBuilder builder;
        builder["indentation"] = "    "; // Pretty-print with 4 spaces for readability
        std::unique_ptr<Json::StreamWriter> writer(builder.newStreamWriter());

        writer->write(root, &myfile);
        myfile.close();
        std::cout << "FILE NAMED " << filepath << " SAVED!" << std::endl;
    }
    else {
        std::cerr << "Error: Could not open file " << filepath << " for writing." << std::endl;
    }
}

void dx3d::SceneMaster::loadScene()
{

}

std::string dx3d::SceneMaster::getFilePath()
{
    return curr_path;
}

void dx3d::SceneMaster::setFilePath(std::string path)
{
    curr_path = path;
}