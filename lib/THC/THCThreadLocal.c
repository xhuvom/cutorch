#include "THCThreadLocal.h"
#include "THCGeneral.h"


THCThreadLocal THCThreadLocal_alloc()
{
#ifndef _WIN32
  pthread_key_t key;
  THAssert(pthread_key_create(&key, NULL) == 0);
  return key;
#else
  DWORD key = TlsAlloc();
  THAssert(key != TLS_OUT_OF_INDEXES);
  return key;
#endif
}

void THCThreadLocal_free(THCThreadLocal local)
{
#ifndef _WIN32
  THAssert(pthread_key_delete(local) == 0);
#else
  THAssert(TlsFree(local));
#endif
}

void* THCThreadLocal_get(THCThreadLocal local)
{
#ifndef _WIN32
  return pthread_getspecific(local);
#else
  return TlsGetValue(local);
#endif
}

void THCThreadLocal_set(THCThreadLocal local, void* value)
{
#ifndef _WIN32
  THAssert(pthread_setspecific(local, value) == 0);
#else
  THAssert(TlsSetValue(local, value));
#endif
}
