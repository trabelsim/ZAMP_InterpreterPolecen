#include <iostream>
#include <string>

#include <dlfcn.h>
#include <memory>
#include <map>
#include <vector>

#include <LibInterface.hh>

using namespace std;

/*!
 * \file
 * \brief Plik zawiera definicje klasy Set4LibInterfaces
 *
 * Plik zawiera definicję klasy Set4LibInterfaces
 */


class Set4LibInterfaces{
    private:
        /*!
        * \brief Kontener przechowujący elementy które są kombinacją nazwy biblioteki i wskaźnika załadowanej już biblioteki
        *
        *  
        */
        map<string,shared_ptr<LibInterface>> set4LibInterfaces;

                /*!
        * \brief Kontener przechowujący elementy które są kombinacją nazwy biblioteki i wskaźnika załadowanej już biblioteki
        *
        *  
        */
        Interp4Command* cmdInstance;


    public:

                /*!
        * \brief Konstruktor klasy Set4LibInterfaces
        *
        *  
        */
        Set4LibInterfaces();

                        /*!
        * \brief Funkcja pozwala wyszukac interfejs wczytanej biblioteki
        *
        * \param[in] libName - referencja do nazwy biblioteki typu string
        *  
        */
        shared_ptr<LibInterface> findInterface(string &libName);

                                /*!
        * \brief Funkcja pozwala dodać interfejs wczytanej biblioteki
        *
        * \param[in] libName - referencja do nazwy biblioteki typu string
        *  
        */
        bool setInterface(string &libName);

        // bool exec(istream & cmdStream , shared_ptr<Scene> scene , int socket);



};

Set4LibInterfaces::Set4LibInterfaces(){}


shared_ptr <LibInterface> Set4LibInterfaces::findInterface(string &libName){
    map<string, shared_ptr<LibInterface>>::iterator iter = set4LibInterfaces.find(libName);
    if(iter != set4LibInterfaces.end()){
        // cout << "Znaleziono wartość : " << iter->second << endl;
        return iter->second;
    }

    return nullptr;
}


bool Set4LibInterfaces::setInterface(string &libName){
    shared_ptr<LibInterface> libInterface = make_shared<LibInterface>();

    if(!libInterface->init(libName)){
        return false;
    }

    set4LibInterfaces.insert({libName,libInterface});
    return true;

}