types = ["Boolean", "String", "Integer", "Double"]
operations = [["Assign", "Assignment"], "Plus", "Minus", "Divide", "Multiply", "Div", "Mod", "Equal", "Unequal", "More", "Less", "MoreOrEqual", "LessOrEqual"]

f = open("generated_code_2.txt", "w+")

for i in range(0, 4):
    f.write("functions_types.insert(std::pair<TupleOfTokens, DataPtr>(TupleOfTokens(Token" + types[i] + ", Token" + operations[0][0] + ", Token" + types[i] + "), std::make_shared<" + operations[0][1] + "Operation<" + types[i] + "Variable, " + types[i] + "Variable>>()));\n")
f.write("\n")

for i in range(0, 3):
    f.write("functions_types.insert(std::pair<TupleOfTokens, DataPtr>(TupleOfTokens(Token" + types[i] + ", Token" + operations[1] + ", Token" + types[i] + "), std::make_shared<" + operations[1] + "Operation<" + types[i] + "Variable, " + types[i] + "Variable, " + types[i] + "Variable>>()));\n")
f.write("\n")

f.write("functions_types.insert(std::pair<TupleOfTokens, DataPtr>(TupleOfTokens(Token" + types[2] + ", Token" + operations[2] + ", Token" + types[2] + "), std::make_shared<" + operations[2] + "Operation<" + types[2] + "Variable, " + types[2] + "Variable, " + types[2] + "Variable>>()));\n")
f.write("\n")

for i in range(1, 3):
    for j in range(2, 4):
        for k in range(2, 4):
            if (j != 2) or (k != 2):
                f.write("functions_types.insert(std::pair<TupleOfTokens, DataPtr>(TupleOfTokens(Token" + types[j] + ", Token" + operations[i] + ", Token" + types[k] + "), std::make_shared<" + operations[i] + "Operation<" + types[j] + "Variable, " + types[k] + "Variable, " + types[3] + "Variable>>()));\n")
f.write("\n")

for i in range(4, 7):
    f.write("functions_types.insert(std::pair<TupleOfTokens, DataPtr>(TupleOfTokens(Token" + types[2] + ", Token" + operations[i] + ", Token" + types[2] + "), std::make_shared<" + operations[i] + "Operation<" + types[2] + "Variable, " + types[2] + "Variable, " + types[2] + "Variable>>()));\n")
f.write("\n")

for i in range(3, 5):
    for j in range(2, 4):
        for k in range(2, 4):
            if (j != 2) or (k != 2) or (i != 4):
                f.write("functions_types.insert(std::pair<TupleOfTokens, DataPtr>(TupleOfTokens(Token" + types[j] + ", Token" + operations[i] + ", Token" + types[k] + "), std::make_shared<" + operations[i] + "Operation<" + types[j] + "Variable, " + types[k] + "Variable, " + types[3] + "Variable>>()));\n")
f.write("\n")

for i in range(0, 2):
    for j in range(7, 13):
        f.write("functions_types.insert(std::pair<TupleOfTokens, DataPtr>(TupleOfTokens(Token" + types[i] + ", Token" + operations[j] + ", Token" + types[i] + "), std::make_shared<" + operations[j] + "Operation<" + types[i] + "Variable, " + types[i] + "Variable, " + types[0] + "Variable>>()));\n")
f.write("\n")

for i in range(2, 4):
    for j in range(2, 4):
        for k in range(7, 13):
            f.write("functions_types.insert(std::pair<TupleOfTokens, DataPtr>(TupleOfTokens(Token" + types[i] + ", Token" + operations[k] + ", Token" + types[j] + "), std::make_shared<" + operations[k] + "Operation<" + types[i] + "Variable, " + types[j] + "Variable, " + types[0] + "Variable>>()));\n")
f.write("\n")

f.close()