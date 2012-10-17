#include <stdlib.h>
#include <stdio.h>
#include <signal.h>

#include "clocaltunnel.h"

static struct clocaltunnel_client *my_client;

void int_handler(int signal) {
	if (my_client) {
			printf("\nShutting down clocaltunnel client...\n");
			clocaltunnel_client_stop(my_client);
			clocaltunnel_client_free(my_client);

			clocaltunnel_global_cleanup();
	}

	exit(0);
}

int main(int argc, char **argv) {
	signal(SIGINT, int_handler);

	clocaltunnel_global_init();

	clocaltunnel_error err;

	my_client = clocaltunnel_client_alloc(&err);

	clocaltunnel_client_init(my_client, 80);

	printf("Starting clocaltunnel client...\n");

	clocaltunnel_client_start(my_client, &err);

	printf("Client running. Use Ctrl+C to exit.\n");

	while(1) {}

	return 0;
}