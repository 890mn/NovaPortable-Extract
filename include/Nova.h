#ifndef NOVA_DEBIAN_NOVA_H
#define NOVA_DEBIAN_NOVA_H
#include <string>
#include <vector>
#include <unordered_map>

class Nova {
private:
    struct Nova_data {
        std::string format;
        std::string name;
        std::string url;
        std::string category;
        std::string cate_en; //use English name instead chinese -> solve utf-8 & gbk trans problem
    };
    std::vector<std::string> novaCategory;
    unsigned int novaSize = 0;
    std::vector<Nova_data> nova;
    std::unordered_map<unsigned int, Nova_data> novaMap;

public:
    static int versionCheck(Nova* no);
    static int recoverData(Nova* no);

    int analyze(Nova* no);
    static int download_extract(const Nova::Nova_data& nova_piece);
    static void display_list(Nova::Nova_data& nova_piece, int order);
    static int menu(Nova* no);

    Nova() {
        novaCategory = {"Tears of Themis", "Honkai Impact 3",
                        "Genshin Impact", "Honkai: Star Rail",
                        " Houkai Gakuen2", "Lumi"};
        novaSize = 0;
    }
};
#endif //NOVA_DEBIAN_NOVA_H
