#include "FilesManagment.h"

using namespace std;



namespace fm
{
    fm::ReadDir_e operator|(const fm::ReadDir_e& x, const fm::ReadDir_e& y)
    {
        return static_cast<ReadDir_e>( static_cast<ReadDirectoryFlag_t>(x) | static_cast<ReadDirectoryFlag_t>(y) );
    }

    fm::ReadDir_e operator&(const fm::ReadDir_e& x, const fm::ReadDir_e& y)
    {
        return static_cast<ReadDir_e>(static_cast<ReadDirectoryFlag_t>(x) & static_cast<ReadDirectoryFlag_t>(y));
    }

    void CopyFile(std::string nameIn, std::string nameOUT)
    {
        string command = "copy /B /-Y /Z \"" + nameIn + "\" \"" + nameOUT + "\"";
        unsigned short error = system(command.c_str());

        if (error)
            throw Error_t{ "Error in copying file.\nFrom: " + nameIn + "\nTo: " + nameOUT + "\nError log: " + to_string(error) };
    }
    void CopyFileW(std::wstring nameIn, std::wstring nameOUT)
    {
        wstring command = L"copy /B /-Y /Z \"" + nameIn + L"\" \"" + nameOUT + L"\"";
        unsigned short error = _wsystem(command.c_str());

        if (error)
        {
            string err = sm::WSTS(L"Error in copying file.\nFrom: " + nameIn + L"\nTo: " + nameOUT + L"\nError log: ");
            err += to_string(error);
            throw Error_t{ err };
        }
    }
    void CopyFileWLog(std::wstring nameIn, std::wstring nameOUT, std::wostream& strumien)
    {
        strumien << "-------------COPY FILE-------------"
            << endl << "FROM:\t" << nameIn << endl << "TO:\t" << nameOUT << endl;
        Sleep(LOG_SLEEP);

        wstring command = L"copy /B /-Y /Z \"" + nameIn + L"\" \"" + nameOUT + L"\"";
        unsigned short error = _wsystem(command.c_str());
        Sleep(LOG_SLEEP);

        if (error)
            strumien << "ERROR: " << error << endl;
        else
            strumien << "SUCCESS!" << endl;
        Sleep(LOG_SLEEP);

    }
    void CopyFileLog(std::string nameIn, std::string nameOUT, std::ostream& strumien)
    {
        strumien << "-------------COPY FILE-------------" 
            << endl << "FROM:\t" << nameIn << endl << "TO:\t" << nameOUT << endl;
        Sleep(LOG_SLEEP);

        string command = "copy /B /-Y /Z \"" + nameIn + "\" \"" + nameOUT + "\"";
        unsigned short error = system(command.c_str());
        Sleep(LOG_SLEEP);

        if (error)
            strumien << "ERROR: " << error << endl;
        else
            strumien << "SUCCESS!" << endl;
        Sleep(LOG_SLEEP);

    }

    void MoveFile(std::string nameIn, std::string nameOUT)
    {
        string command = "move /-Y \"" + nameIn + "\" \"" + nameOUT + "\"";
        unsigned short error = system(command.c_str());

        if (error)
            throw Error_t{ "Error in moving file.\nFrom: " + nameIn + "\nTo: " + nameOUT + "\nError log: " + to_string(error) };
    }
    void MoveFileW(std::wstring nameIn, std::wstring nameOUT)
    {
        wstring command = L"move /-Y \"" + nameIn + L"\" \"" + nameOUT + L"\"";
        unsigned short error = _wsystem(command.c_str());

        if (error)
        {
            string err = sm::WSTS(L"Error in moving file.\nFrom: " + nameIn + L"\nTo: " + nameOUT + L"\nError log: ");
            err += to_string(error);
            throw Error_t{ err };
        }
    }
    void MoveFileWLog(std::wstring nameIn, std::wstring nameOUT, std::wostream& strumien)
    {
        strumien << "-------------MOVE FILE-------------"
            << endl << "FROM:\t" << nameIn << endl << "TO:\t" << nameOUT << endl;
        Sleep(LOG_SLEEP);

        wstring command = L"move /-Y \"" + nameIn + L"\" \"" + nameOUT + L"\"";
        unsigned short error = _wsystem(command.c_str());
        Sleep(LOG_SLEEP);

        if (error)
            strumien << "ERROR: " << error << endl;
        else
            strumien << "SUCCESS!" << endl;
        Sleep(LOG_SLEEP);

    }
    void MoveFileLog(std::string nameIn, std::string nameOUT, std::ostream& strumien)
    {
        strumien << "-------------MOVE FILE-------------"
            << endl << "FROM:\t" << nameIn << endl << "TO:\t" << nameOUT << endl;
        Sleep(LOG_SLEEP);

        string command = "move /-Y \"" + nameIn + "\" \"" + nameOUT + "\"";
        unsigned short error = system(command.c_str());
        Sleep(LOG_SLEEP);

        if (error)
            strumien << "ERROR: " << error << endl;
        else
            strumien << "SUCCESS!" << endl;
        Sleep(LOG_SLEEP);

    }

    void RenameFile(std::string oldName, std::string newName)
    {
        string command = "rename \"" + oldName + "\" \"" + newName + "\"";
        unsigned short error = system(command.c_str());

        if (error)
            throw Error_t{ "Error in changing file name.\nFile: " + oldName + "\nNew name: " + newName + "\nError log: " + to_string(error) };
    }
    void RenameFileW(std::wstring oldName, std::wstring newName)
    {
        wstring command = L"rename \"" + oldName + L"\" \"" + newName + L"\"";
        unsigned short error = _wsystem(command.c_str());

        if (error)
        {
            string err = sm::WSTS(L"Error in changing file name.\nFile: " + oldName + L"\nNew name: " + newName + L"\nError log: ");
            err += to_string(error);
            throw Error_t{ err };
        }
    }
    void RenameFileWLog(std::wstring oldName, std::wstring newName, std::wostream& strumien)
    {
        strumien << "-------------RENAME FILE-------------"
            << endl << "File : " << oldName << endl << "New name : " << newName << endl;
        Sleep(LOG_SLEEP);

        wstring command = L"rename \"" + oldName + L"\" \"" + newName + L"\"";
        unsigned short error = _wsystem(command.c_str());
        Sleep(LOG_SLEEP);

        if (error)
            strumien << "ERROR: " << error << endl;
        else
            strumien << "SUCCESS!" << endl;
        Sleep(LOG_SLEEP);

    }
    void RenameFileLog(std::string oldName, std::string newName, std::ostream& strumien)
    {
        strumien << "-------------RENAME FILE-------------"
            << endl << "File : " << oldName << endl << "New name : " << newName << endl;
        Sleep(LOG_SLEEP);

        string command = "rename \"" + oldName + "\" \"" + newName + "\"";
        unsigned short error = system(command.c_str());
        Sleep(LOG_SLEEP);

        if (error)
            strumien << "ERROR: " << error << endl;
        else
            strumien << "SUCCESS!" << endl;
        Sleep(LOG_SLEEP);

    }

    void OpenFile(std::string name)
    {
        string command = "start \"\" \"" + name + "\"";
        unsigned short error = system(command.c_str());

        if (error)
            throw Error_t{ "Error in opening file name.\nFile: " + name + "\nError log: " + to_string(error) };
    }
    void OpenFileW(std::wstring name)
    {
        wstring command = L"start \"\" \"" + name + L"\"";

        unsigned short error = _wsystem(command.c_str());

        if (error)
        {
            string err = sm::WSTS(L"Error in opening file name.\nFile: " + name + L"\nError log: ");
            err += to_string(error);
            throw Error_t{ err };
        }
    }

    std::string  ReadFile(const std::string name, const unsigned long long rozmiar)
    {
        std::fstream file;
        file.open(name.c_str(), std::ios::in | std::ios::binary);
        if (!file.good())
            throw Error_t{ "Blad otwarcia pliku: " + name + " do czytania!" };

        char* tab = new char[rozmiar];
        file.read(tab, rozmiar);
        std::streamsize gcount = file.gcount();

        if (gcount == rozmiar)
            throw Error_t{ "Nie udalo sie wczytac calego pliku!\n Jego rozmiar jest wiekszy niz: " + std::to_string(rozmiar) };

        std::string temp(tab, gcount);

        delete[] tab;

        return temp;
    }
    std::wstring ReadFileW(const std::wstring filePath)
    {
        //-----------------------------------------------------
        //Wzialem se te funkcje stad: http://www.cplusplus.com/forum/beginner/107125/
        //Ogolnie to smiga jedyny sprawdzony sposob jaki znalazlem zeby odczytac poprawnie polskie znaki z wewnatrz pliku
        //Robi magie ale dzia³a :3
        //-----------------------------------------------------

        // A Windows console will only display Unicode special characters if
        // the translation mode is set to UTF-16
        int oldMode = _setmode(_fileno(stdout), _O_U16TEXT);

        // open the file as Unicode, so we can read into wstrings
        wifstream ifs(filePath);

        // imbue the file with a codecvt_utf8 facet which knows how to
        // convert from UTF-8 to UCS2 (the 2-byte part of UTF-16)
        // Note this is available in Visual C++ 2010 and later
        locale utf8_locale(locale(), new codecvt_utf8<wchar_t>);
        ifs.imbue(utf8_locale);

        // Skip the BOM (this gets translated from the UTF-8 to the
        // UTF-16 version so will be a single character.)
        //wchar_t bom = L'\0';
        //ifs.get(bom);

        // Read the file contents and write to wcout
        wstring line, final;
        while (getline(ifs, line))
            final += (line + L"\n");

        // put the tranlation mode back to normal
        _setmode(_fileno(stdout), oldMode);

        return final;
    }

    void MakeFile(std::string name, std::string data)
    {
        std::fstream file;
        file.open(name.c_str(), std::ios::out | std::ios::trunc | std::ios::binary);
        if (!file.good())
            throw Error_t{ "Blad stworzenia pliku " + name + " !" };

        file.write(data.c_str(), data.size());
        file.close();
    }
    void MakeFileW(std::wstring name, std::wstring data)
    {
        //-----------------------------------------------------
        //Wzialem se te funkcje stad: http://www.cplusplus.com/forum/beginner/107125/
        //Ogolnie to smiga jedyny sprawdzony sposob jaki znalazlem
        //zeby zapisywac poprawnie polskie znaki wczytanie funkcja ReadFileW
        //Robi magie ale dzia³a :3
        //-----------------------------------------------------
        int oldMode = _setmode(_fileno(stdout), _O_U16TEXT);
        wofstream output(name);

        locale utf8_locale(locale(), new codecvt_utf8<wchar_t>);
        output.imbue(utf8_locale); // Also imbue output

        //output << L'\xFEFF'; // write BOM
        output << data << endl;

        output.close();
        _setmode(_fileno(stdout), oldMode);

        //STARA WERSJA W SUMIE NIE WIEM CZY DZIA£A£A
        /*std::wfstream file;

        file.open(name, std::ios::out | std::ios::trunc | std::ios::binary);
        if (!file.good())
            throw Error_t{ "Blad stworzenia pliku " + sm::WSTS(name) + " !" };

        file.write(data.c_str(), data.size());
        file.close();*/
    }

    static std::string WSTS(std::wstring const& text) //WStringToWtring
    {
        std::locale const loc("");
        wchar_t const* from = text.c_str();
        std::size_t const len = text.size();
        std::vector<char> buffer(len + 1);
        std::use_facet<std::ctype<wchar_t> >(loc).narrow(from, from + len, '_', &buffer[0]);
        return std::string(&buffer[0], &buffer[len]);
    }

    bool FilesFilter(const string& s,const std::vector<std::string>& extension) //zwraca true jesli mamy usunac
    {
        bool havingExt = true;

        for (const auto& ex : extension)
            if (!ex.length())
                havingExt = false;
            else if (s.length() > 3 && (s.length() >= ex.length()) && ex == s.substr( s.length() - ex.length() )) ///Jesli dana nazwa jest tego rozszerzenia
                return false;   ///To ja zachowujemy

        if (!havingExt && s.find('.') == string::npos)
            return false;

        return true; //Jesli nie byla zadnego z powyzszych usuwamy       
    }
    bool FilesFilter(const wstring& s, const std::vector<std::string>& e) //zwraca true jesli mamy usunac
    {
        bool havingExt = true;
        std::vector<std::wstring> extension;

        for (const auto& s : e)
        {
            wstring abc(begin(s), end(s));
            extension.push_back(abc);
        }

        for (const auto& ex : extension)
            if (!ex.length())
                havingExt = false;
            else if (s.length() > 3 && (s.length() >= ex.length()) && ex == s.substr(s.length() - ex.length())) ///Jesli dana nazwa jest tego rozszerzenia
                return false;   ///To ja zachowujemy

        if (!havingExt && s.find('.') == string::npos)
            return false;

        return true; //Jesli nie byla zadnego z powyzszych usuwamy       
    }

    std::string GetExecutablePath()
    {
        wchar_t buffer[MAX_PATH];
        GetModuleFileName(NULL, buffer, MAX_PATH);

        wstring ws(buffer);

        string temp = string(ws.begin(), ws.end());
        string::size_type pos = temp.find_last_of('\\');
        return temp.substr(0, pos + 1);
    }
    std::wstring GetExecutablePathW()
    {
        wchar_t buffer[MAX_PATH];
        GetModuleFileName(NULL, buffer, MAX_PATH);

        wstring ws(buffer);

        string::size_type pos = ws.find_last_of('\\');
        return ws.substr(0, pos + 1);
    }

}
