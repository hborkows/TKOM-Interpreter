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
        lvalue,
        block,
        condition
    };

    virtual Type getType() const = 0;

protected:
    ASTNode* parent;
};


#endif //TKOM_INTERPRETER_ASTNODE_H
