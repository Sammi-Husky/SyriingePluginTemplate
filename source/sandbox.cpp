#include <os/OSError.h>
#include <sy_core.h>

namespace Sandbox
{
    void helloWorld()
    {
        OSReport("Hello world.\n");
    }

    void Init(CoreApi *api)
    {
        api->syInlineHook(0x800177B0, reinterpret_cast<void *>(helloWorld));
    }
    void Destroy()
    {
        OSReport("Goodbye\n");
    }
}