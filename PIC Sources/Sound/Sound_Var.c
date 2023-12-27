/*
 * Project name:
     Sound_Var (Usage of Sound library)
 * Copyright:
     (c) Mikroelektronika, 2005.
 * Description:
     This project is a simple demonstration of how to
     use sound library for playing tones on a piezo speaker.
 * Test configuration:
     MCU:             P16F877A
     Dev.Board:       EasyPIC3
     Oscillator:      HS, 08.0000 MHz
     Ext.Modules:     piezo speaker
     SW:              mikroC v6.0
 * NOTES:
     Sound frequencies in this example are calculated for 4Mhz crystal.
*/

void Tone1() {
  Sound_Play(200, 200);   // Period = 2ms <=> 500Hz, Duration = 200 periods
}//~

void Tone2() {
  Sound_Play(180, 200);   // Period = 1.8ms <=> 555Hz
}//~

void Tone3() {
  Sound_Play(160, 200);   // Period = 1.6ms <=> 625Hz
}//~

void Melody() {        // Plays the melody "Yellow house"
  Tone1(); Tone2(); Tone3(); Tone3();
  Tone1(); Tone2(); Tone3(); Tone3();
  Tone1(); Tone2(); Tone3();
  Tone1(); Tone2(); Tone3(); Tone3();
  Tone1(); Tone2(); Tone3();
  Tone3(); Tone3(); Tone2(); Tone2(); Tone1();
}//~

void ToneA() {
  Sound_Play(80, 20);
}
void ToneC() {
  Sound_Play(70, 20);
}
void ToneE() {
  Sound_Play(60, 80);
}

void Melody2() {
  unsigned short i;
  for (i = 9; i > 0; i--) {
    ToneA(); ToneC(); ToneE();
  }
}//~

void main() {
  TRISB = 0xF0;

  Sound_Init(&PORTB, 3);
  //Sound_Play(50, 100);
  Melody();
  Delay_ms(1000);
  Melody2();

}//~!
