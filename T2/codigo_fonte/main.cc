#include "thread.h"
#include "system.h"
#include "main_class.h"

__USING_API 

int main(void)
{
    System::init();
    db<System>(TRC) << "System::init() chamado\n";
    Main *m = new Main();
    delete m;
}