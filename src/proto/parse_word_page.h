#pragma once
#include <lexbor/dom/dom.h>

#include "../proto/wiktionary.h"

#include <string>
#include <unordered_map>


class ParseWordPage {
    public:
        std::string word;
        std::string html;

        ParseWordPage(const std::string& word, const std::string& html, const SupportedLanguage& lang);
        void get_data();
};
