#include <memory>
#include <map>
#include <vector>
#include <string>



struct ElfFile {
    std::string name;
    unsigned int size;
};
class DirectoryRoot;

class Directory : public std::enable_shared_from_this<Directory>{
public:
    Directory(std::string name, std::shared_ptr<Directory> parent) : m_name(name), m_parent(parent) {};
    void addFile(std::string name, unsigned int size);
    std::shared_ptr<Directory> addSubDirectory(std::string name);
    std::shared_ptr<Directory> getParent() {return m_parent;}
    friend DirectoryRoot;
private:
    std::string m_name;
    unsigned int m_size = 0;
    std::shared_ptr<Directory> m_parent;
    std::map<std::string, std::shared_ptr<Directory>> m_subdirectories;
    std::map<std::string, ElfFile> m_files;
};

class DirectoryRoot {
public:
    DirectoryRoot();
    void parseInput(std::string input);
    unsigned int getSmallDirScore();
    unsigned int getDeleteCandidate();
private:
    std::shared_ptr<Directory> m_root;
    std::shared_ptr<Directory> m_cwd;
    std::vector<std::shared_ptr<Directory>> m_dirlist; // for easy iteration
};