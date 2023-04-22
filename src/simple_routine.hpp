#pragma once
#include "util.hpp"
class RoutineHandler;
RoutineHandler *simple_new(TaskFunc task, void *args);

void simple_resume(RoutineHandler *rh);

void simple_await();

void t_simple_pause();

void simple_read(int sockfd, char buffer[], int count);
