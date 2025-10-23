#include "token.h"

#include <ctype.h>
#include <malloc.h>

#define INITAL_QUEUE_SIZE 10

static char SINGLE_CHAR_TOKENS[SINGLE_CHAR_TOKEN_END]
    = {'(', ')', '{', '}', '[', ']', '?', '=', ':', ',', '+', '-', '*', '/'};

static char *MULTI_CHAR_TOKENS[MULTI_CHAR_TOKEN_END] = {"fn", "option", "True", "False"};

static token_type is_single_char_token(char tok);
static token_type is_multi_char_token(str_view view);

static bool is_str_literal(str_view view);
static bool is_integer(str_view view);
static bool is_floating(str_view view);
static bool is_identifier(str_view view);

token_queue *token_queue_alloc()
{
    token_queue *queue = malloc(sizeof(token_queue));
    queue->data = malloc(INITAL_QUEUE_SIZE * sizeof(token));
    queue->max_size = INITAL_QUEUE_SIZE;
    queue->start_idx = 0;
    queue->size = 0;
    return queue;
}

token peek_token(token_queue *queue)
{
    return queue->data[queue->start_idx];
}

int enqueue_token(token_queue *queue, token tok)
{
    if (queue->size == queue->max_size) {
        queue->max_size *= 2;
        queue->data = realloc(queue->data, queue->max_size);
        if (!queue->data)
            return 1;
    }
    queue->data[queue->size++] = tok;
    return 0;
}

token dequeue_token(token_queue *queue)
{
    return queue->data[queue->start_idx++];
}

void token_queue_destroy(token_queue *queue)
{
    free(queue->data);
    free(queue);
}

bool token_queue_empty(token_queue *queue)
{
    return queue->start_idx == queue->size;
}

token_type is_token(str_view view)
{
    token_type out = TOKEN_ERROR;
    if (view.len == 1 && (out = is_single_char_token(view.str[0])) != TOKEN_ERROR) {
        return out;
    }

    if ((out = is_multi_char_token(view)) != TOKEN_ERROR) {
        return out;
    }

    if (is_integer(view)) {
        return TOK_INTEGER;
    }

    if (is_floating(view)) {
        return TOK_FLOATING;
    }

    if (is_str_literal(view)) {
        return TOK_STR_LITERAL;
    }

    if (is_identifier(view)) {
        return TOK_IDENTIFIER;
    }

    return TOKEN_ERROR;
}

void print_token(token t)
{
    printf("%d - %s\n", t.type, view_symbol(t.symbol).str);
}

static token_type is_single_char_token(char tok)
{
    for (int i = 0; i < SINGLE_CHAR_TOKEN_END; i++) {
        if (SINGLE_CHAR_TOKENS[i] == tok) {
            return (token_type) i;
        }
    }
    return TOKEN_ERROR;
}

static token_type is_multi_char_token(str_view view)
{
    for (int i = 0; i < MULTI_CHAR_TOKEN_END - SINGLE_CHAR_TOKEN_END - 1; i++) {
        if (str_view_equals_str(view, MULTI_CHAR_TOKENS[i])) {
            return (token_type) i;
        }
    }
    return TOKEN_ERROR;
}

static bool is_str_literal(str_view view)
{
    return view.len >= 2 && view.str[0] == '\"' && view.str[view.len - 1] == '\"';
}

static bool is_integer(str_view view)
{
    FOR_EACH(i, view)
    {
        if (!isdigit(view.str[i]))
            return false;
    }
    return true;
}

static bool is_floating(str_view view)
{
    bool frac_sep_found = false;
    FOR_EACH(i, view)
    {
        if (view.str[i] == '.') {
            if (frac_sep_found)
                return false;
            frac_sep_found = true;
        }
        if (!isdigit(view.str[i]))
            return false;
    }
    return true;
}

static bool is_identifier(str_view view)
{
    FOR_EACH(i, view)
    {
        if (!isalpha(view.str[i]))
            return false;
    }
    return true;
}
