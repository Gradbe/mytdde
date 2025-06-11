#ifndef FAKE_RANDOM_MINUTE_H
#define FAKE_RANDOM_MINUTE_H

#include "RandomMinute.h"
#include "FakeRandomMinute.h"

void FakeRandomMinute_SetFirstAndIncrement(int seed, int increment);
int FakeRandomMinute_Get(void);

#endif
