   1                     ; C Compiler for STM8 (COSMIC Software)
   2                     ; Parser V4.8.32 - 23 Mar 2010
   3                     ; Generator V4.3.4 - 23 Mar 2010
3444                     	bsct
3445  0000               L1042_temp:
3446  0000 00            	dc.b	0
3507                     ; 14 void main(void)
3507                     ; 15 {
3509                     	switch	.text
3510  0000               _main:
3514                     ; 17 	f_Delay(3000);
3516  0000 ae0bb8        	ldw	x,#3000
3517  0003 cd0000        	call	_f_Delay
3519                     ; 18 	_DI();
3522  0006 9b            sim
3524                     ; 19 	f_pCpuInit();
3526  0007 cd0000        	call	_f_pCpuInit
3528                     ; 20 	f_pLedInit();
3530  000a cd0000        	call	_f_pLedInit
3532                     ; 21 	f_pUart1Init(UART1_BAUT_RATE);
3534  000d ae2580        	ldw	x,#9600
3535  0010 cd0000        	call	_f_pUart1Init
3537                     ; 22 	Cc2500Inf.RF_Channel[0] = 6;
3539  0013 35060000      	mov	_Cc2500Inf,#6
3540                     ; 23 	Cc2500Inf.RF_Channel[1] = 66;
3542  0017 35420001      	mov	_Cc2500Inf+1,#66
3543                     ; 24 	Cc2500Inf.RF_Channel[2] = 126;
3545  001b 357e0002      	mov	_Cc2500Inf+2,#126
3546                     ; 25 	Cc2500Inf.RF_Channel[3] = 186;
3548  001f 35ba0003      	mov	_Cc2500Inf+3,#186
3549                     ; 27 	f_pInitDataEeprom();
3551  0023 cd0000        	call	_f_pInitDataEeprom
3553                     ; 28 	f_Cc2500Init();
3555  0026 cd0000        	call	_f_Cc2500Init
3557                     ; 29 	_EI();
3560  0029 9a            rim
3562  002a               L7242:
3563                     ; 32 		f_pCpuFeedDog();
3565  002a cd0000        	call	_f_pCpuFeedDog
3567                     ; 33 		f_DealRXD();//RF接收处理201705
3569  002d cd0000        	call	_f_DealRXD
3571                     ; 35 		f_pUart1SendDeal(&machineInf);
3573  0030 ae0000        	ldw	x,#_machineInf
3574  0033 cd0000        	call	_f_pUart1SendDeal
3576                     ; 36 		f_pUart1ReceDeal(&machineInf);
3578  0036 ae0000        	ldw	x,#_machineInf
3579  0039 cd0000        	call	_f_pUart1ReceDeal
3581                     ; 37 		if(t1msFlag)
3583  003c c60000        	ld	a,_tTimeFlag
3584  003f a501          	bcp	a,#1
3585  0041 271c          	jreq	L3342
3586                     ; 39 			t1msFlag = 0;
3588  0043 72110000      	bres	_tTimeFlag,#0
3589                     ; 40 			if(tTime.t10msTask == 0)
3591  0047 725d0000      	tnz	_tTime
3592  004b 2603          	jrne	L5342
3593                     ; 42 				f_pUart1TimeCnt();
3595  004d cd0000        	call	_f_pUart1TimeCnt
3597  0050               L5342:
3598                     ; 44 			tTime.t10msTask++;
3600  0050 725c0000      	inc	_tTime
3601                     ; 45 			if(tTime.t10msTask>9)
3603  0054 c60000        	ld	a,_tTime
3604  0057 a10a          	cp	a,#10
3605  0059 2504          	jrult	L3342
3606                     ; 47 				tTime.t10msTask = 0;
3608  005b 725f0000      	clr	_tTime
3609  005f               L3342:
3610                     ; 50 		if(t10msFlag)
3612  005f c60000        	ld	a,_tTimeFlag
3613  0062 a502          	bcp	a,#2
3614  0064 272e          	jreq	L1442
3615                     ; 52 			t10msFlag = 0;
3617  0066 72130000      	bres	_tTimeFlag,#1
3618                     ; 53 			if(tTime.t100msTask == 0)
3620  006a 725d0002      	tnz	_tTime+2
3621  006e 260b          	jrne	L3442
3622                     ; 55 				f_pLedDeal(&machineInf);
3624  0070 ae0000        	ldw	x,#_machineInf
3625  0073 cd0000        	call	_f_pLedDeal
3627                     ; 56 				f_pLedDriveDeal();//LED底层驱动
3629  0076 cd0000        	call	_f_pLedDriveDeal
3632  0079 200a          	jra	L5442
3633  007b               L3442:
3634                     ; 58 			else if(tTime.t100msTask == 1)
3636  007b c60002        	ld	a,_tTime+2
3637  007e a101          	cp	a,#1
3638  0080 2603          	jrne	L5442
3639                     ; 60 				f_pWriteOneDataEeprom();	//EEPROM写入数据
3641  0082 cd0000        	call	_f_pWriteOneDataEeprom
3643  0085               L5442:
3644                     ; 62 			tTime.t100msTask++;
3646  0085 725c0002      	inc	_tTime+2
3647                     ; 63 			if(tTime.t100msTask>9)
3649  0089 c60002        	ld	a,_tTime+2
3650  008c a10a          	cp	a,#10
3651  008e 2504          	jrult	L1442
3652                     ; 65 				tTime.t100msTask = 0;
3654  0090 725f0002      	clr	_tTime+2
3655  0094               L1442:
3656                     ; 68 		if(t55msFlag)
3658  0094 c60000        	ld	a,_tTimeFlag
3659  0097 a540          	bcp	a,#64
3660                     ; 80 		if(t1sFlag)
3662  0099 c60000        	ld	a,_tTimeFlag
3663  009c a520          	bcp	a,#32
3664  009e 278a          	jreq	L7242
3665                     ; 82 			t1sFlag = 0; 
3667  00a0 721b0000      	bres	_tTimeFlag,#5
3668                     ; 83 			tTime.time1sCnt++; 
3670  00a4 725c0003      	inc	_tTime+3
3671                     ; 84 			if(tTime.time1sCnt > 0)
3673  00a8 725d0003      	tnz	_tTime+3
3674  00ac 2704          	jreq	L7542
3675                     ; 86 				tTime.time1sCnt = 0;
3677  00ae 725f0003      	clr	_tTime+3
3678  00b2               L7542:
3679                     ; 90 			if(LedInf.DryDisCnt > 0)
3681  00b2 725d0001      	tnz	_LedInf+1
3682  00b6 2704          	jreq	L1642
3683                     ; 92 				LedInf.DryDisCnt --;
3685  00b8 725a0001      	dec	_LedInf+1
3686  00bc               L1642:
3687                     ; 95 			Cc2500Inf.RF_Channel_Index++;
3689  00bc 725c0004      	inc	_Cc2500Inf+4
3690                     ; 96 			if(Cc2500Inf.RF_Channel_Index > 3)
3692  00c0 c60004        	ld	a,_Cc2500Inf+4
3693  00c3 a104          	cp	a,#4
3694  00c5 2504          	jrult	L3642
3695                     ; 98 				Cc2500Inf.RF_Channel_Index = 0;
3697  00c7 725f0004      	clr	_Cc2500Inf+4
3698  00cb               L3642:
3699                     ; 100  			SetCC2500_ChannelNumber(Cc2500Inf.RF_Channel[Cc2500Inf.RF_Channel_Index]);
3701  00cb c60004        	ld	a,_Cc2500Inf+4
3702  00ce 5f            	clrw	x
3703  00cf 97            	ld	xl,a
3704  00d0 d60000        	ld	a,(_Cc2500Inf,x)
3705  00d3 cd0000        	call	_SetCC2500_ChannelNumber
3707                     ; 101  			f_RxCC2500();
3709  00d6 cd0000        	call	_f_RxCC2500
3711                     ; 102 			t55msFlag = 0;
3713  00d9 721d0000      	bres	_tTimeFlag,#6
3714  00dd ac2a002a      	jpf	L7242
3727                     	xdef	_main
3728                     	xref	_f_pWriteOneDataEeprom
3729                     	xref	_f_pInitDataEeprom
3730                     	xref	_SetCC2500_ChannelNumber
3731                     	xref	_f_RxCC2500
3732                     	xref	_f_Cc2500Init
3733                     	xref	_Cc2500Inf
3734                     	xref	_f_DealRXD
3735                     	xref	_f_pUart1TimeCnt
3736                     	xref	_f_pUart1ReceDeal
3737                     	xref	_f_pUart1SendDeal
3738                     	xref	_f_pUart1Init
3739                     	xref	_f_pLedDriveDeal
3740                     	xref	_f_pLedDeal
3741                     	xref	_f_pLedInit
3742                     	xref	_LedInf
3743                     	xref	_f_Delay
3744                     	xref	_tTime
3745                     	xref	_tTimeFlag
3746                     	xref	_f_pCpuFeedDog
3747                     	xref	_f_pCpuInit
3748                     	switch	.bss
3749  0000               _machineInf:
3750  0000 000000000000  	ds.b	40
3751                     	xdef	_machineInf
3771                     	end
