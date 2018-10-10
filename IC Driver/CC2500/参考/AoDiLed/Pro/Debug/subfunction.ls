   1                     ; C Compiler for STM8 (COSMIC Software)
   2                     ; Parser V4.8.32 - 23 Mar 2010
   3                     ; Generator V4.3.4 - 23 Mar 2010
2700                     ; 9 void *f_Memcpy(void *dest,const void *src, uint nSize)
2700                     ; 10 {
2702                     	switch	.text
2703  0000               _f_Memcpy:
2705  0000 89            	pushw	x
2706  0001 5204          	subw	sp,#4
2707       00000004      OFST:	set	4
2710                     ; 11 	uchar *mov = src;
2712  0003 1e09          	ldw	x,(OFST+5,sp)
2713  0005 1f01          	ldw	(OFST-3,sp),x
2714                     ; 12 	uchar *mov_to = dest;
2716  0007 1e05          	ldw	x,(OFST+1,sp)
2717  0009 1f03          	ldw	(OFST-1,sp),x
2718                     ; 14 	if(src == NULL || dest == NULL)
2720  000b 1e09          	ldw	x,(OFST+5,sp)
2721  000d 2704          	jreq	L7371
2723  000f 1e05          	ldw	x,(OFST+1,sp)
2724  0011 2619          	jrne	L3471
2725  0013               L7371:
2726                     ; 16 		return NULL;
2728  0013 5f            	clrw	x
2730  0014 2027          	jra	L6
2731  0016               L1471:
2732                     ; 21 		*mov_to++ = *mov++;
2734  0016 1e01          	ldw	x,(OFST-3,sp)
2735  0018 1c0001        	addw	x,#1
2736  001b 1f01          	ldw	(OFST-3,sp),x
2737  001d 1d0001        	subw	x,#1
2738  0020 f6            	ld	a,(x)
2739  0021 1e03          	ldw	x,(OFST-1,sp)
2740  0023 1c0001        	addw	x,#1
2741  0026 1f03          	ldw	(OFST-1,sp),x
2742  0028 1d0001        	subw	x,#1
2743  002b f7            	ld	(x),a
2744  002c               L3471:
2745                     ; 19 	while(nSize --)
2747  002c 1e0b          	ldw	x,(OFST+7,sp)
2748  002e 1d0001        	subw	x,#1
2749  0031 1f0b          	ldw	(OFST+7,sp),x
2750  0033 1c0001        	addw	x,#1
2751  0036 a30000        	cpw	x,#0
2752  0039 26db          	jrne	L1471
2753                     ; 24 	return(mov_to);
2755  003b 1e03          	ldw	x,(OFST-1,sp)
2757  003d               L6:
2759  003d 5b06          	addw	sp,#6
2760  003f 81            	ret
2831                     ; 32 uint f_CheckSum(uchar *nBuff,uchar nStartNo,uchar nEndNo)
2831                     ; 33 {
2832                     	switch	.text
2833  0040               _f_CheckSum:
2835  0040 89            	pushw	x
2836  0041 5203          	subw	sp,#3
2837       00000003      OFST:	set	3
2840                     ; 36 	nTotalSum = 0;
2842  0043 5f            	clrw	x
2843  0044 1f01          	ldw	(OFST-2,sp),x
2844                     ; 37 	for(i = nStartNo; i < nEndNo; i ++)
2846  0046 7b08          	ld	a,(OFST+5,sp)
2847  0048 6b03          	ld	(OFST+0,sp),a
2849  004a 2016          	jra	L1102
2850  004c               L5002:
2851                     ; 39 		nTotalSum += nBuff[i];
2853  004c 7b04          	ld	a,(OFST+1,sp)
2854  004e 97            	ld	xl,a
2855  004f 7b05          	ld	a,(OFST+2,sp)
2856  0051 1b03          	add	a,(OFST+0,sp)
2857  0053 2401          	jrnc	L21
2858  0055 5c            	incw	x
2859  0056               L21:
2860  0056 02            	rlwa	x,a
2861  0057 f6            	ld	a,(x)
2862  0058 1b02          	add	a,(OFST-1,sp)
2863  005a 6b02          	ld	(OFST-1,sp),a
2864  005c 2402          	jrnc	L41
2865  005e 0c01          	inc	(OFST-2,sp)
2866  0060               L41:
2867                     ; 37 	for(i = nStartNo; i < nEndNo; i ++)
2869  0060 0c03          	inc	(OFST+0,sp)
2870  0062               L1102:
2873  0062 7b03          	ld	a,(OFST+0,sp)
2874  0064 1109          	cp	a,(OFST+6,sp)
2875  0066 25e4          	jrult	L5002
2876                     ; 41 	return nTotalSum;
2878  0068 1e01          	ldw	x,(OFST-2,sp)
2881  006a 5b05          	addw	sp,#5
2882  006c 81            	ret
2953                     ; 49 uint f_XorSum(uchar *nBuff,uchar nStartNo,uchar nEndNo)
2953                     ; 50 {
2954                     	switch	.text
2955  006d               _f_XorSum:
2957  006d 89            	pushw	x
2958  006e 5203          	subw	sp,#3
2959       00000003      OFST:	set	3
2962                     ; 53 	nTotalSum = nStartNo;
2964  0070 7b08          	ld	a,(OFST+5,sp)
2965  0072 5f            	clrw	x
2966  0073 97            	ld	xl,a
2967  0074 1f01          	ldw	(OFST-2,sp),x
2968                     ; 54 	for(i = (nStartNo+1); i < nEndNo; i ++)
2970  0076 7b08          	ld	a,(OFST+5,sp)
2971  0078 4c            	inc	a
2972  0079 6b03          	ld	(OFST+0,sp),a
2974  007b 2019          	jra	L7502
2975  007d               L3502:
2976                     ; 56 		nTotalSum ^= nBuff[i];
2978  007d 7b04          	ld	a,(OFST+1,sp)
2979  007f 97            	ld	xl,a
2980  0080 7b05          	ld	a,(OFST+2,sp)
2981  0082 1b03          	add	a,(OFST+0,sp)
2982  0084 2401          	jrnc	L02
2983  0086 5c            	incw	x
2984  0087               L02:
2985  0087 02            	rlwa	x,a
2986  0088 f6            	ld	a,(x)
2987  0089 5f            	clrw	x
2988  008a 97            	ld	xl,a
2989  008b 01            	rrwa	x,a
2990  008c 1802          	xor	a,(OFST-1,sp)
2991  008e 01            	rrwa	x,a
2992  008f 1801          	xor	a,(OFST-2,sp)
2993  0091 01            	rrwa	x,a
2994  0092 1f01          	ldw	(OFST-2,sp),x
2995                     ; 54 	for(i = (nStartNo+1); i < nEndNo; i ++)
2997  0094 0c03          	inc	(OFST+0,sp)
2998  0096               L7502:
3001  0096 7b03          	ld	a,(OFST+0,sp)
3002  0098 1109          	cp	a,(OFST+6,sp)
3003  009a 25e1          	jrult	L3502
3004                     ; 58 	return nTotalSum;
3006  009c 1e01          	ldw	x,(OFST-2,sp)
3009  009e 5b05          	addw	sp,#5
3010  00a0 81            	ret
3116                     ; 66 void f_GetSWState(uchar bIOstate, LEVEL_SWITCH_INF *pSwInf, uint needOnTm, uint needOffTm)
3116                     ; 67 {
3117                     	switch	.text
3118  00a1               _f_GetSWState:
3120  00a1 88            	push	a
3121       00000000      OFST:	set	0
3124                     ; 68 	if(bIOstate)
3126  00a2 4d            	tnz	a
3127  00a3 2720          	jreq	L7312
3128                     ; 70 		AddIntData(&(pSwInf->nKeepOnTm));
3130  00a5 1e04          	ldw	x,(OFST+4,sp)
3131  00a7 5c            	incw	x
3132  00a8 cd0195        	call	_AddIntData
3134                     ; 71 		pSwInf->nKeepOffTm = 0;
3136  00ab 1e04          	ldw	x,(OFST+4,sp)
3137  00ad 905f          	clrw	y
3138  00af ef03          	ldw	(3,x),y
3139                     ; 72 		if(pSwInf->nKeepOnTm >= needOnTm)
3141  00b1 1e04          	ldw	x,(OFST+4,sp)
3142  00b3 9093          	ldw	y,x
3143  00b5 51            	exgw	x,y
3144  00b6 ee01          	ldw	x,(1,x)
3145  00b8 1306          	cpw	x,(OFST+6,sp)
3146  00ba 51            	exgw	x,y
3147  00bb 2528          	jrult	L3412
3148                     ; 74 			pSwInf->bSwitchState = SW_ON;
3150  00bd 1e04          	ldw	x,(OFST+4,sp)
3151  00bf f6            	ld	a,(x)
3152  00c0 aa01          	or	a,#1
3153  00c2 f7            	ld	(x),a
3154  00c3 2020          	jra	L3412
3155  00c5               L7312:
3156                     ; 79 		AddIntData(&(pSwInf->nKeepOffTm));
3158  00c5 1e04          	ldw	x,(OFST+4,sp)
3159  00c7 1c0003        	addw	x,#3
3160  00ca cd0195        	call	_AddIntData
3162                     ; 80 		pSwInf->nKeepOnTm = 0;
3164  00cd 1e04          	ldw	x,(OFST+4,sp)
3165  00cf 905f          	clrw	y
3166  00d1 ef01          	ldw	(1,x),y
3167                     ; 81 		if(pSwInf->nKeepOffTm >= needOffTm)
3169  00d3 1e04          	ldw	x,(OFST+4,sp)
3170  00d5 9093          	ldw	y,x
3171  00d7 51            	exgw	x,y
3172  00d8 ee03          	ldw	x,(3,x)
3173  00da 1308          	cpw	x,(OFST+8,sp)
3174  00dc 51            	exgw	x,y
3175  00dd 2506          	jrult	L3412
3176                     ; 83 			pSwInf->bSwitchState = SW_OFF;
3178  00df 1e04          	ldw	x,(OFST+4,sp)
3179  00e1 f6            	ld	a,(x)
3180  00e2 a4fe          	and	a,#254
3181  00e4 f7            	ld	(x),a
3182  00e5               L3412:
3183                     ; 86 }
3186  00e5 84            	pop	a
3187  00e6 81            	ret
3252                     ; 93 void f_ClearRunTimeH(hour_def *nTempHourDef)
3252                     ; 94 {
3253                     	switch	.text
3254  00e7               _f_ClearRunTimeH:
3258                     ; 95 	nTempHourDef -> hour = 0;
3260  00e7 905f          	clrw	y
3261  00e9 ef02          	ldw	(2,x),y
3262                     ; 96 	nTempHourDef -> minute = 0;
3264  00eb 6f01          	clr	(1,x)
3265                     ; 97 	nTempHourDef -> second = 0;
3267  00ed 7f            	clr	(x)
3268                     ; 98 }
3271  00ee 81            	ret
3329                     ; 105 void f_ClearRunTimeM(minute_def *nTempMinDef)
3329                     ; 106 {
3330                     	switch	.text
3331  00ef               _f_ClearRunTimeM:
3335                     ; 107 	nTempMinDef -> minute = 0;
3337  00ef 905f          	clrw	y
3338  00f1 ff            	ldw	(x),y
3339                     ; 108 	nTempMinDef -> second = 0;
3341  00f2 6f02          	clr	(2,x)
3342                     ; 109 }
3345  00f4 81            	ret
3383                     .const:	section	.text
3384  0000               L23:
3385  0000 0000fffa      	dc.l	65530
3386                     ; 116 void f_AddRunTimerM(minute_def *nTempMinDef)
3386                     ; 117 {
3387                     	switch	.text
3388  00f5               _f_AddRunTimerM:
3390  00f5 89            	pushw	x
3391       00000000      OFST:	set	0
3394                     ; 118 	if(nReducedTime)
3396  00f6 725d0000      	tnz	_nReducedTime
3397  00fa 2708          	jreq	L1522
3398                     ; 119 		nTempMinDef -> second += 10;
3400  00fc e602          	ld	a,(2,x)
3401  00fe ab0a          	add	a,#10
3402  0100 e702          	ld	(2,x),a
3404  0102 2004          	jra	L3522
3405  0104               L1522:
3406                     ; 121 		nTempMinDef -> second ++;
3408  0104 1e01          	ldw	x,(OFST+1,sp)
3409  0106 6c02          	inc	(2,x)
3410  0108               L3522:
3411                     ; 122 	if((nTempMinDef -> second >= 60))
3413  0108 1e01          	ldw	x,(OFST+1,sp)
3414  010a e602          	ld	a,(2,x)
3415  010c a13c          	cp	a,#60
3416  010e 2524          	jrult	L5522
3417                     ; 124 		nTempMinDef -> second = 0;
3419  0110 1e01          	ldw	x,(OFST+1,sp)
3420  0112 6f02          	clr	(2,x)
3421                     ; 125 		nTempMinDef -> minute ++;
3423  0114 1e01          	ldw	x,(OFST+1,sp)
3424  0116 9093          	ldw	y,x
3425  0118 fe            	ldw	x,(x)
3426  0119 1c0001        	addw	x,#1
3427  011c 90ff          	ldw	(y),x
3428                     ; 126 		if(nTempMinDef -> minute >= 65530)
3430  011e 9c            	rvf
3431  011f 1e01          	ldw	x,(OFST+1,sp)
3432  0121 fe            	ldw	x,(x)
3433  0122 cd0000        	call	c_uitolx
3435  0125 ae0000        	ldw	x,#L23
3436  0128 cd0000        	call	c_lcmp
3438  012b 2f07          	jrslt	L5522
3439                     ; 127 			nTempMinDef -> minute = 65530;
3441  012d 1e01          	ldw	x,(OFST+1,sp)
3442  012f 90aefffa      	ldw	y,#65530
3443  0133 ff            	ldw	(x),y
3444  0134               L5522:
3445                     ; 129 }
3448  0134 85            	popw	x
3449  0135 81            	ret
3487                     	switch	.const
3488  0004               L63:
3489  0004 0000fffb      	dc.l	65531
3490                     ; 135 void f_AddRunTimerH(hour_def *nTempHourDef)
3490                     ; 136 {
3491                     	switch	.text
3492  0136               _f_AddRunTimerH:
3494  0136 89            	pushw	x
3495       00000000      OFST:	set	0
3498                     ; 137 	if(nReducedTime)
3500  0137 725d0000      	tnz	_nReducedTime
3501  013b 2706          	jreq	L1032
3502                     ; 138 		nTempHourDef->second += 10;
3504  013d f6            	ld	a,(x)
3505  013e ab0a          	add	a,#10
3506  0140 f7            	ld	(x),a
3508  0141 2003          	jra	L3032
3509  0143               L1032:
3510                     ; 140 		nTempHourDef->second ++;
3512  0143 1e01          	ldw	x,(OFST+1,sp)
3513  0145 7c            	inc	(x)
3514  0146               L3032:
3515                     ; 141 	if(nTempHourDef->second >= 60)
3517  0146 1e01          	ldw	x,(OFST+1,sp)
3518  0148 f6            	ld	a,(x)
3519  0149 a13c          	cp	a,#60
3520  014b 2537          	jrult	L5032
3521                     ; 143 		nTempHourDef->second = 0;
3523  014d 1e01          	ldw	x,(OFST+1,sp)
3524  014f 7f            	clr	(x)
3525                     ; 144 		nTempHourDef->minute ++;
3527  0150 1e01          	ldw	x,(OFST+1,sp)
3528  0152 6c01          	inc	(1,x)
3529                     ; 145 		if(nTempHourDef->minute >= 60)
3531  0154 1e01          	ldw	x,(OFST+1,sp)
3532  0156 e601          	ld	a,(1,x)
3533  0158 a13c          	cp	a,#60
3534  015a 2528          	jrult	L5032
3535                     ; 147 			nTempHourDef->minute = 0;
3537  015c 1e01          	ldw	x,(OFST+1,sp)
3538  015e 6f01          	clr	(1,x)
3539                     ; 148 			nTempHourDef->hour++;
3541  0160 1e01          	ldw	x,(OFST+1,sp)
3542  0162 9093          	ldw	y,x
3543  0164 ee02          	ldw	x,(2,x)
3544  0166 1c0001        	addw	x,#1
3545  0169 90ef02        	ldw	(2,y),x
3546                     ; 149 			if(nTempHourDef->hour > 65530)
3548  016c 9c            	rvf
3549  016d 1e01          	ldw	x,(OFST+1,sp)
3550  016f ee02          	ldw	x,(2,x)
3551  0171 cd0000        	call	c_uitolx
3553  0174 ae0004        	ldw	x,#L63
3554  0177 cd0000        	call	c_lcmp
3556  017a 2f08          	jrslt	L5032
3557                     ; 151 				nTempHourDef->hour = 65530;
3559  017c 1e01          	ldw	x,(OFST+1,sp)
3560  017e 90aefffa      	ldw	y,#65530
3561  0182 ef02          	ldw	(2,x),y
3562  0184               L5032:
3563                     ; 155 }
3566  0184 85            	popw	x
3567  0185 81            	ret
3602                     ; 162 void AddCharData(uchar *nTempCharBuff)
3602                     ; 163 {
3603                     	switch	.text
3604  0186               _AddCharData:
3608                     ; 164 	(*nTempCharBuff) ++;
3610  0186 7c            	inc	(x)
3611                     ; 165 	if((*nTempCharBuff) > 250)
3613  0187 f6            	ld	a,(x)
3614  0188 a1fb          	cp	a,#251
3615  018a 2503          	jrult	L1332
3616                     ; 166 		(*nTempCharBuff) = 250;
3618  018c a6fa          	ld	a,#250
3619  018e f7            	ld	(x),a
3620  018f               L1332:
3621                     ; 167 }
3624  018f 81            	ret
3659                     ; 173 void DecCharData(uchar *nTempIntBuff)
3659                     ; 174 {
3660                     	switch	.text
3661  0190               _DecCharData:
3665                     ; 175 	if(*nTempIntBuff)
3667  0190 7d            	tnz	(x)
3668  0191 2701          	jreq	L1532
3669                     ; 176 		(*nTempIntBuff) --;
3671  0193 7a            	dec	(x)
3672  0194               L1532:
3673                     ; 177 }
3676  0194 81            	ret
3711                     ; 183 void AddIntData(uint *nTempIntBuff)
3711                     ; 184 {
3712                     	switch	.text
3713  0195               _AddIntData:
3715  0195 89            	pushw	x
3716       00000000      OFST:	set	0
3719                     ; 185 	(*nTempIntBuff) ++;
3721  0196 9093          	ldw	y,x
3722  0198 fe            	ldw	x,(x)
3723  0199 1c0001        	addw	x,#1
3724  019c 90ff          	ldw	(y),x
3725                     ; 186 	if((*nTempIntBuff) > 65530)
3727  019e 9c            	rvf
3728  019f 1e01          	ldw	x,(OFST+1,sp)
3729  01a1 fe            	ldw	x,(x)
3730  01a2 cd0000        	call	c_uitolx
3732  01a5 ae0004        	ldw	x,#L63
3733  01a8 cd0000        	call	c_lcmp
3735  01ab 2f07          	jrslt	L1732
3736                     ; 187 		(*nTempIntBuff) = 65530;
3738  01ad 1e01          	ldw	x,(OFST+1,sp)
3739  01af 90aefffa      	ldw	y,#65530
3740  01b3 ff            	ldw	(x),y
3741  01b4               L1732:
3742                     ; 188 }
3745  01b4 85            	popw	x
3746  01b5 81            	ret
3781                     ; 194 void DecIntData(uint *nTempIntBuff)
3781                     ; 195 {
3782                     	switch	.text
3783  01b6               _DecIntData:
3787                     ; 196 	if(*nTempIntBuff)
3789  01b6 e601          	ld	a,(1,x)
3790  01b8 fa            	or	a,(x)
3791  01b9 2708          	jreq	L1142
3792                     ; 197 		(*nTempIntBuff) --;
3794  01bb 9093          	ldw	y,x
3795  01bd fe            	ldw	x,(x)
3796  01be 1d0001        	subw	x,#1
3797  01c1 90ff          	ldw	(y),x
3798  01c3               L1142:
3799                     ; 198 }
3802  01c3 81            	ret
3864                     ; 204 uchar AddTotalNum(uchar *nBuff,uchar nEndNo)
3864                     ; 205 {
3865                     	switch	.text
3866  01c4               _AddTotalNum:
3868  01c4 89            	pushw	x
3869  01c5 89            	pushw	x
3870       00000002      OFST:	set	2
3873                     ; 207 	nTotalSum = 0;
3875  01c6 0f01          	clr	(OFST-1,sp)
3876                     ; 208 	for(i = 0; i < nEndNo; i ++)
3878  01c8 0f02          	clr	(OFST+0,sp)
3880  01ca 2012          	jra	L1542
3881  01cc               L5442:
3882                     ; 209 		nTotalSum += nBuff[i];
3884  01cc 7b03          	ld	a,(OFST+1,sp)
3885  01ce 97            	ld	xl,a
3886  01cf 7b04          	ld	a,(OFST+2,sp)
3887  01d1 1b02          	add	a,(OFST+0,sp)
3888  01d3 2401          	jrnc	L25
3889  01d5 5c            	incw	x
3890  01d6               L25:
3891  01d6 02            	rlwa	x,a
3892  01d7 7b01          	ld	a,(OFST-1,sp)
3893  01d9 fb            	add	a,(x)
3894  01da 6b01          	ld	(OFST-1,sp),a
3895                     ; 208 	for(i = 0; i < nEndNo; i ++)
3897  01dc 0c02          	inc	(OFST+0,sp)
3898  01de               L1542:
3901  01de 7b02          	ld	a,(OFST+0,sp)
3902  01e0 1107          	cp	a,(OFST+5,sp)
3903  01e2 25e8          	jrult	L5442
3904                     ; 210 	return nTotalSum;
3906  01e4 7b01          	ld	a,(OFST-1,sp)
3909  01e6 5b04          	addw	sp,#4
3910  01e8 81            	ret
3923                     	xdef	_AddTotalNum
3924                     	xdef	_DecIntData
3925                     	xdef	_AddIntData
3926                     	xdef	_DecCharData
3927                     	xdef	_AddCharData
3928                     	xdef	_f_AddRunTimerH
3929                     	xdef	_f_AddRunTimerM
3930                     	xdef	_f_ClearRunTimeM
3931                     	xdef	_f_ClearRunTimeH
3932                     	xdef	_f_GetSWState
3933                     	xdef	_f_XorSum
3934                     	xdef	_f_CheckSum
3935                     	xdef	_f_Memcpy
3936                     	switch	.bss
3937  0000               _nReducedTime:
3938  0000 00            	ds.b	1
3939                     	xdef	_nReducedTime
3959                     	xref	c_lcmp
3960                     	xref	c_uitolx
3961                     	end
