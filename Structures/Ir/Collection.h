//
// Created by hborkows on 02.06.19.
//

#ifndef TKOM_INTERPRETER_COLLECTION_H
#define TKOM_INTERPRETER_COLLECTION_H

#include <string>
#include <vector>
#include <unordered_map>

class Collection
{
    Collection() = default;

    void addRow(std::string fieldName, std::string value)
    {
        std::unordered_map<std::string, std::string> row;
        row.insert({{fieldName, value}});
        rows.push_back(row);
    }

    std::

private:
    std::vector<std::unordered_map<std::string, std::string>> rows;
};


#endif //TKOM_INTERPRETER_COLLECTION_H
