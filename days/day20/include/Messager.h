#pragma once
#include <iostream>
#include <list>
#include <vector>
#include <memory>
#include <map>

using MessageElement = std::pair<int, bool>; // number,visited


class DoubleLinkedList {
public:
    DoubleLinkedList(int first_number);
    long int score();
    void append(int x);
    void mix();
    void applyKey(unsigned long int key);
    friend std::ostream& operator<<(std::ostream& os, const DoubleLinkedList& dt);
private:
    struct Node {
        long int i;
        Node * prev;
        Node * next;
    };
    std::vector<std::unique_ptr<Node>> m_nodes; // node storage
    Node * zero_ptr = nullptr; // keep track of zero
    void move(Node * p); // Move a node its number of spaces
};


class Messager {
public:
    Messager(std::istream &in, unsigned long int key = 1);
    void mix();
    long int getScore();
private:
    std::unique_ptr<DoubleLinkedList> m_dll;
};