#include "common.h"

struct AST_Literal;
struct AST_BinaryOp;
struct AST_Variable;
struct AST_FCall;

typedef enum AST_ExprType
{
    AST_LITERAL,
    AST_BINARYOP,
    AST_VARIABLE,
    AST_FCALL
} AST_ExprType;

typedef union AST_ExprValue
{
    struct AST_Literal *literal;
} AST_ExprValue;

typedef struct AST_Expression
{
    AST_ExprType type;
    AST_ExprValue value;
} AST_Expression;

typedef struct AST_Literal
{
    Symbol value;
} AST_Literal;

struct AST_BinaryOp
{
    AST_Expression lhs;
    AST_Expression rhs;
};

struct AST_Assignment
{
    Symbol lhs;
};

AST_Literal *as_literal(AST_Expression *expr);