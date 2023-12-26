#include <iostream>
#include <fstream>
#include <cmath>
#include <unordered_map>
#include <sys/stat.h>
#include <json/json.h>

struct Nova {
    std::string format;
    std::string name;
    std::string url;
    std::string category;
    std::string cate_en; //use English name instead chinese -> solve utf-8 & gbk trans problem
};
std::vector<struct Nova> nova;
std::vector<std::string> novaCategory = {
        "Tears of Themis", "Honkai Impact 3",
        "Genshin Impact", "Honkai: Star Rail",
        " Houkai Gakuen2", "Lumi"};
unsigned int novaSize = 0;
std::unordered_map<unsigned int, struct Nova> novaMap;

int fun_download_extract(const struct Nova& nova_piece) {
    std::string output_folder;
    std::string output_suffix;
    if (nova_piece.format == "Static") {
        output_folder = "../output_png_folder/";
        output_suffix = ".png";
    }
    else {
        output_folder = "../output_mp4_folder/";
        output_suffix = ".mp4";
    }
    std::string wget = "wget -O " + output_folder + nova_piece.name
            + "_original" + output_suffix
            + " --progress=bar:force " + nova_piece.url;
    system(wget.c_str());
    if (nova_piece.format == "Dynamic") {
        std::string filename = "../output_mp4_folder/" + nova_piece.name + "_original" + output_suffix;
        std::string output_name = "../output_mp4_folder/" + nova_piece.name + output_suffix;
        std::ifstream extract_file(filename, std::ios::binary);
        std::ofstream output_file(output_name, std::ios::binary);
        char buffer[1024];
        extract_file.seekg(2, std::ios::beg);
        while (!extract_file.eof()) {
            extract_file.read(buffer, sizeof(buffer));
            output_file.write(buffer, extract_file.gcount());
        }
        extract_file.close();
        output_file.close();
        remove(filename.c_str());
        std::cout << "Download " + nova_piece.name + " to ../output_mp4_folder successfully." << std::endl;
    }
    else {
        std::cout << "Download " + nova_piece.name + " to ../output_png_folder successfully." << std::endl;
    }
    return 0;
}

int fun_analyze() {
    Json::Reader reader;
    Json::Value root;

    //Read from file <group_all_data.json>
    std::ifstream jsFile("../cmake-build-debug/group_all_data.json", std::ios::binary);
    if (!jsFile.is_open()) {
        std::cout << "Warning: Contain no correct json file here." << std::endl;
        return 1;
    }

    //Decode to output.dat
    std::ofstream outFile("../cmake-build-debug/main_data", std::ios::binary);
    if (!outFile.is_open()) {
        std::cout << "Warning: Create output error." << std::endl;
        return 1;
    }

    //Read json by <jsoncpp>
    if (reader.parse(jsFile, root)) {
        novaSize = root[2]["wallpapers"].size();
        nova.resize(novaSize);

        for (unsigned int i = 0; i < novaSize; ++i) {
            nova[i].format = root[2]["wallpapers"][i]["format"].asString();
            nova[i].name = root[2]["wallpapers"][i]["langName"][0]["name"].asString();
            // English : nova[i].name = root[2]["wallpapers"][i]["langName"][1]["name"].asString();
            nova[i].url = root[2]["wallpapers"][i]["videos"][0]["wallpaperVideos"][0]["videoUrl"].asString();
            nova[i].category = root[2]["wallpapers"][i]["tags"][0]["lang_name"][0]["name"].asString();
            nova[i].cate_en = root[2]["wallpapers"][i]["tags"][0]["lang_name"][1]["name"].asString();
            novaMap.insert(std::pair<unsigned int, struct Nova>(i + 1, nova[i]));
            outFile << nova[i].format << std::endl;
            outFile << nova[i].name << std::endl;
            outFile << nova[i].url << std::endl;
            outFile << nova[i].category << std::endl;
            outFile << nova[i].cate_en << std::endl;
        }
    }

    //Correct analyse
    std::cout << "Tips: Successfully analyzed by json." << std::endl;
    jsFile.close();
    return 0;
}

int recover_data() {
    std::ifstream data("../cmake-build-debug/main_data");
    if (!data.is_open()) {
        std::cout << "Warning: No data to recover." << std::endl;
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
        data.getline(buff, 200);
        nova[recover_size].category = buff;
        data.getline(buff, 200);
        nova[recover_size].cate_en = buff;
        ++recover_size;
        novaMap.insert(std::pair<unsigned int, struct Nova>(recover_size, nova[recover_size - 1]));
    }
    novaSize = (unsigned int)recover_size - 1;
    data.close();
    std::cout << "Tips: Successfully recovered by main_data." << std::endl;
    return 0;
}

void display_list(const struct Nova& nova_piece, int order) {
    std::cout << "Name: " << nova_piece.name << std::endl;
    std::cout << "[Order]: " << order << "      [Format]: " << nova_piece.format << "       [Category]: " << nova_piece.category << std::endl;
}

int display_main() {
    //info
    std::cout << "\nFunction:" << std::endl;
    std::cout << "<1> Wallpaper list" << std::endl;
    std::cout << "  Usage:" << std::endl;
    std::cout << "         [ls -l] -> display all wallpapers at this version" << std::endl;
    std::cout << "         [ls -x] -> display category with number here" << std::endl;
    std::cout << "         1 - 未定事件簿  |  2 - 崩坏3  |  3 - 原神  |  4 - 崩坏星穹铁道  |  5 - 崩坏学园2  |  6 - yoyo鹿鸣" << std::endl;

    std::cout << "\n<2> Download" << std::endl;
    std::cout << "  Usage:" << std::endl;
    std::cout << "         [do -s a] -> download one file which its number is [a]" << std::endl;
    std::cout << "         [do -x a b c..] -> download files with total [x] which numbers are [a b c..]" << std::endl;
    std::cout << "         [do -l] -> download all of the wallpaper" << std::endl;

    std::cout << "\n<3> Search" << std::endl;
    std::cout << "  Usage:" << std::endl;
    std::cout << "         [fi category name] -> Complete search -> Default[-c -n include] choice MUST with 2 parameters!" << std::endl;
    std::cout << "         [fi -c category] -> Only give category to search wallpaper" << std::endl;
    std::cout << "         [fi -n name] -> Only give name to search wallpaper" << std::endl;

    std::cout << "\n<4> Quit" << std::endl;
    std::cout << "  Usage:" << std::endl;
    std::cout << "         [wq] -> quit this program" << std::endl;

    std::cout << "\nPlease give your choice:";

    std::string cmd;
    std::cin >> cmd;
    //display with several mode
    if (cmd == "ls") {
        std::string subCmd;
        std::cin >> subCmd;
        if (subCmd == "-l") {
            for (int cnt = 0; cnt < novaSize; ++cnt) {
                display_list(nova[cnt], cnt);
                std::cout << std::endl;
            }
        }
        else {
            int cate_choice = subCmd[1] - '1';
            if (cate_choice < 0 || cate_choice > 6) {
                std::cout << "Warning: Out of range." << std::endl;
                return 1;
            }
            std::string cateList = novaCategory[cate_choice];
            for (int cnt = 0; cnt < novaSize; ++cnt) {
                if (nova[cnt].cate_en == cateList) {
                    display_list(nova[cnt], cnt);
                    std::cout << std::endl;
                }
            }
        }
        return 0;
    }
    //download with parameter
    else if (cmd == "do") {
        int downSize = 0, flag;
        std::string subCmd;
        std::cin >> subCmd;
        if (subCmd[0] == '-') {
            //init mode & size
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

            //main download
            for (int i = 0; i < downSize; ++i) {
                int single;
                if (flag == 1) fun_download_extract(nova[i]);
                else {
                    std::cin >> single;
                    fun_download_extract(nova[single]);
                }
            }
            return 0;
        }
        else {
            std::cout << "Warning: Input Error." << std::endl;
            return 1;
        }
    }
    else if (cmd == "wq") {
        return 1;
    }
    else {
        std::cout << "Warning: Wrong input!" << std::endl;
        return 1;
    }
}

int main() {
    __time_t current_version = -1;
    __time_t version = -2;
    std::ifstream timeCheck("../cmake-build-debug/VersionCheck");
    if (!timeCheck.is_open()) {
        std::cout << "Warning: System Error." << std::endl;
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
    std::cout << "Welcome to 「 Nova_Hinar [Debian12-Release]Ver.0.1 」\n" << std::endl;
    std::cout << "Version log: Please update json when there's no latest wallpaper" << std::endl;
    while (!display_main()) ;
    return 0;
}
