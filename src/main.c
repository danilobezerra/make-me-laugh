#include <genesis.h>
#include "global.h"
#include "entity.h"
#include "player.h"
#include "player_input.h"
#include "rope.h"
#include "rope_unit.h"
#include "ball.h"

bool isRunning = TRUE;

Player players[PLAYER_COUNT];
Ball ball;
Rope rope;

int main() {
    VDP_drawText("Hello World!", 14, 12);

    while (isRunning) {
        SYS_doVBlankProcess();

    }

    return 0;
}
