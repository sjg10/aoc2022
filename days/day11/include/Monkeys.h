#pragma once
#include <map>
#include <vector>
#include <memory>
#include <istream>

class Monkey {
public:
    enum Op {
        ADD,
        MULT,
        SQUARE
    };
    Monkey(std::vector<unsigned long int> items, Monkey::Op opcode, unsigned int operand, unsigned int divisor,
        unsigned int true_target, unsigned int false_target, unsigned int worry_divisor);
    std::map<unsigned int, std::vector<unsigned long int>> processRound(unsigned int total_worry_modulus);
    unsigned int getInspections() const {return m_inspections;};
    void addItems(std::vector<unsigned long int> items){m_items.insert(m_items.end(), items.begin(), items.end());};
private:
    std::vector<unsigned long int> m_items;
    Monkey::Op m_opcode;
    unsigned int m_operand;
    unsigned int m_divisor;
    unsigned int m_true_target;
    unsigned int m_false_target;
    unsigned int m_inspections;
    unsigned int m_worry_divisor;
};

class Monkeys {
public:
    Monkeys(std::istream &input, unsigned int worry_divisor = 3);
    void runRound();
    unsigned long int getMonkeyBusiness();
private:
    std::vector<std::unique_ptr<Monkey>> m_monkeys;
    unsigned int m_total_worry_modulus = 1; // to stop item sizes getting too large
};