#include <iostream>
#include <fstream>
#include <unordered_map>
#include <vector>

void AddLetters(std::unordered_map<std::string, std::string>* map, std::string Destination)
{
    int shift = 'A' - 'a';
    for (char i = 'a'; i <= 'z'; i++)
    {
        map->insert(std::pair<std::string, std::string>(std::string(1, i), Destination));
        map->insert(std::pair<std::string, std::string>(std::string(1, i + shift), Destination));
    }
}

void AddNumbers(std::unordered_map<std::string, std::string>* map, std::string Destination)
{
    for (char i = '0'; i <= '9'; i++)
    {
        map->insert(std::pair<std::string, std::string>(std::string(1, i), Destination));
    }
}

void AddSeparators(std::unordered_map<std::string, std::string>* map, std::string Destination)
{
    map->insert(std::pair<std::string, std::string>(":", Destination));
    map->insert(std::pair<std::string, std::string>(";", Destination));
    map->insert(std::pair<std::string, std::string>("=", Destination));
    map->insert(std::pair<std::string, std::string>(">", Destination));
    map->insert(std::pair<std::string, std::string>("<", Destination));
    map->insert(std::pair<std::string, std::string>(">=", Destination));
    map->insert(std::pair<std::string, std::string>("<=", Destination));
    map->insert(std::pair<std::string, std::string>("==", Destination));
    map->insert(std::pair<std::string, std::string>("!=", Destination));
    map->insert(std::pair<std::string, std::string>("-", Destination));
    map->insert(std::pair<std::string, std::string>("+", Destination));
    map->insert(std::pair<std::string, std::string>("(", Destination));
    map->insert(std::pair<std::string, std::string>(")", Destination));
    map->insert(std::pair<std::string, std::string>(".", Destination));
}

void AddSpaces(std::unordered_map<std::string, std::string>* map, std::string Destination)
{
    map->insert(std::pair<std::string, std::string>(" ", Destination));
    map->insert(std::pair<std::string, std::string>("\t", Destination));
    map->insert(std::pair<std::string, std::string>("\n", Destination));
}

void FillDFA(std::vector<std::string>* conditions, std::unordered_map<std::string, std::unordered_map<std::string, std::string>>* transition_table)
{
    conditions->push_back("Start");
    conditions->push_back("Text");
    conditions->push_back("Quote"); // TODO: ASCII symbols
    conditions->push_back("Comment");
    conditions->push_back("Integer");
    conditions->push_back("Double");
    conditions->push_back("Decimal");
    conditions->push_back("E");
    conditions->push_back("Exponent");

    std::unordered_map<std::string, std::string> mask;
    AddLetters(&mask, "Text");
    AddNumbers(&mask, "Integer");
    mask.insert(std::pair<std::string, std::string>("_", "Text"));
    mask.insert(std::pair<std::string, std::string>("'", "Quote"));
    mask.insert(std::pair<std::string, std::string>("{", "Comment"));
    AddSeparators(&mask, "Start");
    AddSpaces(&mask, "Start");
    transition_table->insert(std::pair<std::string, std::unordered_map<std::string, std::string>>("Start", mask));

    mask.clear();
    AddLetters(&mask, "Text");
    AddNumbers(&mask, "Text");
    AddSeparators(&mask, "Start");
    AddSpaces(&mask, "Start");
    transition_table->insert(std::pair<std::string, std::unordered_map<std::string, std::string>>("Text", mask));

    mask.clear();
    mask.insert(std::pair<std::string, std::string>("'", "Start"));
    transition_table->insert(std::pair<std::string, std::unordered_map<std::string, std::string>>("Quote", mask));

    mask.clear();
    mask.insert(std::pair<std::string, std::string>("}", "Start"));
    transition_table->insert(std::pair<std::string, std::unordered_map<std::string, std::string>>("Comment", mask));

    mask.clear();
    AddNumbers(&mask, "Integer");
    mask.insert(std::pair<std::string, std::string>(".", "Double"));
    mask.insert(std::pair<std::string, std::string>("E", "E"));
    mask.insert(std::pair<std::string, std::string>("e", "E"));
    AddSeparators(&mask, "Start");
    AddSpaces(&mask, "Start");
    transition_table->insert(std::pair<std::string, std::unordered_map<std::string, std::string>>("Integer", mask));

    mask.clear();
    AddNumbers(&mask, "Decimal");
    transition_table->insert(std::pair<std::string, std::unordered_map<std::string, std::string>>("Double", mask));

    mask.clear();
    AddNumbers(&mask, "Decimal");
    mask.insert(std::pair<std::string, std::string>("E", "E"));
    mask.insert(std::pair<std::string, std::string>("e", "E"));
    AddSeparators(&mask, "Start");
    AddSpaces(&mask, "Start");
    transition_table->insert(std::pair<std::string, std::unordered_map<std::string, std::string>>("Decimal", mask));

    mask.clear();
    AddNumbers(&mask, "Exponent");
    mask.insert(std::pair<std::string, std::string>("+", "Exponent"));
    mask.insert(std::pair<std::string, std::string>("-", "Exponent"));
    transition_table->insert(std::pair<std::string, std::unordered_map<std::string, std::string>>("E", mask));

    mask.clear();
    AddNumbers(&mask, "Exponent");
    AddSeparators(&mask, "Start");
    AddSpaces(&mask, "Start");
    transition_table->insert(std::pair<std::string, std::unordered_map<std::string, std::string>>("Exponent", mask));
}

void Scanner()
{
    std::vector<std::string> conditions;
    std::unordered_map<std::string, std::unordered_map<std::string, std::string>> transition_table;
    FillDFA(&conditions, &transition_table);
    std::ifstream input_file("input.txt");
    std::string current_state = "Start";
    std::string buffer;
    std::string lexem;
    buffer += static_cast<char>(input_file.get());
    lexem += buffer;
    while (buffer != std::string(1, static_cast<char>(EOF)))
    {
        if (((buffer == "<") || (buffer == ">") || (buffer == "=")) && ((static_cast<char>(input_file.peek()) == '<') || (static_cast<char>(input_file.peek()) == '>') || (static_cast<char>(input_file.peek()) == '=')))
        {
            buffer += static_cast<char>(input_file.get());
            lexem += buffer;
        }
        if (transition_table[current_state].count(buffer) != 0)
        {
            current_state = transition_table[current_state].at(buffer);
            if (current_state == "Start")
            {
                std::cout << lexem << '\n';
                lexem.clear();
            }
            std::cout << buffer;
            buffer.clear();
        }
        else if ((current_state == "Comment") || (current_state == "Quote"))
        {
            lexem.clear();
            buffer.clear();
        }
        else
        {
            //std::cout << (buffer == "EOF");
            std::cout << "Unexpected symbol\n";
            break;
        }
        buffer += static_cast<char>(input_file.get());
    }
}

int main()
{
    Scanner();
    return 0;
}
