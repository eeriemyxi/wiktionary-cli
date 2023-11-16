#include <lexbor/dom/dom.h>
#include <lexbor/html/html.h>
#include <httplib.h>
#include <loguru.hpp>

#include "proto/wiktionary.h"

#include <iostream>


int main(int argc, char* argv[]) {
    loguru::init(argc, argv);
    loguru::g_colorlogtostderr = true;

    std::string word = "apple";

    if (argc == 2) {
        word = argv[1];
    }

    Wiktionary wiki;

    int exit_code = wiki.get_word_definition(word); 

    return exit_code;
}
