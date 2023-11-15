#include "../proto/parse_word_page.h"
#include <iostream>


ParseWordPage::ParseWordPage(const std::string& word, const std::string& html) {
    ParseWordPage::word = word;
    ParseWordPage::html = html;
}

void ParseWordPage::get_data() {
    std::cout << "Hello world!\n\t- from the parser." << std::endl;
}
