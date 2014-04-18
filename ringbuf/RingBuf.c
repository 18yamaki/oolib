/**
 * @file
 * A RingBuffer Class for C.
 * imitates object oriented on C.
 * implement source.
 * @copyright MIT License.
 * @author y.yamaki
 */
#include <stdlib.h>
#include <unistd.h>
#include "RingBuf.h"

static void* RingBuf_getReadBuf(RingBuf* this);
static void RingBuf_readCommit(RingBuf* this);
static void* RingBuf_getWriteBuf(RingBuf* this);
static void RingBuf_writeCommit(RingBuf* this);
static unsigned int RingBuf_getBufCount(RingBuf* this);
static void RingBuf_setSleepTime(RingBuf* this, unsigned int msec);


RingBuf*
RingBuf_new(unsigned int count, unsigned int unit)
{
	RingBuf* ins;
	ins = (RingBuf*) malloc(sizeof(RingBuf));
	if (ins == NULL) return NULL;
	ins->count = count + 1;
	ins->unit = unit;
	ins->bufSize = count * unit;
	ins->sleepTimeMSec = 100 * 1000;
	ins->readCur = 0;
	ins->writeCur = 0;

	ins->buf = malloc(ins->bufSize);
	if (ins->buf == NULL)
	{
		free(ins);
		return NULL;
	}

	ins->getReadBuf = RingBuf_getReadBuf;
	ins->readCommit = RingBuf_readCommit;
	ins->getWriteBuf = RingBuf_getWriteBuf;
	ins->writeCommit = RingBuf_writeCommit;
	ins->getBufCount = RingBuf_getBufCount;
	ins->setSleepTime = RingBuf_setSleepTime;

	return ins;
}

void
RingBuf_destroy(RingBuf** this)
{
	free((*this)->buf);
	free(*this);
	*this = NULL;
}

static void*
RingBuf_getReadBuf(RingBuf* this)
{
	while (RingBuf_getBufCount(this) <= 0)
		usleep(this->sleepTimeMSec);
	return this->buf + (this->readCur * this->unit);
}

static void
RingBuf_readCommit(RingBuf* this)
{
	this->readCur++;
	this->readCur %= this->count;
}

static void*
RingBuf_getWriteBuf(RingBuf* this)
{
	while (RingBuf_getBufCount(this) >= (this->count - 1))
		usleep(this->sleepTimeMSec);
	return this->buf + (this->writeCur * this->unit);
}

static void
RingBuf_writeCommit(RingBuf* this)
{
	this->writeCur++;
	this->writeCur %= this->count;
}

static unsigned int
RingBuf_getBufCount(RingBuf* this)
{
	unsigned int count;
	unsigned int tr, tw;

	count = 0;
	tr = this->readCur;
	tw = this->writeCur;

	if (tr < tw)
		count = tw - tr;
	else if (tw < tr)
		count = tw + (this->count - tr);

	return count;
}

static void
RingBuf_setSleepTime(RingBuf* this, unsigned int msec)
{
	this->sleepTimeMSec = msec * 1000;
}

