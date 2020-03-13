
WAMR porting guide
=========================


This document describes how to port WAMR to a new platform "**super-os**"



<<<<<<< HEAD
# Step 1: Create folders for the new platform

-------------------------
Create folders:
- **core/shared/platform/super-os**: for platform API layer implementations
- **product-mini/platforms/super-os**: for the platform mini product build

# Step 2: Implement platform API layer

-------------------------
Implement folder core/shared/platform/super-os. Normally in this folder you should implement the following files:
- bh_platform.h and bh_platform.c: define the platform related macros, data types and APIs.
- bh_assert.c: implement function bh_assert_internal() and bh_debug_internal().
- bh_platform_log.c: implement function bh_log_emit, bh_fprintf and bh_fflush.
- bh_time.c: implement several time related functions.
- bh_thread.c: implement thread, mutex, condition related functions.
- bh_math.c: implement some math functions if the platform doesn't support them, e.g. sqrt,
                             fabs and isnan. We may use the open source fdlibm implementation, for example,
                             ref to platform/zephyr/bh_math.c.

Please ref to implementation of other platform for more details, e.g. platform/zephyr, platform/linux.

# Step 3: Create the mini product build for the platform

-------------------------
Implement folder product-mini/platforms/super-os. Normally this folder is to implement the C main function, and generate a WAMR VM core binary named iwasm which can load and run wasm apps. We should implement following files:
- main.c: implement the C main function, which reads wasm file to buffer, loads the wasm file to wasm module, instantiate the module, lookup wasm app main function, and then execute the function.
- ext_lib_export.c: implement the native APIs if you want, and if no native API is to be implemented, just keep array extended_native_symbol_defs empty.
- CMakeLists.txt: there are some settings which can be passed from cmake variables:
  - set (WAMR_BUILD_PLATFORM "platform_name"): set the name of the platform
  - set (WAMR_BUILD_TARGET <arch><sub>): set the build target, currently the value supported: X86_64, X86_32, ARM[sub], THUMB[sub], MIPS and XTENSA. For ARM and THUMB, you can specify the sub version, e.g. ARMV4, ARMV7, THUMBV4T, THUMBV7T.
  - set (WAMR_BUILD_INTERP 1 or 0): whether to interpreter or not
  - set (WAMR_BUILD_AOT 1 or 0): whether to build AOT or not
  - set (WAMR_BUILD_JIT 1 or 0): whether to build JIT or not
  - set (WAMR_BUILD_LIBC_BUILTIN 1 or 0): whether to build Libc builtin or not
  - set (WAMR_BUILD_LIBC_WASI 1 or 0): whether to build Libc WASI or not
=======
# Step 1: Implement platform API layer

-------------------------
Firstly create the folder **`core/shared/platform/super-os`** for platform API layer implementations. In the folder you just created, you must provide the following files:

- `platform_internal.h`: It can be used for any platform specific definitions such as macros, data types and internal APIs.
- `shared_platform.cmake`: the cmake file will be included by the building script



Then go to mplement the APIs defined in following header files for the platform abstraction layer:

- [`platform_api_vmcore.h`](../core/shared/platform/include/platform_api_vmcore.h):   mandatory for building mini-product (vmcore only). Part of APIs are needed only for Ahead of Time compilation support. 
- [`platform_api_extension.h`](../core/shared/platform/include/platform_api_extension.h): mandatory for app-mgr and app-framework. Given that the app-mgr and app-framework are not required for your target platform, you won't have to implement the API defined in the `platform_api_extension.h`.



**common/posix:**

There is posix based implementation of the platform API located in the `platform/common/posix` folder. You can include it if your platform support posix API. refer to platform linux implementation.



**common/math:**

Some platforms such as ZephyrOS don't provide math functions e.g. sqrt, fabs and isnan, then you should include source files under the folder `platform/common/math`. 



# Step 2: Create the mini product for the platform

-------------------------
You can build a mini WAMR product which is only the vmcore for you platform. Normally you need to implement the main function which loads a WASM file and run it with the WASM runtime. You don't have to do this step if there is no such need for your platform.



Firstly create folder **product-mini/platforms/super-os** for the platform mini product build, then refer to the linux platform mini-product for the implementation.



Refer to [build_wamr.md](./build_wamr.md) for the building tools and parameters.


>>>>>>> intel/internal/feature

