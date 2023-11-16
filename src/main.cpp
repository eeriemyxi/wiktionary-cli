#include <lexbor/dom/dom.h>
#include <lexbor/html/html.h>
#include <CLI/CLI.hpp>
#include <httplib.h>
#include <loguru.hpp>

#include "proto/wiktionary.h"

#include <iostream>

struct LoguruOptions : loguru::Options{
    const char* verbosity_flag = nullptr;
};

const std::string APP_TITLE = "Wiktionary CLI";
const std::string APP_DESCRIPTION = "A command-line interface to search words at Wiktionary.";

int main(int argc, char* argv[]) {
    int VERBOSE = 0;
    std::string WORD = "";

    CLI::App cli(APP_TITLE + '\n' + std::string(APP_TITLE.length() - 1, ' ') + "| " + APP_DESCRIPTION);
    cli.add_option("-v,--verbose", VERBOSE, "Verbose output level. Set to -9 to turn off logging.");
    cli.add_option("-w,--word", WORD, "Word to search.");
    CLI11_PARSE(cli, argc, argv);

    loguru::g_colorlogtostderr = true;
    loguru::g_stderr_verbosity = VERBOSE;
    loguru::init(argc, argv, LoguruOptions());

    Wiktionary wiki;
    
    try {
        wiki.get_word_definition(WORD); 
    } catch (int code) {
        switch (code) {
            case 101:
                LOG_F(ERROR, "Fetched HTML respone is empty.");
            case 102:
                LOG_F(ERROR, "Empty word provided.");
        }
        LOG_F(WARNING, "Exiting with code %d.", code);
        return code;
    }

    return 0;
}
