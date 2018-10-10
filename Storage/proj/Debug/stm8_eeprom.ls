   1                     ; C Compiler for STM8 (COSMIC Software)
   2                     ; Parser V4.8.32 - 23 Mar 2010
   3                     ; Generator V4.3.4 - 23 Mar 2010
2488                     ; 14 e_bool stm8_UnlockEEPROM(void)
2488                     ; 15 {
2490                     	switch	.text
2491  0000               _stm8_UnlockEEPROM:
2493  0000 89            	pushw	x
2494       00000002      OFST:	set	2
2497                     ; 16 	uint iCnt = 0;
2499  0001 5f            	clrw	x
2500  0002 1f01          	ldw	(OFST-1,sp),x
2501                     ; 18 	FLASH_CR1 |= 0x01;
2503  0004 7210505a      	bset	_FLASH_CR1,#0
2504                     ; 19 	if(FLASH_IAPSR & 0x08)
2506  0008 c6505f        	ld	a,_FLASH_IAPSR
2507  000b a508          	bcp	a,#8
2508  000d 2704          	jreq	L5161
2509                     ; 21         return BOOL_TRUE;
2511  000f a601          	ld	a,#1
2513  0011 2019          	jra	L6
2514  0013               L5161:
2515                     ; 25 		FLASH_DUKR = 0xAE;
2517  0013 35ae5064      	mov	_FLASH_DUKR,#174
2518                     ; 26 		FLASH_DUKR = 0x56;
2520  0017 35565064      	mov	_FLASH_DUKR,#86
2521  001b 2011          	jra	L3261
2522  001d               L1261:
2523                     ; 31 		iCnt ++;
2525  001d 1e01          	ldw	x,(OFST-1,sp)
2526  001f 1c0001        	addw	x,#1
2527  0022 1f01          	ldw	(OFST-1,sp),x
2528                     ; 32 		if(iCnt >= 5000)
2530  0024 1e01          	ldw	x,(OFST-1,sp)
2531  0026 a31388        	cpw	x,#5000
2532  0029 2503          	jrult	L3261
2533                     ; 34 			return BOOL_FALSE;
2535  002b 4f            	clr	a
2537  002c               L6:
2539  002c 85            	popw	x
2540  002d 81            	ret
2541  002e               L3261:
2542                     ; 29 	while(!(FLASH_IAPSR & 0x08))
2544  002e c6505f        	ld	a,_FLASH_IAPSR
2545  0031 a508          	bcp	a,#8
2546  0033 27e8          	jreq	L1261
2547                     ; 37 	return BOOL_TRUE;
2549  0035 a601          	ld	a,#1
2551  0037 20f3          	jra	L6
2575                     ; 47 void stm8_LockEEPROM(void)
2575                     ; 48 {
2576                     	switch	.text
2577  0039               _stm8_LockEEPROM:
2581                     ; 49 	FLASH_IAPSR &= (~0x08);
2583  0039 7217505f      	bres	_FLASH_IAPSR,#3
2584                     ; 50 }
2587  003d 81            	ret
2652                     .const:	section	.text
2653  0000               L41:
2654  0000 00040000      	dc.l	262144
2655                     ; 61 e_bool stm8_WriteToEEPROM(uint offset, uchar numb, const uchar *pData)
2655                     ; 62 {
2656                     	switch	.text
2657  003e               _stm8_WriteToEEPROM:
2659  003e 89            	pushw	x
2660  003f 5204          	subw	sp,#4
2661       00000004      OFST:	set	4
2664                     ; 65 	if (numb == 0)
2666  0041 0d09          	tnz	(OFST+5,sp)
2667  0043 2603          	jrne	L3761
2668                     ; 67         return BOOL_FALSE;
2670  0045 4f            	clr	a
2672  0046 2045          	jra	L61
2673  0048               L3761:
2674                     ; 70 	if(stm8_UnlockEEPROM())
2676  0048 adb6          	call	_stm8_UnlockEEPROM
2678  004a 4d            	tnz	a
2679  004b 2743          	jreq	L5761
2680                     ; 72         writeAddr = STM8_EEPROM_START_ADD + offset;
2682  004d 1e05          	ldw	x,(OFST+1,sp)
2683  004f cd0000        	call	c_uitolx
2685  0052 ae0000        	ldw	x,#L41
2686  0055 cd0000        	call	c_ladd
2688  0058 96            	ldw	x,sp
2689  0059 1c0001        	addw	x,#OFST-3
2690  005c cd0000        	call	c_rtol
2693  005f 2021          	jra	L3071
2694  0061               L7761:
2695                     ; 76             *((@far uchar*)(writeAddr)) = *pData;
2697  0061 1e0a          	ldw	x,(OFST+6,sp)
2698  0063 f6            	ld	a,(x)
2699  0064 88            	push	a
2700  0065 7b03          	ld	a,(OFST-1,sp)
2701  0067 b700          	ld	c_x,a
2702  0069 1e04          	ldw	x,(OFST+0,sp)
2703  006b 84            	pop	a
2704  006c bf01          	ldw	c_x+1,x
2705  006e 92bd0000      	ldf	[c_x.e],a
2706                     ; 77             writeAddr ++;
2708  0072 96            	ldw	x,sp
2709  0073 1c0001        	addw	x,#OFST-3
2710  0076 a601          	ld	a,#1
2711  0078 cd0000        	call	c_lgadc
2713                     ; 78             pData ++;
2715  007b 1e0a          	ldw	x,(OFST+6,sp)
2716  007d 1c0001        	addw	x,#1
2717  0080 1f0a          	ldw	(OFST+6,sp),x
2718  0082               L3071:
2719                     ; 74         while (numb --)
2721  0082 7b09          	ld	a,(OFST+5,sp)
2722  0084 0a09          	dec	(OFST+5,sp)
2723  0086 4d            	tnz	a
2724  0087 26d8          	jrne	L7761
2725                     ; 80         stm8_LockEEPROM();
2728  0089 adae          	call	_stm8_LockEEPROM
2730                     ; 82         return BOOL_TRUE;
2732  008b a601          	ld	a,#1
2734  008d               L61:
2736  008d 5b06          	addw	sp,#6
2737  008f 81            	ret
2738  0090               L5761:
2739                     ; 85     return BOOL_FALSE;
2741  0090 4f            	clr	a
2743  0091 20fa          	jra	L61
2806                     ; 97 void stm8_ReadFromEEPROM(uint offset, uchar numb, uchar *pData)
2806                     ; 98 {
2807                     	switch	.text
2808  0093               _stm8_ReadFromEEPROM:
2810  0093 89            	pushw	x
2811  0094 5204          	subw	sp,#4
2812       00000004      OFST:	set	4
2815                     ; 100 	writeAddr = STM8_EEPROM_START_ADD + offset;
2817  0096 cd0000        	call	c_uitolx
2819  0099 ae0000        	ldw	x,#L41
2820  009c cd0000        	call	c_ladd
2822  009f 96            	ldw	x,sp
2823  00a0 1c0001        	addw	x,#OFST-3
2824  00a3 cd0000        	call	c_rtol
2827  00a6 201f          	jra	L5471
2828  00a8               L1471:
2829                     ; 103         *pData = *((@far uchar*)(writeAddr));
2831  00a8 7b02          	ld	a,(OFST-2,sp)
2832  00aa b700          	ld	c_x,a
2833  00ac 1e03          	ldw	x,(OFST-1,sp)
2834  00ae bf01          	ldw	c_x+1,x
2835  00b0 92bc0000      	ldf	a,[c_x.e]
2836  00b4 1e0a          	ldw	x,(OFST+6,sp)
2837  00b6 f7            	ld	(x),a
2838                     ; 104         writeAddr ++;
2840  00b7 96            	ldw	x,sp
2841  00b8 1c0001        	addw	x,#OFST-3
2842  00bb a601          	ld	a,#1
2843  00bd cd0000        	call	c_lgadc
2845                     ; 105         pData ++;
2847  00c0 1e0a          	ldw	x,(OFST+6,sp)
2848  00c2 1c0001        	addw	x,#1
2849  00c5 1f0a          	ldw	(OFST+6,sp),x
2850  00c7               L5471:
2851                     ; 101 	while (numb --)
2853  00c7 7b09          	ld	a,(OFST+5,sp)
2854  00c9 0a09          	dec	(OFST+5,sp)
2855  00cb 4d            	tnz	a
2856  00cc 26da          	jrne	L1471
2857                     ; 107 }
2861  00ce 5b06          	addw	sp,#6
2862  00d0 81            	ret
2875                     	xdef	_stm8_LockEEPROM
2876                     	xdef	_stm8_UnlockEEPROM
2877                     	xdef	_stm8_ReadFromEEPROM
2878                     	xdef	_stm8_WriteToEEPROM
2879                     	xref.b	c_x
2898                     	xref	c_lgadc
2899                     	xref	c_rtol
2900                     	xref	c_ladd
2901                     	xref	c_uitolx
2902                     	end
