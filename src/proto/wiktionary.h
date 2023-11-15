#pragma once
#include <httplib.h>

#include "../proto/http_fetch.h"

#include <format>


enum SupportedLanguage {
    ENGLISH,
};

std::string support_lang_enum_to_str(SupportedLanguage enum_t);

class Wiktionary {
    public:
        SupportedLanguage LANGUAGE = SupportedLanguage::ENGLISH;
        std::string BASE_URL = std::format("https://{}.{}.{}", support_lang_enum_to_str(LANGUAGE), "wiktionary", "org");
        WiktionaryHTTPFetch fetcher;

        Wiktionary();
        void get_word_definition(const std::string& word);
};
