#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <sys/queue.h>
#include <stdio.h>
#include <locale.h>
#include <lowdown.h>
#include <string.h>

char *markdown_to_ansi(const char *md)
{
    struct lowdown_doc *doc;
    struct lowdown_node *node;
    struct lowdown_buf *out;
    void *renderer;

    setlocale(LC_CTYPE, "");

    doc = lowdown_doc_new(NULL);

    if (!doc)
        return NULL;

    node = lowdown_doc_parse(
        doc,
        NULL,
        md,
        strlen(md),
        NULL
    );

    if (!node) {
        lowdown_doc_free(doc);
        return NULL;
    }

    out = lowdown_buf_new(256);
    if (!out) {
        lowdown_node_free(node);
        lowdown_doc_free(doc);

        return NULL;
    }
    renderer = lowdown_term_new(NULL);
    if (!renderer) {
        lowdown_buf_free(out);
        lowdown_node_free(node);
        lowdown_doc_free(doc);

        return NULL;
    }

    if (!lowdown_term_rndr(out, renderer, node)) {
        lowdown_term_free(renderer);
        lowdown_buf_free(out);
        lowdown_node_free(node);
        lowdown_doc_free(doc);

        return NULL;
    }
    char *result = malloc(out->size + 1);

    if (result) {
        memcpy(result, out->data, out->size);
        result[out->size] = '\0';
    }

    lowdown_term_free(renderer);
    lowdown_buf_free(out);
    lowdown_node_free(node);
    lowdown_doc_free(doc);


    return result;
}