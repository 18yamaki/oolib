/**
 * @file
 * An example how to use RingBuf.
 * @copyright MIT License.
 * @author y.yamaki
 */
#include <stdio.h>
#include <string.h>
#include "RingBuf.h"

#define BUF_COUNT 20

void
doRingBufSample(void)
{
	RingBuf* rbuf;
	void* buf;
	int i;

	rbuf = RingBuf_new(BUF_COUNT, sizeof(int));
	for (i = 0; i < BUF_COUNT; i++) {
		buf = rbuf->getWriteBuf(rbuf);
		memcpy(buf, &i, sizeof(int));
		rbuf->writeCommit(rbuf);
	}

	for (i = 0; i < BUF_COUNT; i++) {
		buf = rbuf->getReadBuf(rbuf);
		printf("buf [%d] \r\n", *((int*)buf));
		fflush(stdout);
		rbuf->readCommit(rbuf);
	}

	RingBuf_destroy(&rbuf);
}

int
main(void)
{
	doRingBufSample();
	return 0;
}


