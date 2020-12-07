#include <iostream>
#include <cstdio>
#include <string>
// Do zarządzania bibliotekami
#include <dlfcn.h>

#include "Interp4Command.hh"

using namespace std;

/*!
 * \file
 * \brief Definicja klasy LibInterface
 *
 * Plik zawiera definicję klasy LibInterface, która odpowiedzialna jest za obsługe biblioteki.
 */




/*!
 * \brief Modeluje ********
 *
 *  Klasa modeluje ...
 */
class LibInterface
{
    private:
        /*!
        * \brief Przechowywuje nazwę biblioteki
        *
        *  
        */


        void* pLibHand;

        // Interp4Command* (*createCmd)(void);

        /*!
        * \brief Przechowywuje nazwę przekazanej komęndy
        *
        *  
        */
        string cmdName;


    public:
            /*!
        * \brief Konstruktor klasy LibInterface
        *
        *  
        */
        LibInterface();
        /*!
        * \brief Destruktor klasy LibInterface
        *
        *  
        */
        ~LibInterface();
        /*!
        * \brief Ładuje bibliotekę dla danego polecenia wyczytanego z pliku
        * 
        * \param[in] fileName - nazwa pliku typu string
        *
        *  
        */
        bool init(string fileName);

       /*!
        * \brief Uruchamia odpowiednie funkcje PrintCmd oraz PrintSyntax które wykazują odpowiednio wczytywane wartości
        * 
        * \param[in] rIstrm - strumień wejściowy 
        * \param[in] mobileObject - referencja do obiektu mobilnego
        *  
        */
        bool exec(istream &rIstrm, shared_ptr<MobileObj> &mobileObject);


        /*!
        * \brief Definicja obiektu
        *
        *  
        */
        Interp4Command* (*pCreateCmd)(void);

        /*!
        * \brief Metoda zwracająca nazwe polecenia
        *
        *  
        */
        const string& GetName() const {return cmdName;}


};


LibInterface::LibInterface(){
    cout << "Konstruktor Interfejsu bibliotek utworzono" << endl;
}


LibInterface::~LibInterface(){
    dlclose(pLibHand);
}


bool LibInterface::init(string fileName){
    string libraryName("libInterp4");
    libraryName.append(fileName);
    libraryName.append(".so");
    pLibHand = dlopen(libraryName.c_str(),RTLD_LAZY);
    cout << "Otwieranie biblioteki  : " << libraryName << endl; 

    if(!pLibHand){
        cerr << "Nie udało się załadować biblioteki " << libraryName.c_str() << endl;
        return false;
    }
    
    void *pFun;
    pFun = dlsym(pLibHand,"CreateCmd");

    if(!pFun){
        cerr << "Nie znaleziono funkcji CreateCmd dla " << libraryName.c_str() << endl;
        return false;

    }



    pCreateCmd = *reinterpret_cast<Interp4Command* (**)(void)>(&pFun);

    return true;

}


bool LibInterface::exec(istream &rIstrm, shared_ptr<MobileObj> &mobileObject){
    Interp4Command *pCmd = pCreateCmd();
    cout << "Polecenie" << endl << endl;
    pCmd->PrintSyntax();
    cout << endl << endl;

    if(!pCmd->ReadParams(rIstrm)){
        return false;
    }

    // if(mobileObject->GetName().find_first_not_of("0123456789")){
    //     string time_declared;
    //     istringstream value_of_time(mobileObject->GetName());

    //     pCmd->ReadParams(value_of_time);
    //     pCmd->PrintCmd();
    //     cout<< endl;
    //     delete pCmd;
    //     return true;
    // }

    cout << "Obiekt : " << mobileObject->GetName() << endl << endl;
    pCmd->PrintCmd();
    cout << endl;
    delete pCmd;
    return true;

}


