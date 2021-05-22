#include <stdio.h>

#include "commandhandler.h"
#include "game.h"

void game_commandhandler (command_t *command) {  
	printf("%d\n", command->instr);

	gamestate_t **state = getgamestate();

	switch (command->instr) {
		case CMD_END_GAME:
			game_stop();
			return;
		case CMD_PAUSE_GAME:
			game_pause();
			return;
		case CMD_UNPAUSE_GAME:
			game_unpause();
			return;
		default:
			return;
	}
}