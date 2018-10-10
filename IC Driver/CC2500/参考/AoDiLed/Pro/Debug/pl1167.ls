   1                     ; C Compiler for STM8 (COSMIC Software)
   2                     ; Parser V4.8.32 - 23 Mar 2010
   3                     ; Generator V4.3.4 - 23 Mar 2010
2621                     .const:	section	.text
2622  0000               _FreqRegAddrTab:
2623  0000 07            	dc.b	7
2624  0001 34            	dc.b	52
2625  0002 07            	dc.b	7
2626  0003               _FreqRegTab:
2627  0003 0073          	dc.w	115
2628  0005 8080          	dc.w	-32640
2629  0007 0083          	dc.w	131
2630  0009 0003          	dc.w	3
2631  000b 8080          	dc.w	-32640
2632  000d 00e3          	dc.w	227
2633  000f 0063          	dc.w	99
2634  0011 8080          	dc.w	-32640
2635  0013 00c3          	dc.w	195
2636  0015 0043          	dc.w	67
2637  0017 8080          	dc.w	-32640
2638  0019 00b3          	dc.w	179
2639  001b 0033          	dc.w	51
2640  001d 8080          	dc.w	-32640
2641  001f 00f3          	dc.w	243
2642                     	bsct
2643  0000               _PrfRegAddrTab:
2644  0000 00            	dc.b	0
2645  0001 01            	dc.b	1
2646  0002 02            	dc.b	2
2647  0003 04            	dc.b	4
2648  0004 05            	dc.b	5
2649  0005 07            	dc.b	7
2650  0006 08            	dc.b	8
2651  0007 09            	dc.b	9
2652  0008 0a            	dc.b	10
2653  0009 0b            	dc.b	11
2654  000a 0c            	dc.b	12
2655  000b 0d            	dc.b	13
2656  000c 16            	dc.b	22
2657  000d 17            	dc.b	23
2658  000e 18            	dc.b	24
2659  000f 19            	dc.b	25
2660  0010 1a            	dc.b	26
2661  0011 1b            	dc.b	27
2662  0012 1c            	dc.b	28
2663  0013 20            	dc.b	32
2664  0014 21            	dc.b	33
2665  0015 22            	dc.b	34
2666  0016 23            	dc.b	35
2667  0017 28            	dc.b	40
2668  0018 29            	dc.b	41
2669  0019 2a            	dc.b	42
2670  001a 2b            	dc.b	43
2671  001b 24            	dc.b	36
2672  001c 25            	dc.b	37
2673  001d 26            	dc.b	38
2674  001e 27            	dc.b	39
2675  001f 07            	dc.b	7
2676  0020 24            	dc.b	36
2677  0021 27            	dc.b	39
2678  0022 07            	dc.b	7
2679  0023               _PrfRegTab:
2680  0023 6fe0          	dc.w	28640
2681  0025 5681          	dc.w	22145
2682  0027 6617          	dc.w	26135
2683  0029 9cc9          	dc.w	-25399
2684  002b 6637          	dc.w	26167
2685  002d 0030          	dc.w	48
2686  002f 6c90          	dc.w	27792
2687  0031 1840          	dc.w	6208
2688  0033 7ffd          	dc.w	32765
2689  0035 0008          	dc.w	8
2690  0037 0000          	dc.w	0
2691  0039 48bd          	dc.w	18621
2692  003b 00ff          	dc.w	255
2693  003d 8005          	dc.w	-32763
2694  003f 0067          	dc.w	103
2695  0041 1659          	dc.w	5721
2696  0043 19e0          	dc.w	6624
2697  0045 1300          	dc.w	4864
2698  0047 1800          	dc.w	6144
2699  0049 5000          	dc.w	20480
2700  004b 3fc7          	dc.w	16327
2701  004d 2000          	dc.w	8192
2702  004f 0340          	dc.w	832
2703  0051 4401          	dc.w	17409
2704  0053 b800          	dc.w	-18432
2705  0055 fdc8          	dc.w	-568
2706  0057 000f          	dc.w	15
2707  0059 0000          	dc.w	0
2708  005b 0000          	dc.w	0
2709  005d 0000          	dc.w	0
2710  005f 7407          	dc.w	29703
2711  0061 0000          	dc.w	0
2712  0063 eede          	dc.w	-4386
2713  0065 11f9          	dc.w	4601
2714  0067 00f3          	dc.w	243
2766                     ; 48 void SpiWr8(uchar dat)
2766                     ; 49 {
2768                     	switch	.text
2769  0000               _SpiWr8:
2771  0000 88            	push	a
2772  0001 88            	push	a
2773       00000001      OFST:	set	1
2776                     ; 52 	for(i=0; i<8; i++)  
2778  0002 0f01          	clr	(OFST+0,sp)
2779  0004               L1271:
2780                     ; 54 		SPICLK = 1;
2782  0004 72145000      	bset	_PA_ODR,#2
2783                     ; 55 		if((dat&0x80)==0x80)
2785  0008 7b02          	ld	a,(OFST+1,sp)
2786  000a a480          	and	a,#128
2787  000c a180          	cp	a,#128
2788  000e 2606          	jrne	L7271
2789                     ; 56 			SPIMOSI = 1;
2791  0010 721a5005      	bset	_PB_ODR,#5
2793  0014 2004          	jra	L1371
2794  0016               L7271:
2795                     ; 58 			SPIMOSI = 0;
2797  0016 721b5005      	bres	_PB_ODR,#5
2798  001a               L1371:
2799                     ; 59 		NOP();NOP();NOP();NOP();NOP();
2802  001a 9d            NOP
2807  001b 9d            NOP
2812  001c 9d            NOP
2817  001d 9d            NOP
2822  001e 9d            NOP
2824                     ; 60 		NOP();NOP();NOP();NOP();NOP();
2827  001f 9d            NOP
2832  0020 9d            NOP
2837  0021 9d            NOP
2842  0022 9d            NOP
2847  0023 9d            NOP
2849                     ; 61 		NOP();NOP();NOP();NOP();NOP();
2852  0024 9d            NOP
2857  0025 9d            NOP
2862  0026 9d            NOP
2867  0027 9d            NOP
2872  0028 9d            NOP
2874                     ; 62 		NOP();NOP();NOP();NOP();NOP();
2877  0029 9d            NOP
2882  002a 9d            NOP
2887  002b 9d            NOP
2892  002c 9d            NOP
2897  002d 9d            NOP
2899                     ; 63 		NOP();NOP();NOP();NOP();NOP();
2902  002e 9d            NOP
2907  002f 9d            NOP
2912  0030 9d            NOP
2917  0031 9d            NOP
2922  0032 9d            NOP
2924                     ; 64 		NOP();NOP();NOP();NOP();NOP();
2927  0033 9d            NOP
2932  0034 9d            NOP
2937  0035 9d            NOP
2942  0036 9d            NOP
2947  0037 9d            NOP
2949                     ; 65 		SPICLK = 0;
2951  0038 72155000      	bres	_PA_ODR,#2
2952                     ; 66 		NOP();NOP();NOP();NOP();NOP();
2955  003c 9d            NOP
2960  003d 9d            NOP
2965  003e 9d            NOP
2970  003f 9d            NOP
2975  0040 9d            NOP
2977                     ; 67 		NOP();NOP();NOP();NOP();NOP();
2980  0041 9d            NOP
2985  0042 9d            NOP
2990  0043 9d            NOP
2995  0044 9d            NOP
3000  0045 9d            NOP
3002                     ; 68 		NOP();NOP();NOP();NOP();NOP();
3005  0046 9d            NOP
3010  0047 9d            NOP
3015  0048 9d            NOP
3020  0049 9d            NOP
3025  004a 9d            NOP
3027                     ; 69 		NOP();NOP();NOP();NOP();NOP();
3030  004b 9d            NOP
3035  004c 9d            NOP
3040  004d 9d            NOP
3045  004e 9d            NOP
3050  004f 9d            NOP
3052                     ; 70 		NOP();NOP();NOP();NOP();NOP();
3055  0050 9d            NOP
3060  0051 9d            NOP
3065  0052 9d            NOP
3070  0053 9d            NOP
3075  0054 9d            NOP
3077                     ; 71 		NOP();NOP();NOP();NOP();NOP();
3080  0055 9d            NOP
3085  0056 9d            NOP
3090  0057 9d            NOP
3095  0058 9d            NOP
3100  0059 9d            NOP
3102                     ; 72 		dat <<= 1;
3104  005a 0802          	sll	(OFST+1,sp)
3105                     ; 52 	for(i=0; i<8; i++)  
3107  005c 0c01          	inc	(OFST+0,sp)
3110  005e 7b01          	ld	a,(OFST+0,sp)
3111  0060 a108          	cp	a,#8
3112  0062 2402          	jruge	L6
3113  0064 209e          	jp	L1271
3114  0066               L6:
3115                     ; 75 }
3118  0066 85            	popw	x
3119  0067 81            	ret
3165                     ; 77 uchar SpiRd8(void)
3165                     ; 78 {
3166                     	switch	.text
3167  0068               _SpiRd8:
3169  0068 89            	pushw	x
3170       00000002      OFST:	set	2
3173                     ; 80 	for(i=0; i<8; i++)
3175  0069 0f01          	clr	(OFST-1,sp)
3176  006b               L5571:
3177                     ; 82 		SPICLK = 1;
3179  006b 72145000      	bset	_PA_ODR,#2
3180                     ; 83 		dat <<= 1;
3182  006f 0802          	sll	(OFST+0,sp)
3183                     ; 84 		NOP();NOP();NOP();NOP();NOP();
3186  0071 9d            NOP
3191  0072 9d            NOP
3196  0073 9d            NOP
3201  0074 9d            NOP
3206  0075 9d            NOP
3208                     ; 85 		NOP();NOP();NOP();NOP();NOP();
3211  0076 9d            NOP
3216  0077 9d            NOP
3221  0078 9d            NOP
3226  0079 9d            NOP
3231  007a 9d            NOP
3233                     ; 86 		NOP();NOP();NOP();NOP();NOP();
3236  007b 9d            NOP
3241  007c 9d            NOP
3246  007d 9d            NOP
3251  007e 9d            NOP
3256  007f 9d            NOP
3258                     ; 87 		NOP();NOP();NOP();NOP();NOP();
3261  0080 9d            NOP
3266  0081 9d            NOP
3271  0082 9d            NOP
3276  0083 9d            NOP
3281  0084 9d            NOP
3283                     ; 88 		NOP();NOP();NOP();NOP();NOP();
3286  0085 9d            NOP
3291  0086 9d            NOP
3296  0087 9d            NOP
3301  0088 9d            NOP
3306  0089 9d            NOP
3308                     ; 89 		NOP();NOP();NOP();NOP();NOP();
3311  008a 9d            NOP
3316  008b 9d            NOP
3321  008c 9d            NOP
3326  008d 9d            NOP
3331  008e 9d            NOP
3333                     ; 90 		SPICLK = 0;
3335  008f 72155000      	bres	_PA_ODR,#2
3336                     ; 91 		NOP();NOP();NOP();NOP();NOP();
3339  0093 9d            NOP
3344  0094 9d            NOP
3349  0095 9d            NOP
3354  0096 9d            NOP
3359  0097 9d            NOP
3361                     ; 92 		NOP();NOP();NOP();NOP();NOP();
3364  0098 9d            NOP
3369  0099 9d            NOP
3374  009a 9d            NOP
3379  009b 9d            NOP
3384  009c 9d            NOP
3386                     ; 93 		NOP();NOP();NOP();NOP();NOP();
3389  009d 9d            NOP
3394  009e 9d            NOP
3399  009f 9d            NOP
3404  00a0 9d            NOP
3409  00a1 9d            NOP
3411                     ; 94 		NOP();NOP();NOP();NOP();NOP();
3414  00a2 9d            NOP
3419  00a3 9d            NOP
3424  00a4 9d            NOP
3429  00a5 9d            NOP
3434  00a6 9d            NOP
3436                     ; 95 		NOP();NOP();NOP();NOP();NOP();
3439  00a7 9d            NOP
3444  00a8 9d            NOP
3449  00a9 9d            NOP
3454  00aa 9d            NOP
3459  00ab 9d            NOP
3461                     ; 96 		NOP();NOP();NOP();NOP();NOP();
3464  00ac 9d            NOP
3469  00ad 9d            NOP
3474  00ae 9d            NOP
3479  00af 9d            NOP
3484  00b0 9d            NOP
3486                     ; 97 		if(SPIMISO==0)
3488  00b1 c65006        	ld	a,_PB_IDR
3489  00b4 a510          	bcp	a,#16
3490  00b6 2608          	jrne	L3671
3491                     ; 98 			dat &= 0xfe;
3493  00b8 7b02          	ld	a,(OFST+0,sp)
3494  00ba a4fe          	and	a,#254
3495  00bc 6b02          	ld	(OFST+0,sp),a
3497  00be 2006          	jra	L5671
3498  00c0               L3671:
3499                     ; 100 			dat |= 0x01;
3501  00c0 7b02          	ld	a,(OFST+0,sp)
3502  00c2 aa01          	or	a,#1
3503  00c4 6b02          	ld	(OFST+0,sp),a
3504  00c6               L5671:
3505                     ; 80 	for(i=0; i<8; i++)
3507  00c6 0c01          	inc	(OFST-1,sp)
3510  00c8 7b01          	ld	a,(OFST-1,sp)
3511  00ca a108          	cp	a,#8
3512  00cc 2402          	jruge	L21
3513  00ce 209b          	jp	L5571
3514  00d0               L21:
3515                     ; 102 	return dat;
3517  00d0 7b02          	ld	a,(OFST+0,sp)
3520  00d2 85            	popw	x
3521  00d3 81            	ret
3567                     ; 105 uint SpiRd16(void)
3567                     ; 106 {
3568                     	switch	.text
3569  00d4               _SpiRd16:
3571  00d4 5203          	subw	sp,#3
3572       00000003      OFST:	set	3
3575                     ; 110 	dat = 0;
3577  00d6 5f            	clrw	x
3578  00d7 1f02          	ldw	(OFST-1,sp),x
3579                     ; 111 	for(i=0; i<16; i++)  
3581  00d9 0f01          	clr	(OFST-2,sp)
3582  00db               L1102:
3583                     ; 113 		SPICLK = 1;
3585  00db 72145000      	bset	_PA_ODR,#2
3586                     ; 114 		dat <<= 1;
3588  00df 0803          	sll	(OFST+0,sp)
3589  00e1 0902          	rlc	(OFST-1,sp)
3590                     ; 115 		NOP();NOP();NOP();NOP();NOP();
3593  00e3 9d            NOP
3598  00e4 9d            NOP
3603  00e5 9d            NOP
3608  00e6 9d            NOP
3613  00e7 9d            NOP
3615                     ; 116 		NOP();NOP();NOP();NOP();NOP();
3618  00e8 9d            NOP
3623  00e9 9d            NOP
3628  00ea 9d            NOP
3633  00eb 9d            NOP
3638  00ec 9d            NOP
3640                     ; 117 		NOP();NOP();NOP();NOP();NOP();
3643  00ed 9d            NOP
3648  00ee 9d            NOP
3653  00ef 9d            NOP
3658  00f0 9d            NOP
3663  00f1 9d            NOP
3665                     ; 118 		NOP();NOP();NOP();NOP();NOP();
3668  00f2 9d            NOP
3673  00f3 9d            NOP
3678  00f4 9d            NOP
3683  00f5 9d            NOP
3688  00f6 9d            NOP
3690                     ; 119 		NOP();NOP();NOP();NOP();NOP();
3693  00f7 9d            NOP
3698  00f8 9d            NOP
3703  00f9 9d            NOP
3708  00fa 9d            NOP
3713  00fb 9d            NOP
3715                     ; 120 		NOP();NOP();NOP();NOP();NOP();
3718  00fc 9d            NOP
3723  00fd 9d            NOP
3728  00fe 9d            NOP
3733  00ff 9d            NOP
3738  0100 9d            NOP
3740                     ; 121 		SPICLK = 0;
3742  0101 72155000      	bres	_PA_ODR,#2
3743                     ; 122 		NOP();NOP();NOP();NOP();NOP();
3746  0105 9d            NOP
3751  0106 9d            NOP
3756  0107 9d            NOP
3761  0108 9d            NOP
3766  0109 9d            NOP
3768                     ; 123 		NOP();NOP();NOP();NOP();NOP();
3771  010a 9d            NOP
3776  010b 9d            NOP
3781  010c 9d            NOP
3786  010d 9d            NOP
3791  010e 9d            NOP
3793                     ; 124 		NOP();NOP();NOP();NOP();NOP();
3796  010f 9d            NOP
3801  0110 9d            NOP
3806  0111 9d            NOP
3811  0112 9d            NOP
3816  0113 9d            NOP
3818                     ; 125 		NOP();NOP();NOP();NOP();NOP();
3821  0114 9d            NOP
3826  0115 9d            NOP
3831  0116 9d            NOP
3836  0117 9d            NOP
3841  0118 9d            NOP
3843                     ; 126 		NOP();NOP();NOP();NOP();NOP();
3846  0119 9d            NOP
3851  011a 9d            NOP
3856  011b 9d            NOP
3861  011c 9d            NOP
3866  011d 9d            NOP
3868                     ; 127 		NOP();NOP();NOP();NOP();NOP();
3871  011e 9d            NOP
3876  011f 9d            NOP
3881  0120 9d            NOP
3886  0121 9d            NOP
3891  0122 9d            NOP
3893                     ; 128 		if(SPIMISO==0)
3895  0123 c65006        	ld	a,_PB_IDR
3896  0126 a510          	bcp	a,#16
3897  0128 2608          	jrne	L7102
3898                     ; 129 			dat &= 0xfffe;
3900  012a 7b03          	ld	a,(OFST+0,sp)
3901  012c a4fe          	and	a,#254
3902  012e 6b03          	ld	(OFST+0,sp),a
3904  0130 2006          	jra	L1202
3905  0132               L7102:
3906                     ; 131 			dat |= 0x0001;
3908  0132 7b03          	ld	a,(OFST+0,sp)
3909  0134 aa01          	or	a,#1
3910  0136 6b03          	ld	(OFST+0,sp),a
3911  0138               L1202:
3912                     ; 111 	for(i=0; i<16; i++)  
3914  0138 0c01          	inc	(OFST-2,sp)
3917  013a 7b01          	ld	a,(OFST-2,sp)
3918  013c a110          	cp	a,#16
3919  013e 2402          	jruge	L61
3920  0140 2099          	jp	L1102
3921  0142               L61:
3922                     ; 133 	return dat;
3924  0142 1e02          	ldw	x,(OFST-1,sp)
3927  0144 5b03          	addw	sp,#3
3928  0146 81            	ret
3973                     ; 137 void PrfWrReg16(uchar reg, uint regval)
3973                     ; 138 {
3974                     	switch	.text
3975  0147               _PrfWrReg16:
3977  0147 88            	push	a
3978       00000000      OFST:	set	0
3981                     ; 139 	SPICS = 0;
3983  0148 72135000      	bres	_PA_ODR,#1
3984                     ; 140 	SpiWr8(reg);
3986  014c cd0000        	call	_SpiWr8
3988                     ; 141 	SpiWr8((uchar)(regval>>8));
3990  014f 7b04          	ld	a,(OFST+4,sp)
3991  0151 cd0000        	call	_SpiWr8
3993                     ; 142 	SpiWr8((uchar)(regval&0x00FF));
3995  0154 7b05          	ld	a,(OFST+5,sp)
3996  0156 a4ff          	and	a,#255
3997  0158 cd0000        	call	_SpiWr8
3999                     ; 143 	SPICS = 1;
4001  015b 72125000      	bset	_PA_ODR,#1
4002                     ; 144 }
4005  015f 84            	pop	a
4006  0160 81            	ret
4052                     ; 158 uint PrfRegRd16(uchar addr)
4052                     ; 159 {
4053                     	switch	.text
4054  0161               _PrfRegRd16:
4056  0161 89            	pushw	x
4057       00000002      OFST:	set	2
4060                     ; 162 	SPICS = 0;
4062  0162 72135000      	bres	_PA_ODR,#1
4063                     ; 163 	SpiWr8(addr|PRF_REG_RD);
4065  0166 aa80          	or	a,#128
4066  0168 cd0000        	call	_SpiWr8
4068                     ; 164 	dat = SpiRd16();
4070  016b cd00d4        	call	_SpiRd16
4072  016e 1f01          	ldw	(OFST-1,sp),x
4073                     ; 165 	SPICS = 1;
4075  0170 72125000      	bset	_PA_ODR,#1
4076                     ; 166 	return dat;
4078  0174 1e01          	ldw	x,(OFST-1,sp)
4081  0176 5b02          	addw	sp,#2
4082  0178 81            	ret
4152                     ; 172 void PL1167_Init(void)
4152                     ; 173 {
4153                     	switch	.text
4154  0179               _PL1167_Init:
4156  0179 5205          	subw	sp,#5
4157       00000005      OFST:	set	5
4160                     ; 176 	SPICLK = 0;
4162  017b 72155000      	bres	_PA_ODR,#2
4163                     ; 177 	SPIMOSI = 0;
4165  017f 721b5005      	bres	_PB_ODR,#5
4166                     ; 178 	SPICS = 0;
4168  0183 72135000      	bres	_PA_ODR,#1
4169                     ; 179 	RFRST = 0;
4171  0187 7219500f      	bres	_PD_ODR,#4
4172                     ; 180 	RFRST = 0;
4174  018b 7219500f      	bres	_PD_ODR,#4
4175                     ; 181 	SPICS = 1;
4177  018f 72125000      	bset	_PA_ODR,#1
4178                     ; 182 	f_Delay(10000);// 10ms
4180  0193 ae2710        	ldw	x,#10000
4181  0196 cd0000        	call	_f_Delay
4183                     ; 183 	RFRST = 1;
4185  0199 7218500f      	bset	_PD_ODR,#4
4186                     ; 184 	f_Delay(10000);// 10ms
4188  019d ae2710        	ldw	x,#10000
4189  01a0 cd0000        	call	_f_Delay
4191                     ; 185 	for(i=0;i<3;i++)
4193  01a3 0f01          	clr	(OFST-4,sp)
4194  01a5               L1212:
4195                     ; 187 		err = 0;
4197  01a5 0f04          	clr	(OFST-1,sp)
4198                     ; 188 		for(j=0;j<PRF_INIT_TAB_LEN;j++)
4200  01a7 0f05          	clr	(OFST+0,sp)
4201  01a9               L7212:
4202                     ; 190 			PrfWrReg16(PrfRegAddrTab[j], PrfRegTab[j]);
4204  01a9 7b05          	ld	a,(OFST+0,sp)
4205  01ab 5f            	clrw	x
4206  01ac 97            	ld	xl,a
4207  01ad 58            	sllw	x
4208  01ae ee23          	ldw	x,(_PrfRegTab,x)
4209  01b0 89            	pushw	x
4210  01b1 7b07          	ld	a,(OFST+2,sp)
4211  01b3 5f            	clrw	x
4212  01b4 97            	ld	xl,a
4213  01b5 e600          	ld	a,(_PrfRegAddrTab,x)
4214  01b7 ad8e          	call	_PrfWrReg16
4216  01b9 85            	popw	x
4217                     ; 191 			regval = PrfRegRd16(PrfRegAddrTab[j]);
4219  01ba 7b05          	ld	a,(OFST+0,sp)
4220  01bc 5f            	clrw	x
4221  01bd 97            	ld	xl,a
4222  01be e600          	ld	a,(_PrfRegAddrTab,x)
4223  01c0 ad9f          	call	_PrfRegRd16
4225  01c2 1f02          	ldw	(OFST-3,sp),x
4226                     ; 192 			if(regval!=PrfRegTab[j])
4228  01c4 7b05          	ld	a,(OFST+0,sp)
4229  01c6 5f            	clrw	x
4230  01c7 97            	ld	xl,a
4231  01c8 58            	sllw	x
4232  01c9 9093          	ldw	y,x
4233  01cb 51            	exgw	x,y
4234  01cc ee23          	ldw	x,(_PrfRegTab,x)
4235  01ce 1302          	cpw	x,(OFST-3,sp)
4236  01d0 51            	exgw	x,y
4237  01d1 2705          	jreq	L5312
4238                     ; 194 				err = 1;
4240  01d3 a601          	ld	a,#1
4241  01d5 6b04          	ld	(OFST-1,sp),a
4242                     ; 195 				NOP();
4245  01d7 9d            NOP
4247  01d8               L5312:
4248                     ; 188 		for(j=0;j<PRF_INIT_TAB_LEN;j++)
4250  01d8 0c05          	inc	(OFST+0,sp)
4253  01da 7b05          	ld	a,(OFST+0,sp)
4254  01dc a123          	cp	a,#35
4255  01de 25c9          	jrult	L7212
4256                     ; 198 		if(err==0)
4258  01e0 0d04          	tnz	(OFST-1,sp)
4259  01e2 2708          	jreq	L5212
4260                     ; 199 			break;		
4262                     ; 185 	for(i=0;i<3;i++)
4264  01e4 0c01          	inc	(OFST-4,sp)
4267  01e6 7b01          	ld	a,(OFST-4,sp)
4268  01e8 a103          	cp	a,#3
4269  01ea 25b9          	jrult	L1212
4270  01ec               L5212:
4271                     ; 201 }
4274  01ec 5b05          	addw	sp,#5
4275  01ee 81            	ret
4278                     	bsct
4279  0069               L1412_temp:
4280  0069 00            	dc.b	0
4341                     ; 228 void f_RfRecDeal(void)
4341                     ; 229 {
4342                     	switch	.text
4343  01ef               _f_RfRecDeal:
4345  01ef 89            	pushw	x
4346       00000002      OFST:	set	2
4349                     ; 233 	if(PKT==0)
4351  01f0 c65010        	ld	a,_PD_IDR
4352  01f3 a502          	bcp	a,#2
4353  01f5 2703          	jreq	L03
4354  01f7 cc02db        	jp	L1712
4355  01fa               L03:
4356                     ; 235 		NOP();NOP();NOP();NOP();
4359  01fa 9d            NOP
4364  01fb 9d            NOP
4369  01fc 9d            NOP
4374  01fd 9d            NOP
4376                     ; 236 		NOP();NOP();NOP();NOP();
4379  01fe 9d            NOP
4384  01ff 9d            NOP
4389  0200 9d            NOP
4394  0201 9d            NOP
4396                     ; 237 		NOP();NOP();NOP();NOP();
4399  0202 9d            NOP
4404  0203 9d            NOP
4409  0204 9d            NOP
4414  0205 9d            NOP
4416                     ; 238 		NOP();NOP();NOP();NOP();
4419  0206 9d            NOP
4424  0207 9d            NOP
4429  0208 9d            NOP
4434  0209 9d            NOP
4436                     ; 239 		if(PKT==0)		
4438  020a c65010        	ld	a,_PD_IDR
4439  020d a502          	bcp	a,#2
4440  020f 2703          	jreq	L23
4441  0211 cc02db        	jp	L1712
4442  0214               L23:
4443                     ; 241 			SPICS = 0;
4445  0214 72135000      	bres	_PA_ODR,#1
4446                     ; 242 			SpiWr8(0x32|PRF_REG_RD);
4448  0218 a6b2          	ld	a,#178
4449  021a cd0000        	call	_SpiWr8
4451                     ; 243 			lenght = SpiRd8();
4453  021d cd0068        	call	_SpiRd8
4455  0220 6b01          	ld	(OFST-1,sp),a
4456                     ; 244 			if(lenght > 11)
4458  0222 7b01          	ld	a,(OFST-1,sp)
4459  0224 a10c          	cp	a,#12
4460  0226 2504          	jrult	L5712
4461                     ; 246 				lenght = 11;
4463  0228 a60b          	ld	a,#11
4464  022a 6b01          	ld	(OFST-1,sp),a
4465  022c               L5712:
4466                     ; 248 			for(i=0;i<lenght;i++)
4468  022c 0f02          	clr	(OFST+0,sp)
4470  022e 200d          	jra	L3022
4471  0230               L7712:
4472                     ; 251 				ucCOMBuf[i] = SpiRd8();
4474  0230 7b02          	ld	a,(OFST+0,sp)
4475  0232 5f            	clrw	x
4476  0233 97            	ld	xl,a
4477  0234 89            	pushw	x
4478  0235 cd0068        	call	_SpiRd8
4480  0238 85            	popw	x
4481  0239 e71d          	ld	(_ucCOMBuf,x),a
4482                     ; 248 			for(i=0;i<lenght;i++)
4484  023b 0c02          	inc	(OFST+0,sp)
4485  023d               L3022:
4488  023d 7b02          	ld	a,(OFST+0,sp)
4489  023f 1101          	cp	a,(OFST-1,sp)
4490  0241 25ed          	jrult	L7712
4491                     ; 253 			SPICS = 1;
4493  0243 72125000      	bset	_PA_ODR,#1
4494                     ; 255 			PrfWrReg16(0x34, 0x8080);
4496  0247 ae8080        	ldw	x,#32896
4497  024a 89            	pushw	x
4498  024b a634          	ld	a,#52
4499  024d cd0147        	call	_PrfWrReg16
4501  0250 85            	popw	x
4502                     ; 256 			PrfWrReg16(0x07, 0x00f3);
4504  0251 ae00f3        	ldw	x,#243
4505  0254 89            	pushw	x
4506  0255 a607          	ld	a,#7
4507  0257 cd0147        	call	_PrfWrReg16
4509  025a 85            	popw	x
4510                     ; 259 			if(machineInf.addrInf.addrFlag == 0)
4512  025b c60025        	ld	a,_machineInf+37
4513  025e a501          	bcp	a,#1
4514  0260 2666          	jrne	L7022
4515                     ; 261 				if( ucCOMBuf[0] == machineInf.AddressRf[0]
4515                     ; 262 				&& ucCOMBuf[1] == machineInf.AddressRf[1]
4515                     ; 263 				&& ucCOMBuf[2] == machineInf.AddressRf[2])
4517  0262 b61d          	ld	a,_ucCOMBuf
4518  0264 c10022        	cp	a,_machineInf+34
4519  0267 2672          	jrne	L1712
4521  0269 b61e          	ld	a,_ucCOMBuf+1
4522  026b c10023        	cp	a,_machineInf+35
4523  026e 266b          	jrne	L1712
4525  0270 b61f          	ld	a,_ucCOMBuf+2
4526  0272 c10024        	cp	a,_machineInf+36
4527  0275 2664          	jrne	L1712
4528                     ; 265 					if(ucCOMBuf[3] != sendNum)	//用于遥控器板接收识别码
4530  0277 b620          	ld	a,_ucCOMBuf+3
4531  0279 b11c          	cp	a,_sendNum
4532  027b 275e          	jreq	L1712
4533                     ; 267 						sendNum = ucCOMBuf[3];
4535  027d 45201c        	mov	_sendNum,_ucCOMBuf+3
4536                     ; 268 						if(ucCOMBuf[4] == 0x03)	//帧类型用于控制命令
4538  0280 b621          	ld	a,_ucCOMBuf+4
4539  0282 a103          	cp	a,#3
4540  0284 2655          	jrne	L1712
4541                     ; 271 							TxComBuff.jSetSeatLevel = ucCOMBuf[5]>>4;
4543  0286 b622          	ld	a,_ucCOMBuf+5
4544  0288 4e            	swap	a
4545  0289 a40f          	and	a,#15
4546  028b c70003        	ld	_TxComBuff+3,a
4547                     ; 273 							TxComBuff.jSetWaterLevel = ucCOMBuf[5]&0x0f; 
4549  028e b622          	ld	a,_ucCOMBuf+5
4550  0290 a40f          	and	a,#15
4551  0292 c70001        	ld	_TxComBuff+1,a
4552                     ; 275 							TxComBuff.jSetDryLevel = ucCOMBuf[6]&0x0f; 
4554  0295 b623          	ld	a,_ucCOMBuf+6
4555  0297 a40f          	and	a,#15
4556  0299 c70002        	ld	_TxComBuff+2,a
4557                     ; 277 							TxComBuff.jLevelState = ucCOMBuf[7]>>4;
4559  029c b624          	ld	a,_ucCOMBuf+7
4560  029e 4e            	swap	a
4561  029f a40f          	and	a,#15
4562  02a1 c70005        	ld	_TxComBuff+5,a
4563                     ; 278 							TxComBuff.jPosState = ucCOMBuf[7]&0x0f; 
4565  02a4 b624          	ld	a,_ucCOMBuf+7
4566  02a6 a40f          	and	a,#15
4567  02a8 c70004        	ld	_TxComBuff+4,a
4568                     ; 279 							TxComBuff.jFunCmd = ucCOMBuf[9];
4570  02ab 5500260006    	mov	_TxComBuff+6,_ucCOMBuf+9
4571                     ; 280 							if(TxComBuff.jFunCmd == 0x08)
4573  02b0 c60006        	ld	a,_TxComBuff+6
4574  02b3 a108          	cp	a,#8
4575  02b5 2604          	jrne	L7122
4576                     ; 284 								LedInf.delayDrytDis = true;
4578  02b7 72120002      	bset	_LedInf+2,#1
4579  02bb               L7122:
4580                     ; 286 							if(TxComBuff.jFunCmd == 0x07)
4582  02bb c60006        	ld	a,_TxComBuff+6
4583  02be a107          	cp	a,#7
4584  02c0 2619          	jrne	L1712
4585                     ; 288 								LedInf.delaySeatDis = true;
4587  02c2 72100002      	bset	_LedInf+2,#0
4588  02c6 2013          	jra	L1712
4589  02c8               L7022:
4590                     ; 298 				machineInf.AddressRf[0] = ucCOMBuf[0];
4592  02c8 55001d0022    	mov	_machineInf+34,_ucCOMBuf
4593                     ; 299 				machineInf.AddressRf[1] = ucCOMBuf[1];
4595  02cd 55001e0023    	mov	_machineInf+35,_ucCOMBuf+1
4596                     ; 300 				machineInf.AddressRf[2] = ucCOMBuf[2];
4598  02d2 55001f0024    	mov	_machineInf+36,_ucCOMBuf+2
4599                     ; 301 				machineInf.addrInf.addrFlag = 0;
4601  02d7 72110025      	bres	_machineInf+37,#0
4602  02db               L1712:
4603                     ; 326 }
4606  02db 85            	popw	x
4607  02dc 81            	ret
4610                     	bsct
4611  006a               L5222_freqTemp:
4612  006a 00            	dc.b	0
4687                     ; 333 void f_FreqDeal(void)
4687                     ; 334 {
4688                     	switch	.text
4689  02dd               _f_FreqDeal:
4691  02dd 5207          	subw	sp,#7
4692       00000007      OFST:	set	7
4695                     ; 338 	i=0;
4697                     ; 339 	for(i=0;i<3;i++)
4699  02df 0f06          	clr	(OFST-1,sp)
4700  02e1               L5622:
4701                     ; 341 		err = 0;
4703  02e1 0f05          	clr	(OFST-2,sp)
4704                     ; 342 		for(j=0;j<PRF_INIT_TAB_LEN;j++)
4706  02e3 0f07          	clr	(OFST+0,sp)
4707  02e5               L3722:
4708                     ; 344 			PrfWrReg16(PrfRegAddrTab[j], PrfRegTab[j]);
4710  02e5 7b07          	ld	a,(OFST+0,sp)
4711  02e7 5f            	clrw	x
4712  02e8 97            	ld	xl,a
4713  02e9 58            	sllw	x
4714  02ea ee23          	ldw	x,(_PrfRegTab,x)
4715  02ec 89            	pushw	x
4716  02ed 7b09          	ld	a,(OFST+2,sp)
4717  02ef 5f            	clrw	x
4718  02f0 97            	ld	xl,a
4719  02f1 e600          	ld	a,(_PrfRegAddrTab,x)
4720  02f3 cd0147        	call	_PrfWrReg16
4722  02f6 85            	popw	x
4723                     ; 345 			regval = PrfRegRd16(PrfRegAddrTab[j]);
4725  02f7 7b07          	ld	a,(OFST+0,sp)
4726  02f9 5f            	clrw	x
4727  02fa 97            	ld	xl,a
4728  02fb e600          	ld	a,(_PrfRegAddrTab,x)
4729  02fd cd0161        	call	_PrfRegRd16
4731  0300 1f03          	ldw	(OFST-4,sp),x
4732                     ; 346 			if(regval!=PrfRegTab[j])
4734  0302 7b07          	ld	a,(OFST+0,sp)
4735  0304 5f            	clrw	x
4736  0305 97            	ld	xl,a
4737  0306 58            	sllw	x
4738  0307 9093          	ldw	y,x
4739  0309 51            	exgw	x,y
4740  030a ee23          	ldw	x,(_PrfRegTab,x)
4741  030c 1303          	cpw	x,(OFST-4,sp)
4742  030e 51            	exgw	x,y
4743  030f 2705          	jreq	L1032
4744                     ; 348 				err = 1;
4746  0311 a601          	ld	a,#1
4747  0313 6b05          	ld	(OFST-2,sp),a
4748                     ; 349 				NOP();
4751  0315 9d            NOP
4753  0316               L1032:
4754                     ; 342 		for(j=0;j<PRF_INIT_TAB_LEN;j++)
4756  0316 0c07          	inc	(OFST+0,sp)
4759  0318 7b07          	ld	a,(OFST+0,sp)
4760  031a a123          	cp	a,#35
4761  031c 25c7          	jrult	L3722
4762                     ; 352 		if(err==0)
4764  031e 0d05          	tnz	(OFST-2,sp)
4765  0320 2708          	jreq	L1722
4766                     ; 353 			break;		
4768                     ; 339 	for(i=0;i<3;i++)
4770  0322 0c06          	inc	(OFST-1,sp)
4773  0324 7b06          	ld	a,(OFST-1,sp)
4774  0326 a103          	cp	a,#3
4775  0328 25b7          	jrult	L5622
4776  032a               L1722:
4777                     ; 356 	i=0;
4779                     ; 357 	for(i=0;i<3;i++)
4781  032a 0f06          	clr	(OFST-1,sp)
4782  032c               L5032:
4783                     ; 359 		PrfWrReg16(FreqRegAddrTab[i], FreqRegTab[freqTemp][i]);
4785  032c 7b06          	ld	a,(OFST-1,sp)
4786  032e 5f            	clrw	x
4787  032f 97            	ld	xl,a
4788  0330 58            	sllw	x
4789  0331 1f01          	ldw	(OFST-6,sp),x
4790  0333 b66a          	ld	a,L5222_freqTemp
4791  0335 97            	ld	xl,a
4792  0336 a606          	ld	a,#6
4793  0338 42            	mul	x,a
4794  0339 72fb01        	addw	x,(OFST-6,sp)
4795  033c de0003        	ldw	x,(_FreqRegTab,x)
4796  033f 89            	pushw	x
4797  0340 7b08          	ld	a,(OFST+1,sp)
4798  0342 5f            	clrw	x
4799  0343 97            	ld	xl,a
4800  0344 d60000        	ld	a,(_FreqRegAddrTab,x)
4801  0347 cd0147        	call	_PrfWrReg16
4803  034a 85            	popw	x
4804                     ; 357 	for(i=0;i<3;i++)
4806  034b 0c06          	inc	(OFST-1,sp)
4809  034d 7b06          	ld	a,(OFST-1,sp)
4810  034f a103          	cp	a,#3
4811  0351 25d9          	jrult	L5032
4812                     ; 361 	freqTemp++;	
4814  0353 3c6a          	inc	L5222_freqTemp
4815                     ; 362 	if(freqTemp > 4)
4817  0355 b66a          	ld	a,L5222_freqTemp
4818  0357 a105          	cp	a,#5
4819  0359 2502          	jrult	L3132
4820                     ; 364 		freqTemp =0;
4822  035b 3f6a          	clr	L5222_freqTemp
4823  035d               L3132:
4824                     ; 366 }
4827  035d 5b07          	addw	sp,#7
4828  035f 81            	ret
4951                     	xdef	_PrfRegRd16
4952                     	xdef	_PrfWrReg16
4953                     	xdef	_SpiRd16
4954                     	xdef	_SpiRd8
4955                     	xdef	_SpiWr8
4956                     	xdef	_PrfRegTab
4957                     	xdef	_PrfRegAddrTab
4958                     	xdef	_FreqRegTab
4959                     	xdef	_FreqRegAddrTab
4960                     	switch	.ubsct
4961  0000               _tempData2:
4962  0000 00            	ds.b	1
4963                     	xdef	_tempData2
4964  0001               _tempData1:
4965  0001 00            	ds.b	1
4966                     	xdef	_tempData1
4967  0002               _irData:
4968  0002 00000000      	ds.b	4
4969                     	xdef	_irData
4970  0006               _RfDataBuff:
4971  0006 000000000000  	ds.b	11
4972                     	xdef	_RfDataBuff
4973  0011               _RfData:
4974  0011 000000000000  	ds.b	11
4975                     	xdef	_RfData
4976  001c               _sendNum:
4977  001c 00            	ds.b	1
4978                     	xdef	_sendNum
4979  001d               _ucCOMBuf:
4980  001d 000000000000  	ds.b	64
4981                     	xdef	_ucCOMBuf
4982                     	xdef	_f_FreqDeal
4983                     	xdef	_f_RfRecDeal
4984                     	xdef	_PL1167_Init
4985  005d               _testPL:
4986  005d 00            	ds.b	1
4987                     	xdef	_testPL
4988                     	xref	_TxComBuff
4989                     	xref	_LedInf
4990                     	xref	_f_Delay
4991                     	xref	_machineInf
5011                     	end
