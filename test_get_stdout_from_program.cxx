/*
From:
https://stackoverflow.com/questions/478898/how-do-i-execute-a-command-and-get-the-output-of-the-command-within-c-using-po
*/

#include <iostream>
#include <stdexcept>
#include <stdio.h>
#include <string>
#include <vector>

std::string exec(const char* cmd)
{
    char buffer[128];
    std::string result = "";
    FILE* pipe = popen(cmd, "r");
    if (!pipe)
        throw std::runtime_error("popen() failed!");
    try {
        while (fgets(buffer, sizeof buffer, pipe) != NULL) {
            result += buffer;
        }
    } catch (...) {
        pclose(pipe);
        throw;
    }
    pclose(pipe);
    return result;
}

std::string check_alias(std::string prog)
{
    auto alias = exec("alias");
    return alias;
}

std::string find_path(std::string prog)
{
    bool found = false;
    std::string path;
    std::vector<std::string> finders = { "which", "type", "command -v", "whereis" };
    for (const auto& finder : finders) {
        auto call = finder + " " + prog;
        path = exec(call.c_str());
        auto prog2 = path.substr(path.size() - prog.size() - 1, path.size());
        if (path[0] == '/') {
            found = true;
            break;
        } else {
            path = "";
        }
    }
    if (found)
        return path.substr(0, path.size() - 1);
    else
        return "";
}

int main()
{
    std::vector<std::string> progs = { "lsx", "cat", "grep" };
    for (const auto& prog : progs) {
        std::cout << "path of " << prog << " is: " << find_path(prog) << std::endl;
    }
    // to test the following
    // define first $> alias xlla=ls
    // std::string alias = "xlla";
    // auto res = find_path(alias);
    // if (res.size() == 0) {
    //     std::cout << "Not in path, checking for aliases" << std::endl;
    //     std::string res2 = "";
    //     // auto res2 = check_alias(alias);
    //     if (res2.size() == 0) {
    //         std::cout << "Sorry..." << std::endl;
    //     } else {
    //         std::cout << "Good, we found it: " << res2 << std::endl;
    //     }
    // } else {
    //     std::cout << "Good, we found it: " << res << std::endl;
    // }
}