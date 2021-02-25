#include "Parser.h"
#include "../Maths/Vector3d.h"
#include <array>
#include <utility>
#include <fstream>
#include <iostream>
#include <map>
#include "../Objects/Sphere.h"
#include "../Objects/Triangle.h"

std::vector<std::string> Parser::splitString(const std::string& stringToParse, char delimiter) {
    std::vector<std::string> rep;
    std::string word;
    for (std::string::const_iterator str_it = stringToParse.begin(); str_it != stringToParse.end(); ++str_it) {
        if (*str_it != delimiter) {
            word += *str_it;
        }
        else if (word != "" && word != " ") {
            rep.push_back(word);
            word = "";
        }
    }
    if (!word.empty()) rep.push_back(word);
    return rep;

}

Scene Parser::parseFileIntoScene(const std::string& fileName) {

    std::string word; //Represents each word of the file separated by blank spaces
    try {
        std::ifstream sceneFile(fileName);    //Tries to open the file
        if (sceneFile) {

            Camera camera(Vector3d(0, 0, 0), Vector3d(0, 0, 1), 1, 0.5, 100, 2, std::pair<int, int>(640, 480));
            LightSource* defaultLight = new LightSource(Vector3d(0, 0, 0), Color(255, 255, 255));
            Material defaultMaterial(Color(255, 255, 255), 0.3, 0.3, 0.3, 0.3, 0.0);

            std::vector<Object3d*> listObjects;
            std::vector<LightSource*> listLights;
            std::map<std::string, Material> mapMaterials;

            mapMaterials.insert({"d", defaultMaterial});            

            while (!sceneFile.eof()) {
                sceneFile >> word;
                if (word == "Camera") {
                    sceneFile >> word; //Position
                    std::vector<std::string> position = splitString(word, '*');
                    Vector3d cameraPosition(position[0], position[1], position[2]);

                    sceneFile >> word; //Direction
                    std::vector<std::string> direction = splitString(word, '*');
                    Vector3d cameraDirection(direction[0], direction[1],direction[2]);

                    sceneFile >> word; //Focal
                    double focal(std::stod(word));

                    sceneFile >> word; //nearPlaneDistance
                    double nearPlaneDistance(std::stod(word));

                    sceneFile >> word; //farPlaneDistance
                    double farPlaneDistance(std::stod(word));

                    sceneFile >> word; //Image size
                    double imageSize(std::stod(word));

                    sceneFile >> word; //Image resolution
                    std::vector<std::string> resolution = splitString(word, '*');
                    std::pair<int, int> imageResolution(std::stoi(resolution[0]), std::stoi(resolution[1]));

                    Camera cameraTmp(cameraPosition, cameraDirection, focal, nearPlaneDistance, farPlaneDistance, imageSize, imageResolution);
                    camera = cameraTmp;
                }
                else if (word == "Light") {
                    sceneFile >> word; //Position
                    std::vector<std::string> position = splitString(word, '*');
                    Vector3d lightPosition(position[0], position[1], position[2]);

                    sceneFile >> word; //Color
                    std::vector<std::string> colorVector = splitString(word, '*');
                    Color color(colorVector[0], colorVector[1], colorVector[2]);
                   
                    LightSource* lightTmp = new LightSource(lightPosition,color);
                    listLights.push_back(lightTmp);
                }
                else if (word == "Material") {
                    sceneFile >> word; //Name
                    std::string name = word;

                    sceneFile >> word; //Color
                    std::vector<std::string> colorVector = splitString(word, '*');
                    Color color(colorVector[0], colorVector[1], colorVector[2]);

                    sceneFile >> word; //diffuse
                    double diffuse(std::stod(word));

                    sceneFile >> word; //ambient
                    double ambient(std::stod(word));

                    sceneFile >> word; //specular
                    double specular(std::stod(word));

                    sceneFile >> word; //shininess
                    double shininess(std::stod(word));

                    sceneFile >> word; //reflectivity
                    double reflectivity(std::stod(word));
                    
                    mapMaterials.insert({ name, Material(color, diffuse, ambient, specular, shininess, reflectivity) });
                }
                else if (word == "Plane") {
                    sceneFile >> word; //Position
                    std::vector<std::string> position = splitString(word, '*');
                    Vector3d planePosition(position[0], position[1], position[2]);

                    sceneFile >> word; //Normal
                    std::vector<std::string> normal = splitString(word, '*');
                    Vector3d planeNormal(normal[0], normal[1], normal[2]);

                    sceneFile >> word; //Material name
                    Plane* plane;
                    try {
                        Plane* planeTmp = new Plane(mapMaterials.at(word), planePosition, planeNormal);
                        plane = planeTmp;
                    }
                    catch (std::exception exception) {
                        std::cerr << exception.what() << std::endl;
                        std::cout << "Material " << word << " does not exist, replaced by default material.\n";
                        Plane* planeTmp = new Plane(defaultMaterial, planePosition, planeNormal);
                        plane = planeTmp;
                    }
                    listObjects.push_back(plane);
                }
                else if (word == "Sphere") {
                    sceneFile >> word; //Position
                    std::vector<std::string> position = splitString(word, '*');
                    Vector3d spherePosition(position[0], position[1], position[2]);

                    sceneFile >> word; //Normal
                    double radius(std::stod(word));

                    sceneFile >> word; //Material name
                    Sphere* sphere;
                    try {
                        Sphere* sphereTmp= new Sphere(mapMaterials.at(word), spherePosition, radius);
                        sphere = sphereTmp;
                    }
                    catch (std::exception exception) {
                        std::cerr << exception.what() << std::endl;
                        std::cout << "Material " << word << " does not exist, replaced by default material.\n";
                        Sphere* sphereTmp = new Sphere(defaultMaterial, spherePosition, radius);
                        sphere = sphereTmp;
                    }
                    listObjects.push_back(sphere);

                }
                else if (word == "Triangle") {
                    std::array<Vector3d, 3> vertices;
                    sceneFile >> word; //Vertex one
                    std::vector<std::string> vertex = splitString(word, '*');
                    vertices[0] = Vector3d(vertex[0],vertex[1],vertex[2]);

                    sceneFile >> word; //Vertex two
                    vertex = splitString(word, '*');
                    vertices[1] = Vector3d(vertex[0], vertex[1], vertex[2]);

                    sceneFile >> word; //Vertex three
                    vertex = splitString(word, '*');
                    vertices[2] = Vector3d(vertex[0], vertex[1], vertex[2]);
                    
                    sceneFile >> word; //Material
                    Triangle* triangle;
                    try {
                        Triangle* triangleTmp = new Triangle(mapMaterials.at(word), vertices);
                        triangle = triangleTmp;
                    }
                    catch (std::exception exception) {
                        std::cerr << exception.what() << std::endl;
                        std::cout << "Material " << word << " does not exist, replaced by default material.\n";
                        Triangle* triangleTmp = new Triangle(defaultMaterial, vertices);
                        triangle = triangleTmp;
                    }
                    listObjects.push_back(triangle);
                }
                
            }

            Scene scene(camera);
            if (!listLights.empty()) {
                scene.addLightSources(listLights);
            }
            
            scene.addObjects(listObjects);

            return scene;
        }
        else {
            throw std::string("Error opening file");
        }
    }
    catch (std::string const& chaine) {
        std::cerr << chaine << std::endl;
        return Scene();
    } 
}

