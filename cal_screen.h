
#ifndef CAL_SCREEN
#define CAL_SCREEN

#include "textarea.h"

class cal_screen {
  public:
    cal_screen();
    int loop_cal_screen();
    void header();

    uint16_t inkColor    = TFT_YELLOW;
    uint16_t paperColor  = TFT_NAVY;
    uint16_t headerColor = TFT_BLUE;
    uint16_t borderColor = TFT_RED;
    uint16_t flagColor   = TFT_RED;
    uint16_t cursorColor = TFT_RED;
  private:
    cal_textArea taMostrar=cal_textArea(30,30,285,20,inkColor,paperColor,cursorColor,32,"");
    String screenTitle="";
    
   
    void pBody();
    void exec(const char *);

    uint16_t HeaderColor[3] = {TFT_NAVY,TFT_DARKGREY,TFT_YELLOW};
    
    TFT_eSPI_Button boton;
    TFT_eSPI_Button listar;
    TFT_eSPI_Button b3;
    TFT_eSPI_Button b4;
    TFT_eSPI_Button key[4];
    uint16_t keyColor[4] = {TFT_DARKGREY,TFT_DARKGREY,TFT_DARKGREY,TFT_DARKGREY};
    String keyLabel[4] ={"CLS","","","Exec"};
};

#endif
