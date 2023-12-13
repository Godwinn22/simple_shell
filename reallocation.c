#include "shell.h"

/**
 * *mem_set - function that fills memory with a constant byte
 * @memoryArea: the pointer to the memory area
 * @byteToFill: the byte to fill memoryArea with
 * @numberOfBytes: the amount of bytes to be filled
 *
 * Return: returns a pointer to the memory area memoryArea
 */
char *mem_set(char *memoryArea, char byteToFill, unsigned int numberOfBytes)
{
	unsigned int index;

	for (index = 0; index < numberOfBytes; index++)
		memoryArea[index] = byteToFill;
	return (memoryArea);
}

/**
 * freeStrs - function that frees a string of strings
 * @strOfStrs: string of strings
 *
 * Return: void
 */
void freeStrs(char **strOfStrs)
{
	char **a = strOfStrs;

	if (!strOfStrs)
		return;
	while (*strOfStrs)
		free(*strOfStrs++);
	free(a);
}

/**
 * *_realloc - a function that reallocates a block of memory
 * @prevMemBlock: pointer to previous malloc'ated block
 * @prevSize: byte size of previous block
 * @newSize: the byte size of new block
 *
 * Return: returns a pointer to the new block of memory
 */
void *_realloc(void *prevMemBlock, unsigned int prevSize, unsigned int newSize)
{
	char *p;

	if (!prevMemBlock)
		return (malloc(newSize));
	if (!newSize)
		return (free(prevMemBlock), NULL);
	if (newSize == prevSize)
		return (prevMemBlock);

	p = malloc(newSize);
	if (!p)
		return (NULL);

	prevSize = prevSize < newSize ? prevSize : newSize;
	while (prevSize--)
		p[prevSize] = ((char *)prevMemBlock)[prevSize];
	free(prevMemBlock);
	return (p);
}

/**
 * freeptr - frees a pointer and NULLs the address
 * @ptrAddress: address of the pointer to be freed
 *
 * Return: returns 1 if freed, otherwise 0.
 */
int freeptr(void **ptrAddress)
{
	if (ptrAddress && *ptrAddress)
	{
		free(*ptrAddress);
		*ptrAddress = NULL;
		return (1);
	}
	return (0);
}
