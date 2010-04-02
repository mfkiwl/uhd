#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/ioctl.h>

#include "usrp_e.h"

// Usage: usrp_e_spi w|rb slave data

int main(int argc, char *argv[])
{
	int fp, slave, length, ret;
	unsigned int data;
	struct usrp_e_spi spi_dat;

	if (argc < 5) {
		printf("Usage: usrp_e_spi w|rb slave transfer_length data\n");
		exit(-1);
	}

	slave = atoi(argv[2]);
	length = atoi(argv[3]);
	data = atoll(argv[4]);

	printf("Data = %X\n", data);

	fp = open("/dev/usrp_e0", O_RDWR);
	printf("fp = %d\n", fp);

	spi_dat.slave = slave;
	spi_dat.data = data;
	spi_dat.length = length;
	spi_dat.flags = 0;

	if (*argv[1] == 'r') {
		spi_dat.readback = 1;
		ret = ioctl(fp, USRP_E_SPI, &spi_dat);
		printf("Data returned = %d\n", ret);
	} else {
		spi_dat.readback = 0;
		ioctl(fp, USRP_E_SPI, &spi_dat);
	}

	return 0;
}
