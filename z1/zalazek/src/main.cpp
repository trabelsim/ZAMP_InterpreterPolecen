#include <iostream>
#include <dlfcn.h>
#include <cassert>
#include <sstream>
#include <string>
#include "Interp4Command.hh"
#include "MobileObj.hh"
#include "Scene.hh"
#include "Set4LibInterfaces.hh"

using namespace std;

string tab_wiersz [300];






// 1. Przekazujemy strumien wejsciowy
// 2. Przekazujemy obiekt odpowiedzialny za interpretacje polecenia
// bool ExecActions(istream &rIStrm , Interp4Command &rInterp){
//   //.. 
//   // w tej funkcji będziemy czytac polecenia klasy string aby wczytac
//   // polecenia 


//   string CmdKey;

//   // Wczytamy strumien
//   rIStrm >> CmdKey;
//     cout << "Reading in ExecActions : " << CmdKey << endl;

//     if(CmdKey == "Move"){
//     if(!rInterp.ReadParams(rIStrm)){
//       cerr << "Błąd przy wywołaniu funkcji Read Params";
//       return false;
//     }
//     cout << "Polecenie  : " << CmdKey<<  endl;
//     cout << "Składnia : ";
//     rInterp.PrintSyntax();
//     rInterp.PrintCmd();
//     cout << endl;
//   }

//   if(CmdKey == "Rotate"){
//     if(!rInterp.ReadParams(rIStrm)){
//       cerr << "Błąd przy wywołaniu funkcji Read Params";
//       return false;
//     }
//     cout << "Polecenie : " << CmdKey << endl;
//     cout << "Składnia : ";
//     rInterp.PrintSyntax();
//     rInterp.PrintCmd();
//     cout << endl;
//   }

//   if(CmdKey == "Set"){
//     if(!rInterp.ReadParams(rIStrm)) return false;
//     cout << "Polecenie : " << CmdKey << endl;
//     cout << "Składnia : ";
//     rInterp.PrintSyntax();
//   }

//   if(CmdKey == "Pause"){
//     if(!rInterp.ReadParams(rIStrm)) return false;
//     cout << "Polecenie : " << CmdKey << endl;
//     cout << "Składnia : ";
//     rInterp.PrintSyntax();
//   }
//   return true;
// }


bool ExecPreprocesor( const char *NazwaPliku, istringstream &IStrm4Cmds){
    string Cmd4Preproc = "cpp -P ";
    char Line[500];
    ostringstream OTmpStrm;

    Cmd4Preproc += NazwaPliku;
    cout << "Wywołanie procesu  : " << Cmd4Preproc << endl;
    FILE* pProc = popen(Cmd4Preproc.c_str(),"r");

    if(!pProc){ 
      cerr << "Otwerianie pliku nie powiodło się , sprawdź komendę : " << Cmd4Preproc << endl;
      return false;
    }
    // Wczytuj ze strumienia 'pProc' i zapisz znaki do Line
    while (fgets(Line,500,pProc)){
        OTmpStrm << Line;
    }

    IStrm4Cmds.str(OTmpStrm.str());
    return pclose(pProc) == 0;
}



int main(int argc, char **argv)
{
  if(argc < 2){
    cerr << "Zbyt mało argumentów - uwzględnić plik CMD.";
    return 1;
  }

  istringstream IStrm4Cmds;
  cout << IStrm4Cmds.str() << endl;


  if(!ExecPreprocesor(argv[1], IStrm4Cmds)){
    cerr << "Coś poszło nie tak! - Wczytywanie nie powiodło się" << endl;
    return false;
  }

  cout << IStrm4Cmds.str() << endl;

  Set4LibInterfaces set4librariesInterfaces;

  Scene objects_scene;


while(!IStrm4Cmds.eof()){
  string libName;
  string objName;

  IStrm4Cmds >> libName;
  
  if(libName == ""){
    break;
  }


  if(!set4librariesInterfaces.findInterface(libName)){
    if(!set4librariesInterfaces.setInterface(libName)){
      return false;
      }
    }
  shared_ptr<LibInterface> interfaceOfLibraries = set4librariesInterfaces.findInterface(libName);

  IStrm4Cmds >> objName;

  if(!objects_scene.findMobileObj(objName)){
    if(!objects_scene.setMobileObj(objName)){
      return false;
    }
  }
  shared_ptr<MobileObj> mobileObj = objects_scene.findMobileObj(objName);

  interfaceOfLibraries->exec(IStrm4Cmds,mobileObj);
  }
}


