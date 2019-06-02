//
// Created by hborkows on 02.06.19.
//

#ifndef TKOM_INTERPRETER_SCOPE_H
#define TKOM_INTERPRETER_SCOPE_H

#include <vector>
#include <unordered_map>
#include "Variable.h"

namespace ir
{
    class Scope
    {
    public:
        explicit Scope(Scope* upperScope): upperScope(upperScope), variableTable(), variableOrder()
        {}

        bool addVariable(Variable* var)
        {
            if(hasVariable(var->getName()))
            {
                return false;
            }
            variableTable.insert({{var->getName(), var}});
            variableOrder.push_back(var->getName());
            return true;
        }

        Variable* getVariable(const std::string& name)
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

        const std::unordered_map<std::string, Variable*>& getVariableTable() const
        {
            return variableTable;
        }

        void setVariableTable(const std::unordered_map<std::string, Variable*>& variableTable)
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
        std::unordered_map<std::string, Variable*> variableTable;
        std::vector<std::string> variableOrder;
    };

}
#endif //TKOM_INTERPRETER_SCOPE_H
