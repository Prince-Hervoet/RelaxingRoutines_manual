# SimpleNetRoutine

This project is in development,please do not clone or run.And it will work like this:

```
    #include "simple_routine.hpp"
    #include <iostream>

    void *test(void *args)
    {
        std::cout << "one" << std::endl;
        simple_await();
        std::cout << "three" << std::endl;
        return nullptr;
    }

    int main()
    {
        RoutineHandler *rh = simple_new(test, nullptr);
        simple_resume(rh);
        std::cout << "two" << std::endl;
        simple_resume(rh);
        return 0;
    }

    // log: one
            two
            three
```

![image](https://user-images.githubusercontent.com/122962161/233800372-1c0f43fb-e458-4146-b9ee-f832426ceaf3.png)
