#include "Messager.h"
#include <algorithm>
#include <cassert>

Messager::Messager(std::istream &in, unsigned long int key) {
    std::string readline; std::getline(in, readline);
    m_dll = std::make_unique<DoubleLinkedList>(std::stol(readline));
    for(;std::getline(in, readline);) {
        m_dll->append(std::stol(readline));
    }
    m_dll->applyKey(key);
}

void Messager::mix() {
    m_dll->mix();
}

long int Messager::getScore() {
    return m_dll->score();
}

long int DoubleLinkedList::score() {
    unsigned int d1 = 1000 % m_nodes.size(); bool d1_added = false;
    unsigned int d2 = 2000 % m_nodes.size(); bool d2_added = false;
    unsigned int d3 = 3000 % m_nodes.size(); bool d3_added = false;
    unsigned int i = 0;
    long int res = 0;
    for(auto itr = zero_ptr; !d1_added || !d2_added || !d3_added; itr = itr->next, i++) {
        if(i == d1 && !d1_added) {
            res += itr->i; d1_added = true;
        }
        if(i == d2 && !d2_added) {
            res += itr->i; d2_added = true;
        }
        if(i == d3 && !d3_added) {
            res += itr->i; d3_added = true;
        }
    }
    return res;
}

DoubleLinkedList::DoubleLinkedList(int first_number) {
    m_nodes.push_back(std::make_unique<Node>(Node({first_number, nullptr, nullptr})));
    m_nodes.back()->prev = m_nodes.back().get();
    m_nodes.back()->next = m_nodes.back().get();
    m_nodes.back().get();
    if(first_number == 0) { zero_ptr = m_nodes.back().get();}
}

void DoubleLinkedList::mix() {
    for(auto &p: m_nodes) {
        move(p.get());
    }
}

void DoubleLinkedList::move(Node * p) {
    if (p->i == 0) {return;}
    auto old_ptr = p;
    // Remove old from list
    p->prev->next = p->next;
    p->next->prev = p->prev;

    int inc = (p->i > 0);
    for(long int i = labs(p->i) % (long int)(m_nodes.size() - 1); i > 0; i--) {
        p = inc ? p->next : p->prev;
    }
    // x > 0, insert after p
    if(inc) {
        auto old_nxt = p->next;
        p->next = old_ptr;
        old_nxt->prev = old_ptr;
        old_ptr->next = old_nxt;
        old_ptr->prev = p;
    }
    else {
        // x < 0, insert before p
        auto old_prv = p->prev;
        p->prev = old_ptr;
        old_prv->next = old_ptr;
        old_ptr->next = p;
        old_ptr->prev = old_prv;
    }
}

void DoubleLinkedList::append(int x) {
    Node * prv = m_nodes.back().get();
    Node * nxt = m_nodes.front().get();
    m_nodes.push_back(std::make_unique<Node>(Node({x, prv, nxt})));
    prv->next = m_nodes.back().get();
    nxt->prev = m_nodes.back().get();
    if (x == 0) { zero_ptr = m_nodes.back().get();}
}

void DoubleLinkedList::applyKey(unsigned long int key) {
    for(auto &p: m_nodes) {
        p->i *= key;
    }
}


std::ostream& operator<<(std::ostream& os, const DoubleLinkedList& dt)
{
    auto ptr = dt.zero_ptr;
    do {
        os << ptr->i << ", ";
        ptr = ptr->next;
    } while(ptr != dt.zero_ptr);
    return os;
}