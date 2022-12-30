#include <iomanip>
#include <iostream>

#include "Entertainment.hpp"
#include "FilesManagment.hpp"
#include "XMLfile.hpp"
#include "encode.hpp"

using namespace std;
using ent::Format_t;
using xml::XMLfile;

int main()
{
    Format_t errorColor(Format_t::Color::red);
    Format_t successColor(Format_t::Color::green);
    Format_t dataColor(Format_t::Color::white);

    try {
        vector<XMLfile> files;

        string path = "";
        fm::ReadDirectory(path, files, {"*.xml"});

        if(files.empty()) {

            cout << errorColor << "BRAK PLIKOW!\n";
            cin.get();
            return 0;
        }
        cout << dataColor;
        cout << "Press enter to continue";
        cin.get();
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

        // cout << image << endl;

        string temp;
        string kodWoj = "K_02"; // Dolnoslaskie
        // string kodPowiatu = "0223";  // Wroclawski
        // string kodGminy = "0223074"; // Sob�tka-miasto

        // string kodPowiatu = "0262";                 //Legnica
        // string kodGminy = "0262011";                //Legnica
        //
        // string kodPowiatu = "0220";                 //TRZEBNICKI
        // string kodGminy =   "0220034";              //Trzebnica

        string kodPowiatu = "0264"; // Wroclaw
        // string kodGminy = "0264029"; // Fabryczna
        // string kodGminy = "0264039";              //Krzyki
        string kodGminy = "0264049"; // Psie Pole
        // string kodGminy = "0264069";              //Srodmiescie
        // string kodGminy = "0264059";              //Stare miasto

        constexpr short precyzjaDomu = 2, precyzjaLokalu = 2;

        for(auto& file : files) {

            //-----------------TUTAJ POPRAWIAJ!------------------------------
            string ulica = file.ElementContent("ulica");
            string temp = file.ElementContent("nrLokalu");
            string nrDomu = temp.substr(0, temp.find('/'));
            string nrLokalu = temp.substr(temp.find('/') + 1);
            // string nrDomu = file.ElementContent("nrDomu");
            // string nrLokalu = file.ElementContent("nrLokalu");

            // cout << nrDomu << " " << nrLokalu << endl;
            // continue;

            file.ChangeElementContent("wojewodztwo", kodWoj);

            if(!file.CheckElement("terytPowiat"))
                file.AddNestedElement({"terytPowiat", "kodPowiatu"}, kodPowiatu, "wojewodztwo");

            if(!file.CheckElement("terytGmina"))
                file.AddNestedElement({"terytGmina", "kodGminy"}, kodGminy, "terytPowiat");

            if(file.ElementContent("nrLokalu").length() > 2)
                file.ChangeElementContent("nrDomu", nrDomu);
            // file.AddElement("nrDomu", nrDomu, "ulica");
            // "sed -i "s#<nrDomu />##g" *.xml" - remove broken tags

            if(file.ElementContent("nrLokalu").length() > 2)
                file.ChangeElementContent("nrLokalu", nrLokalu);

            // file.ChangeElementContent("ulica", ulica);

            if(!file.CheckElement("swiadectwoEnergetyczneImage"))
                file.AddNestedElement({"swiadectwoEnergetyczneImage", "imageResource"}, image,
                                      "swiadectwoEnergetyczneType"); /// Dodanie miniaturki

            if(file.CheckElement("poczta"))
                file.EraseElement("poczta");

            file.SaveToFile();

            std::stringstream newName;
            newName << std::setfill('0') << ulica << "_" << std::setw(precyzjaDomu) << nrDomu << "-"
                    << std::setw(precyzjaLokalu) << nrLokalu << ".xml";

            fm::RenameFile(file.FileName(), newName.str());

            cout << dataColor << newName.str() << successColor << "\t\tDONE" << endl << dataColor;
        }
    }
    catch(fm::Error_t& error) {
        cout << errorColor << "Nastapil blad:" << endl << error.what << endl;
        cin.get();
        return 0;
    }
    catch(xml::Error_t& error) {
        cout << errorColor << "Nastapil blad:" << endl << error.What << endl;
        cin.get();
        return 0;
    }
    catch(...) {
        cout << errorColor << "Nastapil nieznany blad!" << endl;
        cin.get();
        return 0;
    }
    cout << successColor << "Succes!" << endl;
    cin.get();

    return 0;
}