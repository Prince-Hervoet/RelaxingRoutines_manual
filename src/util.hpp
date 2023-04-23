#pragma once
#include <iostream>
#include <cstring>
#include <mutex>
typedef void *(*TaskFunc)(void *);
typedef void (*CallbackFunc)(void *);

long long getNowTimestamp();