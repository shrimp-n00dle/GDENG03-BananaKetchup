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
                objJson["name"] = gameObj->objName;

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

void dx3d::SceneMaster::loadScene(World& world)
{

    std::string filepath = curr_path.empty() ? "test.json" : curr_path;
    std::cout << "Loading scene from filename: " << filepath << std::endl;

    std::ifstream file(filepath, std::ios::in);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << filepath << " for reading." << std::endl;
        return;
    }

    Json::Value root;
    Json::CharReaderBuilder readerBuilder;
    std::string errs;


    bool parsingSuccessful = Json::parseFromStream(readerBuilder, file, &root, &errs);
    file.close();

    if (!parsingSuccessful) {
        std::cerr << "Error: Failed to parse JSON file. Parse errors:\n" << errs << std::endl;
        return;
    }
    if (!root.isMember("GameObjects") || !root["GameObjects"].isArray()) {
        std::cerr << "Error: Invalid JSON format. 'GameObjects' array not found." << std::endl;
        return;
    }

    const Json::Value& objectsArray = root["GameObjects"];

    for (const auto& objJson : objectsArray)
    {
        std::string objName = objJson.isMember("name") ? objJson["name"].asString() : "Default_Object";

        float posX = 0.0f, posY = 0.0f, posZ = 0.0f;
        if (objJson.isMember("position")) {
            posX = objJson["position"].get("x", 0.0f).asFloat();
            posY = objJson["position"].get("y", 0.0f).asFloat();
            posZ = objJson["position"].get("z", 0.0f).asFloat();
        }

        float rotX = 0.0f, rotY = 0.0f, rotZ = 0.0f;
        if (objJson.isMember("rotation")) {
            rotX = objJson["rotation"].get("x", 0.0f).asFloat();
            rotY = objJson["rotation"].get("y", 0.0f).asFloat();
            rotZ = objJson["rotation"].get("z", 0.0f).asFloat();
        }

        float scaleX = 1.0f, scaleY = 1.0f, scaleZ = 1.0f;
        if (objJson.isMember("scale")) {
            scaleX = objJson["scale"].get("x", 1.0f).asFloat();
            scaleY = objJson["scale"].get("y", 1.0f).asFloat();
            scaleZ = objJson["scale"].get("z", 1.0f).asFloat();
        }
        
        auto cube = world.createGameObject<dx3d::GameObject>();
       // dx3d::Component objComp = getComp(objName);
        cube->createOrGetComponent<dx3d::CubeComponent>();
        cube->objName = "Cube";
        auto comp = cube->createOrGetComponent<dx3d::CubeComponent>();
        //comp->setMaterial(basicMat);
        cube->getTransform().setScale({ 1.0f, 1.0f, 1.0f });
        cube->getTransform().setPosition({ 2, 0, 0 });
        
    }

    std::cout << "Successfully loaded scene from " << filepath << std::endl;
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