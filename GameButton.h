#ifndef GAMEBUTTON_H
#define GAMEBUTTON_H
#include <stdint.h>
#include <atomic>

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
    std::atomic<bool> isClicked_;
    std::atomic<int64_t> moveOffset;
    int64_t lastMoveOffset;
};

#endif // GAMEBUTTON_H
