#include "lexer.h"
#include "diagnostics.h"
#include <ctype.h>
#include <string.h>

#define MAX_CHARS_PER_LINE 256

static void tokenize_sub_str(str_view view, token_queue *tokens)
{
    if (view.len <= 0)
        return;

    str_view prefix = view;
    for (int i = 0; i < view.len; i++) {
        token_type type = is_token(prefix);
        //view[0:n-i] is tokenized
        if (type != TOKEN_ERROR) {
            token tok;
            tok.type = type;
            tok.symbol = register_symbol(prefix);
            enqueue_token(tokens, tok);

            //tokeize view[n-i:n]
            view.str += (view.len - i);
            view.len = i;
            tokenize_sub_str(view, tokens);
            return;
        }
        --prefix.len;
    }

    lexical_error("Could not tokenize");
}

static char *strip_cstr(char *line)
{
    int start = 0;
    while (isspace(line[start]) && line[start] != '\0') {
        ++start;
    }
    int end = start;
    while (!isspace(line[end]) && line[end] != '\0') {
        ++end;
    }
    line[end] = '\0';
    return line + start;
}

void tokenize_line(char *line, token_queue *tokens)
{
    char *tok = strtok(line, " ");
    while (tok != NULL) {
        tok = strip_cstr(tok);
        str_view view = view_str(tok, 0, strlen(tok));
        tokenize_sub_str(view, tokens);
        tok = strtok(NULL, " ");
    }
}

token_queue *tokenize_file(FILE *file)
{
    token_queue *queue = token_queue_alloc();
    char line_buff[MAX_CHARS_PER_LINE];
    while (fgets(line_buff, sizeof(line_buff), file)) {
        tokenize_line(line_buff, queue);
    }
    return queue;
}
