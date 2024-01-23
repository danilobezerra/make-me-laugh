#include <genesis.h>

bool isRunning = TRUE;

int main() {
    VDP_drawText("Hello World!", 14, 12);

    while (isRunning) {
        SYS_doVBlankProcess();

    }

    return 0;
}
