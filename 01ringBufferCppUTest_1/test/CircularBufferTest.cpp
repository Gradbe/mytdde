#include "CppUTest/TestHarness.h"

extern "C"
{
#include "CircularBuffer.h"
}

#include "CppUTest/TestHarness.h"

TEST_GROUP(RingBuffer){
	RingBuffer_t* buffer;
	void setup(){
		buffer = RingBuffer_Create(10);
	}
	void teardown(){
		RingBuffer_Destroy(buffer);
	}
};

TEST(RingBuffer, CreateAndDestroy)
{
	CHECK(buffer != NULL);
}

TEST(RingBuffer, IsEmptyAfterCreation){
	CHECK(RingBuffer_IsEmpty(buffer));
}

TEST(RingBuffer, PutAndGetOneCharacter){
	RingBuffer_Put(buffer, 'x');
	char c = RingBuffer_Get(buffer);
	CHECK_EQUAL(c, 'x');
}

TEST(RingBuffer, Overflow){
	RingBuffer_Put(buffer, 'a');
	RingBuffer_Put(buffer, 'b');
	RingBuffer_Put(buffer, 'c');
	char c = RingBuffer_Get(buffer);
	CHECK_EQUAL('a', c);
	RingBuffer_Put(buffer, 'd');
	c = RingBuffer_Get(buffer);
	CHECK_EQUAL('b', c);
	c = RingBuffer_Get(buffer);
	c = RingBuffer_Get(buffer);
	CHECK_EQUAL('d', c);
}

TEST(RingBuffer, NotEmptyAfterPut){
	RingBuffer_Put(buffer, 'a');
	CHECK_FALSE(RingBuffer_IsEmpty(buffer));
}

TEST(RingBuffer, EmptyAgainAfterPutAndGet){
	RingBuffer_Put(buffer, 'a');
	RingBuffer_Get(buffer);
	CHECK(RingBuffer_IsEmpty(buffer));
}

TEST(RingBuffer, FillAndFailOnOverflow){
	for (int i = 0; i < 10; i++){
		CHECK_TRUE(RingBuffer_Put(buffer, 'a'));
	}
	CHECK_FALSE(RingBuffer_Put(buffer, 'a'));
}

TEST(RingBuffer, ReadBackInOrder){
	for(int i=0; i < 10; i++){
		RingBuffer_Put(buffer, 'A'+i);
	}
	for(int i=0; i<10;i++){
		CHECK_EQUAL('A'+i, RingBuffer_Get(buffer));
	}
}

TEST(RingBuffer, FailReadOnEmpty){
	CHECK_EQUAL(0, RingBuffer_Get(buffer));
}

TEST(RingBuffer, PeekDoesNotRemoveData){
	RingBuffer_Put(buffer, 'q');
	char c = 0;
	CHECK_TRUE(RingBuffer_Peek(buffer, &c));
	CHECK_EQUAL('q', c);
	CHECK_FALSE(RingBuffer_IsEmpty(buffer));
}

TEST(RingBuffer, PeekFailsIfEmpty){
	char c = 0;
	CHECK_FALSE(RingBuffer_Peek(buffer, &c));
}
	
