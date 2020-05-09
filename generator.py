types = ["Token::TokenBoolean", "Token::TokenString", "Token::TokenInteger", "Token::TokenDouble"]
sign = ["Token::TokenPlus", "Token::TokenMinus"]
multiplication = ["Token::TokenDivide", "Token::TokenMultiply", "Token::TokenDiv", "Token::TokenMod"]
relation = ["Token::TokenEqual", "Token::TokenUnequal", "Token::TokenLess", "Token::TokenMore", "Token::TokenLessOrEqual", "Token::TokenMoreOrEqual"]

f = open("generated_code.txt", "w+")

for i in range(0, 4):
    f.write("operations_type.insert(std::pair<LValue, Token::Type>(LValue(" + types[i] + ", " + "Token::TokenAssign" + ", " + types[i] + "), " + types[i] + "));\n")
f.write("\n")

for i in range(1, 4):
    f.write("operations_type.insert(std::pair<LValue, Token::Type>(LValue(" + types[i] + ", " + sign[0] + ", " + types[i] + "), " + types[i] + "));\n")
f.write("\n")

for i in range(2, 3):
    f.write("operations_type.insert(std::pair<LValue, Token::Type>(LValue(" + types[i] + ", " + sign[1] + ", " + types[i] + "), " + types[i] + "));\n")
f.write("\n")

for i in range(2, 4):
    for j in range(2, 4):
        for k in range(0, 2):
            if (i != 2) or (j != 2):
                f.write("operations_type.insert(std::pair<LValue, Token::Type>(LValue(" + types[i] + ", " + sign[k] + ", " + types[j] + "), " + types[3] + "));\n")
f.write("\n")

for i in range(1, 4):
    f.write("operations_type.insert(std::pair<LValue, Token::Type>(LValue(" + types[2] + ", " + multiplication[i] + ", " + types[2] + "), " + types[2] + "));\n")
f.write("\n")

for i in range(2, 4):
    for j in range(2, 4):
        for k in range(0, 2):
            if (i != 2) or (j != 2) or (k != 1):
                f.write("operations_type.insert(std::pair<LValue, Token::Type>(LValue(" + types[i] + ", " + multiplication[k] + ", " + types[j] + "), " + types[3] + "));\n")
f.write("\n")

for i in range(0, 2):
    for j in range(0, 6):
        f.write("operations_type.insert(std::pair<LValue, Token::Type>(LValue(" + types[i] + ", " + relation[j] + ", " + types[i] + "), " + types[0] + "));\n")
f.write("\n")

for i in range(2, 4):
    for k in range (2, 4):
        for j in range(0, 6):
            f.write("operations_type.insert(std::pair<LValue, Token::Type>(LValue(" + types[i] + ", " + relation[j] + ", " + types[k] + "), " + types[0] + "));\n")
f.write("\n")

f.close()