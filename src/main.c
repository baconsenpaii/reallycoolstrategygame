#include <stdio.h>
#include <stdlib.h>

#include "timing.h"
#include "random.h"
#include "gamestate.h"
#include "command.h"


#define SEED (0x0213de4208353f2eUL) // my lucky number


gamestate_t *newstate (void);
int gameloop (gamestate_t *game);
void cleanup (gamestate_t *game);

int main (int argc, char **argv) {
    random_seed(SEED);

    gamestate_t *game = newstate();
    if (!game) {
        return -1;
    }

    int gamefail = gameloop(game);
    cleanup(game);

    return gamefail;
}

gamestate_t *newstate (void) {
    gamestate_t *game = malloc(sizeof(gamestate_t));

    if (!game) {
        return 0;
    }

    game->running = 1;
    game->steptime = 1000; // once per second

    game->commands = newcommandqueue();

    return game;
}

static void printerlmao (command_t *command) {
    printf("%d\n", command->instr);
}

int gameloop (gamestate_t *game) {
    long start = millis();
    long now;

    while (game->running) {
        // process inputs
        // process commands

        processcommands(game->commands, &printerlmao);

        // if enough time has passed
            // step the game state

        now = millis();
        if (now - start >= game->steptime) {
            command_t *newcommand = malloc(sizeof(command_t));
            newcommand->instr = (int) ranl();
            enqueuecommand(game->commands, newcommand);
            start = now;
        }

        // render
    }

    return 0;
}

void cleanup (gamestate_t *game) {
    freecommandqueue(game->commands);
    free(game);
}
