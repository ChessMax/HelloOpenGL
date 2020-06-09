#include <fstream>
#include <sstream>
#include <iostream>

bool fail(const char *reason) {
    std::cerr << reason << std::endl;
    return false;
}

int appFail(const char *reason) {
    fail(reason);
    return -1;
}

std::tuple<bool, std::string> GetTextFileContent(const char *filePath) {
    std::ifstream inputStream(filePath);

    if (inputStream.is_open()) {
        std::stringstream stringBuffer;
        stringBuffer << inputStream.rdbuf();
        inputStream.close();

        return {true, stringBuffer.str()};
    }

    return {false, ""};
}