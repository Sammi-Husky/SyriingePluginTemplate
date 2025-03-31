#include <gf/gf_file_io_request.h>
#include <gf/gf_memory_pool.h>
#include <sy_core.h>

#include "sandbox.h"

namespace Syringe
{
    const PluginMeta META = {
        "Sandbox",               // Plugin name
        "Sammi",                 // Author
        Version("0.1.0"),        // Plugin version
        Version(SYRINGE_VERSION) // Syringe version
    };

    extern "C"
    {
        typedef void (*PFN_voidfunc)();
        __attribute__((section(".ctors"))) extern PFN_voidfunc _ctors[];
        __attribute__((section(".ctors"))) extern PFN_voidfunc _dtors[];

        const PluginMeta *_prolog(CoreApi *api);
        void _epilog();
        void _unresolved();
    }

    /**
     * @brief Main entrypoint for the plugin. This function is called when the plugin is loaded.
     * @param api Pointer to the CoreApi interface. This is used to call core functions.
     * @return Pointer to the plugin meta data structure.
     */
    const PluginMeta *_prolog(CoreApi *api)
    {
        // Run global constructors
        PFN_voidfunc *ctor;
        for (ctor = _ctors; *ctor; ctor++)
        {
            (*ctor)();
        }

        // Run our main plugin code
        Sandbox::Init(api);

        return &META;
    }

    /**
     * @brief Epilog function that runs after the plugin main function.
     * This function is called when the plugin is unloaded. It runs all global destructors
     */
    void _epilog()
    {
        // run the global destructors
        PFN_voidfunc *dtor;
        for (dtor = _dtors; *dtor; dtor++)
        {
            (*dtor)();
        }
    }

    /**
     * Unresolved function that usually runs when an undefined reference is attampted to be resolved.
     * @note This function is not called by the plugin loader, but is here for future use.
     */
    void _unresolved(void)
    {
    }

}