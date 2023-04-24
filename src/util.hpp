#pragma once
#include <iostream>
#include <cstring>
#include <mutex>
typedef void *(*TaskFunc)(void *);
typedef void (*CallbackFunc)(void *);
typedef long long bigInt;

long long
getNowTimestamp();