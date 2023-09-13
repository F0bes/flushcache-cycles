#include <stdio.h>
#include <stdlib.h>
#include <kernel.h>

#define T2_COUNT (u16 *)(0x10000800)
#define T2_MODE (u16 *)(0x10000810)

int main(int argc, char *argv[])
{
	printf("Using timer for following iterations\n");

	*T2_MODE = (1 << 7);

	for (int i = 0; i < 20; i++)
	{
		*T2_COUNT = 0;

		for (int j = 0; j < 5; j++)
			FlushCache(0);

		u16 cycles = *T2_COUNT;
		printf("FlushCache()x5 took ~%d bus cycles (%d CPU clock cycles)\n", cycles, cycles * 2);
	}

	printf("Using cop0 count for following iterations\n");

	for (int i = 0; i < 20; i++)
	{
		u32 str_cnt;
		asm volatile("mfc0 %0, $9" : "=r"(str_cnt));

		for (int j = 0; j < 5; j++)
			FlushCache(0);

		u32 end_cnt;
		asm volatile("mfc0 %0, $9" : "=r"(end_cnt));

		printf("FlushCache()x5 took ~%d cycles\n", end_cnt - str_cnt);
	}

	SleepThread();
	return 0;
}
