//
// Created by ghost on 09.05.2020.
//

#include <stack>
#include "flex.h"
#include "type_tables.h"

#pragma once

using OperationIndex = std::size_t;

class Data
{
public:
    using DataPtr = std::shared_ptr<Data>;
    using Stack = std::stack<DataPtr>;

    struct Context
    {
        OperationIndex operation_index = 0;
        Stack stack;
    };

    explicit Data(Type new_type = TokenUndefined)
    {
        type = new_type;
    }

    void Error(std::string expected) const;
    Type GetType() const;
    virtual void Do(Context& context);

private:
    Type type;
};

