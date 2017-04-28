#include "GameButton.h"

GameButton::GameButton()
    : moveOffset(0)
    , lastMoveOffset(0)
    , isClicked_(false)
{

}

bool GameButton::peekClicked() const
{
   return isClicked_;
}

bool GameButton::isClicked()
{
    bool is = isClicked_;
    isClicked_ = false;
    return isClicked_;
}

int64_t GameButton::peekMoveOffset() const
{
    return moveOffset;
}

int64_t GameButton::moveDelta()
{
    int64_t offset = moveOffset;
    int64_t delta = offset-lastMoveOffset;
    lastMoveOffset = offset;
    return delta;
}

void GameButton::clicked()
{
    isClicked_ = true;
}

void GameButton::addMovement(int64_t offset)
{
    moveOffset+=offset;
}
