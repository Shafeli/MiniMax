// RandomAi.h
#pragma once

#include "../Interface/GameAi.h"

//---------------------------------------------------------------------------------------------------------------------
// This AI just chooses a random valid move and makes it.  Its purpose is to show you how the API works.
//---------------------------------------------------------------------------------------------------------------------
class RandomAi : public GameAi
{
public:
    RandomAi(Board* pBoard) : GameAi(pBoard) { }

    virtual Move FindBestMove() override;
};
