#include <iostream>
#include "Nova.h"

int main() {
    Nova *no = new Nova();
    std::cout << "Welcome to 「 NovaPortable-Extract By Hinar.Ver[Debian-Release 1.0] 」\n" << std::endl;
    std::cout << "Version log: Please update json when there's no latest wallpaper" << std::endl;
    std::cout << "Version log: But the json file is dynamic so that it may lack some of wallpaper" << std::endl;
    std::cout << "Version log: So please contact me first and I would like to give more solutions to you" << std::endl;
    std::cout << "Version log: Post to -> linkjoestar402212@gmail.com | 1776078715@qq.com" << std::endl;
    std::cout << "Version log: Or try github issues : " << std::endl;
    Nova::versionCheck(no);
    while (!Nova::menu(no)) ;
    return 0;
}
