#include "XMLfile.hpp"

using namespace std;

namespace xml {
XMLfile::XMLfile(std::string name) : fileName{name} { data = fm::ReadFile(fileName); }

std::string XMLfile::FileName() { return fileName; }

void XMLfile::ReadFromFile() { data = fm::ReadFile(fileName); }

void XMLfile::SaveToFile() { fm::MakeFile(fileName, data); }

void XMLfile::EraseElement(std::string tag)
{
    std::string endTag = "</" + tag + ">";
    tag = "<" + tag + ">";

    uint64_t whereBegin = data.find(tag);
    if(whereBegin == std::string::npos)
        throw Error_t{"Nie znaleziono tagu " + tag + " do usuniecia!"};
    uint64_t whereEnd = data.find(endTag);
    if(whereEnd == std::string::npos)
        throw Error_t{"Nie znaleziono tagu " + endTag + " do usuniecia!"};
    whereEnd += endTag.length();

    data.erase(whereBegin, whereEnd - whereBegin);
}

std::string XMLfile::ElementContent(std::string tag) const
{
    std::string endTag = "</" + tag + ">";
    tag = "<" + tag + ">";

    uint64_t whereBegin = data.find(tag);
    if(whereBegin == std::string::npos)
        throw Error_t{"Nie znaleziono tagu " + tag + " do przeczytania!"};
    uint64_t whereEnd = data.find(endTag);
    if(whereEnd == std::string::npos)
        throw Error_t{"Nie znaleziono tagu " + endTag + " do przeczytania!"};
    whereBegin += tag.length();

    return data.substr(whereBegin, whereEnd - whereBegin);
}

void XMLfile::ChangeElementContent(std::string tag, std::string newData)
{
    std::string endTag = "</" + tag + ">";
    tag = "<" + tag + ">";

    uint64_t whereBegin = data.find(tag);
    if(whereBegin == std::string::npos)
        throw Error_t{"Nie znaleziono tagu " + tag + " do przeczytania!"};
    uint64_t whereEnd = data.find(endTag);
    if(whereEnd == std::string::npos)
        throw Error_t{"Nie znaleziono tagu " + endTag + " do przeczytania!"};
    whereBegin += tag.length();

    data.replace(whereBegin, whereEnd - whereBegin, newData);
}

void XMLfile::AddElement(std::string tag, std::string newData, std::string tagBefore)
{
    std::string tagBeforeEnd = "</" + tagBefore + ">";

    uint64_t whereTagBeforeEnd = data.find(tagBeforeEnd);
    if(whereTagBeforeEnd == std::string::npos)
        throw Error_t{"Nie znaleziono tagu " + tagBeforeEnd + " do przeczytania!"};
    whereTagBeforeEnd += tagBeforeEnd.length();

    newData = "\n<" + tag + ">" + newData + "</" + tag + ">\n";

    data.insert(whereTagBeforeEnd, newData);
}

void XMLfile::AddNestedElement(std::vector<std::string> tags, std::string newData,
                               std::string tagBefore)
{
    std::string tagBeforeEnd = "</" + tagBefore + ">";

    uint64_t whereTagBeforeEnd = data.find(tagBeforeEnd);
    if(whereTagBeforeEnd == std::string::npos)
        throw Error_t{"Nie znaleziono tagu " + tagBeforeEnd + " do przeczytania!"};
    whereTagBeforeEnd += tagBeforeEnd.length();

    std::string newDataFinal = "\n";
    for(int i = 0; i < tags.size(); i++)
        newDataFinal += "<" + tags[i] + ">";
    newDataFinal += newData;
    for(int i = tags.size() - 1; i >= 0; i--)
        newDataFinal += "</" + tags[i] + ">";
    newDataFinal += "\n";

    data.insert(whereTagBeforeEnd, newDataFinal);
}

bool XMLfile::CheckElement(std::string tag)
{
    tag = "<" + tag + ">";

    uint64_t where = data.find(tag);
    if(where == std::string::npos)
        return false;

    return true;
}

} // namespace xml