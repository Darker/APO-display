#include "CooldownCalculator.h"

CooldownCalculator::CooldownCalculator(float cooldownMS)
    : cooldownMS(cooldownMS)
    , remaining(0)
{

}
