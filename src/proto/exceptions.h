#include <unordered_map>
#include <string>
#include <any>


struct AppException {
    int error_code;
    std::string message;
    std::unordered_map<std::string, std::any> data;
};
