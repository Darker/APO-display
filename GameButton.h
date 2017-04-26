#ifndef GAMEBUTTON_H
#define GAMEBUTTON_H
#include <stdint.h>
#include <mutex>
class GameButton
{
public:
    GameButton();
    // Returns true if button is in clicked state
    bool peekClicked() const;
    // returns clicked state and sts it to false
    bool isClicked();

    // Returns total sum of movement since initialization
    int64_t peekMoveOffset() const;
    // returns movement since last request and sets delta to zero
    int64_t moveDelta();

    // used to set values
    void clicked();
    void addMovement(int64_t offset);
protected:
    bool isClicked;
    int64_t moveOffset;
    int64_t lastMoveOffset;
    std::mutex movementMutex;
    std::mutex clickMutex;
};

#endif // GAMEBUTTON_H
