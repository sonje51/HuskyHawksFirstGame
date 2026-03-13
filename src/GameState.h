//GameState.h
#ifndef GAME_STATE_H
#define GAME_STATE_H

/*
// Class GameState Enum
// Represents the different states the game can be in.
// This allows MainManager to switch behavior based on the current state of the game.
*/
enum class GameState
{
    Menu, //title screen
    Playing, //actively playing the game
    Controls, //controls screen
    Credits, // credits screen
    Paused // Game will pause
};

#endif