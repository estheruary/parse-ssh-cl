#include "utils.h"

int
main(int argc, char *argv[]) {
  int opt;
  printf("Options:");
  while ((opt = getopt(argc, argv, "-1246ab:c:e:fgi:kl:m:no:p:qstvx"
      "AB:CD:E:F:GI:J:KL:MNO:PQ:R:S:TVw:W:XYy")) != -1) {
    // Stop processing options after the first positional argument and set
    // optind back to the location of that argument.
    if (opt == 1) {
      optind -= 1;
      break;
    }

    printf(" -%c", opt);
    if (optarg != 0) {
        printf(" %s", optarg);
    }
  }
  printf("\n");

  if (optind >= argc) {
    fprintf(stderr, "No destination found.\n");
    return 1;
  }

  char *destination = argv[optind];
  char *user;
  char *host;
  int port = -1;

  if (parse_ssh_uri(destination, &user, &host, &port) == 0
      || parse_user_host_port(destination, &user, &host, &port) == 0) {

    if (user != NULL) {
      printf("User: %s\n", user);
    } else {
      printf("User:\n");
    }

    printf("Host: %s\n", host);

    if (port != -1) {
      printf("Port: %d\n", port);
    } else {
      printf("Port:\n");
    }

    free(user);
    free(host);

    printf("Command:");
    for (int i = ++optind; i < argc; i++) {
      printf(" %s", argv[i]);
    }
    printf("\n");
  } else {
    fprintf(stderr, "Could not parse destination host.\n");
    return 1;
  }

  return 0;
}
