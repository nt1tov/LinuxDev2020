#define _GNU_SOURCE
#include <dlfcn.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>

typedef int (*orig_type)(int dirfd, const char *pathname, int flags);
int unlinkat(int dirfd, const char *pathname, int flags) {
	orig_type otype;
	if (strstr(pathname, "FIX")) {
		errno = EPERM;
		return -1;
	}
	
	otype  = dlsym(RTLD_NEXT, "unlinkat");
	return otype(dirfd, pathname, flags);
}
