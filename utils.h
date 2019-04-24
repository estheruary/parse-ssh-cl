#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <limits.h>
#include <netdb.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>

#define INVALID 1
#define TOOSMALL 2
#define TOOLARGE 3

long long
strtonum(const char *numstr, long long minval, long long maxval,
         const char **errstrp);

void *
xmalloc(size_t size);

static int
hexchar(const char *s);

int
a2port(const char *s);

static char *
urldecode(const char *src);

char *
hpdelim2(char **cp, char *delim);

int
valid_domain(char *name, int makelower, const char **errstr);

char *
cleanhostname(char *host);

char *
xstrdup(const char *str);

int
parse_uri(const char *scheme, const char *uri, char **userp, char **hostp,
          int *portp, char **pathp);

int
parse_ssh_uri(const char *uri, char **userp, char **hostp, int *portp);

int
parse_user_host_port(const char *s, char **userp, char **hostp, int *portp);

size_t
strlcpy(char * __restrict dst, const char * __restrict src, size_t dsize);
