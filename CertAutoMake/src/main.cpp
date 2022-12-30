#include <iostream>
#include <algorithm>
#include <iterator>
#include <sstream>
#include <iomanip>

#include "XMLfile.h"
#include "encode.h"
#include "FilesManagment.h"
#include "Entertainment.h"

using namespace std;
using xml::XMLfile;


int main()
{
    try
    {
        vector<XMLfile> files;

        wstring path = L"";
        fm::ReadDirectoryWS(path, files, { ".xml" });

        if (files.empty())
        {
            ent::ChangeColor(ent::red);
            cout << "BRAK PLIKOW!\n";
            system("pause");
            return 0;
        }

        ent::ChangeColor(ent::white); system("pause");
        //------------------------------------------------
        string imagePath = "_Miniatura.jpg";

        string image;
        {

            istringstream imageINStr(fm::ReadFile(imagePath, 1'000'000));
            ostringstream imageOUTStr;

            b64::encoder En;
            En.encode(imageINStr, imageOUTStr);

            image = imageOUTStr.str();
        }

        //cout << image << endl;

        string temp;
        string kodWoj = "K_02";                     //Dolnoslaskie
        string kodPowiatu = "0223";                 //Wroclawski
        string kodGminy = "0223074";                //Sobótka-miasto

        //string kodPowiatu = "0262";                 //Legnica
        //string kodGminy = "0262011";                //Legnica
        // 
        //string kodPowiatu = "0220";                 //TRZEBNICKI
        //string kodGminy =   "0220034";              //Trzebnica

        //string kodPowiatu = "0264";                 //Wroclaw
        //string kodGminy = "0264029";                //Fabryczna
        //string kodGminy = "0264039";              //Krzyki
        //string kodGminy = "0264049";              //Psie Pole
        //string kodGminy = "0264069";              //Srodmiescie
        //string kodGminy = "0264059";              //Stare miasto

        constexpr short precyzjaDomu = 2, precyzjaLokalu = 2;

        for (auto& file : files)
        {

            //-----------------TUTAJ POPRAWIAJ!------------------------------
            wstring ulica = file.ElementContent(L"ulica");
            string temp = file.ElementContent("nrLokalu");
            string nrDomu = temp.substr(0, temp.find('/'));
            string nrLokalu   = temp.substr(temp.find('/') + 1);
            //string nrDomu = file.ElementContent("nrDomu");
            //string nrLokalu = file.ElementContent("nrLokalu");

            //cout << nrDomu << " " << nrLokalu << endl;
            //continue;

            file.ChangeElementContent("wojewodztwo", kodWoj);

            if (!file.CheckElement("terytPowiat"))
                file.AddNestedElement({ "terytPowiat", "kodPowiatu" }, kodPowiatu, "wojewodztwo");

            if (!file.CheckElement("terytGmina"))
                file.AddNestedElement({ "terytGmina", "kodGminy" }, kodGminy, "terytPowiat");

            if (file.ElementContent("nrLokalu").length() > 2)
                //file.ChangeElementContent("nrDomu", nrDomu);
                file.AddElement("nrDomu", nrDomu, "ulica");
                // "sed -i "s#<nrDomu />##g" *.xml" - remove broken tags

            if (file.ElementContent("nrLokalu").length() > 2)
                file.ChangeElementContent("nrLokalu", nrLokalu);

            //file.ChangeElementContent(L"ulica", ulica);

            if (!file.CheckElement("swiadectwoEnergetyczneImage"))
                file.AddNestedElement({ "swiadectwoEnergetyczneImage", "imageResource" }, image, "swiadectwoEnergetyczneType"); ///Dodanie miniaturki

            if (file.CheckElement("poczta"))
                file.EraseElement("poczta");

            file.SaveToFile();

            std::wstringstream newName;
            newName << std::setfill(L'0') << ulica << L"_" << std::setw(precyzjaDomu) << sm::STWS(nrDomu)
                << L"-" << std::setw(precyzjaLokalu) << sm::STWS(nrLokalu) 
                << L".xml";

            fm::RenameFileW(file.FileName(), newName.str());

            ent::ChangeColor(ent::white); cout  << sm::WSTS(newName.str()) ;
            ent::ChangeColor(ent::lime);  cout  << "\t\tDONE" << endl;
            ent::ChangeColor(ent::white);
        }


    }
    catch (fm::Error_t& error)
    {
        ent::ChangeColor(ent::red);
        cout << "Nastapil blad:" << endl
            << error.what << endl;
        system("pause");
        return 0;
    }
    catch (xml::Error_t& error)
    {
        ent::ChangeColor(ent::red);
        cout << "Nastapil blad:" << endl
            << error.What << endl;
        system("pause");
        return 0;
    }
    catch (...)
    {
        ent::ChangeColor(ent::red);
        cout << "Nastapil nieznany blad!" << endl;
        system("pause");
        return 0;
    }
    ent::ChangeColor(ent::lime);     cout << "Succes!" << endl;
    system("pause");

    return 0;

}