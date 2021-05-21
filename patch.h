#include <windows.h>

static inline PROC patch_call(char* src, char* dst)
{
    DWORD op = PAGE_EXECUTE_READ;
    VirtualProtect(src, 5, PAGE_EXECUTE_READWRITE, &op);
    src[0] = '\xE8';
    DWORD org = *((DWORD*)(&src[1]));
    *((DWORD*)(&src[1])) = dst - src - 5;
    VirtualProtect(src, 5, op, &op);
    return (PROC)(src + 5 + org);
}

static inline void patch_ljmp(char* src, char* dst)
{
    DWORD op = PAGE_EXECUTE_READ;
    VirtualProtect(src, 5, PAGE_EXECUTE_READWRITE, &op);
    src[0] = '\xE9';
    *((DWORD*)(&src[1])) = dst - src - 5;
    VirtualProtect(src, 5, op, &op);
}

static inline void patch_clear(char* start, char value, char* end)
{
    DWORD op = PAGE_EXECUTE_READ;
    VirtualProtect(start, end - start, PAGE_EXECUTE_READWRITE, &op);
    memset(start, value, end - start);
    VirtualProtect(start, end - start, op, &op);
}

static inline void patch_setdword(DWORD* dst, DWORD value)
{
    DWORD op = PAGE_EXECUTE_READ;
    VirtualProtect(dst, sizeof(DWORD), PAGE_EXECUTE_READWRITE, &op);
    *dst = value;
    VirtualProtect(dst, sizeof(DWORD), op, &op);
}

static inline void patch_setbytes(char* dst, char* buf, size_t size)
{
    DWORD op = PAGE_EXECUTE_READ;
    VirtualProtect(dst, size, PAGE_EXECUTE_READWRITE, &op);
    memcpy(dst, buf, size);
    VirtualProtect(dst, size, op, &op);
}

#define PATCH_SET(a,b) patch_setbytes(a,b,sizeof(b)-1)