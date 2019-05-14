//
// Created by hborkows on 14.05.19.
//

#ifndef TKOM_INTERPRETER_FIELDACCESS_H
#define TKOM_INTERPRETER_FIELDACCESS_H


#include "Assignable.h"
#include "LogVar.h"
#include <string>


class FieldAccess: public Assignable, public Variable
{
public:
    void setFieldName(const std::string& name) {fieldName = name;}

    void setLogVar(Variable* var) {log = var;}

    Type getType()const override {return Type::field_access;}
protected:
    std::string fieldName;
    Variable* log;
};


#endif //TKOM_INTERPRETER_FIELDACCESS_H
