#include "state.h"


#define F1 25
#define F2 26
#define F3 27
#define F4 14
#define F5 12
#define F6 13
#define C1 34
#define C2 35
#define C3 32
#define C4 33
#define C5 22
#define C6 39
#define C7 36

int Filas[6]={F1,F2,F3,F4,F5,F6};
int Columnas[7]={C1,C2,C3,C4,C5,C6,C7};



void initTeclado(){
  pinMode(F1, OUTPUT);
  pinMode(F2, OUTPUT);
  pinMode(F3, OUTPUT);
  pinMode(F4, OUTPUT);
  pinMode(F5, OUTPUT);
  pinMode(F6, OUTPUT);

  pinMode(C1, INPUT_PULLDOWN);
  pinMode(C2, INPUT_PULLDOWN);
  pinMode(C3, INPUT_PULLDOWN);
  pinMode(C4, INPUT_PULLDOWN);
  pinMode(C5, INPUT_PULLDOWN);
  pinMode(C6, INPUT_PULLDOWN);
  pinMode(C7, INPUT_PULLDOWN);
}

String  keys_1[7][6] = {
  {"mode","up","graf","sin()","cos()","tan()"},
  {"left","cnt","rigth","log()","^","^2"},
  {"x","down","y","var","cat","pi"},
  {"7","8","9",   "+","'","e"},
  {"4","5","6",   "-",","," "},
  {"1","2","3",   "*","(",")"},
  {"0",".","=",   "/","del","exe"}
};
String  keys_2[7][6] = {
  {"mode","up","graf",  "a","b","c"},
  {"left","cnt","rigth","d","e","f"},
  {"x","down","y",      "g","h","i"},
  {"j","k","l",         "m","'","e"},
  {"n","o","p",         "q",","," "},
  {"r","s","t",         "u","(",")"},
  {"v",".","=",         "z","del","exe"}
};
String  keys_3[7][6] = {
  {"mode","up","graf",  "A","B","C"},
  {"left","cnt","rigth","D","E","F"},
  {"X","down","Y",      "G","H","I"},
  {"J","k","l",         "M","'","e"},
  {"N","O","P",         "Q",","," "},
  {"R","S","T",         "U","(",")"},
  {"V",".","=",         "Z","del","exe"}
};

String lastKey="-";

int lastCol=-1;
int lastRow=-1;
boolean newKeyPrees=false;
int lasttimepressed=0;

String  getKey(){
  String newKey="";
  int iFila,iCol;
    for(iFila=0;iFila<6;iFila++){
    //ponemos todas las filas a LOW
    for(int i=0;i<6;i++)  digitalWrite(Filas[i], LOW);
    //ponemos la que toca como HIGH
    digitalWrite(Filas[iFila], HIGH);
    for(iCol=0;iCol<7;iCol++){
      if (digitalRead(Columnas[iCol])==HIGH){
        //Serial.printf("C%d_%d\n",Columnas[iCol],Filas[iFila]);
        if ((lastCol==iCol) && (lastRow==iFila) && (millis()-lasttimepressed<300)){
          //Serial.println("repetida");
          return "";
        }
        else{
          lastCol=iCol;
          lastRow=iFila;
          newKeyPrees=true;
        }
        lasttimepressed=millis();
      }
    }
  }
  
if (newKeyPrees){
     switch(sGaldeano.Mode){
        case NUMERIC_MODE:
          newKey=keys_1[lastCol][lastRow];
          break;
        case ALPHA_MODE:
          newKey=keys_2[lastCol][lastRow];
          break;
        case SHIFT_MODE:
          newKey=keys_3[lastCol][lastRow];
          break;
        default:
          newKey=keys_1[lastCol][lastRow];
      }
      newKeyPrees=false;
      return commandKey(newKey);;
 }
 return "";
}


//Si tratamos el comando, devolvemos "" para que no lo trate nadie mas
String commandKey(String newKey){
  if (newKey=="mode"){
    sGaldeano.Mode=sGaldeano.Mode+1;
    if(sGaldeano.Mode>MODE_NUMBER)
      sGaldeano.Mode=NUMERIC_MODE;
    pScreen->header();
    return "";
  }
  if (newKey=="exit"){
    exit(1);
  }
  return newKey;
}
