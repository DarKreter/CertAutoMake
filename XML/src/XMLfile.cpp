#include "XMLfile.h"

namespace xml
{
    XMLfile::XMLfile(std::wstring name): fileName{name}
    {
        data = fm::ReadFileW(fileName);
    }
    XMLfile::XMLfile(std::string name) : XMLfile(sm::STWS(name))
    {
        ;
    }

    std::wstring XMLfile::FileName()
    {
        return fileName;
    }

    void XMLfile::ReadFromFile()
    {
        data = fm::ReadFileW(fileName);
    }

    void XMLfile::SaveToFile()
    {
        fm::MakeFileW(fileName, data);
    }

    void XMLfile::EraseElement(std::wstring tag)
    {
        std::wstring endTag = L"</" + tag + L">";
        tag = L"<" + tag + L">";

        uint64_t whereBegin = data.find(tag);
        if (whereBegin == std::wstring::npos)   throw Error_t{ "Nie znaleziono tagu " + sm::WSTS(tag) + " do usuniecia!" };
        uint64_t whereEnd = data.find(endTag);
        if (whereEnd == std::wstring::npos)   throw Error_t{ "Nie znaleziono tagu " + sm::WSTS(endTag) + " do usuniecia!" };
        whereEnd += endTag.length();

        data.erase(whereBegin, whereEnd - whereBegin);
    }
    void XMLfile::EraseElement(std::string tag)
    {
        this->EraseElement(sm::STWS(tag));
    }

    std::wstring XMLfile::ElementContent(std::wstring tag) const
    {
        std::wstring endTag = L"</" + tag + L">";
        tag = L"<" + tag + L">";

        uint64_t whereBegin = data.find(tag);
        if (whereBegin == std::wstring::npos)   throw Error_t{ "Nie znaleziono tagu " + sm::WSTS(tag) + " do przeczytania!" };
        uint64_t whereEnd = data.find(endTag);
        if (whereEnd == std::wstring::npos)   throw Error_t{ "Nie znaleziono tagu " + sm::WSTS(endTag) + " do przeczytania!" };
        whereBegin += tag.length();

        return data.substr(whereBegin, whereEnd - whereBegin);
    }
    std::string XMLfile::ElementContent(std::string tag) const
    {
        return sm::WSTS( this->ElementContent(sm::STWS(tag)) );
    }

    void XMLfile::ChangeElementContent(std::wstring tag, std::wstring newData)
    {
        std::wstring endTag = L"</" + tag + L">";
        tag = L"<" + tag + L">";

        uint64_t whereBegin = data.find(tag);
        if (whereBegin == std::wstring::npos)   throw Error_t{ "Nie znaleziono tagu " + sm::WSTS(tag) + " do przeczytania!" };
        uint64_t whereEnd = data.find(endTag);
        if (whereEnd == std::wstring::npos)   throw Error_t{ "Nie znaleziono tagu " + sm::WSTS(endTag) + " do przeczytania!" };
        whereBegin += tag.length();

        data.replace(whereBegin, whereEnd - whereBegin, newData);
    }
    void XMLfile::ChangeElementContent(std::string tag, std::string newData)
    {
        this->ChangeElementContent(sm::STWS(tag), sm::STWS(newData));
    }

    void XMLfile::AddElement(std::wstring tag, std::wstring newData, std::wstring tagBefore)
    {
        std::wstring tagBeforeEnd = L"</" + tagBefore + L">";

        uint64_t whereTagBeforeEnd = data.find(tagBeforeEnd);
        if (whereTagBeforeEnd == std::wstring::npos)   throw Error_t{ "Nie znaleziono tagu " + sm::WSTS(tagBeforeEnd) + " do przeczytania!" };
        whereTagBeforeEnd += tagBeforeEnd.length();

        newData = L"\n<" + tag + L">" + newData + L"</" + tag + L">\n";

        data.insert(whereTagBeforeEnd, newData);
    }
    void XMLfile::AddElement(std::string tag, std::string newData, std::string tagBefore)
    {
        this->AddElement(sm::STWS(tag), sm::STWS(newData), sm::STWS(tagBefore));
    }

    void XMLfile::AddNestedElement(std::vector<std::wstring> tags, std::wstring newData, std::wstring tagBefore)
    {
        std::wstring tagBeforeEnd = L"</" + tagBefore + L">";

        uint64_t whereTagBeforeEnd = data.find(tagBeforeEnd);
        if (whereTagBeforeEnd == std::wstring::npos)   throw Error_t{ "Nie znaleziono tagu " + sm::WSTS(tagBeforeEnd) + " do przeczytania!" };
        whereTagBeforeEnd += tagBeforeEnd.length();

        std::wstring newDataFinal = L"\n";
        for (int i = 0; i < tags.size(); i++)
            newDataFinal += L"<" + tags[i] + L">";
        newDataFinal += newData;
        for (int i = tags.size() - 1; i >= 0; i--)
            newDataFinal += L"</" + tags[i] + L">";
        newDataFinal += L"\n";

        data.insert(whereTagBeforeEnd, newDataFinal);
    }
    void XMLfile::AddNestedElement(std::vector<std::string> tags, std::string newData, std::string tagBefore)
    {
        std::vector<std::wstring> temp;
        for (auto e : tags)
            temp.push_back(sm::STWS(e));

        this->AddNestedElement(temp, sm::STWS(newData), sm::STWS(tagBefore));
    }

    bool XMLfile::CheckElement(std::wstring tag)
    {
        tag = L"<" + tag + L">";

        uint64_t where = data.find(tag);
        if (where == std::wstring::npos)   return false;

        return true;
    }
    bool XMLfile::CheckElement(std::string tag)
    {
        return this->CheckElement(sm::STWS(tag));
    }

}