#pragma once
#include <string>
#include <vector>
#include <memory>

// Base class for all AST nodes
class ASTNode {
    public:
        virtual ~ASTNode() = default;
};

// Represents a condition
class ConditionNode : public ASTNode {
    public:
        std::string condition;
        char type;

        ConditionNode(const std::string& cond, char type) : condition(cond), type(type) {}
};

// Represents a line in the file
class LineNode : public ASTNode {
    public:
        std::string line;

        LineNode(const std::string& ln) : line(ln) {}
};

// Represents a file with conditions and lines
class FileNode : public ASTNode {
    public:
        std::vector<std::shared_ptr<ConditionNode>> conditions;
        std::vector<std::shared_ptr<LineNode>> lines;
        std::string filename, prefix, postfix;

        void addCondition(const std::shared_ptr<ConditionNode>& condition);
        void addLine(const std::shared_ptr<LineNode>& line);
};
