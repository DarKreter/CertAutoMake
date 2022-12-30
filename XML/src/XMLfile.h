#ifndef XMLFILE_H
#define XMLFILE_H

#include <iostream>
#include <fstream>
#include <windows.h>
#include <conio.h>
#include <vector>
#include <algorithm>
#include <string>
#include <list>
#include <clocale>
#include <sstream>
#include <locale>
#include "FilesManagment.h"

namespace xml
{

    struct Error_t
    {
        std::string What;
    };


    class XMLfile
    {
    public:
        std::wstring fileName;
        std::wstring data;
    public:
        std::wstring FileName();

        bool CheckElement(std::string tag);
        bool CheckElement(std::wstring tag);

        void EraseElement(std::string tag);
        void EraseElement(std::wstring tag);

        void ChangeElementContent(std::string tag, std::string newData);
        void ChangeElementContent(std::wstring tag, std::wstring newData);

        void AddElement(std::wstring tag, std::wstring newData, std::wstring tagBefore);
        void AddElement(std::string tag, std::string newData, std::string tagBefore);

        void AddNestedElement(std::vector<std::string> tags, std::string newData, std::string tagBefore);
        void AddNestedElement(std::vector<std::wstring> tags, std::wstring newData, std::wstring tagBefore);

        std::string ElementContent(std::string tag) const;
        std::wstring ElementContent(std::wstring tag) const;

        XMLfile(std::wstring name);
        XMLfile(std::string name);
        void ReadFromFile();
        void SaveToFile();

    };

}


#endif // XMLFILE_H
