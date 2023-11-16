#include "../proto/wiktionary.h"
#include "../proto/http_fetch.h"
#include "../proto/parse_word_page.h"

#include <loguru.hpp>
#include <format>


// Returns the ISO 639-1 code of the language.
std::string support_lang_enum_to_iso_code(SupportedLanguage lang){
    switch (lang) {
        case SupportedLanguage::ENGLISH:
            return "en";
    }
    return "en";
}

Wiktionary::Wiktionary() : fetcher(BASE_URL) {
};

int Wiktionary::get_word_definition(const std::string& word) {
    std::string word_page_html = fetcher.fetch_word_page(word);

    if (word_page_html == "") {
        LOG_F(WARNING, "Quitting, because of empty html response.");
        return 1;
    }

    ParseWordPage parser(word, word_page_html, LANGUAGE);
    parser.get_data();

    return 0;
};
