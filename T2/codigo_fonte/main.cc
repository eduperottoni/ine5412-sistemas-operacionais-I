#include "thread.h"
#include "system.h"
#include "main_class.h"

__USING_API 

int main(void)
{
    System::init();
    db<System>(INF) << "[Debug] System::init() chamado\n";
    Main *m = new Main();
    delete m;
}