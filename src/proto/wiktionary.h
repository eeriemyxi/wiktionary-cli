#pragma once
#include "httplib.h"
#include "../proto/http_fetch.h"


enum SupportedLanguage {
    ENGLISH,
};

std::string support_lang_enum_to_str(SupportedLanguage enum_t);

class Wiktionary {
    public:
        SupportedLanguage LANGUAGE;
        std::string BASE_URL;
        // WiktionaryHTTPFetch fetcher;

        Wiktionary();
        void get_word_definition(const std::string& word);
};
