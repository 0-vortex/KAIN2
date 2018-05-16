#include "LOAD3D.H"

#include "G2TYPES.H"

#include <SYS\TYPES.H>
#include <LIBCD.H>
#include <LIBETC.H>
#include <LIBGPU.H>
#include <LIBSN.H>
#include <STDLIB.H>

struct LoadStatus loadStatus;

void LOAD_InitCd()
{
	CdInit();
	ResetCallback();
	CdSetDebug(0);
}

void LOAD_CdSeekCallback(unsigned char intr, unsigned char* result)
{
	if (loadStatus.waitingForSeek)
	{
		loadStatus.waitingForSeek = 0;
	}
}

void LOAD_CdDataReady()
{
	if (loadStatus.currentSector > loadStatus.currentQueueFile->blocks)
	{
		loadStatus.currentQueueFile->bufferFlags |= 0x1;
	}
}

void LOAD_CdReadReady(unsigned char intr, unsigned char* result)
{
	if (loadStatus.waitingForData != NULL)
	{
		if ((intr & 0xFF) == 1)
		{
			if (loadStatus.currentSector < loadStatus.currentQueueFile->blocks)
			{
				CdGetSector((void*)loadStatus.currentQueueFile->dest[loadStatus.currentSector++ << 9], 1 << 9);

				if (loadStatus.currentSector > loadStatus.currentQueueFile->blocks)
				{
					CdControlF(9, NULL);
				}
			}
		}
	}
}

void LOAD_UpdateCheckSum(struct FileAccessInfo* currentQueueFile, long sectors)
{
	long i;

	if (currentQueueFile->checksumType == 1)
	{
		i = 0;
		if ((sectors << 9) <= 0)
		{
			return;
		}

		++i;

		//loc_8003775C
		while (i < sectors)
		{
			loadStatus.checksum += *loadStatus.checkAddr;
			loadStatus.checkAddr++;
			i++;
		}
	}//loc_8003778C
	else if (currentQueueFile->checksumType == 2)
	{
		i = 0;

		if (sectors <= 0)
		{
			return;
		}

		++i;

		//loc_800377A0
		while (i < sectors)
		{
			loadStatus.checksum += *loadStatus.checkAddr;
			loadStatus.checkAddr += 512;
			i++;
		}
	}
}
/*
 * Offset 0x800377D0
 * C:\kain2\game\LOAD3D.C (line 489)
 * Stack frame base $sp, size 32
 * Saved registers at offset -8: s0 s1 ra
 */
void /*$ra*/ LOAD_DoCDReading(struct FileAccessInfo* currentQueueFile /*$s1*/)
{ // line 1, offset 0x800377d0
    long sectorsLoaded; // $s0
    long decompressLen; // $s0
} // line 57, offset 0x80037954
/*
 * Offset 0x80037968
 * C:\kain2\game\LOAD3D.C (line 549)
 * Stack frame base $sp, size 40
 * Saved registers at offset -8: s0 s1 ra
 */
void /*$ra*/ LOAD_DoCDBufferedReading(struct FileAccessInfo* currentQueueFile /*$s0*/)
{ // line 1, offset 0x80037968
    struct NonBlockLoadEntry *loadEntry; // $s1
    long actualReadSize; // $a1
    long status; // $a2
} // line 91, offset 0x80037b34
/*
 * Offset 0x80037B48
 * C:\kain2\game\LOAD3D.C (line 642)
 * Stack frame base $sp, size 24
 * Saved registers at offset -8: ra
 */
void /*$ra*/ LOAD_SetupFileToDoCDReading(struct FileAccessInfo* currentQueueFile /*$a1*/)
{ // line 1, offset 0x80037b48
    long i; // $a0
} // line 34, offset 0x80037c1c
/*
 * Offset 0x80037C68
 * C:\kain2\game\LOAD3D.C (line 754)
 * Stack frame base $sp, size 24
 * Saved registers at offset -8: ra
 */
void /*$ra*/ LOAD_SetupFileToDoBufferedCDReading(struct FileAccessInfo* currentQueueFile /*$a1*/)
{
}
/*
 * Offset 0x80037D08
 * C:\kain2\game\LOAD3D.C (line 782)
 * Stack frame base $sp, size 24
 * Saved registers at offset -4: s0 ra
 */
void /*$ra*/ LOAD_ProcessReadQueue()
{ // line 1, offset 0x80037d08
    struct FileAccessInfo *currentQueueFile; // $s0
} // line 55, offset 0x80037de4

long LOAD_CdReadFromBigFile(long fileOffset, unsigned long* loadAddr, unsigned long* finalDest, long blocks, long chksumLevel, long checksum, long compressed)
{
    struct FileAccessInfo* currentQueueReq;
    long oldQueueReqIndex;

	currentQueueReq = &loadStatus.loadQueue[loadStatus.currentQueueReqIndex];
	
	if (currentQueueReq->status != 0)
	{
		while (currentQueueReq->status != 0)
		{
			LOAD_ProcessReadQueue();
		}
	}//loc_80037E68

	CdIntToPos(loadStatus.bigFile.bigfileBaseOffset + fileOffset, &currentQueueReq->loc);

	currentQueueReq->blocks = blocks;
	currentQueueReq->dest = loadAddr;
	currentQueueReq->finalDest = finalDest;
	currentQueueReq->fileOffset = fileOffset;
	currentQueueReq->status = 1;
	currentQueueReq->checksumType = chksumLevel;
	currentQueueReq->checksum = checksum;
	currentQueueReq->bufferBlocks = 0;
	currentQueueReq->compressedLen = compressed;

	oldQueueReqIndex = loadStatus.currentQueueReqIndex;

	loadStatus.currentQueueReqIndex = (oldQueueReqIndex + 1) & 3;

	LOAD_ProcessReadQueue();

	return oldQueueReqIndex;
} // line 13, offset 0x80037e68
/*
 * Offset 0x80037EF4
 * C:\kain2\game\LOAD3D.C (line 874)
 * Stack frame base $sp, size 80
 * Saved registers at offset -8: s0 s1 ra
 */
void /*$ra*/ LOAD_InitCdLoader(char* bigFileName /*$s0*/, char* voiceFileName /*$a1*/)
{ // line 1, offset 0x80037ef4
    CdlFILE fp; // stack offset -48
    long i; // $a0
    long fileId; // $a0
    long sizeOfContents; // $s0
    char *bigFileContents; // $s1
    unsigned char cdMode; // stack offset -24

	//s0 = bigFileName
	//a0 = 0x80030000
	//v0 = 0x80
	cdMode = 0x80;
	loadStatus.waitingForData = 0;

	CdReadyCallback(LOAD_CdReadReady);
	//a0 = LOAD_CdSeekCallback;
	loadStatus.waitingForSeek = 0;
	CdSyncCallback(LOAD_CdSeekCallback);
	CdDataCallback(LOAD_CdDataReady);
	
	if (CdSearchFile(&fp, bigFileName) == NULL)
	{
		return;
	}

	CdControl(0xE, &cdMode, NULL);
	loadStatus.bigFile.bigfileBaseOffset = CdPosToInt(&fp.pos);

	//loc_80037F78
	for (i = 0; i < 4; i++)
	{
		loadStatus.loadQueue[i].status = 0;
	}

	loadStatus.currentQueueFile = &loadStatus.loadQueue[0];
	loadStatus.currentQueueFileIndex = 0;
	loadStatus.currentQueueReqIndex = 0;

	bigFileContents = MEMPACK_Malloc(4096, 8);

	fileId = LOAD_CdReadFromBigFile(0, bigFileContents, bigFileContents, 1, 0, 0, 0);

	sizeof(struct FileAccessInfo);
	//v1 = loadStatus.loadQueue[fileId]
	//v0 = loadStatus.loadQueue[fileId].status
	//s0 = v1
	if (loadStatus.loadQueue[fileId].status != 0)
	{
		while (loadStatus.loadQueue[fileId].status != 0)
		{
			LOAD_ProcessReadQueue();
		}
	}//loc_80038014
	loadStatus.bigFile.numFiles = ((long*)bigFileContents)[0];
	MEMPACK_Free(bigFileContents);
	//v1 = loadStatus.bigFile.numFiles;
	//a1 = 8;
	//v0 = ((loadStatus.bigFile.numFiles << 1) + loadStatus.bigFile.numFiles) << 3;
	sizeOfContents = ((loadStatus.bigFile.numFiles << 1) + loadStatus.bigFile.numFiles) << 3;
	sizeOfContents = ((sizeOfContents & 0x7FF) >> 11) << 11;

	loadStatus.bigFile.contents = MEMPACK_Malloc(sizeOfContents);
	if (loadStatus.bigFile.contents == NULL)
	{
		PSYQpause();
	}
	//loc_80038064
	fileId = LOAD_CdReadFromBigFile(0, loadStatus.bigFile.contents, loadStatus.bigFile.contents, sizeOfContents >> 11, 0, 0, 0);
	loadStatus.bigFile.contents = &((long*)loadStatus.bigFile.contents)[1];

	if (loadStatus.loadQueue[fileId].status != 0)
	{
		while (loadStatus.loadQueue[fileId].status != 0);
			LOAD_ProcessReadQueue();

	}
	//loc_800380DC
}

/*
 * Offset 0x800380F0
 * C:\kain2\game\LOAD3D.C (line 945)
 * Stack frame base $sp, size 64
 * Saved registers at offset -8: s0 s1 s2 s3 s4 s5 ra
 */
long * /*$ra*/ LOAD_ReadFile(char* fileName /*$a0*/, unsigned char memType /*$s0*/)
{ // line 1, offset 0x800380f0
    long bigFileIndex; // $s3
    long length; // $s1
    long checksum; // $v1
    long compressed; // $s5
    long compressedLength; // $s4
    char *finalDest; // $s0
    struct BigFileFileInfo *fileInfo; // $s2

	return NULL;
} // line 23, offset 0x80038158
/*
 * Offset 0x800381E0
 * C:\kain2\game\LOAD3D.C (line 992)
 * Stack frame base $sp, size 32
 * Saved registers at offset -4: s0 s1 s2 ra
 */
long * /*$ra*/ LOAD_SetupNonBlockingReadFile(char* fileName /*$a0*/, unsigned char memType /*$s2*/, struct NonBlockLoadEntry* loadEntry /*$s0*/, long forceSize /*$s1*/)
{ // line 1, offset 0x800381e0
    long bigFileIndex; // $a0
    long length; // $a1
    long checksum; // $a0
    long compressed; // $a2
    long compressedLength; // $t0
    struct BigFileFileInfo *fileInfo; // $a3

	return NULL;
} // line 44, offset 0x800382bc
/*
 * Offset 0x800382D8
 * C:\kain2\game\LOAD3D.C (line 1040)
 * Stack frame base $sp, size 40
 * Saved registers at offset -4: s0 ra
 */
long LOAD_NonBlockingReadFile(struct NonBlockLoadEntry* loadEntry)
{
	///loadEntry->finalDest = MEMPACK_Malloc(loadEntry->mallocedSize, loadEntry->memType);
	loadEntry->loadAddr = &loadEntry->finalDest[((loadEntry->mallocedSize >> 11) - loadEntry->compressedLength) << 11];
	return LOAD_CdReadFromBigFile(loadEntry->filePos, loadEntry->loadAddr, loadEntry->finalDest, loadEntry->compressedLength, loadEntry->checksumType, loadEntry->checksum, loadEntry->compressed);
}

/*
 * Offset 0x80038360
 * C:\kain2\game\LOAD3D.C (line 1059)
 * Stack frame base $sp, size 32
 * Saved registers at offset -8: s0 s1 ra
 */
long /*$ra*/ LOAD_CD_ReadPartOfFile(struct NonBlockLoadEntry* loadEntry /*$s1*/)
{ // line 1, offset 0x80038360
    struct FileAccessInfo *currentQueueReq; // $s0
    long oldQueueReqIndex; // $s0
	return 0;
} // line 13, offset 0x800383bc
/*
 * Offset 0x800384A0
 * C:\kain2\game\LOAD3D.C (line 1100)
 * Stack frame base $sp, size 24
 * Saved registers at offset -4: s0 ra
 */
int /*$ra*/ LOAD_IsFileLoading(long fileId /*$s0*/)
{ // line 1, offset 0x800384a0
    long loopFlag; // $v0
	return 0;
} // line 28, offset 0x80038534
/*
 * Offset 0x80038544
 * C:\kain2\game\LOAD3D.C (line 1141)
 * Stack frame base $sp, size 56
 * Saved registers at offset -4: s0 s1 s2 s3 s4 s5 s6 s7 fp ra
 */
long /*$ra*/ LOAD_HashName(char* string /*stack 0*/)
{ // line 1, offset 0x80038544
    long sum; // $s5
    long xor; // $s6
    long length; // $s4
    long ext; // $s7
    char c; // $v1
    long strl; // $s2
    long endPos; // $fp
    long i; // $s0
    char *pos; // $s3
	return 0;
} // line 41, offset 0x8003864c
/*
 * Offset 0x80038694
 * C:\kain2\game\LOAD3D.C (line 1185)
 * Stack frame base $sp, size 24
 * Saved registers at offset -8: ra
 */
long /*$ra*/ LOAD_GetBigFileFileIndex(char* fileName /*$a0*/)
{ // line 1, offset 0x80038694
    long hash; // $a2
    long bigFileIndex; // $v1
	return 0;
} // line 17, offset 0x800386e0
/*
 * Offset 0x800386F0
 * C:\kain2\game\LOAD3D.C (line 1215)
 * Stack frame base $sp, size 24
 * Saved registers at offset -4: s0 ra
 */
long /*$ra*/ LOAD_DoesFileExist(char* fileName /*$a0*/)
{ // line 1, offset 0x800386f0
    long hash; // $a2
    long bigFileIndex; // $v1
    long result; // $s0
	return 0;
} // line 18, offset 0x80038754
/*
 * Offset 0x80038768
 * C:\kain2\game\LOAD3D.C (line 1238)
 * Stack frame base $sp, size 40
 * Saved registers at offset -4: s0 s1 s2 ra
 */
void /*$ra*/ LOAD_LoadTIM(long* addr /*$s0*/, long x_pos /*$s1*/, long y_pos /*$s2*/, long clut_x /*$a3*/, long clut_y /*stack 16*/)
{ // line 1, offset 0x80038768
    RECT rect; // stack offset -24
} // line 18, offset 0x800387c8

void LOAD_LoadTIM2(long* addr, long x_pos, long y_pos, long width, long height)
{
	RECT rect;

	rect.x = x_pos;
	addr = &addr[2];
	rect.y = y_pos;
	rect.w = ((short*)addr)[4];
	addr = &addr[3];
	rect.h = ((short*)addr)[5];
	LoadImage(&rect, (u_long*)addr);
	DrawSync(0);
}

/*
 * Offset 0x80038860
 * C:\kain2\game\LOAD3D.C (line 1314)
 * Stack frame base $sp, size 48
 * Saved registers at offset -8: s0 s1 s2 s3 ra
 */
void * /*$ra*/ LOAD_RelocBinaryData(long* data /*$s0*/)
{ // line 1, offset 0x80038860
    long *dataAddr; // $s1
    long *lastMoveDest; // $v1
    long tableSize; // $s3
    long fileSize; // $v0
    struct RedirectList redirectListX; // stack offset -32
    struct RedirectList *redirectList; // $a0

	return NULL;
} // line 21, offset 0x80038900
/*
 * Offset 0x8003892C
 * C:\kain2\game\LOAD3D.C (line 1346)
 * Stack frame base $sp, size 0
 */
long /*$ra*/ LOAD_lzrw1_decompress(unsigned long src_len /*$a0*/, long overBufferTolerance /*$a1*/)
{ // line 2, offset 0x8003892c
    unsigned char *p_src; // $a2
    unsigned char *p_dst; // $a3
    unsigned long controlbits; // $t1
    unsigned long control; // $t0
    unsigned char *p_src_post; // $t3
    unsigned long offset; // $v0
    unsigned long len; // $a0
    long remainingBytes; // $v0
    unsigned char *p; // $v1

	return 0;
} // line 62, offset 0x80038a14

void LOAD_LoadingScreen(long fileId)
{
    long loopFlag;

	if (fileId == -1)
	{
		loopFlag = 1;
	}
	else
	{
		loopFlag = 0 < loadStatus.loadQueue[fileId].status ? 1 : 0;
	}

	//loc_80038A70
	if (loopFlag != 0)
	{
		while (loopFlag != 0)
		{
			loopFlag = 0;
			if (fileId != -1)
			{
				LOAD_ProcessReadQueue();
				loopFlag = 0 < loadStatus.loadQueue[fileId].status ? 1 : 0;
			}
		}
	}

	DrawSync(0);
}