#include "Directories.h"
#include <sstream>


void Directory::addFile(std::string name, unsigned int size) {
    m_files[name] = {name, size};
    auto dir = shared_from_this();
    do {
        dir->m_size += size;
        dir = dir->getParent();
    } while (dir != nullptr);
}

std::shared_ptr<Directory> Directory::addSubDirectory(std::string name) {
    m_subdirectories[name] = std::make_shared<Directory>(name, shared_from_this());
    return m_subdirectories[name];
}


DirectoryRoot::DirectoryRoot() {
    m_root = std::make_shared<Directory>("/", nullptr);
}

void DirectoryRoot::parseInput(std::string input) {
    if(input == "$ cd /") {
        m_cwd = m_root;
    }
    else if(input == "$ cd ..") {
        m_cwd = m_cwd->getParent();
    }
    else if(input.substr(0,5) == "$ cd ") {
        m_cwd = m_cwd->m_subdirectories.at(input.substr(5));
    }
    else if(input.substr(0,4) == "dir ") {
        auto dir = m_cwd->addSubDirectory(input.substr(4));
        m_dirlist.push_back(dir);
    }
    else if(input == "$ ls") {
        //do nothing, ls output incoming!
    }
    else { // new file
        auto idx = input.find(' ');
        m_cwd->addFile(input.substr(idx + 1), std::stoul(input.substr(0,idx)));
    }
}

unsigned int DirectoryRoot::getSmallDirScore() {
    unsigned int score = 0;
    for(auto const &dir: m_dirlist) {
        if (dir->m_size <= 100000) {
            score += dir->m_size;
        }
    }
    return score;
}
unsigned int DirectoryRoot::getDeleteCandidate() {
    unsigned int required_space = 30000000 - (70000000 - m_root->m_size);
    unsigned int mindirdelsize = m_root->m_size;
    for (auto const &dir: m_dirlist) {
        if (dir->m_size >= required_space && dir->m_size < mindirdelsize) {
            mindirdelsize = dir->m_size;
        }
    }
    return mindirdelsize;
}
