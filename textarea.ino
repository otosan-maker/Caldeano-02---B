#include "textarea.h"


cal_textArea::cal_textArea(){
  ;
}


String cal_textArea::getText(){
  return m_strTexto;
}

cal_textArea::cal_textArea(int x, int y, int w, int h,uint16_t inkColor,uint16_t paperColor,
                            uint16_t cursorColor,int maxCarX,String strCad){
    m_x = x;
    m_y = y;
    m_w = w;
    m_h = h;
    m_inkColor    = inkColor;
    m_paperColor  = paperColor;
    m_cursorColor = cursorColor;
    m_strTexto    = strCad;
    m_maxCarX     = maxCarX; //maximo numero de caracteres que vamos a mostrar
    m_curX        = m_strTexto.length();
}

void cal_textArea::drawTextArea(){
//  Serial.printf("el cursor esta en %d\n",m_curX);
//  Serial.printf("la altura de la fuente es: %d\n",tft.fontHeight());
  calcVisible();

  tft.setTextWrap(false, false);
  tft.setTextColor(m_inkColor, m_paperColor);
  tft.setTextDatum(TL_DATUM);
  tft.fillRect(m_x,m_y,m_w,m_h,m_paperColor);
  tft.setCursor(m_x+3, m_y+tft.fontHeight()/2);
  tft.print(m_strTexto.substring(m_inicioX,m_curX));
  tft.setTextColor(m_cursorColor, m_paperColor);
  tft.print("|");
  tft.setTextColor(m_inkColor, m_paperColor);
  tft.print(m_strTexto.substring(m_curX,m_finX));
  if(m_text_final){
    tft.fillRect(m_x+m_w-3,m_y,3,m_h,m_cursorColor);
  }
  if(m_texto_inicio){
    tft.fillRect(m_x,m_y,3,m_h,m_cursorColor);
  }
}


void cal_textArea::getEvent(String nKey){
  if (nKey=="rigth"){
    incCursorX();
  }else if (nKey=="left"){
    decCursorX();
  }else if (nKey!=""){
    m_strTexto=m_strTexto.substring(0, m_curX)+nKey+m_strTexto.substring(m_curX, m_strTexto.length());
    m_curX+=nKey.length();
  }
  drawTextArea();
}

void cal_textArea::calcVisible(){
  if(m_strTexto.length()<m_maxCarX){  // si cabe toda la cadena la ponemos entera
    m_finX=m_strTexto.length();
    m_inicioX=0;
    m_text_final=false;
    m_texto_inicio=false;
    return;
  }
  if(m_curX<m_maxCarX){     //si el cursor esta cerca del principio, ponemor el principio
      m_finX=m_maxCarX;
      m_inicioX=0;
      m_text_final=true;
      m_texto_inicio=false;
      return;
    }
  if ((m_strTexto.length()-m_curX)<m_maxCarX ){//si el cursor esta cerca del final, ponemor la parte final
      m_finX=m_strTexto.length();
      m_inicioX=m_strTexto.length()-m_maxCarX;
      m_text_final=false;
      m_texto_inicio=true;
      return;
    }
  
  m_finX= m_curX + m_maxCarX/2;//si no, ponemos el cursor en el centro
  m_inicioX= m_curX -m_maxCarX/2;
  m_text_final=true;
  m_texto_inicio=true;
  
}


void cal_textArea::delChar(){
  m_strTexto=m_strTexto.substring(0, m_curX-1)+m_strTexto.substring(m_curX, m_strTexto.length());
  decCursorX();
}

void cal_textArea::empty(){
  m_strTexto="";
  m_curX=0;
}

void cal_textArea::decCursorX(){
  m_curX--;
  if(m_curX<0)
    m_curX=0;
}

void cal_textArea::incCursorX(){
  m_curX++;
  if (m_curX>m_strTexto.length())
    m_curX=m_strTexto.length();
}
