   1                     ; C Compiler for STM8 (COSMIC Software)
   2                     ; Parser V4.8.32 - 23 Mar 2010
   3                     ; Generator V4.3.4 - 23 Mar 2010
2868                     ; 9 void f_Delay(uint rTime)
2868                     ; 10 {
2870                     	switch	.text
2871  0000               _f_Delay:
2873  0000 89            	pushw	x
2874  0001 89            	pushw	x
2875       00000002      OFST:	set	2
2878                     ; 12 	for(i =0; i < rTime;i++)
2880  0002 5f            	clrw	x
2881  0003 1f01          	ldw	(OFST-1,sp),x
2883  0005 2008          	jra	L7302
2884  0007               L3302:
2885                     ; 14 		NOP();
2888  0007 9d            NOP
2890                     ; 12 	for(i =0; i < rTime;i++)
2892  0008 1e01          	ldw	x,(OFST-1,sp)
2893  000a 1c0001        	addw	x,#1
2894  000d 1f01          	ldw	(OFST-1,sp),x
2895  000f               L7302:
2898  000f 1e01          	ldw	x,(OFST-1,sp)
2899  0011 1303          	cpw	x,(OFST+1,sp)
2900  0013 25f2          	jrult	L3302
2901                     ; 16 }
2904  0015 5b04          	addw	sp,#4
2905  0017 81            	ret
2935                     ; 29 IT_HEADE void TIM1_OverFlowIRQHandler(void)//100us
2935                     ; 30 { 
2937                     	switch	.text
2938  0018               f_TIM1_OverFlowIRQHandler:
2940  0018 be02          	ldw	x,c_lreg+2
2941  001a 89            	pushw	x
2942  001b be00          	ldw	x,c_lreg
2943  001d 89            	pushw	x
2946                     ; 31 	TIM1_SR1 &= (~0x01);
2948  001e 72115255      	bres	_TIM1_SR1,#0
2949                     ; 32 	TIM1_SR2 = 0;
2951  0022 725f5256      	clr	_TIM1_SR2
2952                     ; 33 	t1msFlag = 1;
2954  0026 7210000c      	bset	_tTimeFlag,#0
2955                     ; 34 	tTime.time10msCnt++;
2957  002a 725c0005      	inc	_tTime+5
2958                     ; 35 	tTime.time55msCnt++;
2960  002e 725c0001      	inc	_tTime+1
2961                     ; 36 	tTime.time200msCnt++;
2963  0032 725c0007      	inc	_tTime+7
2964                     ; 37 	tTime.time500msCnt++;
2966  0036 ce0008        	ldw	x,_tTime+8
2967  0039 1c0001        	addw	x,#1
2968  003c cf0008        	ldw	_tTime+8,x
2969                     ; 38 	tTime.time1000msCnt++;
2971  003f ce000a        	ldw	x,_tTime+10
2972  0042 1c0001        	addw	x,#1
2973  0045 cf000a        	ldw	_tTime+10,x
2974                     ; 40 	if(tTime.time10msCnt > 9)//10ms
2976  0048 c60005        	ld	a,_tTime+5
2977  004b a10a          	cp	a,#10
2978  004d 2508          	jrult	L3502
2979                     ; 42 		tTime.time10msCnt = 0;
2981  004f 725f0005      	clr	_tTime+5
2982                     ; 43 		t10msFlag = 1;   
2984  0053 7212000c      	bset	_tTimeFlag,#1
2985  0057               L3502:
2986                     ; 45 	if(tTime.time55msCnt > 44)//55ms
2988  0057 c60001        	ld	a,_tTime+1
2989  005a a12d          	cp	a,#45
2990  005c 2508          	jrult	L5502
2991                     ; 47 		t55msFlag = 1;  
2993  005e 721c000c      	bset	_tTimeFlag,#6
2994                     ; 48 		tTime.time55msCnt = 0;
2996  0062 725f0001      	clr	_tTime+1
2997  0066               L5502:
2998                     ; 50 	if(tTime.time200msCnt >199)//200ms
3000  0066 c60007        	ld	a,_tTime+7
3001  0069 a1c8          	cp	a,#200
3002  006b 250c          	jrult	L7502
3003                     ; 52 		tTime.time200msCnt = 0;
3005  006d 725f0007      	clr	_tTime+7
3006                     ; 53 		LedPowerFlickS ^= true;
3008  0071 90100000      	bcpl	_LedDisFlickS,#0
3009                     ; 54 		t200msFlag = 1;    
3011  0075 7216000c      	bset	_tTimeFlag,#3
3012  0079               L7502:
3013                     ; 56 	if(tTime.time500msCnt >499)//500ms
3015  0079 ce0008        	ldw	x,_tTime+8
3016  007c a301f4        	cpw	x,#500
3017  007f 2524          	jrult	L1602
3018                     ; 58 		tTime.time500msCnt= 0;
3020  0081 5f            	clrw	x
3021  0082 cf0008        	ldw	_tTime+8,x
3022                     ; 59 		t500msFlag = 1;  
3024  0085 7218000c      	bset	_tTimeFlag,#4
3025                     ; 60 		LedWaterBFlickS ^= true;
3027  0089 90160000      	bcpl	_LedDisFlickS,#3
3028                     ; 61 		LedWaterGFlickS ^= true;
3030  008d 90180000      	bcpl	_LedDisFlickS,#4
3031                     ; 62 		LedWaterRFlickS ^= true;
3033  0091 90140000      	bcpl	_LedDisFlickS,#2
3034                     ; 64 		LedDryBFlickS ^= true;
3036  0095 901c0000      	bcpl	_LedDisFlickS,#6
3037                     ; 65 		LedDryGFlickS ^= true;
3039  0099 901e0000      	bcpl	_LedDisFlickS,#7
3040                     ; 66 		LedDryRFlickS ^= true;
3042  009d 901a0000      	bcpl	_LedDisFlickS,#5
3043                     ; 68 		LedPower500mss ^= true;
3045  00a1 90100000      	bcpl	_LedDisPower500S,#0
3046  00a5               L1602:
3047                     ; 70 	if(tTime.time1000msCnt > 999)//1000ms
3049  00a5 ce000a        	ldw	x,_tTime+10
3050  00a8 a303e8        	cpw	x,#1000
3051  00ab 2508          	jrult	L3602
3052                     ; 72 		tTime.time1000msCnt = 0;
3054  00ad 5f            	clrw	x
3055  00ae cf000a        	ldw	_tTime+10,x
3056                     ; 73 		t1sFlag = 1; 
3058  00b1 721a000c      	bset	_tTimeFlag,#5
3059  00b5               L3602:
3060                     ; 75 }
3063  00b5 85            	popw	x
3064  00b6 bf00          	ldw	c_lreg,x
3065  00b8 85            	popw	x
3066  00b9 bf02          	ldw	c_lreg+2,x
3067  00bb 80            	iret
3079                     	xref	_LedDisPower500S
3080                     	xref	_LedDisFlickS
3081                     	xdef	f_TIM1_OverFlowIRQHandler
3082                     	xdef	_f_Delay
3083                     	switch	.bss
3084  0000               _tTime:
3085  0000 000000000000  	ds.b	12
3086                     	xdef	_tTime
3087  000c               _tTimeFlag:
3088  000c 00            	ds.b	1
3089                     	xdef	_tTimeFlag
3090                     	xref.b	c_lreg
3110                     	end
