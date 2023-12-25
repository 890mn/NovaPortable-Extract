#include <iostream>
#include <filesystem>
#include <fstream>
#include <math.h>
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
std::unordered_map<unsigned int, struct Nova> novaMap;

int fun_extract() {
    return 0;
}

int fun_download(const struct Nova& nova_piece) {
    std::string wget = "wget --progress=bar:force " + nova_piece.url;
    system(wget.c_str());
    fun_extract();
    return 0;
}

int fun_analyze() {
    Json::Reader reader;
    Json::Value root;

    //Read from file <group_all_data.json>
    std::ifstream jsFile("../cmake-build-debug/group_all_data.json", std::ios::binary);
    if (!jsFile.is_open()) {
        std::cout << "Contain no correct json file here." << std::endl;
        return 1;
    }

    //Decode to output.dat
    std::ofstream outFile("../cmake-build-debug/output.dat", std::ios::binary);
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
            novaMap.insert(std::pair<unsigned int, struct Nova>(i + 1, nova[i]));
            outFile << nova[i].format << std::endl;
            outFile << nova[i].name << std::endl;
            outFile << nova[i].url << std::endl;
        }
    }

    //Correct analyse
    std::cout << "Analyze ending." << std::endl;
    jsFile.close();
    return 0;
}

int recover_data() {
    std::ifstream data("../cmake-build-debug/output.dat");
    if (!data.is_open()) {
        std::cout << "No data to recover." << std::endl;
        return 1;
    }

    int recover_size = 0;
    while (!data.eof()) {
        char buff[200];
        nova.resize(recover_size + 1);
        data.getline(buff, 200);
        nova[recover_size].format = buff;
        data.getline(buff, 200);
        nova[recover_size].name = buff;
        data.getline(buff, 200);
        nova[recover_size].url = buff;
        ++recover_size;
        novaMap.insert(std::pair<unsigned int, struct Nova>(recover_size, nova[recover_size - 1]));
    }
    novaSize = (unsigned int)recover_size - 1;
    data.close();
    return 0;
}

void display_list() {

}

int display_main() {
    //info
    std::cout << "Choose the wallpaper with format here:" << std::endl;
    std::cout << "\n<      Input -> sum_of_wallpapers | every number of these wallpaper      >\n" << std::endl;
    std::cout << "Here gives some examples to further understand:" << std::endl;
    std::cout << "  For 1 file which its number is a -> please input : [1 a]" << std::endl;
    std::cout << "  For other[x] files which numbers are [a,b,c...] -> Please input : [x a b c ...]" << std::endl;
    std::cout << "  Specially, you can download all of them by -> [-1] and exit by -> [0]" << std::endl;
    std::cout << "Please give your choice:";

    std::string cmd;
    std::cin >> cmd;
    if (cmd == "ls") {
        std::string subCmd;
        std::cin >> subCmd;
        if (subCmd == "-l") {
            display_list();
        }
        else {
            display_list();
        }
    }
    else if (cmd == "do") {
        int downSize = 0, flag = 2;
        std::string subCmd;
        std::cin >> subCmd;
        if (subCmd[0] == '-') {
            if (subCmd[1] == 's') {
                flag = 0;
                downSize = 1;
            }
            else if (subCmd[1] == 'l') {
                flag = 1;
                downSize = (int)novaSize;
            }
            else {
                flag = 0;
                for (int i = 1; i < subCmd.size(); ++i) {
                    downSize += (subCmd[i] - '0') * (int)std::pow(10, subCmd.size() - i - 1);
                }
            }
            return 0;
        }
        else {
            std::cout << "Input Error." << std::endl;
            return 1;
        }
    }
    else if (cmd == "wq") {
        return 0;
    }
    else {
        std::cout << "Wrong input!" << std::endl;
        return 1;
    }
}

int main() {
    __time_t current_version = -1;
    __time_t version = -2;
    std::ifstream timeCheck("../cmake-build-debug/VersionCheck");
    if (!timeCheck.is_open()) {
        std::cout << "System Error." << std::endl;
        return 0;
    }
    timeCheck >> version;
    timeCheck.close();

    //stack overflow <get last modify time>
    struct stat result{};
    if(stat("../cmake-build-debug/group_all_data.json", &result)==0) {
        auto mod_time = result.st_mtime;
        current_version = mod_time;
    }

    if (current_version != version) {
        //update version
        std::ofstream newVersion("../cmake-build-debug/VersionCheck");
        newVersion << current_version;
        newVersion.close();

        //try analyze
        int res = fun_analyze();
        if (res == 1) return 0;
    }
    else {
        if (recover_data() == 1) return 0;
    }
    while (display_main()) ;
    return 0;
}
