#pragma once
#include <httplib.h>

#include "../proto/wiktionary_http_fetch.h"

#include <format>


enum SupportedLanguage {
    ENGLISH,
};

std::string support_lang_enum_to_iso_code(SupportedLanguage lang);

class Wiktionary {
    public:
        SupportedLanguage LANGUAGE = SupportedLanguage::ENGLISH;

        std::string SUBDOMAIN = support_lang_enum_to_iso_code(LANGUAGE);
        std::string DOMAIN = "wiktionary";
        std::string TLD = "org";
        std::string BASE_URL = std::format("https://{}.{}.{}", SUBDOMAIN, DOMAIN, TLD);

        WiktionaryHTTPFetch fetcher;

        Wiktionary();
        void get_word_definition(const std::string& word);
};
