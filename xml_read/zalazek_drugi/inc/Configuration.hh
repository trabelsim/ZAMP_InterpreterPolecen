#ifndef CONFIGURATION_HH
#define CONFIGURATION_HH

#include <string>
#include <Scene.hh>
#include "Set4LibInterfaces.hh"

using namespace std;

class Configuration {
  //...


public:
 shared_ptr<Set4LibInterfaces> ZbiorBibliotek;

 shared_ptr<Scene> Scena;


 Configuration(){
  ZbiorBibliotek = make_shared<Set4LibInterfaces>();
  Scena = make_shared<Scene>();
 }
};


#endif
