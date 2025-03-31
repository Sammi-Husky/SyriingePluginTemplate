#include <os/OSError.h>
#include <sy_core.h>

namespace Sandbox
{
    void helloWorld()
    {
        OSReport("Hello world.\n");
    }

    void Init()
    {
        SyringeCore::syInlineHook(0x800177B0, (void *)helloWorld);
    }
    void Destroy()
    {
        OSReport("Goodbye\n");
    }
}