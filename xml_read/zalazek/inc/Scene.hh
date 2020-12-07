#include "MobileObj.hh"
#include <map>
#include <memory>

using namespace std;
/*!
 * \file
 * \brief Definicja klasy Scene
 *
 * Plik zawiera definicję klasy Scene, która przechowuje stworzone obiekty.
 */

class Scene {

    private:
            /*!
        * \brief Kontener przechowujący obiekty mobilne których wartości są kombinacją nazwy obiektu i jego wskaznika
        *
        *  
        */
        map<string, shared_ptr<MobileObj>> mobileObjects;

    public:
           /*!
        * \brief Znajduje obiekt umieszczony na scenie 
        * 
        * \param[in] objectName - referencja nazwa obiektu typu string
        *  
        */
        shared_ptr<MobileObj> findMobileObj (string &objectName);

                   /*!
        * \brief Dodaje obiekt do sceny
        * 
        * \param[in] objectName - referencja nazwa obiektu typu string
        *  
        */
        bool setMobileObj(string &objectName);


            /*!
        * \brief Konstruktor klasy Scene
        *
        *  
        */
        Scene();
        

                    /*!
        * \brief Destruktor klasy Scene
        *
        *  
        */
        ~Scene();

    
};


Scene::Scene(){
    cout << "Konstruktor Sceny" << endl;
}

Scene::~Scene(){
    cout << "Destruktor Sceny" << endl;
}



shared_ptr<MobileObj> Scene::findMobileObj(string &objectName){
    map<string, shared_ptr<MobileObj>>::iterator iter = mobileObjects.find(objectName);
    if( iter != mobileObjects.end()){
        // cout << " Znaleziono objekt  : " << iter->first << endl;
        return iter->second;
    }
    return nullptr;
}


bool Scene::setMobileObj(string &objectName){
    if(!findMobileObj(objectName)){
        shared_ptr<MobileObj> mobileObject = make_shared<MobileObj>();
        mobileObject->SetName(objectName);
        mobileObjects.insert({objectName, mobileObject});
        return true;
    }
    return false;
}