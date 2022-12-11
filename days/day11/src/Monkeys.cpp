#include "Monkeys.h"
#include <regex>
#include <iostream>
#include <cassert>

Monkey::Monkey(std::vector<unsigned long int> items, Monkey::Op opcode, unsigned int operand,
    unsigned int divisor, unsigned int true_target, unsigned int false_target, unsigned int worry_divisor) :
    m_items(items),
    m_opcode(opcode),
    m_operand(operand),
    m_divisor(divisor),
    m_true_target(true_target),
    m_false_target(false_target),
    m_inspections(0),
    m_worry_divisor(worry_divisor)  {}

std::map<unsigned int, std::vector<unsigned long int>> Monkey::processRound(unsigned int total_worry_modulus) {
    std::map<unsigned int, std::vector<unsigned long int>> ret = {{m_true_target, {}}, {m_false_target, {}}};
    (void)total_worry_modulus;
    for(int items = m_items.size(); items>0; items--) {
        m_inspections++;
        auto item = m_items.back();
        m_items.pop_back();
        if (m_opcode == ADD) { item += m_operand;}
        else if (m_opcode == MULT) { item *= m_operand;}
        else if (m_opcode == SQUARE) { item *= item;}
        item /= m_worry_divisor;
        item %= total_worry_modulus;
        unsigned int target = ((item % m_divisor) == 0) ? m_true_target : m_false_target;
        ret[target].push_back(item);
    }
    return ret;
}

Monkeys::Monkeys(std::istream &input, unsigned int worry_divisor ) {
    std::string readline;
    std::smatch m;
    unsigned int monkey = 0;
    m_total_worry_modulus = 1;
    do {
        std::vector<unsigned long int> items;
        Monkey::Op opcode = Monkey::Op::ADD;
        unsigned int operand = 0;
        unsigned int divisor = 0, true_target = 0, false_target = 0;


        std::getline(input, readline);
        const std::regex re1("Monkey (\\d*):");
        std::regex_match(readline, m, re1);
        assert(m.size() == 2);
        assert(monkey == std::stoul(m[1]));


        std::getline(input, readline);
        const std::regex re2("  Starting items: ([\\d,\\s]*)");
        std::regex_match(readline, m, re2);
        assert(m.size() == 2);
        size_t last = 0;
        for(size_t x = m.str(1).find(", "); x != std::string::npos; x = m.str(1).find(", ", x + 1)) {
            items.push_back(std::stoul(m.str(1).substr(last, x)));
            last = x + 2;
        }
        items.push_back(std::stoul(m.str(1).substr(last)));

        std::getline(input, readline);
        const std::regex re3("  Operation: new = old (.) ([\\d|old]*)");
        std::regex_match(readline, m, re3);
        assert(m.size() == 3);
        if(m.str(1) == "+") {
            opcode = Monkey::Op::ADD;
            operand = std::stoul(m.str(2));
        }
        else if (m.str(2) == "old"){
            opcode = Monkey::Op::SQUARE;
        }
        else {
            opcode = Monkey::Op::MULT;
            operand = std::stoul(m.str(2));
        }

        std::getline(input, readline);
        const std::regex re4("  Test: divisible by ([\\d]*)");
        std::regex_match(readline, m, re4);
        assert(m.size() == 2);
        divisor = std::stoul(m.str(1));
        
        std::getline(input, readline);
        const std::regex re5("    If true: throw to monkey ([\\d]*)");
        std::regex_match(readline, m, re5);
        assert(m.size() == 2);
        true_target = std::stoul(m.str(1));

        std::getline(input, readline);
        const std::regex re6("    If false: throw to monkey ([\\d]*)");
        std::regex_match(readline, m, re6);
        assert(m.size() == 2);
        false_target = std::stoul(m.str(1));

        m_monkeys.push_back(std::make_unique<Monkey>(items, opcode, operand,
            divisor, true_target, false_target, worry_divisor));
        m_total_worry_modulus *= divisor;
        monkey++;
    } while (std::getline(input, readline)); // get empty line or end
    
}

void Monkeys::runRound() {
    for(unsigned int i = 0; i < m_monkeys.size(); i++) {
        auto ret = m_monkeys[i]->processRound(m_total_worry_modulus);
        for(auto const &x: ret) {
            m_monkeys[x.first]->addItems(x.second);
        }
    }
}

unsigned long int Monkeys::getMonkeyBusiness() {
    unsigned long int max = 0;
    unsigned long int second_max = 0;
    for(unsigned int i = 0; i < m_monkeys.size(); i++) {
        auto inspections = m_monkeys[i]->getInspections();
        if (inspections > max) {
            second_max = max;
            max = inspections;
        }
        else if (inspections > second_max) {
            second_max = inspections;
        }
    }
    return max * second_max;
}