   1                     ; C Compiler for STM8 (COSMIC Software)
   2                     ; Parser V4.8.32 - 23 Mar 2010
   3                     ; Generator V4.3.4 - 23 Mar 2010
2729                     ; 58 uchar sSpiWrite(uchar data)
2729                     ; 59 {
2731                     	switch	.text
2732  0000               _sSpiWrite:
2734  0000 88            	push	a
2735  0001 89            	pushw	x
2736       00000002      OFST:	set	2
2739                     ; 61 	uchar rc = 0;
2741  0002 0f02          	clr	(OFST+0,sp)
2742                     ; 62 	for(i = 0; i < 8; i++)
2744  0004 0f01          	clr	(OFST-1,sp)
2745  0006               L7471:
2746                     ; 64 		CC_UCLK_LOW;	
2748  0006 7219500f      	bres	_PD_ODR,#4
2749                     ; 65 		if (data&0x80)
2751  000a 7b03          	ld	a,(OFST+1,sp)
2752  000c a580          	bcp	a,#128
2753  000e 2706          	jreq	L5571
2754                     ; 67 			CC_SIMO_HIGH;
2756  0010 72165000      	bset	_PA_ODR,#3
2758  0014 2004          	jra	L7571
2759  0016               L5571:
2760                     ; 71 			CC_SIMO_LOW;
2762  0016 72175000      	bres	_PA_ODR,#3
2763  001a               L7571:
2764                     ; 73 		data <<= 1;
2766  001a 0803          	sll	(OFST+1,sp)
2767                     ; 74 		CC_UCLK_HIGH;	
2769  001c 7218500f      	bset	_PD_ODR,#4
2770                     ; 75 		rc <<= 1;
2772  0020 0802          	sll	(OFST+0,sp)
2773                     ; 76 		if (CC_SOMI_IN)
2775  0022 c65006        	ld	a,_PB_IDR
2776  0025 a510          	bcp	a,#16
2777  0027 2706          	jreq	L1671
2778                     ; 78 			rc |= 1;
2780  0029 7b02          	ld	a,(OFST+0,sp)
2781  002b aa01          	or	a,#1
2782  002d 6b02          	ld	(OFST+0,sp),a
2783  002f               L1671:
2784                     ; 62 	for(i = 0; i < 8; i++)
2786  002f 0c01          	inc	(OFST-1,sp)
2789  0031 7b01          	ld	a,(OFST-1,sp)
2790  0033 a108          	cp	a,#8
2791  0035 25cf          	jrult	L7471
2792                     ; 81 	CC_UCLK_LOW;																							//clock low
2794  0037 7219500f      	bres	_PD_ODR,#4
2795                     ; 82 	return rc;
2797  003b 7b02          	ld	a,(OFST+0,sp)
2800  003d 5b03          	addw	sp,#3
2801  003f 81            	ret
2846                     ; 90 uchar sSpiRead(void)
2846                     ; 91 {
2847                     	switch	.text
2848  0040               _sSpiRead:
2850  0040 89            	pushw	x
2851       00000002      OFST:	set	2
2854                     ; 93 	uchar data = 0;
2856  0041 0f02          	clr	(OFST+0,sp)
2857                     ; 94 	for(i = 0; i < 8; i++)
2859  0043 0f01          	clr	(OFST-1,sp)
2860  0045               L5002:
2861                     ; 96 		CC_UCLK_HIGH;	
2863  0045 7218500f      	bset	_PD_ODR,#4
2864                     ; 97 		data <<= 1;
2866  0049 0802          	sll	(OFST+0,sp)
2867                     ; 98 		if (CC_SOMI_IN)
2869  004b c65006        	ld	a,_PB_IDR
2870  004e a510          	bcp	a,#16
2871  0050 2706          	jreq	L3102
2872                     ; 100 			data |= 1;
2874  0052 7b02          	ld	a,(OFST+0,sp)
2875  0054 aa01          	or	a,#1
2876  0056 6b02          	ld	(OFST+0,sp),a
2877  0058               L3102:
2878                     ; 102 		CC_UCLK_LOW;	
2880  0058 7219500f      	bres	_PD_ODR,#4
2881                     ; 94 	for(i = 0; i < 8; i++)
2883  005c 0c01          	inc	(OFST-1,sp)
2886  005e 7b01          	ld	a,(OFST-1,sp)
2887  0060 a108          	cp	a,#8
2888  0062 25e1          	jrult	L5002
2889                     ; 104 	return data;
2891  0064 7b02          	ld	a,(OFST+0,sp)
2894  0066 85            	popw	x
2895  0067 81            	ret
2951                     ; 112 void sSpiWriteByte(uchar addr,uchar value)
2951                     ; 113 {
2952                     	switch	.text
2953  0068               _sSpiWriteByte:
2955  0068 89            	pushw	x
2956  0069 89            	pushw	x
2957       00000002      OFST:	set	2
2960                     ; 115 	CC_CS_LOW;
2962  006a 72135000      	bres	_PA_ODR,#1
2963                     ; 116 	i = 0;
2965  006e 5f            	clrw	x
2966  006f 1f01          	ldw	(OFST-1,sp),x
2968  0071 2028          	jra	L7402
2969  0073               L3402:
2970                     ; 120 		f_Delay(20);
2972  0073 ae0014        	ldw	x,#20
2973  0076 cd0000        	call	_f_Delay
2975                     ; 121 		if (i ++ > 1000)
2977  0079 1e01          	ldw	x,(OFST-1,sp)
2978  007b 1c0001        	addw	x,#1
2979  007e 1f01          	ldw	(OFST-1,sp),x
2980  0080 1d0001        	subw	x,#1
2981  0083 a303e9        	cpw	x,#1001
2982  0086 2513          	jrult	L7402
2983                     ; 122 			break;
2984  0088               L1502:
2985                     ; 124 	sSpiWrite(addr&0x7F);																		//wait for tx to finish
2987  0088 7b03          	ld	a,(OFST+1,sp)
2988  008a a47f          	and	a,#127
2989  008c cd0000        	call	_sSpiWrite
2991                     ; 125 	sSpiWrite(value);
2993  008f 7b04          	ld	a,(OFST+2,sp)
2994  0091 cd0000        	call	_sSpiWrite
2996                     ; 126 	CC_CS_HIGH;
2998  0094 72125000      	bset	_PA_ODR,#1
2999                     ; 127 }
3002  0098 5b04          	addw	sp,#4
3003  009a 81            	ret
3004  009b               L7402:
3005                     ; 117 	while(CC_SOMI_IN)
3007  009b c65006        	ld	a,_PB_IDR
3008  009e a510          	bcp	a,#16
3009  00a0 26d1          	jrne	L3402
3010  00a2 20e4          	jra	L1502
3076                     ; 134 void sSpiWriteMore(uchar addr, uchar *buffer, uchar count)
3076                     ; 135 {
3077                     	switch	.text
3078  00a4               _sSpiWriteMore:
3080  00a4 88            	push	a
3081  00a5 89            	pushw	x
3082       00000002      OFST:	set	2
3085                     ; 137 	CC_CS_LOW;
3087  00a6 72135000      	bres	_PA_ODR,#1
3088                     ; 138 	i = 0;
3090  00aa 5f            	clrw	x
3091  00ab 1f01          	ldw	(OFST-1,sp),x
3093  00ad 2021          	jra	L3112
3094  00af               L7012:
3095                     ; 142 		f_Delay(20);
3097  00af ae0014        	ldw	x,#20
3098  00b2 cd0000        	call	_f_Delay
3100                     ; 143 		if (i ++ > 1000)
3102  00b5 1e01          	ldw	x,(OFST-1,sp)
3103  00b7 1c0001        	addw	x,#1
3104  00ba 1f01          	ldw	(OFST-1,sp),x
3105  00bc 1d0001        	subw	x,#1
3106  00bf a303e9        	cpw	x,#1001
3107  00c2 250c          	jrult	L3112
3108                     ; 144 			break;
3109  00c4               L5112:
3110                     ; 146 	sSpiWrite(addr|TI_CCxxx0_WRITE_BURST);
3112  00c4 7b03          	ld	a,(OFST+1,sp)
3113  00c6 aa40          	or	a,#64
3114  00c8 cd0000        	call	_sSpiWrite
3116                     ; 147 	for(i = 0; i < count; i++)
3118  00cb 5f            	clrw	x
3119  00cc 1f01          	ldw	(OFST-1,sp),x
3121  00ce 2019          	jra	L5212
3122  00d0               L3112:
3123                     ; 139 	while(CC_SOMI_IN)
3125  00d0 c65006        	ld	a,_PB_IDR
3126  00d3 a510          	bcp	a,#16
3127  00d5 26d8          	jrne	L7012
3128  00d7 20eb          	jra	L5112
3129  00d9               L1212:
3130                     ; 149 		sSpiWrite(buffer[i]);
3132  00d9 1e06          	ldw	x,(OFST+4,sp)
3133  00db 72fb01        	addw	x,(OFST-1,sp)
3134  00de f6            	ld	a,(x)
3135  00df cd0000        	call	_sSpiWrite
3137                     ; 147 	for(i = 0; i < count; i++)
3139  00e2 1e01          	ldw	x,(OFST-1,sp)
3140  00e4 1c0001        	addw	x,#1
3141  00e7 1f01          	ldw	(OFST-1,sp),x
3142  00e9               L5212:
3145  00e9 7b08          	ld	a,(OFST+6,sp)
3146  00eb 5f            	clrw	x
3147  00ec 97            	ld	xl,a
3148  00ed bf00          	ldw	c_x,x
3149  00ef 1e01          	ldw	x,(OFST-1,sp)
3150  00f1 b300          	cpw	x,c_x
3151  00f3 25e4          	jrult	L1212
3152                     ; 151 	CC_CS_HIGH;
3154  00f5 72125000      	bset	_PA_ODR,#1
3155                     ; 152 }
3158  00f9 5b03          	addw	sp,#3
3159  00fb 81            	ret
3216                     ; 159 uchar sSpiReadByte(uchar addr)
3216                     ; 160 {
3217                     	switch	.text
3218  00fc               _sSpiReadByte:
3220  00fc 88            	push	a
3221  00fd 5203          	subw	sp,#3
3222       00000003      OFST:	set	3
3225                     ; 163 	CC_CS_LOW;
3227  00ff 72135000      	bres	_PA_ODR,#1
3228                     ; 164 	i = 0;
3230  0103 5f            	clrw	x
3231  0104 1f02          	ldw	(OFST-1,sp),x
3233  0106 202a          	jra	L3612
3234  0108               L7512:
3235                     ; 168 		f_Delay(20);
3237  0108 ae0014        	ldw	x,#20
3238  010b cd0000        	call	_f_Delay
3240                     ; 169 		if (i ++ > 1000)
3242  010e 1e02          	ldw	x,(OFST-1,sp)
3243  0110 1c0001        	addw	x,#1
3244  0113 1f02          	ldw	(OFST-1,sp),x
3245  0115 1d0001        	subw	x,#1
3246  0118 a303e9        	cpw	x,#1001
3247  011b 2515          	jrult	L3612
3248                     ; 170 			break;
3249  011d               L5612:
3250                     ; 172 	sSpiWrite(addr|TI_CCxxx0_READ_SINGLE);							
3252  011d 7b04          	ld	a,(OFST+1,sp)
3253  011f aa80          	or	a,#128
3254  0121 cd0000        	call	_sSpiWrite
3256                     ; 173 	i_ReturnValue = sSpiRead();
3258  0124 cd0040        	call	_sSpiRead
3260  0127 6b01          	ld	(OFST-2,sp),a
3261                     ; 174 	CC_CS_HIGH;
3263  0129 72125000      	bset	_PA_ODR,#1
3264                     ; 175 	return i_ReturnValue;
3266  012d 7b01          	ld	a,(OFST-2,sp)
3269  012f 5b04          	addw	sp,#4
3270  0131 81            	ret
3271  0132               L3612:
3272                     ; 165 	while(CC_SOMI_IN)
3274  0132 c65006        	ld	a,_PB_IDR
3275  0135 a510          	bcp	a,#16
3276  0137 26cf          	jrne	L7512
3277  0139 20e2          	jra	L5612
3344                     ; 183 void sSpiReadMore(uchar addr, uchar *buffer, uchar count)
3344                     ; 184 {
3345                     	switch	.text
3346  013b               _sSpiReadMore:
3348  013b 88            	push	a
3349  013c 88            	push	a
3350       00000001      OFST:	set	1
3353                     ; 186 	CC_CS_LOW;
3355  013d 72135000      	bres	_PA_ODR,#1
3356                     ; 187 	i = 0;
3358  0141 0f01          	clr	(OFST+0,sp)
3360  0143 2008          	jra	L7222
3361  0145               L3222:
3362                     ; 191 		f_Delay(20);
3364  0145 ae0014        	ldw	x,#20
3365  0148 cd0000        	call	_f_Delay
3367                     ; 192 		if (i ++ > 1000)
3369  014b 0c01          	inc	(OFST+0,sp)
3371  014d               L7222:
3372                     ; 188 	while(CC_SOMI_IN)
3374  014d c65006        	ld	a,_PB_IDR
3375  0150 a510          	bcp	a,#16
3376  0152 26f1          	jrne	L3222
3377                     ; 195 	sSpiWrite(addr|TI_CCxxx0_READ_BURST);
3379  0154 7b02          	ld	a,(OFST+1,sp)
3380  0156 aac0          	or	a,#192
3381  0158 cd0000        	call	_sSpiWrite
3383                     ; 196 	for(i = 0; i < count; i++)
3385  015b 0f01          	clr	(OFST+0,sp)
3387  015d 2013          	jra	L1422
3388  015f               L5322:
3389                     ; 198 		buffer[i] = sSpiRead();
3391  015f 7b05          	ld	a,(OFST+4,sp)
3392  0161 97            	ld	xl,a
3393  0162 7b06          	ld	a,(OFST+5,sp)
3394  0164 1b01          	add	a,(OFST+0,sp)
3395  0166 2401          	jrnc	L02
3396  0168 5c            	incw	x
3397  0169               L02:
3398  0169 02            	rlwa	x,a
3399  016a 89            	pushw	x
3400  016b cd0040        	call	_sSpiRead
3402  016e 85            	popw	x
3403  016f f7            	ld	(x),a
3404                     ; 196 	for(i = 0; i < count; i++)
3406  0170 0c01          	inc	(OFST+0,sp)
3407  0172               L1422:
3410  0172 7b01          	ld	a,(OFST+0,sp)
3411  0174 1107          	cp	a,(OFST+6,sp)
3412  0176 25e7          	jrult	L5322
3413                     ; 200 	CC_CS_HIGH;
3415  0178 72125000      	bset	_PA_ODR,#1
3416                     ; 201 }
3419  017c 85            	popw	x
3420  017d 81            	ret
3477                     ; 208 uchar sSpiReadStatus(uchar addr)
3477                     ; 209 {
3478                     	switch	.text
3479  017e               _sSpiReadStatus:
3481  017e 88            	push	a
3482  017f 5203          	subw	sp,#3
3483       00000003      OFST:	set	3
3486                     ; 212 	CC_CS_LOW;
3488  0181 72135000      	bres	_PA_ODR,#1
3489                     ; 213 	i = 0;
3491  0185 5f            	clrw	x
3492  0186 1f02          	ldw	(OFST-1,sp),x
3494  0188 202a          	jra	L7722
3495  018a               L3722:
3496                     ; 217 		f_Delay(20);
3498  018a ae0014        	ldw	x,#20
3499  018d cd0000        	call	_f_Delay
3501                     ; 218 		if (i ++ > 1000)
3503  0190 1e02          	ldw	x,(OFST-1,sp)
3504  0192 1c0001        	addw	x,#1
3505  0195 1f02          	ldw	(OFST-1,sp),x
3506  0197 1d0001        	subw	x,#1
3507  019a a303e9        	cpw	x,#1001
3508  019d 2515          	jrult	L7722
3509                     ; 219 			break;
3510  019f               L1032:
3511                     ; 221 	sSpiWrite(addr|TI_CCxxx0_READ_BURST);
3513  019f 7b04          	ld	a,(OFST+1,sp)
3514  01a1 aac0          	or	a,#192
3515  01a3 cd0000        	call	_sSpiWrite
3517                     ; 222 	i_ReturnValue = sSpiRead();
3519  01a6 cd0040        	call	_sSpiRead
3521  01a9 6b01          	ld	(OFST-2,sp),a
3522                     ; 223 	CC_CS_HIGH;
3524  01ab 72125000      	bset	_PA_ODR,#1
3525                     ; 224 	return i_ReturnValue;
3527  01af 7b01          	ld	a,(OFST-2,sp)
3530  01b1 5b04          	addw	sp,#4
3531  01b3 81            	ret
3532  01b4               L7722:
3533                     ; 214 	while(CC_SOMI_IN)
3535  01b4 c65006        	ld	a,_PB_IDR
3536  01b7 a510          	bcp	a,#16
3537  01b9 26cf          	jrne	L3722
3538  01bb 20e2          	jra	L1032
3585                     ; 232 void sSpiWriteStatus(uchar strobe)
3585                     ; 233 {
3586                     	switch	.text
3587  01bd               _sSpiWriteStatus:
3589  01bd 88            	push	a
3590  01be 89            	pushw	x
3591       00000002      OFST:	set	2
3594                     ; 235 	CC_CS_LOW;
3596  01bf 72135000      	bres	_PA_ODR,#1
3597                     ; 236 	i = 0;
3599  01c3 5f            	clrw	x
3600  01c4 1f01          	ldw	(OFST-1,sp),x
3602  01c6 2021          	jra	L3332
3603  01c8               L7232:
3604                     ; 240 		f_Delay(20);
3606  01c8 ae0014        	ldw	x,#20
3607  01cb cd0000        	call	_f_Delay
3609                     ; 241 		if (i ++ > 1000)
3611  01ce 1e01          	ldw	x,(OFST-1,sp)
3612  01d0 1c0001        	addw	x,#1
3613  01d3 1f01          	ldw	(OFST-1,sp),x
3614  01d5 1d0001        	subw	x,#1
3615  01d8 a303e9        	cpw	x,#1001
3616  01db 250c          	jrult	L3332
3617                     ; 242 			break;
3618  01dd               L5332:
3619                     ; 244 	sSpiWrite(strobe);
3621  01dd 7b03          	ld	a,(OFST+1,sp)
3622  01df cd0000        	call	_sSpiWrite
3624                     ; 245 	CC_CS_HIGH;
3626  01e2 72125000      	bset	_PA_ODR,#1
3627                     ; 246 }
3630  01e6 5b03          	addw	sp,#3
3631  01e8 81            	ret
3632  01e9               L3332:
3633                     ; 237 	while(CC_SOMI_IN)
3635  01e9 c65006        	ld	a,_PB_IDR
3636  01ec a510          	bcp	a,#16
3637  01ee 26d8          	jrne	L7232
3638  01f0 20eb          	jra	L5332
3675                     ; 253 uchar CC2500_Settings_250k(unsigned char rf_channel) 
3675                     ; 254 //uchar halRfConfig(const HAL_RF_CONFIG* rfConfig, const uchar* rfPaTable, const uchar rfPaTableLen)
3675                     ; 255 {
3676                     	switch	.text
3677  01f2               _CC2500_Settings_250k:
3679  01f2 88            	push	a
3680       00000000      OFST:	set	0
3683                     ; 257 	sSpiWriteByte(TI_CCxxx0_FSCTRL1, 0x0A);// Frequency synthesizer control.
3685  01f3 ae000a        	ldw	x,#10
3686  01f6 a60b          	ld	a,#11
3687  01f8 95            	ld	xh,a
3688  01f9 cd0068        	call	_sSpiWriteByte
3690                     ; 258 	sSpiWriteByte(TI_CCxxx0_FSCTRL0, 0x00);// Frequency synthesizer control.
3692  01fc 5f            	clrw	x
3693  01fd a60c          	ld	a,#12
3694  01ff 95            	ld	xh,a
3695  0200 cd0068        	call	_sSpiWriteByte
3697                     ; 259 	sSpiWriteByte(TI_CCxxx0_FREQ2, 0x5C);// Frequency control word, high byte.
3699  0203 ae005c        	ldw	x,#92
3700  0206 a60d          	ld	a,#13
3701  0208 95            	ld	xh,a
3702  0209 cd0068        	call	_sSpiWriteByte
3704                     ; 260 	sSpiWriteByte(TI_CCxxx0_FREQ1, 0x58);// Frequency control word, middle byte.
3706  020c ae0058        	ldw	x,#88
3707  020f a60e          	ld	a,#14
3708  0211 95            	ld	xh,a
3709  0212 cd0068        	call	_sSpiWriteByte
3711                     ; 261 	sSpiWriteByte(TI_CCxxx0_FREQ0, 0x9D);// Frequency control word, low byte.		
3713  0215 ae009d        	ldw	x,#157
3714  0218 a60f          	ld	a,#15
3715  021a 95            	ld	xh,a
3716  021b cd0068        	call	_sSpiWriteByte
3718                     ; 262 	sSpiWriteByte(TI_CCxxx0_MDMCFG4, 0x2D);// Modem configuration.
3720  021e ae002d        	ldw	x,#45
3721  0221 a610          	ld	a,#16
3722  0223 95            	ld	xh,a
3723  0224 cd0068        	call	_sSpiWriteByte
3725                     ; 263 	sSpiWriteByte(TI_CCxxx0_MDMCFG3, 0x3B);// Modem configuration. 
3727  0227 ae003b        	ldw	x,#59
3728  022a a611          	ld	a,#17
3729  022c 95            	ld	xh,a
3730  022d cd0068        	call	_sSpiWriteByte
3732                     ; 264 	sSpiWriteByte(TI_CCxxx0_MDMCFG2, 0x73);// Modem configuration.	//2-fsk
3734  0230 ae0073        	ldw	x,#115
3735  0233 a612          	ld	a,#18
3736  0235 95            	ld	xh,a
3737  0236 cd0068        	call	_sSpiWriteByte
3739                     ; 266 	sSpiWriteByte(TI_CCxxx0_MDMCFG1, 0x23);// Modem configuration.  333.33KHz 
3741  0239 ae0023        	ldw	x,#35
3742  023c a613          	ld	a,#19
3743  023e 95            	ld	xh,a
3744  023f cd0068        	call	_sSpiWriteByte
3746                     ; 267 	sSpiWriteByte(TI_CCxxx0_MDMCFG0, 0xa4);// Modem configuration.
3748  0242 ae00a4        	ldw	x,#164
3749  0245 a614          	ld	a,#20
3750  0247 95            	ld	xh,a
3751  0248 cd0068        	call	_sSpiWriteByte
3753                     ; 268 	sSpiWriteByte(TI_CCxxx0_CHANNR, rf_channel);// Channel number.
3755  024b 7b01          	ld	a,(OFST+1,sp)
3756  024d 97            	ld	xl,a
3757  024e a60a          	ld	a,#10
3758  0250 95            	ld	xh,a
3759  0251 cd0068        	call	_sSpiWriteByte
3761                     ; 269 	sSpiWriteByte(TI_CCxxx0_DEVIATN, 0x00);// Modem deviation setting (when FSK modulation is enabled).
3763  0254 5f            	clrw	x
3764  0255 a615          	ld	a,#21
3765  0257 95            	ld	xh,a
3766  0258 cd0068        	call	_sSpiWriteByte
3768                     ; 270 	sSpiWriteByte(TI_CCxxx0_FREND1, 0xB6);// Front end RX configuration.
3770  025b ae00b6        	ldw	x,#182
3771  025e a621          	ld	a,#33
3772  0260 95            	ld	xh,a
3773  0261 cd0068        	call	_sSpiWriteByte
3775                     ; 271 	sSpiWriteByte(TI_CCxxx0_FREND0, 0x10);// Front end TX configuration.
3777  0264 ae0010        	ldw	x,#16
3778  0267 a622          	ld	a,#34
3779  0269 95            	ld	xh,a
3780  026a cd0068        	call	_sSpiWriteByte
3782                     ; 272 	sSpiWriteByte(TI_CCxxx0_MCSM1, 0x30);//
3784  026d ae0030        	ldw	x,#48
3785  0270 a617          	ld	a,#23
3786  0272 95            	ld	xh,a
3787  0273 cd0068        	call	_sSpiWriteByte
3789                     ; 273 	sSpiWriteByte(TI_CCxxx0_MCSM0, 0x08);//0X18 Never (manually calibrate using SCAL strobe)
3791  0276 ae0008        	ldw	x,#8
3792  0279 a618          	ld	a,#24
3793  027b 95            	ld	xh,a
3794  027c cd0068        	call	_sSpiWriteByte
3796                     ; 274 	sSpiWriteByte(TI_CCxxx0_FOCCFG, 0x1D);// Frequency Offset Compensation Configuration.
3798  027f ae001d        	ldw	x,#29
3799  0282 a619          	ld	a,#25
3800  0284 95            	ld	xh,a
3801  0285 cd0068        	call	_sSpiWriteByte
3803                     ; 275 	sSpiWriteByte(TI_CCxxx0_BSCFG, 0x1C);// Bit synchronization Configuration.
3805  0288 ae001c        	ldw	x,#28
3806  028b a61a          	ld	a,#26
3807  028d 95            	ld	xh,a
3808  028e cd0068        	call	_sSpiWriteByte
3810                     ; 276 	sSpiWriteByte(TI_CCxxx0_AGCCTRL2, 0xC7);// AGC control.
3812  0291 ae00c7        	ldw	x,#199
3813  0294 a61b          	ld	a,#27
3814  0296 95            	ld	xh,a
3815  0297 cd0068        	call	_sSpiWriteByte
3817                     ; 277 	sSpiWriteByte(TI_CCxxx0_AGCCTRL1, 0x00);// AGC control.
3819  029a 5f            	clrw	x
3820  029b a61c          	ld	a,#28
3821  029d 95            	ld	xh,a
3822  029e cd0068        	call	_sSpiWriteByte
3824                     ; 278 	sSpiWriteByte(TI_CCxxx0_AGCCTRL0, 0xB0);// AGC control.
3826  02a1 ae00b0        	ldw	x,#176
3827  02a4 a61d          	ld	a,#29
3828  02a6 95            	ld	xh,a
3829  02a7 cd0068        	call	_sSpiWriteByte
3831                     ; 279 	sSpiWriteByte(TI_CCxxx0_FSCAL3, 0xEA);// Frequency synthesizer calibration.
3833  02aa ae00ea        	ldw	x,#234
3834  02ad a623          	ld	a,#35
3835  02af 95            	ld	xh,a
3836  02b0 cd0068        	call	_sSpiWriteByte
3838                     ; 280 	sSpiWriteByte(TI_CCxxx0_FSCAL2, 0x0A);// Frequency synthesizer calibration.
3840  02b3 ae000a        	ldw	x,#10
3841  02b6 a624          	ld	a,#36
3842  02b8 95            	ld	xh,a
3843  02b9 cd0068        	call	_sSpiWriteByte
3845                     ; 281 	sSpiWriteByte(TI_CCxxx0_FSCAL1, 0x00);// Frequency synthesizer calibration.
3847  02bc 5f            	clrw	x
3848  02bd a625          	ld	a,#37
3849  02bf 95            	ld	xh,a
3850  02c0 cd0068        	call	_sSpiWriteByte
3852                     ; 282 	sSpiWriteByte(TI_CCxxx0_FSCAL0, 0x11);// Frequency synthesizer calibration.
3854  02c3 ae0011        	ldw	x,#17
3855  02c6 a626          	ld	a,#38
3856  02c8 95            	ld	xh,a
3857  02c9 cd0068        	call	_sSpiWriteByte
3859                     ; 283 	sSpiWriteByte(TI_CCxxx0_FSTEST, 0x59);// Frequency synthesizer calibration.
3861  02cc ae0059        	ldw	x,#89
3862  02cf a629          	ld	a,#41
3863  02d1 95            	ld	xh,a
3864  02d2 cd0068        	call	_sSpiWriteByte
3866                     ; 284 	sSpiWriteByte(TI_CCxxx0_TEST2, 0x88);// Various test settings.
3868  02d5 ae0088        	ldw	x,#136
3869  02d8 a62c          	ld	a,#44
3870  02da 95            	ld	xh,a
3871  02db cd0068        	call	_sSpiWriteByte
3873                     ; 285 	sSpiWriteByte(TI_CCxxx0_TEST1, 0x31);// Various test settings.
3875  02de ae0031        	ldw	x,#49
3876  02e1 a62d          	ld	a,#45
3877  02e3 95            	ld	xh,a
3878  02e4 cd0068        	call	_sSpiWriteByte
3880                     ; 286 	sSpiWriteByte(TI_CCxxx0_TEST0, 0x0B);// Various test settings.
3882  02e7 ae000b        	ldw	x,#11
3883  02ea a62e          	ld	a,#46
3884  02ec 95            	ld	xh,a
3885  02ed cd0068        	call	_sSpiWriteByte
3887                     ; 287 	sSpiWriteByte(TI_CCxxx0_IOCFG2, 0x06);//Asserts when sync word has been sent / received, and de-asserts at the end of the packet. 
3889  02f0 ae0006        	ldw	x,#6
3890  02f3 4f            	clr	a
3891  02f4 95            	ld	xh,a
3892  02f5 cd0068        	call	_sSpiWriteByte
3894                     ; 288 	sSpiWriteByte(TI_CCxxx0_IOCFG0, 0x06);//In RX, the pin will de-assert when the optional address check fails or the RX FIFO overflows.
3896  02f8 ae0006        	ldw	x,#6
3897  02fb a602          	ld	a,#2
3898  02fd 95            	ld	xh,a
3899  02fe cd0068        	call	_sSpiWriteByte
3901                     ; 289 	sSpiWriteByte(TI_CCxxx0_IOCFG1, 0x06);//In TX the pin will de-assert if the TX FIFO underflows.
3903  0301 ae0006        	ldw	x,#6
3904  0304 a601          	ld	a,#1
3905  0306 95            	ld	xh,a
3906  0307 cd0068        	call	_sSpiWriteByte
3908                     ; 290 	sSpiWriteByte(TI_CCxxx0_PKTCTRL1, 0x04);//Packet Automation Control No address check
3910  030a ae0004        	ldw	x,#4
3911  030d a607          	ld	a,#7
3912  030f 95            	ld	xh,a
3913  0310 cd0068        	call	_sSpiWriteByte
3915                     ; 291 	sSpiWriteByte(TI_CCxxx0_PKTCTRL0, 0x45);//Packet Automation Control
3917  0313 ae0045        	ldw	x,#69
3918  0316 a608          	ld	a,#8
3919  0318 95            	ld	xh,a
3920  0319 cd0068        	call	_sSpiWriteByte
3922                     ; 297 	sSpiWriteByte(TI_CCxxx0_ADDR, 0x00);
3924  031c 5f            	clrw	x
3925  031d a609          	ld	a,#9
3926  031f 95            	ld	xh,a
3927  0320 cd0068        	call	_sSpiWriteByte
3929                     ; 298 	sSpiWriteByte(TI_CCxxx0_PKTLEN, 0xFF); 
3931  0323 ae00ff        	ldw	x,#255
3932  0326 a606          	ld	a,#6
3933  0328 95            	ld	xh,a
3934  0329 cd0068        	call	_sSpiWriteByte
3936                     ; 299 	sSpiWriteByte(TI_CCxxx0_PATABLE, 0xFF);//配置功率  +1dBm	
3938  032c ae00ff        	ldw	x,#255
3939  032f a63e          	ld	a,#62
3940  0331 95            	ld	xh,a
3941  0332 cd0068        	call	_sSpiWriteByte
3943                     ; 301 	if(sSpiReadByte(TI_CCxxx0_MDMCFG3) != 0x3B)return TRUE;
3945  0335 a611          	ld	a,#17
3946  0337 cd00fc        	call	_sSpiReadByte
3948  033a a13b          	cp	a,#59
3949  033c 2705          	jreq	L7532
3952  033e a601          	ld	a,#1
3955  0340 5b01          	addw	sp,#1
3956  0342 81            	ret
3957  0343               L7532:
3958                     ; 302 	return FALSE;     		//如果是初始化成功就返回FALSE
3960  0343 4f            	clr	a
3963  0344 5b01          	addw	sp,#1
3964  0346 81            	ret
3989                     ; 310 void sSpiInitIO(void)
3989                     ; 311 {
3990                     	switch	.text
3991  0347               _sSpiInitIO:
3995                     ; 312 	CC_CS_HIGH;
3997  0347 72125000      	bset	_PA_ODR,#1
3998                     ; 313 	CC_SIMO_LOW;
4000  034b 72175000      	bres	_PA_ODR,#3
4001                     ; 314 	CC_UCLK_LOW;
4003  034f 7219500f      	bres	_PD_ODR,#4
4004                     ; 315 }
4007  0353 81            	ret
4033                     ; 322 void sSetInterrupt(void)
4033                     ; 323 {
4034                     	switch	.text
4035  0354               _sSetInterrupt:
4039                     ; 324 	PB_DDR &= ~0x20;   //设置PE1输入  
4041  0354 721b5007      	bres	_PB_DDR,#5
4042                     ; 325 	PB_CR2 = 0x20; //PE1外部中断
4044  0358 35205009      	mov	_PB_CR2,#32
4045                     ; 326 	EXTI_CR1 |= 0x08;//PB口下降沿中断
4047  035c 721650a0      	bset	_EXTI_CR1,#3
4048                     ; 327 }
4051  0360 81            	ret
4075                     ; 334 void f_SleepCC2500(void)
4075                     ; 335 { 
4076                     	switch	.text
4077  0361               _f_SleepCC2500:
4081                     ; 336 	sSpiWriteStatus(TI_CCxxx0_SIDLE);
4083  0361 a636          	ld	a,#54
4084  0363 cd01bd        	call	_sSpiWriteStatus
4086                     ; 337 	sSpiWriteStatus(TI_CCxxx0_SPWD);
4088  0366 a639          	ld	a,#57
4089  0368 cd01bd        	call	_sSpiWriteStatus
4091                     ; 338 } 
4094  036b 81            	ret
4118                     ; 345 void f_RxCC2500(void)                  
4118                     ; 346 {                    
4119                     	switch	.text
4120  036c               _f_RxCC2500:
4124                     ; 347 	sSpiWriteStatus(TI_CCxxx0_SIDLE);
4126  036c a636          	ld	a,#54
4127  036e cd01bd        	call	_sSpiWriteStatus
4129                     ; 348 	sSpiWriteStatus(TI_CCxxx0_SFRX);
4131  0371 a63a          	ld	a,#58
4132  0373 cd01bd        	call	_sSpiWriteStatus
4134                     ; 349 	sSpiWriteStatus(TI_CCxxx0_SRX);
4136  0376 a634          	ld	a,#52
4137  0378 cd01bd        	call	_sSpiWriteStatus
4139                     ; 350 } 
4142  037b 81            	ret
4198                     ; 357 uchar f_SendPacket(uchar *txBuffer, uchar size)       
4198                     ; 358 {
4199                     	switch	.text
4200  037c               _f_SendPacket:
4202  037c 89            	pushw	x
4203  037d 89            	pushw	x
4204       00000002      OFST:	set	2
4207                     ; 359 	uint j=0;
4209                     ; 360 	sSpiWriteStatus(TI_CCxxx0_SIDLE);
4211  037e a636          	ld	a,#54
4212  0380 cd01bd        	call	_sSpiWriteStatus
4214                     ; 361 	sSpiWriteStatus(TI_CCxxx0_SFTX);
4216  0383 a63b          	ld	a,#59
4217  0385 cd01bd        	call	_sSpiWriteStatus
4219                     ; 362 	sSpiWriteMore(TI_CCxxx0_TXFIFO,txBuffer,size);
4221  0388 7b07          	ld	a,(OFST+5,sp)
4222  038a 88            	push	a
4223  038b 1e04          	ldw	x,(OFST+2,sp)
4224  038d 89            	pushw	x
4225  038e a63f          	ld	a,#63
4226  0390 cd00a4        	call	_sSpiWriteMore
4228  0393 5b03          	addw	sp,#3
4229                     ; 363 	sSpiWriteStatus(TI_CCxxx0_STX);
4231  0395 a635          	ld	a,#53
4232  0397 cd01bd        	call	_sSpiWriteStatus
4234                     ; 364 	j=800;
4236  039a ae0320        	ldw	x,#800
4237  039d 1f01          	ldw	(OFST-1,sp),x
4239  039f 2016          	jra	L3542
4240  03a1               L7442:
4241                     ; 368 		if(j-- == 0)break; 
4243  03a1 1e01          	ldw	x,(OFST-1,sp)
4244  03a3 1d0001        	subw	x,#1
4245  03a6 1f01          	ldw	(OFST-1,sp),x
4246  03a8 1c0001        	addw	x,#1
4247  03ab a30000        	cpw	x,#0
4248  03ae 2607          	jrne	L3542
4250  03b0               L5542:
4251                     ; 370 	j=2400;
4253  03b0 ae0960        	ldw	x,#2400
4254  03b3 1f01          	ldw	(OFST-1,sp),x
4256  03b5 201c          	jra	L5642
4257  03b7               L3542:
4258                     ; 366 	while(!CC_SOMI_IN)
4260  03b7 c65006        	ld	a,_PB_IDR
4261  03ba a510          	bcp	a,#16
4262  03bc 27e3          	jreq	L7442
4263  03be 20f0          	jra	L5542
4264  03c0               L1642:
4265                     ; 374 		if(j-- == 0)break; 
4267  03c0 1e01          	ldw	x,(OFST-1,sp)
4268  03c2 1d0001        	subw	x,#1
4269  03c5 1f01          	ldw	(OFST-1,sp),x
4270  03c7 1c0001        	addw	x,#1
4271  03ca a30000        	cpw	x,#0
4272  03cd 2604          	jrne	L5642
4274  03cf               L7642:
4275                     ; 377 	return 0;
4277  03cf 4f            	clr	a
4280  03d0 5b04          	addw	sp,#4
4281  03d2 81            	ret
4282  03d3               L5642:
4283                     ; 372 	while(CC_SOMI_IN)
4285  03d3 c65006        	ld	a,_PB_IDR
4286  03d6 a510          	bcp	a,#16
4287  03d8 26e6          	jrne	L1642
4288  03da 20f3          	jra	L7642
4366                     ; 385 uchar halRfReceivePacket(uchar *rxBuffer, uchar *length)
4366                     ; 386 {
4367                     	switch	.text
4368  03dc               _halRfReceivePacket:
4370  03dc 89            	pushw	x
4371  03dd 5203          	subw	sp,#3
4372       00000003      OFST:	set	3
4375                     ; 388 	nTemp = sSpiReadStatus(TI_CCxxx0_RXBYTES);
4377  03df a63b          	ld	a,#59
4378  03e1 cd017e        	call	_sSpiReadStatus
4380  03e4 6b03          	ld	(OFST+0,sp),a
4381                     ; 389 	if (nTemp & TI_CCxxx0_NUM_RXBYTES)
4383  03e6 7b03          	ld	a,(OFST+0,sp)
4384  03e8 a57f          	bcp	a,#127
4385  03ea 274c          	jreq	L1352
4386                     ; 391 		packetLength = sSpiReadByte(TI_CCxxx0_RXFIFO);//读包长度
4388  03ec a63f          	ld	a,#63
4389  03ee cd00fc        	call	_sSpiReadByte
4391  03f1 6b03          	ld	(OFST+0,sp),a
4392                     ; 392 		if (packetLength <= 62)
4394  03f3 7b03          	ld	a,(OFST+0,sp)
4395  03f5 a13f          	cp	a,#63
4396  03f7 2436          	jruge	L3352
4397                     ; 394 			sSpiReadMore(TI_CCxxx0_RXFIFO,rxBuffer,packetLength);
4399  03f9 7b03          	ld	a,(OFST+0,sp)
4400  03fb 88            	push	a
4401  03fc 1e05          	ldw	x,(OFST+2,sp)
4402  03fe 89            	pushw	x
4403  03ff a63f          	ld	a,#63
4404  0401 cd013b        	call	_sSpiReadMore
4406  0404 5b03          	addw	sp,#3
4407                     ; 395 			*length = packetLength;
4409  0406 7b03          	ld	a,(OFST+0,sp)
4410  0408 1e08          	ldw	x,(OFST+5,sp)
4411  040a f7            	ld	(x),a
4412                     ; 396 			sSpiReadMore(TI_CCxxx0_RXFIFO,status,2);//read 2 appended status bytes (status[0]=RSSI,status[1]=LQI)
4414  040b 4b02          	push	#2
4415  040d 96            	ldw	x,sp
4416  040e 1c0002        	addw	x,#OFST-1
4417  0411 89            	pushw	x
4418  0412 a63f          	ld	a,#63
4419  0414 cd013b        	call	_sSpiReadMore
4421  0417 5b03          	addw	sp,#3
4422                     ; 397 			sSpiWriteStatus(TI_CCxxx0_SFRX);
4424  0419 a63a          	ld	a,#58
4425  041b cd01bd        	call	_sSpiWriteStatus
4427                     ; 398 			if (status[1] & TI_CCxxx0_CRC_OK)
4429  041e 7b02          	ld	a,(OFST-1,sp)
4430  0420 a580          	bcp	a,#128
4431  0422 2704          	jreq	L5352
4432                     ; 400 				return 1;
4434  0424 a601          	ld	a,#1
4436  0426 2004          	jra	L44
4437  0428               L5352:
4438                     ; 404 				f_RxCC2500();
4440  0428 cd036c        	call	_f_RxCC2500
4442                     ; 405 				return 0;
4444  042b 4f            	clr	a
4446  042c               L44:
4448  042c 5b05          	addw	sp,#5
4449  042e 81            	ret
4450  042f               L3352:
4451                     ; 410 			*length = 0;								
4453  042f 1e08          	ldw	x,(OFST+5,sp)
4454  0431 7f            	clr	(x)
4455                     ; 411 			f_RxCC2500();
4457  0432 cd036c        	call	_f_RxCC2500
4459                     ; 412 			return 0;
4461  0435 4f            	clr	a
4463  0436 20f4          	jra	L44
4464  0438               L1352:
4465                     ; 417 		*length = 0;										
4467  0438 1e08          	ldw	x,(OFST+5,sp)
4468  043a 7f            	clr	(x)
4469                     ; 418 		f_RxCC2500();
4471  043b cd036c        	call	_f_RxCC2500
4473                     ; 419 		return 0;
4475  043e 4f            	clr	a
4477  043f 20eb          	jra	L44
4516                     ; 428 uchar sPowerReset(void)
4516                     ; 429 {
4517                     	switch	.text
4518  0441               _sPowerReset:
4520  0441 89            	pushw	x
4521       00000002      OFST:	set	2
4524                     ; 431 	CC_UCLK_HIGH;																							//ADD
4526  0442 7218500f      	bset	_PD_ODR,#4
4527                     ; 432 	CC_SIMO_LOW;
4529  0446 72175000      	bres	_PA_ODR,#3
4530                     ; 433 	CC_CS_LOW;
4532  044a 72135000      	bres	_PA_ODR,#1
4533                     ; 434 	f_Delay(20);
4535  044e ae0014        	ldw	x,#20
4536  0451 cd0000        	call	_f_Delay
4538                     ; 435 	CC_CS_HIGH;
4540  0454 72125000      	bset	_PA_ODR,#1
4541                     ; 436 	f_Delay(20000);
4543  0458 ae4e20        	ldw	x,#20000
4544  045b cd0000        	call	_f_Delay
4546                     ; 437 	CC_CS_LOW;
4548  045e 72135000      	bres	_PA_ODR,#1
4549                     ; 438 	i = 0;
4551  0462 5f            	clrw	x
4552  0463 1f01          	ldw	(OFST-1,sp),x
4554  0465 2024          	jra	L7652
4555  0467               L3652:
4556                     ; 442 		f_Delay(20);
4558  0467 ae0014        	ldw	x,#20
4559  046a cd0000        	call	_f_Delay
4561                     ; 443 		if (i ++ > 1000)
4563  046d 1e01          	ldw	x,(OFST-1,sp)
4564  046f 1c0001        	addw	x,#1
4565  0472 1f01          	ldw	(OFST-1,sp),x
4566  0474 1d0001        	subw	x,#1
4567  0477 a303e9        	cpw	x,#1001
4568  047a 250f          	jrult	L7652
4569                     ; 444 			break;
4570  047c               L1752:
4571                     ; 446 	if (i >= 1000)
4573  047c 1e01          	ldw	x,(OFST-1,sp)
4574  047e a303e8        	cpw	x,#1000
4575  0481 2511          	jrult	L5752
4576                     ; 448 		CC_CS_HIGH;
4578  0483 72125000      	bset	_PA_ODR,#1
4579                     ; 449 			return 1;
4581  0487 a601          	ld	a,#1
4583  0489 203b          	jra	L05
4584  048b               L7652:
4585                     ; 439 	while(CC_SOMI_IN)
4587  048b c65006        	ld	a,_PB_IDR
4588  048e a510          	bcp	a,#16
4589  0490 26d5          	jrne	L3652
4590  0492 20e8          	jra	L1752
4591  0494               L5752:
4592                     ; 451 	sSpiWrite(TI_CCxxx0_SRES);
4594  0494 a630          	ld	a,#48
4595  0496 cd0000        	call	_sSpiWrite
4597                     ; 452 	f_Delay(20000);
4599  0499 ae4e20        	ldw	x,#20000
4600  049c cd0000        	call	_f_Delay
4602                     ; 453 	i = 0;
4604  049f 5f            	clrw	x
4605  04a0 1f01          	ldw	(OFST-1,sp),x
4607  04a2 2024          	jra	L3062
4608  04a4               L7752:
4609                     ; 457 		f_Delay(20);
4611  04a4 ae0014        	ldw	x,#20
4612  04a7 cd0000        	call	_f_Delay
4614                     ; 458 		if (i ++ > 1000)
4616  04aa 1e01          	ldw	x,(OFST-1,sp)
4617  04ac 1c0001        	addw	x,#1
4618  04af 1f01          	ldw	(OFST-1,sp),x
4619  04b1 1d0001        	subw	x,#1
4620  04b4 a303e9        	cpw	x,#1001
4621  04b7 250f          	jrult	L3062
4622                     ; 459 			break;
4623  04b9               L5062:
4624                     ; 461 	if (i >= 1000)
4626  04b9 1e01          	ldw	x,(OFST-1,sp)
4627  04bb a303e8        	cpw	x,#1000
4628  04be 2511          	jrult	L1162
4629                     ; 463 		CC_CS_HIGH;
4631  04c0 72125000      	bset	_PA_ODR,#1
4632                     ; 464 		return 1;
4634  04c4 a601          	ld	a,#1
4636  04c6               L05:
4638  04c6 85            	popw	x
4639  04c7 81            	ret
4640  04c8               L3062:
4641                     ; 454 	while(CC_SOMI_IN)
4643  04c8 c65006        	ld	a,_PB_IDR
4644  04cb a510          	bcp	a,#16
4645  04cd 26d5          	jrne	L7752
4646  04cf 20e8          	jra	L5062
4647  04d1               L1162:
4648                     ; 466 	CC_CS_HIGH;
4650  04d1 72125000      	bset	_PA_ODR,#1
4651                     ; 467 	return 0;	
4653  04d5 4f            	clr	a
4655  04d6 20ee          	jra	L05
4695                     ; 475 uchar f_InitCC2500(uchar Channel)
4695                     ; 476 {
4696                     	switch	.text
4697  04d8               _f_InitCC2500:
4699  04d8 88            	push	a
4700       00000000      OFST:	set	0
4703                     ; 478 	sSpiInitIO();	
4705  04d9 cd0347        	call	_sSpiInitIO
4707                     ; 479 	if(sPowerReset())
4709  04dc cd0441        	call	_sPowerReset
4711  04df 4d            	tnz	a
4712  04e0 2705          	jreq	L1362
4713                     ; 480 	return TRUE;//复位 
4715  04e2 a601          	ld	a,#1
4718  04e4 5b01          	addw	sp,#1
4719  04e6 81            	ret
4720  04e7               L1362:
4721                     ; 481 	NOP();
4724  04e7 9d            NOP
4726                     ; 482 	if(CC2500_Settings_250k(Channel))
4728  04e8 7b01          	ld	a,(OFST+1,sp)
4729  04ea cd01f2        	call	_CC2500_Settings_250k
4731  04ed 4d            	tnz	a
4732  04ee 2705          	jreq	L3362
4733                     ; 483 	return TRUE;
4735  04f0 a601          	ld	a,#1
4738  04f2 5b01          	addw	sp,#1
4739  04f4 81            	ret
4740  04f5               L3362:
4741                     ; 484 	NOP();
4744  04f5 9d            NOP
4746                     ; 485 	sSetInterrupt();
4748  04f6 cd0354        	call	_sSetInterrupt
4750                     ; 487 	sSpiWriteStatus(TI_CCxxx0_SIDLE);
4752  04f9 a636          	ld	a,#54
4753  04fb cd01bd        	call	_sSpiWriteStatus
4755                     ; 488 	sSpiWriteStatus(TI_CCxxx0_SCAL);//检验
4757  04fe a633          	ld	a,#51
4758  0500 cd01bd        	call	_sSpiWriteStatus
4760                     ; 489 	f_Delay(20000);
4762  0503 ae4e20        	ldw	x,#20000
4763  0506 cd0000        	call	_f_Delay
4765                     ; 490 	return FALSE;
4767  0509 4f            	clr	a
4770  050a 5b01          	addw	sp,#1
4771  050c 81            	ret
4807                     ; 498 void f_Cc2500Init(void)
4807                     ; 499 {
4808                     	switch	.text
4809  050d               _f_Cc2500Init:
4811  050d 88            	push	a
4812       00000001      OFST:	set	1
4815  050e               L3562:
4816                     ; 503 		err = f_InitCC2500(Cc2500Inf.RF_Channel[Cc2500Inf.RF_Channel_Index]);//初始化2.4G
4818  050e c60004        	ld	a,_Cc2500Inf+4
4819  0511 5f            	clrw	x
4820  0512 97            	ld	xl,a
4821  0513 d60000        	ld	a,(_Cc2500Inf,x)
4822  0516 adc0          	call	_f_InitCC2500
4824  0518 6b01          	ld	(OFST+0,sp),a
4825                     ; 504 	}while(err);
4827  051a 0d01          	tnz	(OFST+0,sp)
4828  051c 26f0          	jrne	L3562
4829                     ; 505 }
4832  051e 84            	pop	a
4833  051f 81            	ret
4871                     ; 512 void SetCC2500_ChannelNumber(uchar number)
4871                     ; 513 {
4872                     	switch	.text
4873  0520               _SetCC2500_ChannelNumber:
4875  0520 88            	push	a
4876       00000000      OFST:	set	0
4879                     ; 514 	sSpiWriteStatus(TI_CCxxx0_SIDLE);
4881  0521 a636          	ld	a,#54
4882  0523 cd01bd        	call	_sSpiWriteStatus
4884                     ; 515 	sSpiWriteByte(TI_CCxxx0_CHANNR, number);// Channel number.
4886  0526 7b01          	ld	a,(OFST+1,sp)
4887  0528 97            	ld	xl,a
4888  0529 a60a          	ld	a,#10
4889  052b 95            	ld	xh,a
4890  052c cd0068        	call	_sSpiWriteByte
4892                     ; 516 	sSpiWriteStatus(TI_CCxxx0_SCAL);//检验
4894  052f a633          	ld	a,#51
4895  0531 cd01bd        	call	_sSpiWriteStatus
4897                     ; 517 	f_Delay(200);
4899  0534 ae00c8        	ldw	x,#200
4900  0537 cd0000        	call	_f_Delay
4902                     ; 518 }
4905  053a 84            	pop	a
4906  053b 81            	ret
4919                     	xdef	_sPowerReset
4920                     	xdef	_f_SleepCC2500
4921                     	xdef	_sSetInterrupt
4922                     	xdef	_sSpiInitIO
4923                     	xdef	_CC2500_Settings_250k
4924                     	xdef	_sSpiWriteStatus
4925                     	xdef	_sSpiReadStatus
4926                     	xdef	_sSpiReadMore
4927                     	xdef	_sSpiReadByte
4928                     	xdef	_sSpiWriteMore
4929                     	xdef	_sSpiWriteByte
4930                     	xdef	_sSpiRead
4931                     	xdef	_sSpiWrite
4932                     	xdef	_SetCC2500_ChannelNumber
4933                     	xdef	_f_RxCC2500
4934                     	xdef	_f_Cc2500Init
4935                     	xdef	_f_InitCC2500
4936                     	xdef	_halRfReceivePacket
4937                     	xdef	_f_SendPacket
4938                     	switch	.bss
4939  0000               _Cc2500Inf:
4940  0000 000000000000  	ds.b	9
4941                     	xdef	_Cc2500Inf
4942                     	xref	_f_Delay
4943                     	xref.b	c_x
4963                     	end
