void main() {
     TRISA = 0;
     PORTA = 0xFF;
     PORTA = 0;
     PORTA++;
     if (PORTA > 1) {
        PORTA = 0;
     }
}