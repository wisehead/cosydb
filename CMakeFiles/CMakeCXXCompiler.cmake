SET(CMAKE_CXX_COMPILER "/opt/compiler/gcc-4.8.2/bin/c++")
SET(CMAKE_CXX_COMPILER_ARG1 "")
SET(CMAKE_CXX_COMPILER_ID "GNU")
SET(CMAKE_CXX_PLATFORM_ID "Linux")

SET(CMAKE_AR "/opt/compiler/gcc-4.8.2/bin/ar")
SET(CMAKE_RANLIB "/opt/compiler/gcc-4.8.2/bin/ranlib")
SET(CMAKE_LINKER "/opt/compiler/gcc-4.8.2/bin/ld")
SET(CMAKE_COMPILER_IS_GNUCXX 1)
SET(CMAKE_CXX_COMPILER_LOADED 1)
SET(CMAKE_COMPILER_IS_MINGW )
SET(CMAKE_COMPILER_IS_CYGWIN )
IF(CMAKE_COMPILER_IS_CYGWIN)
  SET(CYGWIN 1)
  SET(UNIX 1)
ENDIF(CMAKE_COMPILER_IS_CYGWIN)

SET(CMAKE_CXX_COMPILER_ENV_VAR "CXX")

IF(CMAKE_COMPILER_IS_MINGW)
  SET(MINGW 1)
ENDIF(CMAKE_COMPILER_IS_MINGW)
SET(CMAKE_CXX_COMPILER_ID_RUN 1)
SET(CMAKE_CXX_IGNORE_EXTENSIONS inl;h;hpp;HPP;H;o;O;obj;OBJ;def;DEF;rc;RC)
SET(CMAKE_CXX_SOURCE_FILE_EXTENSIONS C;M;c++;cc;cpp;cxx;m;mm;CPP)
SET(CMAKE_CXX_LINKER_PREFERENCE 30)
SET(CMAKE_CXX_LINKER_PREFERENCE_PROPAGATES 1)

# Save compiler ABI information.
SET(CMAKE_CXX_SIZEOF_DATA_PTR "8")
SET(CMAKE_CXX_COMPILER_ABI "ELF")

IF(CMAKE_CXX_SIZEOF_DATA_PTR)
  SET(CMAKE_SIZEOF_VOID_P "${CMAKE_CXX_SIZEOF_DATA_PTR}")
ENDIF(CMAKE_CXX_SIZEOF_DATA_PTR)

IF(CMAKE_CXX_COMPILER_ABI)
  SET(CMAKE_INTERNAL_PLATFORM_ABI "${CMAKE_CXX_COMPILER_ABI}")
ENDIF(CMAKE_CXX_COMPILER_ABI)

SET(CMAKE_CXX_HAS_ISYSROOT "")


SET(CMAKE_CXX_IMPLICIT_LINK_LIBRARIES "stdc++;m;c")
SET(CMAKE_CXX_IMPLICIT_LINK_DIRECTORIES "/home/opt/gcc-4.8.2.bpkg-r2/gcc-4.8.2.bpkg-r2/lib/gcc/x86_64-baidu-linux-gnu/4.8.2;/home/opt/gcc-4.8.2.bpkg-r2/gcc-4.8.2.bpkg-r2/lib/gcc;/home/opt/gcc-4.8.2.bpkg-r2/gcc-4.8.2.bpkg-r2/lib64;/home/opt/gcc-4.8.2.bpkg-r2/gcc-4.8.2.bpkg-r2/x86_64-baidu-linux-gnu/sys-root/lib64;/home/opt/gcc-4.8.2.bpkg-r2/gcc-4.8.2.bpkg-r2/x86_64-baidu-linux-gnu/sys-root/usr/lib64;/home/opt/gcc-4.8.2.bpkg-r2/gcc-4.8.2.bpkg-r2/x86_64-baidu-linux-gnu/lib;/home/opt/gcc-4.8.2.bpkg-r2/gcc-4.8.2.bpkg-r2/lib;/home/opt/gcc-4.8.2.bpkg-r2/gcc-4.8.2.bpkg-r2/x86_64-baidu-linux-gnu/sys-root/lib;/home/opt/gcc-4.8.2.bpkg-r2/gcc-4.8.2.bpkg-r2/x86_64-baidu-linux-gnu/sys-root/usr/lib")
