//
// Created by hborkows on 05.05.19.
//

#ifndef TKOM_INTERPRETER_ASTNODE_H
#define TKOM_INTERPRETER_ASTNODE_H



class ASTNode
{
public:
    enum class Type{
        variable,
        var_declaration,
        return_statement,
        assignment,
        while_statement,
        for_statement,
        if_statement,
        function_call,
        function_definition,
        rvalue,
        assignable,
        block,
        condition,
        expression,
        statement,
        int_lit,
        string_lit,
        int_var,
        string_var,
        log_var,
        literal,
        program
    };

    virtual Type getType() const = 0;

protected:
    ASTNode* parent;
};


#endif //TKOM_INTERPRETER_ASTNODE_H
