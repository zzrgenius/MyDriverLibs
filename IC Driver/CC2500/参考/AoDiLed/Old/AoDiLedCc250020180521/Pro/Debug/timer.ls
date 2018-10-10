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
2934                     ; 29 IT_HEADE void TIM1_OverFlowIRQHandler(void)//100us
2934                     ; 30 { 
2936                     	switch	.text
2937  0018               f_TIM1_OverFlowIRQHandler:
2939  0018 be02          	ldw	x,c_lreg+2
2940  001a 89            	pushw	x
2941  001b be00          	ldw	x,c_lreg
2942  001d 89            	pushw	x
2945                     ; 31 	TIM1_SR1 &= (~0x01);
2947  001e 72115255      	bres	_TIM1_SR1,#0
2948                     ; 32 	TIM1_SR2 = 0;
2950  0022 725f5256      	clr	_TIM1_SR2
2951                     ; 33 	t1msFlag = 1;
2953  0026 7210000c      	bset	_tTimeFlag,#0
2954                     ; 34 	tTime.time10msCnt++;
2956  002a 725c0005      	inc	_tTime+5
2957                     ; 35 	tTime.time55msCnt++;
2959  002e 725c0001      	inc	_tTime+1
2960                     ; 36 	tTime.time200msCnt++;
2962  0032 725c0007      	inc	_tTime+7
2963                     ; 37 	tTime.time500msCnt++;
2965  0036 ce0008        	ldw	x,_tTime+8
2966  0039 1c0001        	addw	x,#1
2967  003c cf0008        	ldw	_tTime+8,x
2968                     ; 38 	tTime.time1000msCnt++;
2970  003f ce000a        	ldw	x,_tTime+10
2971  0042 1c0001        	addw	x,#1
2972  0045 cf000a        	ldw	_tTime+10,x
2973                     ; 40 	if(tTime.time10msCnt > 9)//10ms
2975  0048 c60005        	ld	a,_tTime+5
2976  004b a10a          	cp	a,#10
2977  004d 2508          	jrult	L3502
2978                     ; 42 		tTime.time10msCnt = 0;
2980  004f 725f0005      	clr	_tTime+5
2981                     ; 43 		t10msFlag = 1;   
2983  0053 7212000c      	bset	_tTimeFlag,#1
2984  0057               L3502:
2985                     ; 45 	if(tTime.time55msCnt > 44)//55ms
2987  0057 c60001        	ld	a,_tTime+1
2988  005a a12d          	cp	a,#45
2989  005c 2508          	jrult	L5502
2990                     ; 47 		t55msFlag = 1;  
2992  005e 721c000c      	bset	_tTimeFlag,#6
2993                     ; 48 		tTime.time55msCnt = 0;
2995  0062 725f0001      	clr	_tTime+1
2996  0066               L5502:
2997                     ; 50 	if(tTime.time200msCnt >199)//200ms
2999  0066 c60007        	ld	a,_tTime+7
3000  0069 a1c8          	cp	a,#200
3001  006b 250c          	jrult	L7502
3002                     ; 52 		tTime.time200msCnt = 0;
3004  006d 725f0007      	clr	_tTime+7
3005                     ; 53 		LedPowerFlickS ^= true;
3007  0071 90100000      	bcpl	_LedDisFlickS,#0
3008                     ; 54 		t200msFlag = 1;    
3010  0075 7216000c      	bset	_tTimeFlag,#3
3011  0079               L7502:
3012                     ; 56 	if(tTime.time500msCnt >499)//500ms
3014  0079 ce0008        	ldw	x,_tTime+8
3015  007c a301f4        	cpw	x,#500
3016  007f 2518          	jrult	L1602
3017                     ; 58 		tTime.time500msCnt= 0;
3019  0081 5f            	clrw	x
3020  0082 cf0008        	ldw	_tTime+8,x
3021                     ; 59 		t500msFlag = 1;   
3023  0085 7218000c      	bset	_tTimeFlag,#4
3024                     ; 60 		LedWaterRFlickS ^=true;
3026  0089 90140000      	bcpl	_LedDisFlickS,#2
3027                     ; 61 		LedWaterBFlickS ^=true;
3029  008d 90160000      	bcpl	_LedDisFlickS,#3
3030                     ; 62 		LedWaterGFlickS ^=true;
3032  0091 90180000      	bcpl	_LedDisFlickS,#4
3033                     ; 63 		LedDryRFlickS ^=true;
3035  0095 901a0000      	bcpl	_LedDisFlickS,#5
3036  0099               L1602:
3037                     ; 65 	if(tTime.time1000msCnt > 999)//1000ms
3039  0099 ce000a        	ldw	x,_tTime+10
3040  009c a303e8        	cpw	x,#1000
3041  009f 2508          	jrult	L3602
3042                     ; 67 		tTime.time1000msCnt = 0;
3044  00a1 5f            	clrw	x
3045  00a2 cf000a        	ldw	_tTime+10,x
3046                     ; 68 		t1sFlag = 1; 
3048  00a5 721a000c      	bset	_tTimeFlag,#5
3049  00a9               L3602:
3050                     ; 70 }
3053  00a9 85            	popw	x
3054  00aa bf00          	ldw	c_lreg,x
3055  00ac 85            	popw	x
3056  00ad bf02          	ldw	c_lreg+2,x
3057  00af 80            	iret
3069                     	xref	_LedDisFlickS
3070                     	xdef	f_TIM1_OverFlowIRQHandler
3071                     	xdef	_f_Delay
3072                     	switch	.bss
3073  0000               _tTime:
3074  0000 000000000000  	ds.b	12
3075                     	xdef	_tTime
3076  000c               _tTimeFlag:
3077  000c 00            	ds.b	1
3078                     	xdef	_tTimeFlag
3079                     	xref.b	c_lreg
3099                     	end
