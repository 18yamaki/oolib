/**
 * @file
 * A RingBuffer Class for C.
 * imitates object oriented on C.
 * @copyright MIT License.
 * @author y.yamaki
 */
#ifndef _RING_BUF_H_
#define _RING_BUF_H_

/**
 * A type of RingBuffer
 */
typedef struct RingBuf RingBuf;

/**
 * RingBuffer class.
 */
struct RingBuf {

	/** A pointer of buffer */
	void* buf;
	/** An element count */
	unsigned int count;
	/** An element size */
	unsigned int unit;
	/** A size of buffer */
	unsigned int bufSize;
	/** A time to wait cursors.[unit:msec] */
	unsigned int sleepTimeMSec;
	/** A cursor to read */
	unsigned int readCur;
	/** A cursor to write */
	unsigned int writeCur;

	/**
	 * gets cursor to read.
	 * @param this a instance of RingBuffer
	 * @return pointer of buffer.
	 */
	void* (*getReadBuf)(RingBuf* this);

	/**
	 * commits cursor to read.
	 * @param this a instance of RingBuffer
	 */
	void (*readCommit)(RingBuf* this);

	/**
	 * gets cursor to write.
	 * @param this a instance of RingBuffer
	 * @return pointer of buffer.
	 */
	void* (*getWriteBuf)(RingBuf* this);

	/**
	 * commits cursor to write.
	 * @param this a instance of RingBuffer
	 */
	void (*writeCommit)(RingBuf* this);

	/**
	 * gets count of buffer.
	 * @param this a instance of RingBuffer
	 */
	unsigned int (*getBufCount)(RingBuf* this);

	/**
	 * sets time to wait cursors.
	 * should be called if modify wait time.
	 * @param this a instance of RingBuffer
	 */
	void (*setSleepTime)(RingBuf* this, unsigned int msec);
};

/**
 * A constructor.
 * @param count a element count.
 * @param unit a element size.
 */
extern RingBuf* RingBuf_new(unsigned int count, unsigned int unit);

/**
 * A destructor.
 * @param this a instance.
 */
extern void RingBuf_destroy(RingBuf** this);

#endif /* _RING_BUF_H_ */

