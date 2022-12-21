#pragma once
#include <string>
#include <iostream>
#include <sstream>
#include <map>
#include <list>
#include <vector>
#include <set>
#include <cmath>
#include <numeric>

class Polynomial {
public:
    Polynomial(std::vector<long int> coefficients)  {
        if(coefficients.size()) {m_coefficients = coefficients;}
    }
    Polynomial() {}
    long int evaluate(long int x) const {
        long int res = 0;
        long int mul = 1;
        for(unsigned int i = 0; i <  m_coefficients.size(); i++) {
            res += (mul * m_coefficients[i]);
            mul *= x;
        }
        return res;
    }
    Polynomial operator+(Polynomial const &obj) const {
        unsigned int order = std::max(m_coefficients.size(), obj.m_coefficients.size());
        std::vector<long int> coefficients;
        for(unsigned int i = 0; i < order; i++) {
            long int a = (i < m_coefficients.size()) ? m_coefficients[i] : 0;
            long int b = (i < obj.m_coefficients.size()) ? obj.m_coefficients[i] : 0;
            coefficients.push_back(a+b);
        }
        return Polynomial(coefficients);
    }
    Polynomial operator-(Polynomial const &obj) const {
        unsigned int order = std::max(m_coefficients.size(), obj.m_coefficients.size());
        std::vector<long int> coefficients = {};
        std::vector<long int> tmp = {};
        for(unsigned int i = 0; i < order; i++) {
            long int a = (i < m_coefficients.size()) ? m_coefficients[i] : 0;
            long int b = (i < obj.m_coefficients.size()) ? obj.m_coefficients[i] : 0;
            tmp.push_back(a-b);
            if (a-b != 0) {
                std::move(tmp.begin(), tmp.end(), std::back_inserter(coefficients)); 
                tmp = {};
            } 
        }
        return Polynomial(coefficients);
    }
    Polynomial operator*(Polynomial const &obj) const {
        unsigned int order = m_coefficients.size() + obj.m_coefficients.size() - 1;
        std::vector<long int> coefficients(order, 0);
        for(unsigned int i = 0; i <  m_coefficients.size(); i++) {
        for(unsigned int j = 0; j < obj.m_coefficients.size(); j++) {
            coefficients[i + j] += (m_coefficients[i] * obj.m_coefficients[j]);
        }
        }
        return Polynomial(coefficients);
    }

    void rescale(Polynomial &p) {
        if(p.m_coefficients.size() == 1) {
            long int gcd = std::gcd(p.m_coefficients[0], m_coefficients[0]);
            for(unsigned int i = 1; i < m_coefficients.size(); i++) {
                gcd = std::gcd(gcd, m_coefficients[i]);
            }
            for(unsigned int i = 0; i < m_coefficients.size(); i++) {
                m_coefficients[i] /= gcd;
            }
            p.m_coefficients[0] /= gcd;
        }
    }
    long int root() 
    {
        if (m_coefficients.size() == 2) {
            return (-1) * m_coefficients[0] / m_coefficients[1];
        }
        long int constant = labs(m_coefficients[0]);
        for (long int i = 1; i <= constant; i++) {
            if((m_coefficients[0] % i) == 0) {
                long int res = evaluate(i);
                if (res == 0) {
                    return i;
                }
            }
        }
        return 0;
    }
    friend std::ostream& operator<<(std::ostream& os, const Polynomial& p) {
        for(unsigned int i =0; i< p.m_coefficients.size() - 1; i++) {
             os << p.m_coefficients[i] << "x^" <<  i;
             if (p.m_coefficients[i + 1] >= 0) { os << "+";}
        }
        os << p.m_coefficients[p.m_coefficients.size() - 1] << "x^" <<  p.m_coefficients.size() - 1;
        return os;
    }

private:
    std::vector<long int> m_coefficients = {0};
};


class PolynomialFraction {
public:
    PolynomialFraction(Polynomial const &numerator, Polynomial const &denominator)  : m_numerator(numerator), m_denominator(denominator) {}
    PolynomialFraction() {m_numerator = Polynomial(); m_denominator = Polynomial({1});}
    PolynomialFraction(long int x) {m_numerator = Polynomial({x}); m_denominator = Polynomial({1});}
    PolynomialFraction operator+(PolynomialFraction const &obj) const  {
        Polynomial d = m_denominator * obj.m_denominator;
        Polynomial n = (obj.m_denominator * m_numerator) + (m_denominator * obj.m_numerator);
        auto p =  PolynomialFraction(n,d);
        p.m_numerator.rescale(p.m_denominator);
        return p;
    }
    PolynomialFraction operator-(PolynomialFraction const &obj) const  {
        Polynomial d = m_denominator * obj.m_denominator;
        Polynomial l =  (m_numerator * obj.m_denominator);
        Polynomial r =  (obj.m_numerator * m_denominator);
        Polynomial n = l - r;
        auto p =  PolynomialFraction(n,d);
        p.m_numerator.rescale(p.m_denominator);
        return p;
    }
    PolynomialFraction operator*(PolynomialFraction const &obj) const  {
        auto p = PolynomialFraction(m_numerator*obj.m_numerator, m_denominator * obj.m_denominator);
        p.m_numerator.rescale(p.m_denominator);
        return p;
    }
    PolynomialFraction operator/(PolynomialFraction const &obj) const  {
        auto p =  PolynomialFraction(m_numerator*obj.m_denominator, m_denominator * obj.m_numerator);
        p.m_numerator.rescale(p.m_denominator);
        return p;
    }
    long int root() {
        return m_numerator.root();
    }
    friend std::ostream& operator<<(std::ostream& os, const PolynomialFraction& p) {
        os << "(" << p.m_numerator << ")/(" << p.m_denominator << ")";
        return os;
    }
private:
    Polynomial m_numerator;
    Polynomial m_denominator;
};




class MonkeyMaths {
public:
    MonkeyMaths(std::istream &in);
    unsigned long int getRootScore();
    unsigned long int getHumanScore();
private:
    // If all deps are solved for a monkey, solve the monkey and return true, else false
    void process();
    void reset();
    bool solve(std::string monkey);
    enum Op {
        NONE,
        ADD,
        SUB,
        MULT,
        DIV
    };
    struct Equation {
        unsigned long int value;
        PolynomialFraction humn_value;
        bool solved;
        std::string a;
        std::string b;
        Op oper;
        void solve(unsigned long int a, unsigned long int b);
        void solve(unsigned long int a, PolynomialFraction const &ap, unsigned long int b, PolynomialFraction const &bp);
    };
    std::map<std::string, Equation> m_orig_equations; // from load
    std::map<std::string, Equation> m_equations; // running
    std::map<std::string, std::set<std::string>> m_deps;
    std::map<std::string, std::list<std::string>> m_reverse_deps;
};