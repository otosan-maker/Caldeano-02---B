#ifndef CAL_TEXTAREA
#define CAL_TEXTAREA
#include <vector>

#define TEXTTIPE   3

class cal_textArea {
  public:
    cal_textArea();
    cal_textArea(int x, int y, int w, int h,uint16_t inkColor,uint16_t paperColor,uint16_t cursorColor,int maxCarX,String strCad);
    void    drawTextArea();
    void    getEvent(String);
    void    delChar();          //delete one char
    void    empty();
    String  getText();
  private:
    int m_x,m_y,m_w,m_h;
    uint16_t m_inkColor,m_paperColor,m_cursorColor;
    int m_num_Ylines;
    int m_maxCarX;    // max numero de caracteres a imprimir
    int m_inicioX=0;  // el primer caracter
    int m_finX=0;     // el ultimo caracter
    boolean m_text_final=false; // indica si hay mas texto al final
    boolean m_texto_inicio=false; // indica si hay mas texto al inicio
    int m_curX,m_curY;
    String m_strTexto = "Hello String"; 
    std::vector<int> v;
    void decCursorX();
    void incCursorX();
    void calcVisible();
};

#endif
