#ifndef LEXER_H
#define LEXER_H

#include "token.h"
#include <stdio.h>

token_queue *tokenize_file(FILE *file);
void tokenize_line(char *line, token_queue *tokens);

void lexer_test();

#endif // LEXER_H
