#ifndef LOAD3D_H
#define LOAD3D_H

#include "G2TYPES.H"

extern void LOAD_InitCd();
extern void LOAD_CdSeekCallback(unsigned char intr, unsigned char* result);
extern void LOAD_CdDataReady();
extern void LOAD_CdReadReady(unsigned char intr, unsigned char* result);
extern void LOAD_UpdateCheckSum(struct FileAccessInfo* currentQueueFile, long sectors);
extern void LOAD_DoCDReading(struct FileAccessInfo* currentQueueFile);
extern void LOAD_DoCDBufferedReading(struct FileAccessInfo* currentQueueFile);
extern void LOAD_SetupFileToDoCDReading(struct FileAccessInfo* currentQueueFile);
extern void LOAD_SetupFileToDoBufferedCDReading(struct FileAccessInfo* currentQueueFile);
extern void LOAD_ProcessReadQueue();
extern long LOAD_CdReadFromBigFile(long fileOffset, unsigned long* loadAddr, unsigned long* finalDest, long blocks, long chksumLevel, long checksum, long compressed);
extern void LOAD_InitCdLoader(char* bigFileName, char* voiceFileName);
extern long* LOAD_ReadFile(char* fileName, unsigned char memType);
extern long* LOAD_SetupNonBlockingReadFile(char* fileName, unsigned char memType, struct NonBlockLoadEntry* loadEntry, long forceSize);
extern long LOAD_NonBlockingReadFile(struct NonBlockLoadEntry* loadEntry);
extern long LOAD_CD_ReadPartOfFile(struct NonBlockLoadEntry* loadEntry);
extern int LOAD_IsFileLoading(long fileId);
extern long LOAD_HashName(char* string);
extern long LOAD_GetBigFileFileIndex(char* fileName);
extern long LOAD_DoesFileExist(char* fileName);
extern void LOAD_LoadTIM(long* addr, long x_pos, long y_pos, long clut_x, long clut_y);
extern void LOAD_LoadTIM2(long* addr, long x_pos, long y_pos, long width, long height);
extern void* LOAD_RelocBinaryData(long* data);
extern long LOAD_lzrw1_decompress(unsigned long src_len, long overBufferTolerance);
extern void LOAD_LoadingScreen(long fileId);

#endif