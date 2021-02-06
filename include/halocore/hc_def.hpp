#ifndef HC_DEF_HPP
#define HC_DEF_HPP

#ifdef _WIN32
#    ifdef HC_EXPORTING
#        define HC_API __declspec(dllexport)
#    else
#        define HC_API __declspec(dllimport)
#    endif
#else
#    define HC_API
#endif

#endif // HC_DEF_HPP
