#include "../proto/wiktionary.h"
#include "../proto/wiktionary_http_fetch.h"
#include "../proto/parse_word_page.h"

#include <cctype>
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

void Wiktionary::get_word_definition(const std::string& word) {
    if (word.empty() or std::all_of(word.begin(), word.end(), [](auto ch) {return std::isspace(ch);})) {
        throw 102;
    }
    std::string word_page_html = fetcher.fetch_word_page(word);

    if (word_page_html == "") {
        throw 101;
    }

    ParseWordPage parser(word, word_page_html, LANGUAGE);
    parser.get_data();
};
