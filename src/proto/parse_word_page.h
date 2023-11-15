#pragma once
#include <string>
#include <unordered_map>


class ParseWordPage {
    public:
        std::string word;
        std::string html;
        ParseWordPage(const std::string& word, const std::string& html);
        // std::unordered_map<std::string, std::string> get_data();
        void get_data();
};
