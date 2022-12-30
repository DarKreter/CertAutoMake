#ifndef XMLFILE_H
#define XMLFILE_H

#include "FilesManagment.hpp"
#include <string>

namespace xml {

struct Error_t {
    std::string What;
};

class XMLfile {
public:
    std::string fileName;
    std::string data;

public:
    std::string FileName();
    bool CheckElement(std::string tag);
    void EraseElement(std::string tag);
    void ChangeElementContent(std::string tag, std::string newData);
    void AddElement(std::string tag, std::string newData, std::string tagBefore);
    void AddNestedElement(std::vector<std::string> tags, std::string newData,
                          std::string tagBefore);
    std::string ElementContent(std::string tag) const;

    XMLfile(std::string name);
    void ReadFromFile();
    void SaveToFile();

    bool operator==(const XMLfile& other)
    {
        return (fileName == other.fileName && data == other.data);
    }
    bool operator<(const XMLfile& other) { return (fileName < other.fileName); }
};

} // namespace xml

#endif // XMLFILE_H
