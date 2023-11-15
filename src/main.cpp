#include "lexbor/dom/dom.h"
#include "lexbor/html/html.h"

#include "httplib.h"

#include "proto/parse_word.h"
#include <iostream>


lxb_inline lxb_status_t serializer_callback(const lxb_char_t *data, size_t len, void *ctx)
{
    printf("%.*s", (int) len, (const char *) data);
    return LXB_STATUS_OK;
}

lxb_inline void serialize_node(lxb_dom_node_t *node)
{
    lxb_html_serialize_pretty_cb(node, LXB_HTML_SERIALIZE_OPT_UNDEF,
                                          0, serializer_callback, NULL);
}

int main() {
    // std::string html = "<div class=\"best blue some\"><span></div>"
    //     "<div class=\"red pref_best grep\"></div>"
    //     "<div class=\"red best grep\"></div>"
    //     "<div class=\"red c++ best\"></div>";
    my_func();
    std::string html = "<h2 class=\"city\">London</h2>";

    lxb_html_parser_t* parser = lxb_html_parser_create();
    lxb_html_parser_init(parser);

    auto document = lxb_html_parse(parser, (lxb_char_t*) html.data(), html.size());
    auto collection = lxb_dom_collection_make(&document->dom_document, 128);

    lxb_dom_elements_by_class_name(lxb_dom_interface_element(document->body), collection, (const lxb_char_t *) "city", 4);

    for (size_t i = 0; i < lxb_dom_collection_length(collection); i++) {
            auto element = lxb_dom_collection_element(collection, i);
            serialize_node(lxb_dom_interface_node(element));
        }
    return 0;
}
