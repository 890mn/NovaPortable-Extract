#include <iostream>
#include <filesystem>
#include <fstream>
#include <unordered_map>
#include <sys/stat.h>
#include <json/json.h>

struct Nova {
    std::string format;
    std::string name;
    std::string url;
};
std::vector<struct Nova> nova;
std::vector<int> downloadList;
unsigned int novaSize = 0;
std::unordered_map<unsigned int, struct Nova> novaList;

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
        return 1;
    }

    //Read json by <jsoncpp>
    if (reader.parse(jsFile, root)) {
        novaSize = root[2]["wallpapers"].size();
        nova.resize(novaSize);

        for (unsigned int i = 0; i < novaSize; ++i) {
            nova[i].format = root[2]["wallpapers"][i]["format"].asString();
            nova[i].name = root[2]["wallpapers"][i]["langName"][0]["name"].asString();
            nova[i].url = root[2]["wallpapers"][i]["videos"][0]["wallpaperVideos"][0]["videoUrl"].asString();
            novaList.insert(std::pair<unsigned int, struct Nova>(i, nova[i]));
            outFile << nova[i].format << std::endl;
            outFile << nova[i].name << std::endl;
            outFile << nova[i].url << std::endl;
            outFile << "Sign of end." << std::endl;
        }
    }

    //Correct analyse
    std::cout << "Analyze ending." << std::endl;
    jsFile.close();
    return 0;
}

int fun_download() {

    return 0;
}

int display_main() {
    std::cout << "Choose the wallpaper with format here:" << std::endl;
    std::cout << "\n<      Input -> sum_of_wallpapers | every number of these wallpaper      >\n" << std::endl;
    std::cout << "Here gives some examples to further understand:" << std::endl;
    std::cout << "  For 1 file which its number is a -> please input : [1 a]" << std::endl;
    std::cout << "  For other[x] files which numbers are [a,b,c...] -> Please input : [x a b c ...]" << std::endl;
    std::cout << "  Specially, you can download all of them by -> [-1] and exit by -> [0]" << std::endl;
    std::cout << "Please give your choice:";
    int choice;
    std::cin >> choice;
    if (choice != 0 && choice != -1) {
        downloadList.resize(choice);
        for (int i = 0; i < choice; ++i) {
            std::cin >> downloadList[i];
        }
    }
    return choice;
}

int main() {
    __time_t current_version = -1;
    __time_t version = -2;
    std::ifstream timeCheck("VersionCheck");
    if (!timeCheck.is_open()) {
        std::cout << "System Error." << std::endl;
        return 0;
    }
    timeCheck >> version;
    timeCheck.close();

    //stack overflow <get last modify time>
    struct stat result{};
    if(stat("group_all_data.json", &result)==0) {
        auto mod_time = result.st_mtime;
        current_version = mod_time;
    }

    if (current_version != version) {
        //update version
        std::ofstream newVersion("VersionCheck");
        newVersion << current_version;
        newVersion.close();

        //try analyze
        int res = fun_analyze();
        if (!res) return 0;
    }
    int dis_status = display_main();
    while (dis_status != 0) {
        if (dis_status == -1) {
            dis_status = (int)novaSize;
        }

        dis_status = display_main();
    }


    return 0;
}
