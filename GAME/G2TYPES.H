#ifndef G2TYPES_H
#define G2TYPES_H

#include <LIBCD.H>

struct FileAccessInfo
{
	CdlLOC loc;
	unsigned long* dest;
	unsigned long* finalDest;
	long fileOffset;
	long blocks;
	long status;
	long checksum;
	long checksumType;
	long compressedLen;
	long bufferBlocks;
	long totalBlocks;
	long curBufferOffset;
	unsigned long* buffer1;
	unsigned long* buffer2;
	short bufferFlags;
	short currentBuffer;
	unsigned long* bufferRead;
	long numberOfBlocksRead;
	void* retFunc;
	void* retData;
	void* retData2;
	struct NonBlockLoadEntry* loadEntry;
};

struct BigFileFileInfo
{
	long fileHash;
	long fileLen;
	long compressedLen;
	long filePos;
	long checkSumFull;
	long checkSumBlocks;
};

struct BigFile
{
	long numFiles;
	long bigfileBaseOffset;
	struct BigFileFileInfo* contents;
};

struct LoadStatus
{
	struct FileAccessInfo loadQueue[4];
	struct FileAccessInfo* currentQueueFile;
	long currentQueueFileIndex;
	long currentQueueReqIndex;
	long waitingForSeek;
	long* waitingForData;
	long* waitingSector;
	long remSectors;
	long currentSector;
	long cdWaitTime;
	unsigned char* compSrcAddr;
	unsigned char* compDstAddr;
	long compControlbits;
	long compControl;
	long compEndBytes;
	long decompressLen;
	long checksum;
	long* checkAddr;
	struct BigFile bigFile;
};

extern struct LoadStatus loadStatus;

#endif