   1                     ; C Compiler for STM8 (COSMIC Software)
   2                     ; Parser V4.8.32 - 23 Mar 2010
   3                     ; Generator V4.3.4 - 23 Mar 2010
3397                     	bsct
3398  0000               L5532_temp:
3399  0000 00            	dc.b	0
3460                     ; 14 void main(void)
3460                     ; 15 {
3462                     	switch	.text
3463  0000               _main:
3467                     ; 17 	f_Delay(3000);
3469  0000 ae0bb8        	ldw	x,#3000
3470  0003 cd0000        	call	_f_Delay
3472                     ; 18 	_DI();
3475  0006 9b            sim
3477                     ; 19 	f_pCpuInit();
3479  0007 cd0000        	call	_f_pCpuInit
3481                     ; 20 	f_pLedInit();
3483  000a cd0000        	call	_f_pLedInit
3485                     ; 21 	f_pUart1Init(UART1_BAUT_RATE);
3487  000d ae2580        	ldw	x,#9600
3488  0010 cd0000        	call	_f_pUart1Init
3490                     ; 22 	Cc2500Inf.RF_Channel[0] = 6;
3492  0013 35060000      	mov	_Cc2500Inf,#6
3493                     ; 23 	Cc2500Inf.RF_Channel[1] = 66;
3495  0017 35420001      	mov	_Cc2500Inf+1,#66
3496                     ; 24 	Cc2500Inf.RF_Channel[2] = 126;
3498  001b 357e0002      	mov	_Cc2500Inf+2,#126
3499                     ; 25 	Cc2500Inf.RF_Channel[3] = 186;
3501  001f 35ba0003      	mov	_Cc2500Inf+3,#186
3502                     ; 27 	f_pInitDataEeprom();
3504  0023 cd0000        	call	_f_pInitDataEeprom
3506                     ; 28 	f_Cc2500Init();
3508  0026 cd0000        	call	_f_Cc2500Init
3510                     ; 29 	_EI();
3513  0029 9a            rim
3515  002a               L3042:
3516                     ; 32 		f_pCpuFeedDog();
3518  002a cd0000        	call	_f_pCpuFeedDog
3520                     ; 33 		f_DealRXD();//RF接收处理201705
3522  002d cd0000        	call	_f_DealRXD
3524                     ; 35 		f_pUart1SendDeal(&machineInf);
3526  0030 ae0000        	ldw	x,#_machineInf
3527  0033 cd0000        	call	_f_pUart1SendDeal
3529                     ; 36 		f_pUart1ReceDeal(&machineInf);
3531  0036 ae0000        	ldw	x,#_machineInf
3532  0039 cd0000        	call	_f_pUart1ReceDeal
3534                     ; 37 		if(t1msFlag)
3536  003c c60000        	ld	a,_tTimeFlag
3537  003f a501          	bcp	a,#1
3538  0041 271c          	jreq	L7042
3539                     ; 39 			t1msFlag = 0;
3541  0043 72110000      	bres	_tTimeFlag,#0
3542                     ; 40 			if(tTime.t10msTask == 0)
3544  0047 725d0000      	tnz	_tTime
3545  004b 2603          	jrne	L1142
3546                     ; 42 				f_pUart1TimeCnt();
3548  004d cd0000        	call	_f_pUart1TimeCnt
3550  0050               L1142:
3551                     ; 44 			tTime.t10msTask++;
3553  0050 725c0000      	inc	_tTime
3554                     ; 45 			if(tTime.t10msTask>9)
3556  0054 c60000        	ld	a,_tTime
3557  0057 a10a          	cp	a,#10
3558  0059 2504          	jrult	L7042
3559                     ; 47 				tTime.t10msTask = 0;
3561  005b 725f0000      	clr	_tTime
3562  005f               L7042:
3563                     ; 50 		if(t10msFlag)
3565  005f c60000        	ld	a,_tTimeFlag
3566  0062 a502          	bcp	a,#2
3567  0064 272e          	jreq	L5142
3568                     ; 52 			t10msFlag = 0;
3570  0066 72130000      	bres	_tTimeFlag,#1
3571                     ; 53 			if(tTime.t100msTask == 0)
3573  006a 725d0002      	tnz	_tTime+2
3574  006e 260b          	jrne	L7142
3575                     ; 55 				f_pLedDeal(&machineInf);
3577  0070 ae0000        	ldw	x,#_machineInf
3578  0073 cd0000        	call	_f_pLedDeal
3580                     ; 56 				f_pLedDriveDeal();//LED底层驱动
3582  0076 cd0000        	call	_f_pLedDriveDeal
3585  0079 200a          	jra	L1242
3586  007b               L7142:
3587                     ; 58 			else if(tTime.t100msTask == 1)
3589  007b c60002        	ld	a,_tTime+2
3590  007e a101          	cp	a,#1
3591  0080 2603          	jrne	L1242
3592                     ; 60 				f_pWriteOneDataEeprom();	//EEPROM写入数据
3594  0082 cd0000        	call	_f_pWriteOneDataEeprom
3596  0085               L1242:
3597                     ; 62 			tTime.t100msTask++;
3599  0085 725c0002      	inc	_tTime+2
3600                     ; 63 			if(tTime.t100msTask>9)
3602  0089 c60002        	ld	a,_tTime+2
3603  008c a10a          	cp	a,#10
3604  008e 2504          	jrult	L5142
3605                     ; 65 				tTime.t100msTask = 0;
3607  0090 725f0002      	clr	_tTime+2
3608  0094               L5142:
3609                     ; 68 		if(t55msFlag)
3611  0094 c60000        	ld	a,_tTimeFlag
3612  0097 a540          	bcp	a,#64
3613                     ; 80 		if(t1sFlag)
3615  0099 c60000        	ld	a,_tTimeFlag
3616  009c a520          	bcp	a,#32
3617  009e 278a          	jreq	L3042
3618                     ; 82 			t1sFlag = 0; 
3620  00a0 721b0000      	bres	_tTimeFlag,#5
3621                     ; 83 			tTime.time1sCnt++; 
3623  00a4 725c0003      	inc	_tTime+3
3624                     ; 84 			if(tTime.time1sCnt > 0)
3626  00a8 725d0003      	tnz	_tTime+3
3627  00ac 2704          	jreq	L3342
3628                     ; 86 				tTime.time1sCnt = 0;
3630  00ae 725f0003      	clr	_tTime+3
3631  00b2               L3342:
3632                     ; 90 			if(LedInf.DryDisCnt > 0)
3634  00b2 725d0001      	tnz	_LedInf+1
3635  00b6 2704          	jreq	L5342
3636                     ; 92 				LedInf.DryDisCnt --;
3638  00b8 725a0001      	dec	_LedInf+1
3639  00bc               L5342:
3640                     ; 95 			Cc2500Inf.RF_Channel_Index++;
3642  00bc 725c0004      	inc	_Cc2500Inf+4
3643                     ; 96 			if(Cc2500Inf.RF_Channel_Index > 3)
3645  00c0 c60004        	ld	a,_Cc2500Inf+4
3646  00c3 a104          	cp	a,#4
3647  00c5 2504          	jrult	L7342
3648                     ; 98 				Cc2500Inf.RF_Channel_Index = 0;
3650  00c7 725f0004      	clr	_Cc2500Inf+4
3651  00cb               L7342:
3652                     ; 100  			SetCC2500_ChannelNumber(Cc2500Inf.RF_Channel[Cc2500Inf.RF_Channel_Index]);
3654  00cb c60004        	ld	a,_Cc2500Inf+4
3655  00ce 5f            	clrw	x
3656  00cf 97            	ld	xl,a
3657  00d0 d60000        	ld	a,(_Cc2500Inf,x)
3658  00d3 cd0000        	call	_SetCC2500_ChannelNumber
3660                     ; 101  			f_RxCC2500();
3662  00d6 cd0000        	call	_f_RxCC2500
3664                     ; 102 			t55msFlag = 0;
3666  00d9 721d0000      	bres	_tTimeFlag,#6
3667  00dd ac2a002a      	jpf	L3042
3680                     	xdef	_main
3681                     	xref	_f_pWriteOneDataEeprom
3682                     	xref	_f_pInitDataEeprom
3683                     	xref	_SetCC2500_ChannelNumber
3684                     	xref	_f_RxCC2500
3685                     	xref	_f_Cc2500Init
3686                     	xref	_Cc2500Inf
3687                     	xref	_f_DealRXD
3688                     	xref	_f_pUart1TimeCnt
3689                     	xref	_f_pUart1ReceDeal
3690                     	xref	_f_pUart1SendDeal
3691                     	xref	_f_pUart1Init
3692                     	xref	_f_pLedDriveDeal
3693                     	xref	_f_pLedDeal
3694                     	xref	_f_pLedInit
3695                     	xref	_LedInf
3696                     	xref	_f_Delay
3697                     	xref	_tTime
3698                     	xref	_tTimeFlag
3699                     	xref	_f_pCpuFeedDog
3700                     	xref	_f_pCpuInit
3701                     	switch	.bss
3702  0000               _machineInf:
3703  0000 000000000000  	ds.b	39
3704                     	xdef	_machineInf
3724                     	end
