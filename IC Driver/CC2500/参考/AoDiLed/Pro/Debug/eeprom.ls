   1                     ; C Compiler for STM8 (COSMIC Software)
   2                     ; Parser V4.8.32 - 23 Mar 2010
   3                     ; Generator V4.3.4 - 23 Mar 2010
2554                     .const:	section	.text
2555  0000               _pValuAdd_uchar:
2556  0000 0022          	dc.w	_machineInf+34
2557  0002 0023          	dc.w	_machineInf+35
2558  0004 0024          	dc.w	_machineInf+36
2559  0006               _TAB_Limit_uchar:
2560  0006 00            	dc.b	0
2561  0007 ff            	dc.b	255
2562  0008 ff            	dc.b	255
2563  0009 00            	dc.b	0
2564  000a ff            	dc.b	255
2565  000b ff            	dc.b	255
2566  000c 00            	dc.b	0
2567  000d ff            	dc.b	255
2568  000e ff            	dc.b	255
2575  000f               _TAB_Save_Data_List:
2576  000f 00            	dc.b	0
2577  0010 03            	dc.b	3
2578  0011 14            	dc.b	20
2579  0012 01            	dc.b	1
2580  0013 00            	dc.b	0
2581  0014 17            	dc.b	23
2582  0015 02            	dc.b	2
2583  0016 00            	dc.b	0
2584  0017 17            	dc.b	23
2722                     ; 76 uchar f_pUnLockEeprom(void)
2722                     ; 77 {
2724                     	switch	.text
2725  0000               _f_pUnLockEeprom:
2727  0000 89            	pushw	x
2728       00000002      OFST:	set	2
2731                     ; 79 	iCnt = 0;
2733  0001 5f            	clrw	x
2734  0002 1f01          	ldw	(OFST-1,sp),x
2735                     ; 80 	FLASH_CR1 |= 0x01;
2737  0004 7210505a      	bset	_FLASH_CR1,#0
2738                     ; 81 	if(FLASH_IAPSR & 0x08)
2740  0008 c6505f        	ld	a,_FLASH_IAPSR
2741  000b a508          	bcp	a,#8
2742  000d 2704          	jreq	L1371
2743                     ; 83 		return true;
2745  000f a601          	ld	a,#1
2747  0011 2019          	jra	L6
2748  0013               L1371:
2749                     ; 87 		FLASH_DUKR = 0xAE;
2751  0013 35ae5064      	mov	_FLASH_DUKR,#174
2752                     ; 88 		FLASH_DUKR = 0x56;
2754  0017 35565064      	mov	_FLASH_DUKR,#86
2755  001b 2011          	jra	L7371
2756  001d               L5371:
2757                     ; 92 		iCnt ++;
2759  001d 1e01          	ldw	x,(OFST-1,sp)
2760  001f 1c0001        	addw	x,#1
2761  0022 1f01          	ldw	(OFST-1,sp),x
2762                     ; 93 		if(iCnt >= 5000)
2764  0024 1e01          	ldw	x,(OFST-1,sp)
2765  0026 a31388        	cpw	x,#5000
2766  0029 2503          	jrult	L7371
2767                     ; 95 			return false;
2769  002b 4f            	clr	a
2771  002c               L6:
2773  002c 85            	popw	x
2774  002d 81            	ret
2775  002e               L7371:
2776                     ; 90 	while(!(FLASH_IAPSR & 0x08))
2778  002e c6505f        	ld	a,_FLASH_IAPSR
2779  0031 a508          	bcp	a,#8
2780  0033 27e8          	jreq	L5371
2781                     ; 98 	return true;
2783  0035 a601          	ld	a,#1
2785  0037 20f3          	jra	L6
2809                     ; 114 void f_pLockEeprom(void)
2809                     ; 115 {
2810                     	switch	.text
2811  0039               _f_pLockEeprom:
2815                     ; 116 	FLASH_IAPSR &= (~0x08);
2817  0039 7217505f      	bres	_FLASH_IAPSR,#3
2818                     ; 117 }
2821  003d 81            	ret
2884                     ; 134 void f_pWriteEeprom(uchar ADD,uchar iNO,uchar *iData)
2884                     ; 135 {
2885                     	switch	.text
2886  003e               _f_pWriteEeprom:
2888  003e 89            	pushw	x
2889  003f 5204          	subw	sp,#4
2890       00000004      OFST:	set	4
2893                     ; 137 	if(f_pUnLockEeprom() == false)
2895  0041 adbd          	call	_f_pUnLockEeprom
2897  0043 4d            	tnz	a
2898  0044 273d          	jreq	L61
2899                     ; 139 		return;
2901                     ; 141 	Start_ADD = START_EEROM_ADD + ADD;
2903  0046 a640          	ld	a,#64
2904  0048 97            	ld	xl,a
2905  0049 a600          	ld	a,#0
2906  004b 1b05          	add	a,(OFST+1,sp)
2907  004d 2401          	jrnc	L41
2908  004f 5c            	incw	x
2909  0050               L41:
2910  0050 cd0000        	call	c_itol
2912  0053 96            	ldw	x,sp
2913  0054 1c0001        	addw	x,#OFST-3
2914  0057 cd0000        	call	c_rtol
2917  005a 2023          	jra	L5102
2918  005c               L1102:
2919                     ; 144 		*((@far uchar*)Start_ADD) = *iData;
2921  005c 1e09          	ldw	x,(OFST+5,sp)
2922  005e f6            	ld	a,(x)
2923  005f 88            	push	a
2924  0060 7b03          	ld	a,(OFST-1,sp)
2925  0062 b700          	ld	c_x,a
2926  0064 1e04          	ldw	x,(OFST+0,sp)
2927  0066 84            	pop	a
2928  0067 bf01          	ldw	c_x+1,x
2929  0069 92bd0000      	ldf	[c_x.e],a
2930                     ; 145 		Start_ADD ++;
2932  006d 96            	ldw	x,sp
2933  006e 1c0001        	addw	x,#OFST-3
2934  0071 a601          	ld	a,#1
2935  0073 cd0000        	call	c_lgadc
2937                     ; 146 		iData ++;
2939  0076 1e09          	ldw	x,(OFST+5,sp)
2940  0078 1c0001        	addw	x,#1
2941  007b 1f09          	ldw	(OFST+5,sp),x
2942                     ; 147 		iNO --;
2944  007d 0a06          	dec	(OFST+2,sp)
2945  007f               L5102:
2946                     ; 142 	while(iNO)
2948  007f 0d06          	tnz	(OFST+2,sp)
2949  0081 26d9          	jrne	L1102
2950                     ; 149 }
2951  0083               L61:
2954  0083 5b06          	addw	sp,#6
2955  0085 81            	ret
3017                     ; 166 void f_pReadEeprom(uchar iADD,uchar iNO,uchar *iData)
3017                     ; 167 {
3018                     	switch	.text
3019  0086               _f_pReadEeprom:
3021  0086 89            	pushw	x
3022  0087 5204          	subw	sp,#4
3023       00000004      OFST:	set	4
3026                     ; 169 	Start_ADD = START_EEROM_ADD + iADD;
3028  0089 a640          	ld	a,#64
3029  008b 97            	ld	xl,a
3030  008c a600          	ld	a,#0
3031  008e 1b05          	add	a,(OFST+1,sp)
3032  0090 2401          	jrnc	L22
3033  0092 5c            	incw	x
3034  0093               L22:
3035  0093 cd0000        	call	c_itol
3037  0096 96            	ldw	x,sp
3038  0097 1c0001        	addw	x,#OFST-3
3039  009a cd0000        	call	c_rtol
3042  009d 201f          	jra	L7502
3043  009f               L3502:
3044                     ; 172 		*iData = *((@far uchar*)Start_ADD);
3046  009f 7b02          	ld	a,(OFST-2,sp)
3047  00a1 b700          	ld	c_x,a
3048  00a3 1e03          	ldw	x,(OFST-1,sp)
3049  00a5 bf01          	ldw	c_x+1,x
3050  00a7 92bc0000      	ldf	a,[c_x.e]
3051  00ab 1e09          	ldw	x,(OFST+5,sp)
3052  00ad f7            	ld	(x),a
3053                     ; 173 		iData ++;
3055  00ae 1e09          	ldw	x,(OFST+5,sp)
3056  00b0 1c0001        	addw	x,#1
3057  00b3 1f09          	ldw	(OFST+5,sp),x
3058                     ; 174 		Start_ADD ++;
3060  00b5 96            	ldw	x,sp
3061  00b6 1c0001        	addw	x,#OFST-3
3062  00b9 a601          	ld	a,#1
3063  00bb cd0000        	call	c_lgadc
3065  00be               L7502:
3066                     ; 170 	while(iNO --)
3068  00be 7b06          	ld	a,(OFST+2,sp)
3069  00c0 0a06          	dec	(OFST+2,sp)
3070  00c2 4d            	tnz	a
3071  00c3 26da          	jrne	L3502
3072                     ; 176 }
3075  00c5 5b06          	addw	sp,#6
3076  00c7 81            	ret
3150                     ; 192 void f_pReadOneTypeData(uchar iDataType,uchar iAddInEerom)
3150                     ; 193 {
3151                     	switch	.text
3152  00c8               _f_pReadOneTypeData:
3154  00c8 89            	pushw	x
3155  00c9 5204          	subw	sp,#4
3156       00000004      OFST:	set	4
3159                     ; 197 	iReadByte = 0;
3161  00cb 0f04          	clr	(OFST+0,sp)
3162                     ; 198 	if(iDataType == UCHAR)
3164  00cd 9e            	ld	a,xh
3165  00ce 4d            	tnz	a
3166  00cf 2615          	jrne	L1212
3167                     ; 201 		iRealDataAdd = pValuAdd_uchar[iAddInEerom];
3169  00d1 9f            	ld	a,xl
3170  00d2 5f            	clrw	x
3171  00d3 97            	ld	xl,a
3172  00d4 58            	sllw	x
3173  00d5 de0000        	ldw	x,(_pValuAdd_uchar,x)
3174  00d8 1f01          	ldw	(OFST-3,sp),x
3175                     ; 202 		iAddress = iAddInEerom + UCHAR_START_ADD;
3177  00da 7b06          	ld	a,(OFST+2,sp)
3178  00dc ab14          	add	a,#20
3179  00de 6b03          	ld	(OFST-1,sp),a
3180                     ; 203 		iReadByte = 1;
3182  00e0 a601          	ld	a,#1
3183  00e2 6b04          	ld	(OFST+0,sp),a
3185  00e4 200a          	jra	L3212
3186  00e6               L1212:
3187                     ; 206 	else if(iDataType == UINT)
3189  00e6 7b05          	ld	a,(OFST+1,sp)
3190  00e8 a101          	cp	a,#1
3191  00ea 2704          	jreq	L3212
3193                     ; 214 	else if(iDataType == ULONG)
3195  00ec 7b05          	ld	a,(OFST+1,sp)
3196  00ee a102          	cp	a,#2
3197  00f0               L3212:
3198                     ; 222 	if(iReadByte)
3200  00f0 0d04          	tnz	(OFST+0,sp)
3201  00f2 270c          	jreq	L3312
3202                     ; 223 		f_pReadEeprom(iAddress,iReadByte,iRealDataAdd);
3204  00f4 1e01          	ldw	x,(OFST-3,sp)
3205  00f6 89            	pushw	x
3206  00f7 7b06          	ld	a,(OFST+2,sp)
3207  00f9 97            	ld	xl,a
3208  00fa 7b05          	ld	a,(OFST+1,sp)
3209  00fc 95            	ld	xh,a
3210  00fd ad87          	call	_f_pReadEeprom
3212  00ff 85            	popw	x
3213  0100               L3312:
3214                     ; 224 }
3217  0100 5b06          	addw	sp,#6
3218  0102 81            	ret
3221                     	bsct
3222  0000               L7312_changeFlag:
3223  0000 00            	dc.b	0
3224                     	switch	.ubsct
3225  0000               L1412_iAddInEerom:
3226  0000 00            	ds.b	1
3227  0001               L5312_iWriteByte:
3228  0001 00            	ds.b	1
3229  0002               L3412_iAddress:
3230  0002 00            	ds.b	1
3313                     ; 239 void f_pWriteOneDataEeprom(void)
3313                     ; 240 {
3314                     	switch	.text
3315  0103               _f_pWriteOneDataEeprom:
3317  0103 5203          	subw	sp,#3
3318       00000003      OFST:	set	3
3321                     ; 248 	for(i=0;i<UCHAR_NO;i++)
3323  0105 0f03          	clr	(OFST+0,sp)
3324  0107               L7022:
3325                     ; 250 		if(pBuff_uchar[i] != *(pValuAdd_uchar[i]))
3327  0107 7b03          	ld	a,(OFST+0,sp)
3328  0109 5f            	clrw	x
3329  010a 97            	ld	xl,a
3330  010b 58            	sllw	x
3331  010c de0000        	ldw	x,(_pValuAdd_uchar,x)
3332  010f 7b03          	ld	a,(OFST+0,sp)
3333  0111 905f          	clrw	y
3334  0113 9097          	ld	yl,a
3335  0115 90d60000      	ld	a,(_pBuff_uchar,y)
3336  0119 f1            	cp	a,(x)
3337  011a 272f          	jreq	L5122
3338                     ; 252 			pBuff_uchar[i] = *(pValuAdd_uchar[i]);
3340  011c 7b03          	ld	a,(OFST+0,sp)
3341  011e 5f            	clrw	x
3342  011f 97            	ld	xl,a
3343  0120 7b03          	ld	a,(OFST+0,sp)
3344  0122 905f          	clrw	y
3345  0124 9097          	ld	yl,a
3346  0126 9058          	sllw	y
3347  0128 90de0000      	ldw	y,(_pValuAdd_uchar,y)
3348  012c 90f6          	ld	a,(y)
3349  012e d70000        	ld	(_pBuff_uchar,x),a
3350                     ; 253 			iWriteByte = 1;
3352  0131 35010001      	mov	L5312_iWriteByte,#1
3353                     ; 254 			iAddInEerom = i;
3355  0135 7b03          	ld	a,(OFST+0,sp)
3356  0137 b700          	ld	L1412_iAddInEerom,a
3357                     ; 255 			iRealDataAdd = pValuAdd_uchar[iAddInEerom];
3359  0139 b600          	ld	a,L1412_iAddInEerom
3360  013b 5f            	clrw	x
3361  013c 97            	ld	xl,a
3362  013d 58            	sllw	x
3363  013e de0000        	ldw	x,(_pValuAdd_uchar,x)
3364  0141 1f01          	ldw	(OFST-2,sp),x
3365                     ; 256 			iAddress = iAddInEerom + UCHAR_START_ADD;
3367  0143 b600          	ld	a,L1412_iAddInEerom
3368  0145 ab14          	add	a,#20
3369  0147 b702          	ld	L3412_iAddress,a
3370                     ; 257 			break;
3372  0149 2008          	jra	L3122
3373  014b               L5122:
3374                     ; 248 	for(i=0;i<UCHAR_NO;i++)
3376  014b 0c03          	inc	(OFST+0,sp)
3379  014d 7b03          	ld	a,(OFST+0,sp)
3380  014f a103          	cp	a,#3
3381  0151 25b4          	jrult	L7022
3382  0153               L3122:
3383                     ; 295 	if(iWriteByte)
3385  0153 3d01          	tnz	L5312_iWriteByte
3386  0155 270f          	jreq	L7122
3387                     ; 297 		f_pWriteEeprom(iAddress,iWriteByte,iRealDataAdd);
3389  0157 1e01          	ldw	x,(OFST-2,sp)
3390  0159 89            	pushw	x
3391  015a b601          	ld	a,L5312_iWriteByte
3392  015c 97            	ld	xl,a
3393  015d b602          	ld	a,L3412_iAddress
3394  015f 95            	ld	xh,a
3395  0160 cd003e        	call	_f_pWriteEeprom
3397  0163 85            	popw	x
3398                     ; 298 		iWriteByte = 0;
3400  0164 3f01          	clr	L5312_iWriteByte
3401  0166               L7122:
3402                     ; 300 }
3405  0166 5b03          	addw	sp,#3
3406  0168 81            	ret
3481                     ; 316 void f_pWriteOneTypeData(uchar iDataType,uchar iAddInEerom)
3481                     ; 317 {
3482                     	switch	.text
3483  0169               _f_pWriteOneTypeData:
3485  0169 89            	pushw	x
3486  016a 5204          	subw	sp,#4
3487       00000004      OFST:	set	4
3490                     ; 321 	iWriteByte = 0;
3492  016c 0f04          	clr	(OFST+0,sp)
3493                     ; 322 	if(iDataType == UCHAR)
3495  016e 9e            	ld	a,xh
3496  016f 4d            	tnz	a
3497  0170 2615          	jrne	L7522
3498                     ; 325 		iRealDataAdd = pValuAdd_uchar[iAddInEerom];
3500  0172 9f            	ld	a,xl
3501  0173 5f            	clrw	x
3502  0174 97            	ld	xl,a
3503  0175 58            	sllw	x
3504  0176 de0000        	ldw	x,(_pValuAdd_uchar,x)
3505  0179 1f01          	ldw	(OFST-3,sp),x
3506                     ; 326 		iAddress = iAddInEerom + UCHAR_START_ADD;
3508  017b 7b06          	ld	a,(OFST+2,sp)
3509  017d ab14          	add	a,#20
3510  017f 6b03          	ld	(OFST-1,sp),a
3511                     ; 327 		iWriteByte = 1;
3513  0181 a601          	ld	a,#1
3514  0183 6b04          	ld	(OFST+0,sp),a
3516  0185 200a          	jra	L1622
3517  0187               L7522:
3518                     ; 330 	else if(iDataType == UINT)
3520  0187 7b05          	ld	a,(OFST+1,sp)
3521  0189 a101          	cp	a,#1
3522  018b 2704          	jreq	L1622
3524                     ; 338 	else if(iDataType == ULONG)
3526  018d 7b05          	ld	a,(OFST+1,sp)
3527  018f a102          	cp	a,#2
3528  0191               L1622:
3529                     ; 346 	if(iWriteByte)
3531  0191 0d04          	tnz	(OFST+0,sp)
3532  0193 270d          	jreq	L1722
3533                     ; 347 		f_pWriteEeprom(iAddress,iWriteByte,iRealDataAdd);
3535  0195 1e01          	ldw	x,(OFST-3,sp)
3536  0197 89            	pushw	x
3537  0198 7b06          	ld	a,(OFST+2,sp)
3538  019a 97            	ld	xl,a
3539  019b 7b05          	ld	a,(OFST+1,sp)
3540  019d 95            	ld	xh,a
3541  019e cd003e        	call	_f_pWriteEeprom
3543  01a1 85            	popw	x
3544  01a2               L1722:
3545                     ; 348 }
3548  01a2 5b06          	addw	sp,#6
3549  01a4 81            	ret
3552                     	switch	.ubsct
3553  0003               L3722_i:
3554  0003 00            	ds.b	1
3591                     ; 363 void f_pReadAllDataEeprom(void)
3591                     ; 364 {
3592                     	switch	.text
3593  01a5               _f_pReadAllDataEeprom:
3597                     ; 367 		for(i=0;i< UCHAR_NO;i++)
3599  01a5 3f03          	clr	L3722_i
3600  01a7               L3132:
3601                     ; 369 			f_pReadOneTypeData(UCHAR, i);
3603  01a7 b603          	ld	a,L3722_i
3604  01a9 97            	ld	xl,a
3605  01aa 4f            	clr	a
3606  01ab 95            	ld	xh,a
3607  01ac cd00c8        	call	_f_pReadOneTypeData
3609                     ; 370 			pBuff_uchar[i] = *(pValuAdd_uchar[i]);
3611  01af b603          	ld	a,L3722_i
3612  01b1 5f            	clrw	x
3613  01b2 97            	ld	xl,a
3614  01b3 b603          	ld	a,L3722_i
3615  01b5 905f          	clrw	y
3616  01b7 9097          	ld	yl,a
3617  01b9 9058          	sllw	y
3618  01bb 90de0000      	ldw	y,(_pValuAdd_uchar,y)
3619  01bf 90f6          	ld	a,(y)
3620  01c1 d70000        	ld	(_pBuff_uchar,x),a
3621                     ; 371 			if((*(pValuAdd_uchar[i]) < TAB_Limit_uchar[i][0]) || (*(pValuAdd_uchar[i]) > TAB_Limit_uchar[i][1]))
3623  01c4 b603          	ld	a,L3722_i
3624  01c6 97            	ld	xl,a
3625  01c7 a603          	ld	a,#3
3626  01c9 42            	mul	x,a
3627  01ca b603          	ld	a,L3722_i
3628  01cc 905f          	clrw	y
3629  01ce 9097          	ld	yl,a
3630  01d0 9058          	sllw	y
3631  01d2 90de0000      	ldw	y,(_pValuAdd_uchar,y)
3632  01d6 90f6          	ld	a,(y)
3633  01d8 d10006        	cp	a,(_TAB_Limit_uchar,x)
3634  01db 2519          	jrult	L3232
3636  01dd b603          	ld	a,L3722_i
3637  01df 97            	ld	xl,a
3638  01e0 a603          	ld	a,#3
3639  01e2 42            	mul	x,a
3640  01e3 b603          	ld	a,L3722_i
3641  01e5 905f          	clrw	y
3642  01e7 9097          	ld	yl,a
3643  01e9 9058          	sllw	y
3644  01eb 90de0000      	ldw	y,(_pValuAdd_uchar,y)
3645  01ef 90f6          	ld	a,(y)
3646  01f1 d10007        	cp	a,(_TAB_Limit_uchar+1,x)
3647  01f4 2326          	jrule	L1232
3648  01f6               L3232:
3649                     ; 373 				*(pValuAdd_uchar[i]) = TAB_Limit_uchar[i][2];
3651  01f6 b603          	ld	a,L3722_i
3652  01f8 5f            	clrw	x
3653  01f9 97            	ld	xl,a
3654  01fa 58            	sllw	x
3655  01fb de0000        	ldw	x,(_pValuAdd_uchar,x)
3656  01fe 89            	pushw	x
3657  01ff b603          	ld	a,L3722_i
3658  0201 97            	ld	xl,a
3659  0202 a603          	ld	a,#3
3660  0204 42            	mul	x,a
3661  0205 d60008        	ld	a,(_TAB_Limit_uchar+2,x)
3662  0208 85            	popw	x
3663  0209 f7            	ld	(x),a
3664                     ; 374 				pBuff_uchar[i] = TAB_Limit_uchar[i][2];
3666  020a b603          	ld	a,L3722_i
3667  020c 5f            	clrw	x
3668  020d 97            	ld	xl,a
3669  020e 89            	pushw	x
3670  020f b603          	ld	a,L3722_i
3671  0211 97            	ld	xl,a
3672  0212 a603          	ld	a,#3
3673  0214 42            	mul	x,a
3674  0215 d60008        	ld	a,(_TAB_Limit_uchar+2,x)
3675  0218 85            	popw	x
3676  0219 d70000        	ld	(_pBuff_uchar,x),a
3677  021c               L1232:
3678                     ; 367 		for(i=0;i< UCHAR_NO;i++)
3680  021c 3c03          	inc	L3722_i
3683  021e b603          	ld	a,L3722_i
3684  0220 a103          	cp	a,#3
3685  0222 2583          	jrult	L3132
3686                     ; 402 }
3689  0224 81            	ret
3692                     	switch	.ubsct
3693  0004               L5232_i:
3694  0004 00            	ds.b	1
3742                     ; 417 void f_pWriteAllDataEeprom(void)
3742                     ; 418 {
3743                     	switch	.text
3744  0225               _f_pWriteAllDataEeprom:
3746  0225 89            	pushw	x
3747       00000002      OFST:	set	2
3750                     ; 423 		for(i=0;i< UCHAR_NO;i++)
3752  0226 3f04          	clr	L5232_i
3753  0228               L1532:
3754                     ; 425 			*(pValuAdd_uchar[i]) = TAB_Limit_uchar[i][2];
3756  0228 b604          	ld	a,L5232_i
3757  022a 5f            	clrw	x
3758  022b 97            	ld	xl,a
3759  022c 58            	sllw	x
3760  022d de0000        	ldw	x,(_pValuAdd_uchar,x)
3761  0230 89            	pushw	x
3762  0231 b604          	ld	a,L5232_i
3763  0233 97            	ld	xl,a
3764  0234 a603          	ld	a,#3
3765  0236 42            	mul	x,a
3766  0237 d60008        	ld	a,(_TAB_Limit_uchar+2,x)
3767  023a 85            	popw	x
3768  023b f7            	ld	(x),a
3769                     ; 426 			pBuff_uchar[i] = TAB_Limit_uchar[i][2];
3771  023c b604          	ld	a,L5232_i
3772  023e 5f            	clrw	x
3773  023f 97            	ld	xl,a
3774  0240 89            	pushw	x
3775  0241 b604          	ld	a,L5232_i
3776  0243 97            	ld	xl,a
3777  0244 a603          	ld	a,#3
3778  0246 42            	mul	x,a
3779  0247 d60008        	ld	a,(_TAB_Limit_uchar+2,x)
3780  024a 85            	popw	x
3781  024b d70000        	ld	(_pBuff_uchar,x),a
3782                     ; 427 			f_pWriteOneTypeData(UCHAR, i);
3784  024e b604          	ld	a,L5232_i
3785  0250 97            	ld	xl,a
3786  0251 4f            	clr	a
3787  0252 95            	ld	xh,a
3788  0253 cd0169        	call	_f_pWriteOneTypeData
3790                     ; 423 		for(i=0;i< UCHAR_NO;i++)
3792  0256 3c04          	inc	L5232_i
3795  0258 b604          	ld	a,L5232_i
3796  025a a103          	cp	a,#3
3797  025c 25ca          	jrult	L1532
3798                     ; 448 	iTemp = FIRST_POWER_ON_FLAG;
3800  025e ae5161        	ldw	x,#20833
3801  0261 1f01          	ldw	(OFST-1,sp),x
3802                     ; 449 	f_pWriteEeprom(FIRST_POWER_ON_FLAG_ADD,2,(const uchar *)(&iTemp));
3804  0263 96            	ldw	x,sp
3805  0264 1c0001        	addw	x,#OFST-1
3806  0267 89            	pushw	x
3807  0268 ae0002        	ldw	x,#2
3808  026b 4f            	clr	a
3809  026c 95            	ld	xh,a
3810  026d cd003e        	call	_f_pWriteEeprom
3812  0270 85            	popw	x
3813                     ; 450 	f_pLockEeprom();
3815  0271 cd0039        	call	_f_pLockEeprom
3817                     ; 451 }
3820  0274 85            	popw	x
3821  0275 81            	ret
3847                     ; 466 void f_pInitDataEeprom(void)
3847                     ; 467 {
3848                     	switch	.text
3849  0276               _f_pInitDataEeprom:
3853                     ; 468 	if(eFirstPowerON == FIRST_POWER_ON_FLAG)
3855  0276 ce4000        	ldw	x,_eFirstPowerON
3856  0279 a35161        	cpw	x,#20833
3857  027c 2605          	jrne	L7632
3858                     ; 470 		f_pReadAllDataEeprom();
3860  027e cd01a5        	call	_f_pReadAllDataEeprom
3863  0281 2002          	jra	L1732
3864  0283               L7632:
3865                     ; 475 		f_pWriteAllDataEeprom();
3867  0283 ada0          	call	_f_pWriteAllDataEeprom
3869  0285               L1732:
3870                     ; 477 }
3873  0285 81            	ret
3898                     	xdef	_f_pWriteAllDataEeprom
3899                     	xdef	_f_pReadEeprom
3900                     	xdef	_f_pWriteEeprom
3901                     	xdef	_f_pLockEeprom
3902                     	xdef	_f_pUnLockEeprom
3903                     	switch	.bss
3904  0000               _pBuff_uchar:
3905  0000 000000        	ds.b	3
3906                     	xdef	_pBuff_uchar
3907                     	xdef	_f_pWriteOneDataEeprom
3908                     	xdef	_f_pInitDataEeprom
3909                     	xdef	_f_pReadAllDataEeprom
3910                     	xdef	_f_pReadOneTypeData
3911                     	xdef	_f_pWriteOneTypeData
3912                     	xdef	_TAB_Save_Data_List
3913                     	xdef	_TAB_Limit_uchar
3914                     	xdef	_pValuAdd_uchar
3915                     	xref	_machineInf
3916                     	xref.b	c_x
3936                     	xref	c_lgadc
3937                     	xref	c_rtol
3938                     	xref	c_itol
3939                     	end
