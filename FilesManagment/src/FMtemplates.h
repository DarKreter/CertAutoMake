#ifndef FMTEMPLATES_H
#define FMTEMPLATES_H

/**
	Funkcja przeszukuje wskazany katalog i zwraca wszystkie nazwy plikow i folderow znajdujace sie w nim jako stringi
	Mozna podac filtr w ktorym po podaniu rozszerzen tylko pliki z tymi rozszerzeniami pozostana w wektorze
	@param sciezka do katalogu do przejrzenia | ""  - oznacza katalog pliku wykonywalnego
		   Zalecam uzycia funkcji fm::GetExecutablePath() do dosatnia katalogu pliku wykonywalnego
	@param wektor do ktorego zostana dodane wykryte pliki spelniajace filtr | REFERENCJA
		   moze byc to wektor STRING'ow, musi miec kontruktor tworzacy obiekt na podstawie stringa
	@param wektor rozszerzen do zachowania | FORMAT: .* | domniemany argument [pusta lista] nazwy nie beda filtrowane | "" oznacza brak rozszerzenia
	@param Sa to wszystkie dodatkowe opcje ktore mozemy chciec ustawic
		   fm::ReadFir_e::nothing	-	zadna z powyzszych flag
		   fm::ReadFir_e::fullDir	-	nazwy beda pelnymi sciezkami bezwzglednymi zamiast po prostu nazwami
		   fm::ReadFir_e::includeDir-	zalaczy do wektora wszystkie nazwy folderow
		   fm::ReadFir_e::allFiles	-	wyszukuje pliki(foldery jesli wlaczymy inlcudeDir) we wszystkich podfolderach nie tylko w danej lokalizacji
		   Zeby zaznaczyc dwie flagi uzywamy operatora sumy bitowej |
		   EXAMPLE: fm::ReadFir_e::allFiles | fm::ReadFir_e::fullDir	ustawimy dwie flagi
	@return brak
*/
template<typename T>
inline void ReadDirectory(const std::string name, std::vector<T>& v, const std::vector<std::string>& filters, fm::ReadDir_e flag)
{
	//std::cout << static_cast<fm::ReadDirectoryFlag_t>(flag) << std::endl;
	bool dir	  = static_cast<bool>(flag & fm::ReadDir_e::includeDir);
	bool fullPath = static_cast<bool>(flag & fm::ReadDir_e::fullDir);
	bool allFiles = static_cast<bool>(flag & fm::ReadDir_e::allFiles);
	//std::cout << dir << fullPath << allFiles << std::endl;
	//std::cout << "name = " << name << std::endl;

	std::vector<std::string> tempFiles;
	std::vector<std::string> tempDir;

	std::string pattern(name);
	pattern.append("*");
	WIN32_FIND_DATA data;
	HANDLE hFind;

	std::wstring stemp = std::wstring(pattern.begin(), pattern.end());
	LPCWSTR sw = stemp.c_str();

	if ((hFind = FindFirstFile(sw, &data)) != INVALID_HANDLE_VALUE) {
		do {

			if (data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
			{
				std::string temppp{ sm::WSTS(data.cFileName) };

				if (fullPath)
					tempDir.push_back(name + temppp);
				else
					tempDir.push_back(temppp);
			}
			else
			{
				std::string temppp{ sm::WSTS(data.cFileName) };

				if (fullPath)
					tempFiles.push_back(name + temppp);
				else
					tempFiles.push_back(temppp);
			}

		} while (FindNextFile(hFind, &data) != 0);
		FindClose(hFind);
	}

	if (filters.empty() == false)
	{
		auto RemoverFiles([&filters](std::string t)
			{
				return FilesFilter(t, filters);
			}); //Lambda ktora zwroci true dla rozszerzen spoza puli
		remove_copy_if(begin(tempFiles), end(tempFiles), back_inserter(v), RemoverFiles);
	}
	else
		copy(begin(tempFiles), end(tempFiles), back_inserter(v));

	if (dir)
	{
		auto RemoverDir([](std::string t)
			{
				return (t.substr(t.length() - 1) == "."  || (t.length() > 1 && t.substr(t.length() - 2) == ".."));
			}); //Lambda ktora zwroci true dla kropek
		remove_copy_if(begin(tempDir), end(tempDir), back_inserter(v), RemoverDir);
	}

	if (allFiles)
	{
		auto recursionAllFiles = [name, &v, &filters, &flag, fullPath](std::string t)
		{
			//std::cout << "Check: " << t << "\t";
			if (t.substr(t.length() - 1) != "." && (t.length() == 1 || t.substr(t.length() - 2) != ".."))	//bez kropek
			{
				//std::cout << "Rekurencja dla folderu: " << t << std::endl;
				if(fullPath)
					ReadDirectory(t + "\\", v, filters, flag);
				else
					ReadDirectory(name + t + "\\", v, filters, flag);
			}
		};

		for_each(begin(tempDir), end(tempDir), recursionAllFiles);
	}


}

/**
	Dziala tak jak ReadDirectory ale czyta nazwy plikow jako wstringi
	Kazdy obiekt vectora musi byc mozliwy do stworzenia na podstawie wstringa
*/
template<typename T>
void ReadDirectoryWS(const std::wstring name, std::vector<T>& v, const std::vector<std::string>& filters, fm::ReadDir_e flag)
{
	//std::cout << static_cast<fm::ReadDirectoryFlag_t>(flag) << std::endl;
	bool dir = static_cast<bool>(flag & fm::ReadDir_e::includeDir);
	bool fullPath = static_cast<bool>(flag & fm::ReadDir_e::fullDir);
	bool allFiles = static_cast<bool>(flag & fm::ReadDir_e::allFiles);
	//std::cout << dir << fullPath << allFiles << std::endl;
	//std::cout << "name = " << name << std::endl;

	std::vector<std::wstring> tempFiles;
	std::vector<std::wstring> tempDir;

	WIN32_FIND_DATA data;
	HANDLE hFind;

	std::wstring stemp = name + L"*";
	LPCWSTR sw = stemp.c_str();

	if ((hFind = FindFirstFile(sw, &data)) != INVALID_HANDLE_VALUE) {
		do {

			if (data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
			{
				std::wstring wsTmp(name.begin(), name.end());

				if (fullPath)
					tempDir.push_back(wsTmp + data.cFileName);
				else
					tempDir.push_back(data.cFileName);
			}
			else
			{
				std::wstring wsTmp(name.begin(), name.end());

				if (fullPath)
					tempFiles.push_back(wsTmp + data.cFileName);
				else
					tempFiles.push_back(data.cFileName);
			}

		} while (FindNextFile(hFind, &data) != 0);
		FindClose(hFind);
	}

	if (filters.empty() == false)
	{
		auto RemoverFiles([&filters](std::wstring t)
			{
				return FilesFilter(t, filters);
			}); //Lambda ktora zwroci true dla rozszerzen spoza puli
		remove_copy_if(begin(tempFiles), end(tempFiles), back_inserter(v), RemoverFiles);
	}
	else
		copy(begin(tempFiles), end(tempFiles), back_inserter(v));

	if (dir)
	{
		auto RemoverDir([](std::wstring t)
			{
				return (t.substr(t.length() - 1) == L"." || (t.length() > 1 && t.substr(t.length() - 2) == L".."));
			}); //Lambda ktora zwroci true dla kropek

		remove_copy_if(begin(tempDir), end(tempDir), back_inserter(v), RemoverDir);
	}


	if (allFiles)
	{
		auto recursionAllFiles = [name, &v, &filters, &flag, fullPath](std::wstring t)
		{
			//std::cout << "Check: " << t << "\t";
			if (t.substr(t.length() - 1) != L"." && (t.length() == 1 || t.substr(t.length() - 2) != L".."))	//bez kropek
			{
				//std::cout << "Rekurencja dla folderu: " << sm::WSTS(t) << std::endl;
				if (fullPath)
					ReadDirectoryWS(t + L"\\", v, filters, flag);
				else
					ReadDirectoryWS(name + t + L"\\", v, filters, flag);
			}
		};

		for_each(begin(tempDir), end(tempDir), recursionAllFiles);
	}

}

#endif //FMTEMPLATES_H