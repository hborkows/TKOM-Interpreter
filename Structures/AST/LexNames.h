//
// Created by hborkows on 15.05.19.
//

#ifndef TKOM_INTERPRETER_LEXNAMES_H
#define TKOM_INTERPRETER_LEXNAMES_H

#include <string>

static std::string lexNames[] = {
        "empty",
        "plus_op", "minus_op", "mul_op", "div_op", "assign_op", "access_op",
        "and_op", "or_op", "not_op", "gt_op", "lt_op", "ge_op", "le_op", "equal_op", "not_equal_op",
        "lbracket", "rbracket", "lcurlbracket", "rcurlbracket",
        "for_kw", "while_kw", "in_kw",
        "if_kw", "else_kw", "elif_kw",
        "int_const", "text_const",
        "id",
        "int_kw", "log_kw", "string_kw", "void_kw",
        "return_kw",
        "start_define", "end_define",
        "semicolon", "comma", "end_of_code",
        "unknown"
};

#endif //TKOM_INTERPRETER_LEXNAMES_H
