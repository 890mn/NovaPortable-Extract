#include <iostream>
#include <filesystem>
#include <fstream>
#include <json/json.h>

namespace fs = std::filesystem;

int fun_extract() {
    return 0;
}

int fun_analyze() {
    Json::Reader reader;
    Json::Value root;

    //Read from file <group_all_data.json>
    std::ifstream jsFile("group_all_data.json", std::ios::binary);
    if (!jsFile.is_open()) {
        std::cout << "Contain no correct json file here." << std::endl;
        return 1;
    }

    //Decode to output.dat
    std::ofstream outFile("output.dat", std::ios::binary);
    if (!outFile.is_open()) {
        std::cout << "Create output error." << std::endl;
        return 2;
    }

    //Read json by <jsoncpp>
    if (reader.parse(jsFile, root)) {
        for (unsigned int i = 0; i < root[2]["wallpapers"].size(); ++i) {
            std::string format = root[2]["wallpapers"][i]["format"].asString();
            std::string name = root[2]["wallpapers"][i]["langName"][0]["name"].asString();
            std::string video = root[2]["wallpapers"][i]["videos"][0]["wallpaperVideos"][0]["videoUrl"].asString();
            outFile << format << std::endl;
            outFile << name << std::endl;
            outFile << video << std::endl;
            outFile << "Sign of end." << std::endl;
        }
    }

    //Correct analyse
    std::cout << "Analyze ending." << std::endl;
    jsFile.close();
    return 0;
}

int display_main() {
    return 0;
}

int main() {
    fun_analyze();
    return 0;
}
