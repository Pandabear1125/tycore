extern unsigned int blah();

volatile int x = 0;

int main() {
    while (1) {x++; blah();}
}