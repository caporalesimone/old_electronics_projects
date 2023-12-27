#line 1 "D:/pic/Sound/Sound_Var.c"
#line 19 "D:/pic/Sound/Sound_Var.c"
void Tone1() {
 Sound_Play(200, 200);
}

void Tone2() {
 Sound_Play(180, 200);
}

void Tone3() {
 Sound_Play(160, 200);
}

void Melody() {
 Tone1(); Tone2(); Tone3(); Tone3();
 Tone1(); Tone2(); Tone3(); Tone3();
 Tone1(); Tone2(); Tone3();
 Tone1(); Tone2(); Tone3(); Tone3();
 Tone1(); Tone2(); Tone3();
 Tone3(); Tone3(); Tone2(); Tone2(); Tone1();
}

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
}

void main() {
 TRISB = 0xF0;

 Sound_Init(&PORTB, 3);

 Melody();
 Delay_ms(1000);
 Melody2();

}
