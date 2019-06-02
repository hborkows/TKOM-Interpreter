//
// Created by hborkows on 02.06.19.
//

#ifndef TKOM_INTERPRETER_SCOPE_H
#define TKOM_INTERPRETER_SCOPE_H

#include <vector>
#include <unordered_map>
#include "VariableIr.h"


class Scope
{
public:
    explicit Scope(Scope* upperScope): upperScope(upperScope), variableTable(), variableOrder()
    {}

    bool addVariable(VariableIr* var)
    {
        if(hasVariable(var->getName()))
        {
            return false;
        }
        variableTable.insert({{var->getName(), var}});
        variableOrder.push_back(var->getName());
        return true;
    }

    VariableIr* getVariable(const std::string& name)
    {
        auto result = variableTable.find(name);

        if(result != variableTable.end())
        {
            return result->second;
        }

        if(upperScope != nullptr)
        {
            return upperScope->getVariable(name);
        }

        return nullptr;
    }

    bool hasVariable(const std::string& name)
    {
        return variableTable.find(name) != variableTable.end();
    }

    Scope* getUpperScope() const
    {
        return upperScope;
    }

    void setUpperScope(Scope* upperScope)
    {
        Scope::upperScope = upperScope;
    }

    const std::unordered_map<std::string, VariableIr*>& getVariableTable() const
    {
        return variableTable;
    }

    void setVariableTable(const std::unordered_map<std::string, VariableIr*>& variableTable)
    {
        Scope::variableTable = variableTable;
    }

    const std::vector<std::string>& getVariableOrder() const
    {
        return variableOrder;
    }

    void setVariableOrder(const std::vector<std::string>& variableOrder)
    {
        Scope::variableOrder = variableOrder;
    }

private:
    Scope* upperScope;
    std::unordered_map<std::string, VariableIr*> variableTable;
    std::vector<std::string> variableOrder;
};


#endif //TKOM_INTERPRETER_SCOPE_H
