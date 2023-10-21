#pragma once

#ifdef _WIN32
  #define conan-exp2_EXPORT __declspec(dllexport)
#else
  #define conan-exp2_EXPORT
#endif

conan-exp2_EXPORT void conan-exp2();
