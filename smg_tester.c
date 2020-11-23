#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include <net/if.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>

#include <linux/can.h>
#include <linux/can/raw.h>
#include <pthread.h>
#include "./include/smg_tester.h"

int s;
struct can_frame frame;

void *canSend(void *vargp)
{

	while (1)
	{
		usleep(TIME_100MS);
		printf("can thread\n");
	}
	return NULL;
}

int main(void)
{
	pthread_t can_thread;

	initialize();

	pthread_create(&can_thread, NULL, canSend, NULL);
	pthread_join(can_thread, NULL);

	frame.can_id = 0x123;
	frame.can_dlc = 2;
	frame.data[0] = 0x11;
	frame.data[1] = 0x22;

	while (1)
	{
		sleep(0.5);
		printf("main thread\n");
	}

	return 0;
}

int initialize()
{
	struct ifreq ifr;
	struct sockaddr_can addr;

	const char *ifname = "vcan0";

	if ((s = socket(PF_CAN, SOCK_RAW, CAN_RAW)) < 0)
	{
		perror("Error while opening socket");
		return -1;
	}

	strcpy(ifr.ifr_name, ifname);
	ioctl(s, SIOCGIFINDEX, &ifr);

	addr.can_family = AF_CAN;
	addr.can_ifindex = ifr.ifr_ifindex;

	printf("%s at index %d\n", ifname, ifr.ifr_ifindex);

	if (bind(s, (struct sockaddr *)&addr, sizeof(addr)) < 0)
	{
		perror("Error in socket bind");
		return -2;
	}

	return 1;
}