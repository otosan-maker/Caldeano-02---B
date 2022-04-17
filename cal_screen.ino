#include "cal_screen.h"

extern void run(char *s);


cal_screen::cal_screen(){
  
  tft.setTextSize(1);
  tft.setFreeFont(FSB9);
  
  tft.fillScreen(paperColor);

  for (uint8_t row = 0; row < 4; row++) {
    key[row].initButton(&tft, 40+80*row, 220, 80, 25, inkColor,headerColor,inkColor, (char*)keyLabel[row].c_str(), 1);
  }
  screenTitle="Galdeano CAS 02";
  header();
  pBody();
  
}


int cal_screen::loop_cal_screen(){
  uint16_t t_x = 0, t_y = 0; // To store the touch coordinates
  tft.setTextColor(inkColor, paperColor);
  tft.setTextDatum(TL_DATUM);
  tft.setTextSize(1);
  tft.setFreeFont(FSB9);
  String c=getKey();
  if (c=="del"){
    taMostrar.delChar();
    taMostrar.drawTextArea();
  }else if (c=="exe"){
    exec(taMostrar.getText().c_str());
  }else if (c!=""){
    taMostrar.getEvent(c);
  }

  bool pressed = tft.getTouch(&t_x, &t_y);
  for (uint8_t row = 0; row < 4; row++) {
    if (pressed &&  key[row].contains(t_x, t_y)) {
       key[row].press(true);  // tell the button it is pressed
    } else {
       key[row].press(false);  // tell the button it is NOT pressed
    }
    if (key[row].justReleased()) key[row].drawButton();
  }


  if (key[0].justPressed()) {
      key[0].drawButton(true);
      taMostrar.empty();
      tft.fillScreen(paperColor);
      header();
      pBody();
  }
  if (key[3].justPressed()) {
      exec(taMostrar.getText().c_str());
  }


  
}



// Print the header for a display screen
void cal_screen::header()
{
  char szTmp[32];
  
  tft.setTextSize(1);
  tft.setTextColor(inkColor, headerColor);
  tft.fillRect(0, 0, 320, 20, headerColor);
  tft.setTextDatum(TC_DATUM);
  tft.drawString(screenTitle.c_str(), 160, 2); // Font 4 for fast drawing with background
  tft.setTextColor(flagColor, headerColor);
  switch (sGaldeano.Mode ) {
    case NUMERIC_MODE:
      tft.drawString("Num", 290, 2);
      break;
    case ALPHA_MODE:
      tft.drawString("Alf", 290, 2);
      break;
    case SHIFT_MODE:
      tft.drawString("Sft", 290, 2);
      break;
  }
  
  tft.setTextColor(inkColor, headerColor);
}




void cal_screen::pBody(){
    // For comaptibility with Adafruit_GFX library the text background is not plotted when using the print class
  // even if we specify it.
  int xpos =  0;
  int ypos = 40;
  tft.setTextColor(inkColor);
  tft.setCursor(xpos, ypos);    // Set cursor near top left corner of screen

  tft.setFreeFont(FSB9);   // Select Free Serif 9 point font, could use:
  // tft.setFreeFont(&FreeSerif9pt7b);
  //tft.println();          // Free fonts plot with the baseline (imaginary line the letter A would sit on)
  // as the datum, so we must move the cursor down a line from the 0,0 position
  tft.print(">>");  // Print the font name onto the TFT screen
  tft.println();
  for (uint8_t row = 0; row < 4; row++) {
    key[row].drawButton();
  }
 
 
}




void cal_screen::exec(const char *szComando){
  char comando[128];
  int i,j,c;

  tft.setFreeFont(FF1); 
  //tft.showFont(2000);
  //delay(10000);
  sprintf(comando,"%s",szComando);
  run(comando );
  Serial.printf("filas    %d\n",res_nrow);
  Serial.printf("columnas %d\n",res_ncol);
  tft.fillRect(10,60,300,100,paperColor);
  tft.setViewport(10,60,300,100);
  tft.frameViewport(borderColor, -1);
  tft.setCursor(0, 20);
  for(i=0;i<res_nrow;i++){
    for(j=0;j<res_ncol;j++){
      c=res_buf[i * res_ncol + j];
      Serial.printf("%d-",c);
      if(c==0)
        c=' ';
      tft.printf("%c",c);
    }
    Serial.println("");
    tft.printf("\n");
  }
  tft.resetViewport();
  

  tft.setFreeFont(FSB9);
   
  free(res_buf);
}
