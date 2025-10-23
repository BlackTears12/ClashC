#ifndef TOKEN_H
#define TOKEN_H

#include "str.h"
#include "symbol.h"
#include <stdbool.h>

typedef enum token_type {
    TOK_L_BRACKET,
    TOK_R_BRACKET,
    TOK_LC_BRACKET,
    TOK_RC_BRACKET,
    TOK_LSQ_BRACKET,
    TOK_RSQ_BRACKET,
    TOK_QUESTION_MARK,
    TOK_EQUALS,
    TOK_COLON,
    TOK_COMMA,
    TOK_PLUS,
    TOK_MINUS,
    TOK_MULTIPLY,
    TOK_DIVIDE,

    SINGLE_CHAR_TOKEN_END,

    TOK_FN,
    TOK_OPTION,
    TOK_BOOL_TRUE,
    TOK_BOOL_FALSE,

    MULTI_CHAR_TOKEN_END,

    TOK_INTEGER,
    TOK_FLOATING,
    TOK_STR_LITERAL,
    TOK_IDENTIFIER,
    TOKEN_ERROR,
} token_type;

typedef struct token
{
    enum token_type type;
    symbol_ptr symbol;
} token;

void print_token(token t);

typedef struct token_queue
{
    token *data;
    size_t size;
    size_t start_idx;
    size_t max_size;
} token_queue;

token_queue *token_queue_alloc();
void token_queue_destroy(token_queue *queue);

bool token_queue_empty(token_queue *queue);

token peek_token(token_queue *queue);
int enqueue_token(token_queue *queue, token tok);
token dequeue_token(token_queue *queue);

token_type is_token(str_view view);

#endif // TOKEN_H
