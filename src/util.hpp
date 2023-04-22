#pragma once
#include <iostream>
#include <thread>
#include <ucontext.h>
#include <cstring>
#include <mutex>
typedef void *(*TaskFunc)(void *);
typedef void (*CallbackFunc)(void *);