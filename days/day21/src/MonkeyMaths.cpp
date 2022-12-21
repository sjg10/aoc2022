#include "MonkeyMaths.h"
#include <cassert>
#include <algorithm>
#include <iostream>

MonkeyMaths::MonkeyMaths(std::istream &in) {
    for(std::string readline; std::getline(in,readline);) {
        std::string monkey = readline.substr(0,4);
        std::string eqn = readline.substr(6);
        try {
            unsigned long int val = std::stoul(eqn);
            if(monkey == "humn") {
                m_orig_equations[monkey] = Equation({val, PolynomialFraction(Polynomial({0,1}), Polynomial({1})), true, "","",NONE});
            }
            else {
                m_orig_equations[monkey] = Equation({val, PolynomialFraction(val), true, "","",NONE});
            }
        }
        catch (std::invalid_argument &e) {
            std::string a = eqn.substr(0,4);
            std::string op = eqn.substr(5,1);
            std::string b = eqn.substr(7,4);
            Op oper = (op == "+") ? Op::ADD : ((op == "*") ? Op::MULT :((op == "/") ? Op::DIV : Op::SUB));
            m_orig_equations[monkey] = Equation({0, PolynomialFraction(), false, a, b, oper});
        }
    }
}

void MonkeyMaths::reset() {
    for (auto const &eqn : m_orig_equations) {
        m_equations[eqn.first] = m_orig_equations[eqn.first];
        if(eqn.second.solved) {continue;}
        m_deps[eqn.first] = std::set({eqn.second.a,eqn.second.b});
        m_reverse_deps[eqn.second.a].push_back(eqn.first);
        m_reverse_deps[eqn.second.b].push_back(eqn.first);
    }
}

void MonkeyMaths::Equation::solve(unsigned long int a, PolynomialFraction const &ap, unsigned long int b, PolynomialFraction const &bp) {
    solved = true;
    switch (oper) {
        case ADD: value = a + b; humn_value = ap + bp; break;
        case MULT: value = a * b; humn_value = ap * bp;break;
        case DIV: value = a / b; humn_value = ap / bp;break;
        case SUB: value = a - b; humn_value = ap - bp;break;
        default: assert(false); break;;
    };
}

bool MonkeyMaths::solve(std::string monkey) {
    if(m_deps[monkey].empty() && !m_equations[monkey].solved) {
        m_equations[monkey].solve(
            m_equations[m_equations[monkey].a].value,
            m_equations[m_equations[monkey].a].humn_value,
            m_equations[m_equations[monkey].b].value,
            m_equations[m_equations[monkey].b].humn_value);
        return true;
    }
    else {return false;}
}

void MonkeyMaths::process() {
    std::list<std::string> queue;
    for (auto const &p : m_equations) {
        if(p.second.solved) {queue.push_back(p.first);}
    }
    while(!queue.empty()) {
        std::string monkey = queue.front();
        queue.pop_front();
        while(!m_reverse_deps[monkey].empty()) {
            std::string dep_monkey = m_reverse_deps[monkey].front();
            m_reverse_deps[monkey].pop_front();
            m_deps[dep_monkey].erase(monkey);
            if(solve(dep_monkey)) {
                queue.push_back(dep_monkey);
            };
        }
    }
}

unsigned long int MonkeyMaths::getRootScore() {
    reset();
    process();
    assert(m_equations["root"].solved);
    return m_equations["root"].value;
}


unsigned long int MonkeyMaths::getHumanScore() {
    auto a = m_orig_equations["root"].a;
    auto b = m_orig_equations["root"].b;
    PolynomialFraction p = m_equations[a].humn_value - m_equations[b].humn_value;
    auto root = p.root();
    assert(root > 0);
    return labs(root);
}