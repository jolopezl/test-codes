#include <iostream>
#include <string>

#include "tcl.h"

int main(int argc, char **argv) {
    Tcl_Interp *interp;
    int _argc;
    const char **_argv;

    std::string list;
    for (int i = 0; i < argc; ++i) {
        list.append(*(argv + i));
        if (i < argc - 1) {
            list.append(" ");
        }
    }
    // char *list = nullptr;

    int result = Tcl_SplitList(
        interp,
        list.c_str(),
        &_argc,
        &_argv
    );

    if (result != TCL_OK) {
        std::cout << "Tcl_SplitList [not ok]" << std::endl;
    } else {
        std::cout << "Tcl_SplitList [ok]" << std::endl;
    }

    for (int i = 0; i < _argc; ++i) {
        std::cout << *(_argv + i) << std::endl;
    }

    return 0;
}