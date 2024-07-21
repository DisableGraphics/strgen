#include <stringgenerator.hpp>
#include <parser.hpp>
#include <unordered_set>
#include <random>
#include <tokens.hpp>

std::string StringGenerator::generate(const std::vector<std::shared_ptr<FileNode>>& files, const std::string &interconnect) {
    std::string finalString;
    std::unordered_set<std::shared_ptr<FileNode>> processedFiles;
    std::unordered_map<std::string, std::string> selected_lines;
    bool progress = true;
    while (progress) {
        progress = false;
        for (const auto& fileNode : files) {
            std::string prev_line;
            if (!processedFiles.contains(fileNode) && evaluateConditions(fileNode->conditions, finalString, selected_lines, prev_line)) {
                std::string line;
                if(prev_line.empty())
                    line = selectRandomLine(fileNode->lines);
                else
                    line = prev_line;
                if (!line.empty()) {
                    finalString += fileNode->prefix + line + fileNode->postfix + interconnect;
                    selected_lines.emplace(fileNode->filename, line);
                    processedFiles.insert(fileNode);
                    progress = true;
                }
            }
        }
    }
    if(finalString.size() >= interconnect.size()) {
        finalString = finalString.substr(0, finalString.size() - interconnect.size());
    }

    return finalString;
}

bool StringGenerator::evaluateConditions(const std::vector<std::shared_ptr<ConditionNode>>& conditions, const std::string& finalString, const std::unordered_map<std::string, std::string> &selected_lines, std::string &prev_line) {
    bool eval = true;
    for (const auto& condition : conditions) {
        if(!eval && condition->type == TOKEN_OR) {
            auto find = finalString.find(condition->condition);
            if(find != std::string::npos)
                eval = true;
        } else if(eval && condition->type == TOKEN_AND) {
            auto find = finalString.find(condition->condition);
            if(find == std::string::npos)
                eval = false;
        } else if(condition->type == TOKEN_EQUALS) {
            eval = selected_lines.contains(condition->condition);
            if(eval)
                prev_line = selected_lines.at(condition->condition);
        }
    }
    return eval;
}

std::string StringGenerator::selectRandomLine(const std::vector<std::shared_ptr<LineNode>>& lines) {
    if (lines.empty()) {
        return "";
    }

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, lines.size() - 1);

    return lines[dis(gen)]->line;
}