##construction.  
 jenga build.  
 --target NKMath --config Debug 
jenga: error executing command 'build': Command not found: clang++ -x c++-header 'C:\Users\Pc\OneDrive\Desktop\Nkentseu\Kernel\Foundation\NKPlatform\pch\pch.h' -o 'C:\Users\Pc\OneDrive\Desktop\Nkentseu\Build\Obj\Debug-Windows\NKPlatform\NKPlatform.pch' -g -O0 '-IC:\Users\Pc\OneDrive\Desktop\Nkentseu\Kernel\Foundation\NKPlatform\src' '-IC:\Users\Pc\OneDrive\Desktop\Nkentseu\Kernel\Foundation\NKPlatform\pch' '-IC:\Users\Pc\OneDrive\Desktop\Nkentseu\Kernel\Foundation\NKPlatform\pch' -MMD -MF 'C:\Users\Pc\OneDrive\Desktop\Nkentseu\Build\Obj\Debug-Windows\NKPlatform\NKPlatform.pch.d' -MT 'C:\Users\Pc\OneDrive\Desktop\Nkentseu\Build\Obj\Debug-Windows\NKPlatform\NKPlatform.pch' -DNKENTSEU_PLATFORM_STATIC_LIB -D_DEBUG -DDEBUG -DNKENTSEU_DEBUG -std=c++20 --target=x86_64-w64-windows-gnu -DWINVER=0x0601 -D_WIN32_WINNT=0x0601
## ordre de construction
Build Order (5 projects):
  1. NKPlatform [STATIC_LIB] → 
  2. NKCore [STATIC_LIB] (depends: NKPlatform) → 
  3. NKMemory [STATIC_LIB] (depends: NKCore, NKPlatform) → 
  4. NKContainers [STATIC_LIB] (depends: NKCore, NKMemory, NKPlatform) → 
  5. NKMath [STATIC_LIB] (depends: NKContainers, NKCore, NKMemory, NKPlatform)
