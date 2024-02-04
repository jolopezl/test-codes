/*
    using: Tcl_StringCaseMatch from tcl/generic/tclUtil.c
*/

#include <tcl.h> // Include the Tcl header
#include <iostream>

// Function that wraps Tcl_StringCaseMatch for easier use in C++
bool matchString(const char* str, const char* pattern, bool caseSensitive) {
    // Convert caseSensitive into Tcl's boolean type
    int tclCaseSensitive = caseSensitive ? 1 : 0;

    // Call Tcl_StringCaseMatch
    return Tcl_StringCaseMatch(str, pattern, tclCaseSensitive) != 0; // Convert result to bool
}

int main() {
    const char* str = "Hello, World!";
    const char* pattern = "*ello*";

    // Using the function
    bool match = matchString(str, pattern, true); // Case insensitive match

    std::cout << "Pattern matches: " << (match ? "Yes" : "No") << std::endl;

    return 0;
}
