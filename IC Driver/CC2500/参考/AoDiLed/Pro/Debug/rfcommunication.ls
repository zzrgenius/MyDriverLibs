   1                     ; C Compiler for STM8 (COSMIC Software)
   2                     ; Parser V4.8.32 - 23 Mar 2010
   3                     ; Generator V4.3.4 - 23 Mar 2010
2659                     ; 17 uchar f_AddTotalNum(uchar *nBuff,uchar nEndNo)
2659                     ; 18 {
2661                     	switch	.text
2662  0000               _f_AddTotalNum:
2664  0000 89            	pushw	x
2665  0001 89            	pushw	x
2666       00000002      OFST:	set	2
2669                     ; 20 	nTotalSum = 0;
2671  0002 0f01          	clr	(OFST-1,sp)
2672                     ; 21 	for(i = 0; i < nEndNo; i ++)
2674  0004 0f02          	clr	(OFST+0,sp)
2676  0006 2012          	jra	L1271
2677  0008               L5171:
2678                     ; 23 		nTotalSum += nBuff[i];
2680  0008 7b03          	ld	a,(OFST+1,sp)
2681  000a 97            	ld	xl,a
2682  000b 7b04          	ld	a,(OFST+2,sp)
2683  000d 1b02          	add	a,(OFST+0,sp)
2684  000f 2401          	jrnc	L6
2685  0011 5c            	incw	x
2686  0012               L6:
2687  0012 02            	rlwa	x,a
2688  0013 7b01          	ld	a,(OFST-1,sp)
2689  0015 fb            	add	a,(x)
2690  0016 6b01          	ld	(OFST-1,sp),a
2691                     ; 21 	for(i = 0; i < nEndNo; i ++)
2693  0018 0c02          	inc	(OFST+0,sp)
2694  001a               L1271:
2697  001a 7b02          	ld	a,(OFST+0,sp)
2698  001c 1107          	cp	a,(OFST+5,sp)
2699  001e 25e8          	jrult	L5171
2700                     ; 25 	return nTotalSum;
2702  0020 7b01          	ld	a,(OFST-1,sp)
2705  0022 5b04          	addw	sp,#4
2706  0024 81            	ret
2743                     ; 47 void f_StartDataSend(void)
2743                     ; 48 {
2744                     	switch	.text
2745  0025               _f_StartDataSend:
2747  0025 88            	push	a
2748       00000001      OFST:	set	1
2751                     ; 51 	if(!bSendFlag)																						//无发送数据返回
2753  0026 b642          	ld	a,_tComState
2754  0028 a504          	bcp	a,#4
2755  002a 2602          	jrne	L3471
2756                     ; 52 		return;
2759  002c 84            	pop	a
2760  002d 81            	ret
2761  002e               L3471:
2762                     ; 53 	j = TXD_TOTAL_BYTES - 1;
2764                     ; 54 	ucCOMBuf[j] = f_AddTotalNum(ucCOMBuf,j);
2766  002e 4b0b          	push	#11
2767  0030 ae0002        	ldw	x,#_ucCOMBuf
2768  0033 adcb          	call	_f_AddTotalNum
2770  0035 5b01          	addw	sp,#1
2771  0037 b70d          	ld	_ucCOMBuf+11,a
2772                     ; 55 	if (bSendFlag)																						//发送数据
2774  0039 b642          	ld	a,_tComState
2775  003b a504          	bcp	a,#4
2776                     ; 59 }
2779  003d 84            	pop	a
2780  003e 81            	ret
2823                     ; 67 void f_DealRXD(void)
2823                     ; 68 {
2824                     	switch	.text
2825  003f               _f_DealRXD:
2827  003f 88            	push	a
2828       00000001      OFST:	set	1
2831                     ; 70 	if (!bReceiveOverFlag)			/* 接收未完成，返回 */
2833  0040 b642          	ld	a,_tComState
2834  0042 a501          	bcp	a,#1
2835  0044 2602          	jrne	L5671
2836                     ; 71 		return;
2839  0046 84            	pop	a
2840  0047 81            	ret
2841  0048               L5671:
2842                     ; 72 	bReceiveOverFlag = 0;
2844  0048 72110042      	bres	_tComState,#0
2845                     ; 74 	j = RXD_TOTAL_BYTES - 1;
2847                     ; 75 	if(ucCOMBuf[j] != f_AddTotalNum(ucCOMBuf,j))
2849  004c 4b0b          	push	#11
2850  004e ae0002        	ldw	x,#_ucCOMBuf
2851  0051 adad          	call	_f_AddTotalNum
2853  0053 5b01          	addw	sp,#1
2854  0055 b10d          	cp	a,_ucCOMBuf+11
2855  0057 2705          	jreq	L7671
2856                     ; 77 		f_RxCC2500();
2858  0059 cd0000        	call	_f_RxCC2500
2860                     ; 78 		return;
2863  005c 84            	pop	a
2864  005d 81            	ret
2865  005e               L7671:
2866                     ; 80 	if(machineInf.addrInf.addrFlag == 0)
2868  005e c60025        	ld	a,_machineInf+37
2869  0061 a501          	bcp	a,#1
2870  0063 266e          	jrne	L1771
2871                     ; 82 		if( ucCOMBuf[1] == machineInf.AddressRf[0]
2871                     ; 83 		&& ucCOMBuf[2] == machineInf.AddressRf[1]
2871                     ; 84 		&& ucCOMBuf[3] == machineInf.AddressRf[2])
2873  0065 b603          	ld	a,_ucCOMBuf+1
2874  0067 c10022        	cp	a,_machineInf+34
2875  006a 267a          	jrne	L7002
2877  006c b604          	ld	a,_ucCOMBuf+2
2878  006e c10023        	cp	a,_machineInf+35
2879  0071 2673          	jrne	L7002
2881  0073 b605          	ld	a,_ucCOMBuf+3
2882  0075 c10024        	cp	a,_machineInf+36
2883  0078 266c          	jrne	L7002
2884                     ; 86 			if(ucCOMBuf[4] != sendNum)	//用于遥控器板接收识别码
2886  007a b606          	ld	a,_ucCOMBuf+4
2887  007c b101          	cp	a,_sendNum
2888  007e 2766          	jreq	L7002
2889                     ; 88 				sendNum = ucCOMBuf[4];
2891  0080 450601        	mov	_sendNum,_ucCOMBuf+4
2892                     ; 89 				if(ucCOMBuf[5] == 0x03)	//帧类型用于控制命令
2894  0083 b607          	ld	a,_ucCOMBuf+5
2895  0085 a103          	cp	a,#3
2896  0087 265d          	jrne	L7002
2897                     ; 91 					dataRecBuff++;
2899  0089 3c00          	inc	_dataRecBuff
2900                     ; 92 					TxComBuff.jSetSeatLevel = ucCOMBuf[6]>>4;
2902  008b b608          	ld	a,_ucCOMBuf+6
2903  008d 4e            	swap	a
2904  008e a40f          	and	a,#15
2905  0090 c70003        	ld	_TxComBuff+3,a
2906                     ; 93 					TxComBuff.jSetWaterLevel = ucCOMBuf[6]&0x0f; 
2908  0093 b608          	ld	a,_ucCOMBuf+6
2909  0095 a40f          	and	a,#15
2910  0097 c70001        	ld	_TxComBuff+1,a
2911                     ; 94 					TxComBuff.jSetDryLevel = ucCOMBuf[7]&0x0f; 
2913  009a b609          	ld	a,_ucCOMBuf+7
2914  009c a40f          	and	a,#15
2915  009e c70002        	ld	_TxComBuff+2,a
2916                     ; 95 					TxComBuff.jLevelState = ucCOMBuf[8]>>4;
2918  00a1 b60a          	ld	a,_ucCOMBuf+8
2919  00a3 4e            	swap	a
2920  00a4 a40f          	and	a,#15
2921  00a6 c70005        	ld	_TxComBuff+5,a
2922                     ; 96 					TxComBuff.jPosState = ucCOMBuf[8]&0x0f; 
2924  00a9 b60a          	ld	a,_ucCOMBuf+8
2925  00ab a40f          	and	a,#15
2926  00ad c70004        	ld	_TxComBuff+4,a
2927                     ; 97 					TxComBuff.jFunCmd = ucCOMBuf[10];
2929  00b0 55000c0006    	mov	_TxComBuff+6,_ucCOMBuf+10
2930                     ; 98 					if(TxComBuff.jFunCmd == 0x08)
2932  00b5 c60006        	ld	a,_TxComBuff+6
2933  00b8 a108          	cp	a,#8
2934  00ba 2606          	jrne	L1002
2935                     ; 100 						LedInf.delayDrytDis = true;
2937  00bc 72120002      	bset	_LedInf+2,#1
2939  00c0 2024          	jra	L7002
2940  00c2               L1002:
2941                     ; 104 					else if(TxComBuff.jFunCmd == 0x07)
2943  00c2 c60006        	ld	a,_TxComBuff+6
2944  00c5 a107          	cp	a,#7
2945  00c7 261d          	jrne	L7002
2946                     ; 106 						LedInf.delayDrytDis = false;
2948  00c9 72130002      	bres	_LedInf+2,#1
2949                     ; 107 						LedInf.DryDisCnt = 0;// 延时10S
2951  00cd 725f0001      	clr	_LedInf+1
2952  00d1 2013          	jra	L7002
2953  00d3               L1771:
2954                     ; 115 		machineInf.AddressRf[0] = ucCOMBuf[1];
2956  00d3 5500030022    	mov	_machineInf+34,_ucCOMBuf+1
2957                     ; 116 		machineInf.AddressRf[1] = ucCOMBuf[2];
2959  00d8 5500040023    	mov	_machineInf+35,_ucCOMBuf+2
2960                     ; 117 		machineInf.AddressRf[2] = ucCOMBuf[3];
2962  00dd 5500050024    	mov	_machineInf+36,_ucCOMBuf+3
2963                     ; 118 		machineInf.addrInf.addrFlag = 0;
2965  00e2 72110025      	bres	_machineInf+37,#0
2966  00e6               L7002:
2967                     ; 120 	f_RxCC2500();
2969  00e6 cd0000        	call	_f_RxCC2500
2971                     ; 121 }
2974  00e9 84            	pop	a
2975  00ea 81            	ret
3006                     ; 128 IT_HEADE void PBExtInterrupt(void)
3006                     ; 129 {
3008                     	switch	.text
3009  00eb               f_PBExtInterrupt:
3011  00eb 3b0002        	push	c_x+2
3012  00ee be00          	ldw	x,c_x
3013  00f0 89            	pushw	x
3014  00f1 3b0002        	push	c_y+2
3015  00f4 be00          	ldw	x,c_y
3016  00f6 89            	pushw	x
3017  00f7 be02          	ldw	x,c_lreg+2
3018  00f9 89            	pushw	x
3019  00fa be00          	ldw	x,c_lreg
3020  00fc 89            	pushw	x
3023                     ; 130 	if((EXTI_CR1  & 0x08) == 0x08)//下降沿有效
3025  00fd c650a0        	ld	a,_EXTI_CR1
3026  0100 a408          	and	a,#8
3027  0102 a108          	cp	a,#8
3028  0104 263c          	jrne	L1202
3029                     ; 132 		if(PBI_5==0)
3031  0106 c65006        	ld	a,_PB_IDR
3032  0109 a520          	bcp	a,#32
3033  010b 2635          	jrne	L1202
3034                     ; 134 			NOP();NOP();NOP();NOP();
3037  010d 9d            NOP
3042  010e 9d            NOP
3047  010f 9d            NOP
3052  0110 9d            NOP
3054                     ; 135 			if(PBI_5==0)
3056  0111 c65006        	ld	a,_PB_IDR
3057  0114 a520          	bcp	a,#32
3058  0116 262a          	jrne	L1202
3059                     ; 137 				if (bSendFlag)	
3061  0118 b642          	ld	a,_tComState
3062  011a a504          	bcp	a,#4
3063  011c 2709          	jreq	L7202
3064                     ; 139 					bSendFlag = 0;	
3066  011e 72150042      	bres	_tComState,#2
3067                     ; 140 					f_RxCC2500(); 	
3069  0122 cd0000        	call	_f_RxCC2500
3072  0125 201b          	jra	L1202
3073  0127               L7202:
3074                     ; 144 					if(halRfReceivePacket(&ucCOMBuf[1], &ucCOMBuf[0]) == 1)
3076  0127 ae0002        	ldw	x,#_ucCOMBuf
3077  012a 89            	pushw	x
3078  012b ae0003        	ldw	x,#_ucCOMBuf+1
3079  012e cd0000        	call	_halRfReceivePacket
3081  0131 85            	popw	x
3082  0132 a101          	cp	a,#1
3083  0134 260c          	jrne	L1202
3084                     ; 146 						bReceiveOverFlag = 1;  
3086  0136 72100042      	bset	_tComState,#0
3087                     ; 147 						Cc2500Inf.nCC2500Time1 = 0;
3089  013a 725f0006      	clr	_Cc2500Inf+6
3090                     ; 148 						Cc2500Inf.nCC2500Time2 = 0;
3092  013e 5f            	clrw	x
3093  013f cf0007        	ldw	_Cc2500Inf+7,x
3094  0142               L1202:
3095                     ; 154 }
3098  0142 85            	popw	x
3099  0143 bf00          	ldw	c_lreg,x
3100  0145 85            	popw	x
3101  0146 bf02          	ldw	c_lreg+2,x
3102  0148 85            	popw	x
3103  0149 bf00          	ldw	c_y,x
3104  014b 320002        	pop	c_y+2
3105  014e 85            	popw	x
3106  014f bf00          	ldw	c_x,x
3107  0151 320002        	pop	c_x+2
3108  0154 80            	iret
3271                     	xdef	f_PBExtInterrupt
3272                     	switch	.ubsct
3273  0000               _dataRecBuff:
3274  0000 00            	ds.b	1
3275                     	xdef	_dataRecBuff
3276                     	xdef	_f_StartDataSend
3277                     	xdef	_f_AddTotalNum
3278  0001               _sendNum:
3279  0001 00            	ds.b	1
3280                     	xdef	_sendNum
3281  0002               _ucCOMBuf:
3282  0002 000000000000  	ds.b	64
3283                     	xdef	_ucCOMBuf
3284  0042               _tComState:
3285  0042 00            	ds.b	1
3286                     	xdef	_tComState
3287                     	xref	_f_RxCC2500
3288                     	xref	_halRfReceivePacket
3289                     	xref	_Cc2500Inf
3290                     	xdef	_f_DealRXD
3291                     	xref	_TxComBuff
3292                     	xref	_LedInf
3293                     	xref	_machineInf
3294                     	xref.b	c_lreg
3295                     	xref.b	c_x
3296                     	xref.b	c_y
3316                     	end
