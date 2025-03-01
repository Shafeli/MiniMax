// GameState.h
#pragma once
#include "Types.h"

class GameState
{
public:
    virtual ~GameState() = default;
    virtual GameStateHashType GetHash() const = 0;
};
