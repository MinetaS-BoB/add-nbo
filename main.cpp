#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "nhcvt.h"


/* Error Macros =================================================================== */

#define ERROR0(err)                             \
do {                                            \
        fprintf(stderr, "add-nbo: " err "\n");  \
} while ( 0 )

#define ERROR1(err, arg1)                               \
do {                                                    \
        fprintf(stderr, "add-nbo: " err "\n", arg1);    \
} while ( 0 )

#define ERROR2(err, arg1, arg2)                                 \
do {                                                            \
        fprintf(stderr, "add-nbo: " err "\n", arg1, arg2);      \
} while ( 0 )


/* Main Routine =================================================================== */

int s_open(const char *pathname, int flags) {
	int fd;

	if ((fd = open(pathname, flags)) == -1) {
		ERROR2("'%s' : %s", pathname, strerror(errno));
	}

	return fd;
}

int main(int argc, char **argv, char **envp) {
	if (argc == 0) {
		ERROR0("invalid execution");
		exit(1);
	}

	if (argc != 3) {
		ERROR1("Usage: %s [file1] [file2]", argv[0]);
		exit(1);
	}

	int f1 = s_open(argv[1], O_RDONLY);
	int f2 = s_open(argv[2], O_RDONLY);

	if (f1 == -1 || f2 == -1) {
		goto errout;
	}

	uint32_t v1, v2;

	if (read(f1, &v1, 4) < 4) {
		if (errno)
			ERROR2("'%s' : %s", argv[1], strerror(errno));
		else
			ERROR1("'%s' : insufficient bytes", argv[1]);
		goto errout;
	}

	if (read(f2, &v2, 4) < 4) {
		if (errno)
			ERROR2("'%s' : %s", argv[2], strerror(errno));
		else
			ERROR1("'%s' : insufficient bytes", argv[2]);
		goto errout;
	}

	{
		v1 = ntohl(v1);
		v2 = ntohl(v2);
		uint32_t r = v1 + v2;

		printf("%u(%#x) + %u(%#x) = %u(%#x)\n", v1, v1, v2, v2, r, r);
	}

errout:
	close(f2);
	close(f1);

	return 0;
}