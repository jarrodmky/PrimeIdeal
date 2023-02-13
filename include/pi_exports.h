#pragma once

#ifdef SHARED_EXPORTS_BUILT_AS_STATIC
#  define PRIMEIDEAL_EXPORT
#  define PRIMEIDEAL_NO_EXPORT
#else
#  ifndef PRIMEIDEAL_EXPORT
#    ifdef PrimeIdeal_EXPORTS
        /* We are building this library */
#      define PRIMEIDEAL_EXPORT __declspec(dllexport)
#    else
        /* We are using this library */
#      define PRIMEIDEAL_EXPORT __declspec(dllimport)
#    endif
#  endif

#  ifndef PRIMEIDEAL_NO_EXPORT
#    define PRIMEIDEAL_NO_EXPORT 
#  endif
#endif

#ifndef PRIMEIDEAL_DEPRECATED
#  define PRIMEIDEAL_DEPRECATED __declspec(deprecated)
#endif

#ifndef PRIMEIDEAL_DEPRECATED_EXPORT
#  define PRIMEIDEAL_DEPRECATED_EXPORT PRIMEIDEAL_EXPORT PRIMEIDEAL_DEPRECATED
#endif

#ifndef PRIMEIDEAL_DEPRECATED_NO_EXPORT
#  define PRIMEIDEAL_DEPRECATED_NO_EXPORT PRIMEIDEAL_NO_EXPORT PRIMEIDEAL_DEPRECATED
#endif

#if 0 /* DEFINE_NO_DEPRECATED */
#  ifndef PRIMEIDEAL_NO_DEPRECATED
#    define PRIMEIDEAL_NO_DEPRECATED
#  endif
#endif
