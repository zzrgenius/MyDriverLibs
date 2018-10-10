   1                     ; C Compiler for STM8 (COSMIC Software)
   2                     ; Parser V4.8.32 - 23 Mar 2010
   3                     ; Generator V4.3.4 - 23 Mar 2010
2827                     	bsct
2828  0000               L5102_LedInitCnt:
2829  0000 00            	dc.b	0
2830  0001               L7102_LedNoWatrFlag:
2831  0001 00            	dc.b	0
2832  0002               L1202_LedNoWaterCnt:
2833  0002 00            	dc.b	0
3682                     ; 66 void f_pLedDeal(BIG_STRUCT *pFuctionData)
3682                     ; 67 {
3684                     	switch	.text
3685  0000               _f_pLedDeal:
3687  0000 89            	pushw	x
3688       00000000      OFST:	set	0
3691                     ; 71 	if((pFuctionData->bInitInf== rSYS_INIT_NO) || (pFuctionData->bInitInf == rSYS_INIT_HLAF))
3693  0001 7d            	tnz	(x)
3694  0002 2705          	jreq	L3552
3696  0004 f6            	ld	a,(x)
3697  0005 a101          	cp	a,#1
3698  0007 2648          	jrne	L1552
3699  0009               L3552:
3700                     ; 73 		LedPowerIcon = true;
3702  0009 72100002      	bset	_LedDisIcon,#0
3703                     ; 74 		if(LedInitCnt < 29)
3705  000d b600          	ld	a,L5102_LedInitCnt
3706  000f a11d          	cp	a,#29
3707  0011 2420          	jruge	L5552
3708                     ; 76 			LedInitCnt++;
3710  0013 3c00          	inc	L5102_LedInitCnt
3711                     ; 77 			LedSeatIcon = true;
3713  0015 72120002      	bset	_LedDisIcon,#1
3714                     ; 78 			LedWaterRIcon = true;
3716  0019 72140002      	bset	_LedDisIcon,#2
3717                     ; 79 			LedWaterBIcon = true;
3719  001d 72160002      	bset	_LedDisIcon,#3
3720                     ; 80 			LedWaterGIcon = true;
3722  0021 72180002      	bset	_LedDisIcon,#4
3723                     ; 81 			LedDryRIcon = true;
3725  0025 721a0002      	bset	_LedDisIcon,#5
3726                     ; 82 			LedDryBIcon = true;
3728  0029 721c0002      	bset	_LedDisIcon,#6
3729                     ; 83 			LedDryGIcon = true;
3731  002d 721e0002      	bset	_LedDisIcon,#7
3733  0031 201c          	jra	L1652
3734  0033               L5552:
3735                     ; 87 			LedSeatIcon = false;
3737  0033 72130002      	bres	_LedDisIcon,#1
3738                     ; 88 			LedWaterRIcon = false;
3740  0037 72150002      	bres	_LedDisIcon,#2
3741                     ; 89 			LedWaterBIcon = false;
3743  003b 72170002      	bres	_LedDisIcon,#3
3744                     ; 90 			LedWaterGIcon = false;
3746  003f 72190002      	bres	_LedDisIcon,#4
3747                     ; 91 			LedDryRIcon = false;
3749  0043 721b0002      	bres	_LedDisIcon,#5
3750                     ; 92 			LedDryBIcon = false;
3752  0047 721d0002      	bres	_LedDisIcon,#6
3753                     ; 93 			LedDryGIcon = false;
3755  004b 721f0002      	bres	_LedDisIcon,#7
3756  004f               L1652:
3757                     ; 341 }
3760  004f 85            	popw	x
3761  0050 81            	ret
3762  0051               L1552:
3763                     ; 96 	else if(pFuctionData->bInitInf == rSYS_INIT_OK)
3765  0051 1e01          	ldw	x,(OFST+1,sp)
3766  0053 f6            	ld	a,(x)
3767  0054 a102          	cp	a,#2
3768  0056 26f7          	jrne	L1652
3769                     ; 98 		if(LedNoWatrFlag == 0)
3771  0058 3d01          	tnz	L7102_LedNoWatrFlag
3772  005a 2620          	jrne	L5652
3773                     ; 100 			if(pFuctionData->systemErrInf.flag.bNoWaterErr == true)
3775  005c 1e01          	ldw	x,(OFST+1,sp)
3776  005e e620          	ld	a,(32,x)
3777  0060 a508          	bcp	a,#8
3778  0062 2712          	jreq	L7652
3779                     ; 102 				LedNoWaterCnt++;
3781  0064 3c02          	inc	L1202_LedNoWaterCnt
3782                     ; 103 				LedPowerFlickF = true;
3784  0066 72100001      	bset	_LedDisFlickF,#0
3785                     ; 104 				if(LedNoWaterCnt > 32)
3787  006a b602          	ld	a,L1202_LedNoWaterCnt
3788  006c a121          	cp	a,#33
3789  006e 25df          	jrult	L1652
3790                     ; 106 					LedNoWatrFlag = 1;
3792  0070 35010001      	mov	L7102_LedNoWatrFlag,#1
3793  0074 20d9          	jra	L1652
3794  0076               L7652:
3795                     ; 111 				LedNoWatrFlag = 1;
3797  0076 35010001      	mov	L7102_LedNoWatrFlag,#1
3798  007a 20d3          	jra	L1652
3799  007c               L5652:
3800                     ; 116 			if(pFuctionData->SystemCurState == STANDBY_STATE)
3802  007c 1e01          	ldw	x,(OFST+1,sp)
3803  007e 6d01          	tnz	(1,x)
3804  0080 2606          	jrne	L7752
3805                     ; 118 				LedAllIcon = 0x00;
3807  0082 725f0002      	clr	_LedDisIcon
3809  0086 20c7          	jra	L1652
3810  0088               L7752:
3811                     ; 124 			else if(pFuctionData->SystemCurState == RUNNING_STATE)
3813  0088 1e01          	ldw	x,(OFST+1,sp)
3814  008a e601          	ld	a,(1,x)
3815  008c a101          	cp	a,#1
3816  008e 2703          	jreq	L6
3817  0090 cc02a1        	jp	L3062
3818  0093               L6:
3819                     ; 126 				if(pFuctionData->seatInf.SeatOffTm.hour >= 24)
3821  0093 1e01          	ldw	x,(OFST+1,sp)
3822  0095 9093          	ldw	y,x
3823  0097 90ee18        	ldw	y,(24,y)
3824  009a 90a30018      	cpw	y,#24
3825  009e 2506          	jrult	L5062
3826                     ; 128 					LedAllIcon = 0x00;
3828  00a0 725f0002      	clr	_LedDisIcon
3830  00a4 20a9          	jra	L1652
3831  00a6               L5062:
3832                     ; 132 					LedPowerIcon = true;
3834  00a6 72100002      	bset	_LedDisIcon,#0
3835                     ; 133 					if(pFuctionData->seatInf.seatSensorState.bSwitchState == SW_ON
3835                     ; 134 					||pFuctionData->seatInf.SwitchSeatEn == true
3835                     ; 135 					||pFuctionData->flushTimeState > 0)
3837  00aa 1e01          	ldw	x,(OFST+1,sp)
3838  00ac e61a          	ld	a,(26,x)
3839  00ae a501          	bcp	a,#1
3840  00b0 260e          	jrne	L3162
3842  00b2 1e01          	ldw	x,(OFST+1,sp)
3843  00b4 e611          	ld	a,(17,x)
3844  00b6 a501          	bcp	a,#1
3845  00b8 2606          	jrne	L3162
3847  00ba 1e01          	ldw	x,(OFST+1,sp)
3848  00bc 6d26          	tnz	(38,x)
3849  00be 2722          	jreq	L1162
3850  00c0               L3162:
3851                     ; 137 						LedSeatIcon = true;
3853  00c0 72120002      	bset	_LedDisIcon,#1
3855  00c4               L7162:
3856                     ; 143 					if(pFuctionData->heatInf.waterHeat.setWaterLevel == TEMP_OFF)
3858  00c4 1e01          	ldw	x,(OFST+1,sp)
3859  00c6 6d0d          	tnz	(13,x)
3860  00c8 2643          	jrne	L1262
3861                     ; 145 						if(pFuctionData->systemErrInf.flag.bNoWaterErr == true)
3863  00ca 1e01          	ldw	x,(OFST+1,sp)
3864  00cc e620          	ld	a,(32,x)
3865  00ce a508          	bcp	a,#8
3866  00d0 2716          	jreq	L3262
3867                     ; 147 							LedWaterRFlickF = true;
3869  00d2 72140001      	bset	_LedDisFlickF,#2
3870                     ; 148 							LedWaterBFlickF = true;
3872  00d6 72160001      	bset	_LedDisFlickF,#3
3873                     ; 149 							LedWaterGFlickF = true;
3875  00da 72180001      	bset	_LedDisFlickF,#4
3877  00de ac930193      	jpf	L3362
3878  00e2               L1162:
3879                     ; 141 						LedSeatIcon = false;
3881  00e2 72130002      	bres	_LedDisIcon,#1
3882  00e6 20dc          	jra	L7162
3883  00e8               L3262:
3884                     ; 153 							if(pFuctionData->WashInf.bTempChange == TEMP_NO_CHANGE)
3886  00e8 1e01          	ldw	x,(OFST+1,sp)
3887  00ea 6d1f          	tnz	(31,x)
3888  00ec 2610          	jrne	L7262
3889                     ; 155 								LedWaterRIcon = false;
3891  00ee 72150002      	bres	_LedDisIcon,#2
3892                     ; 156 								LedWaterBIcon = false;
3894  00f2 72170002      	bres	_LedDisIcon,#3
3895                     ; 157 								LedWaterGIcon = false;
3897  00f6 72190002      	bres	_LedDisIcon,#4
3899  00fa ac930193      	jpf	L3362
3900  00fe               L7262:
3901                     ; 161 								LedWaterRFlickF = true;
3903  00fe 72140001      	bset	_LedDisFlickF,#2
3904                     ; 162 								LedWaterBFlickF = true;
3906  0102 72160001      	bset	_LedDisFlickF,#3
3907                     ; 163 								LedWaterGFlickF = true;
3909  0106 72180001      	bset	_LedDisFlickF,#4
3910  010a cc0193        	jra	L3362
3911  010d               L1262:
3912                     ; 167 					else if(pFuctionData->heatInf.waterHeat.setWaterLevel == TEMP_LEVEL1)
3914  010d 1e01          	ldw	x,(OFST+1,sp)
3915  010f e60d          	ld	a,(13,x)
3916  0111 a101          	cp	a,#1
3917  0113 2628          	jrne	L5362
3918                     ; 169 						if(pFuctionData->systemErrInf.flag.bNoWaterErr == true)
3920  0115 1e01          	ldw	x,(OFST+1,sp)
3921  0117 e620          	ld	a,(32,x)
3922  0119 a508          	bcp	a,#8
3923  011b 2706          	jreq	L7362
3924                     ; 171 							LedWaterBFlickF = true;
3926  011d 72160001      	bset	_LedDisFlickF,#3
3928  0121 2010          	jra	L1462
3929  0123               L7362:
3930                     ; 175 							if(pFuctionData->WashInf.bTempChange == TEMP_NO_CHANGE)
3932  0123 1e01          	ldw	x,(OFST+1,sp)
3933  0125 6d1f          	tnz	(31,x)
3934  0127 2606          	jrne	L3462
3935                     ; 177 								LedWaterBIcon = true;
3937  0129 72160002      	bset	_LedDisIcon,#3
3939  012d 2004          	jra	L1462
3940  012f               L3462:
3941                     ; 181 								LedWaterBFlickF = true;								
3943  012f 72160001      	bset	_LedDisFlickF,#3
3944  0133               L1462:
3945                     ; 184 						LedWaterRIcon = false;
3947  0133 72150002      	bres	_LedDisIcon,#2
3948                     ; 185 						LedWaterGIcon = false;
3950  0137 72190002      	bres	_LedDisIcon,#4
3952  013b 2056          	jra	L3362
3953  013d               L5362:
3954                     ; 187 					else if(pFuctionData->heatInf.waterHeat.setWaterLevel == TEMP_LEVEL2)
3956  013d 1e01          	ldw	x,(OFST+1,sp)
3957  013f e60d          	ld	a,(13,x)
3958  0141 a102          	cp	a,#2
3959  0143 2628          	jrne	L1562
3960                     ; 189 						if(pFuctionData->systemErrInf.flag.bNoWaterErr == true)
3962  0145 1e01          	ldw	x,(OFST+1,sp)
3963  0147 e620          	ld	a,(32,x)
3964  0149 a508          	bcp	a,#8
3965  014b 2706          	jreq	L3562
3966                     ; 191 							LedWaterGFlickF = true;	
3968  014d 72180001      	bset	_LedDisFlickF,#4
3970  0151 2010          	jra	L5562
3971  0153               L3562:
3972                     ; 195 							if(pFuctionData->WashInf.bTempChange == TEMP_NO_CHANGE)
3974  0153 1e01          	ldw	x,(OFST+1,sp)
3975  0155 6d1f          	tnz	(31,x)
3976  0157 2606          	jrne	L7562
3977                     ; 197 								LedWaterGIcon = true;
3979  0159 72180002      	bset	_LedDisIcon,#4
3981  015d 2004          	jra	L5562
3982  015f               L7562:
3983                     ; 201 								LedWaterGFlickF = true;									
3985  015f 72180001      	bset	_LedDisFlickF,#4
3986  0163               L5562:
3987                     ; 205 						LedWaterRIcon = false;
3989  0163 72150002      	bres	_LedDisIcon,#2
3990                     ; 206 						LedWaterBIcon = false;
3992  0167 72170002      	bres	_LedDisIcon,#3
3994  016b 2026          	jra	L3362
3995  016d               L1562:
3996                     ; 210 						if(pFuctionData->systemErrInf.flag.bNoWaterErr == true)
3998  016d 1e01          	ldw	x,(OFST+1,sp)
3999  016f e620          	ld	a,(32,x)
4000  0171 a508          	bcp	a,#8
4001  0173 2706          	jreq	L5662
4002                     ; 212 							LedWaterRFlickF = true;	
4004  0175 72140001      	bset	_LedDisFlickF,#2
4006  0179 2010          	jra	L7662
4007  017b               L5662:
4008                     ; 216 							if(pFuctionData->WashInf.bTempChange == TEMP_NO_CHANGE)
4010  017b 1e01          	ldw	x,(OFST+1,sp)
4011  017d 6d1f          	tnz	(31,x)
4012  017f 2606          	jrne	L1762
4013                     ; 218 								LedWaterRIcon = true;
4015  0181 72140002      	bset	_LedDisIcon,#2
4017  0185 2004          	jra	L7662
4018  0187               L1762:
4019                     ; 222 								LedWaterRFlickF = true;									
4021  0187 72140001      	bset	_LedDisFlickF,#2
4022  018b               L7662:
4023                     ; 225 						LedWaterGIcon = false;
4025  018b 72190002      	bres	_LedDisIcon,#4
4026                     ; 226 						LedWaterBIcon = false;
4028  018f 72170002      	bres	_LedDisIcon,#3
4029  0193               L3362:
4030                     ; 228 					if(pFuctionData->systemErrInf.flag.bSeatTempHighErr == true)
4032  0193 1e01          	ldw	x,(OFST+1,sp)
4033  0195 e620          	ld	a,(32,x)
4034  0197 a502          	bcp	a,#2
4035  0199 2756          	jreq	L5762
4036                     ; 230 						if(pFuctionData->heatInf.seatHeat.setSeatLevel == TEMP_OFF)
4038  019b 1e01          	ldw	x,(OFST+1,sp)
4039  019d 6d0b          	tnz	(11,x)
4040  019f 2610          	jrne	L7762
4041                     ; 232 							LedWaterRFlickF = true;
4043  01a1 72140001      	bset	_LedDisFlickF,#2
4044                     ; 233 							LedWaterBFlickF = true;
4046  01a5 72160001      	bset	_LedDisFlickF,#3
4047                     ; 234 							LedWaterGFlickF = true;
4049  01a9 72180001      	bset	_LedDisFlickF,#4
4051  01ad ac4f004f      	jpf	L1652
4052  01b1               L7762:
4053                     ; 236 						else if(pFuctionData->heatInf.seatHeat.setSeatLevel == TEMP_LEVEL1)
4055  01b1 1e01          	ldw	x,(OFST+1,sp)
4056  01b3 e60b          	ld	a,(11,x)
4057  01b5 a101          	cp	a,#1
4058  01b7 2610          	jrne	L3072
4059                     ; 238 							LedDryRIcon = false;
4061  01b9 721b0002      	bres	_LedDisIcon,#5
4062                     ; 239 							LedDryGIcon = false;
4064  01bd 721f0002      	bres	_LedDisIcon,#7
4065                     ; 240 							LedWaterBFlickF = true;
4067  01c1 72160001      	bset	_LedDisFlickF,#3
4069  01c5 ac4f004f      	jpf	L1652
4070  01c9               L3072:
4071                     ; 242 						else  if(pFuctionData->heatInf.seatHeat.setSeatLevel == TEMP_LEVEL2)
4073  01c9 1e01          	ldw	x,(OFST+1,sp)
4074  01cb e60b          	ld	a,(11,x)
4075  01cd a102          	cp	a,#2
4076  01cf 2610          	jrne	L7072
4077                     ; 244 							LedDryRIcon = false;
4079  01d1 721b0002      	bres	_LedDisIcon,#5
4080                     ; 245 							LedDryBIcon = false;
4082  01d5 721d0002      	bres	_LedDisIcon,#6
4083                     ; 246 							LedWaterGFlickF = true;
4085  01d9 72180001      	bset	_LedDisFlickF,#4
4087  01dd ac4f004f      	jpf	L1652
4088  01e1               L7072:
4089                     ; 250 							LedDryGIcon = false;
4091  01e1 721f0002      	bres	_LedDisIcon,#7
4092                     ; 251 							LedDryBIcon = false;
4094  01e5 721d0002      	bres	_LedDisIcon,#6
4095                     ; 252 							LedWaterRFlickF = true;
4097  01e9 72140001      	bset	_LedDisFlickF,#2
4098  01ed ac4f004f      	jpf	L1652
4099  01f1               L5762:
4100                     ; 257 						if(LedInf.DryDisCnt > 0)
4102  01f1 725d0004      	tnz	_LedInf+1
4103  01f5 2756          	jreq	L5172
4104                     ; 259 							if(pFuctionData->heatInf.dryHeat.setDryLevel == DRY_OFF)
4106  01f7 1e01          	ldw	x,(OFST+1,sp)
4107  01f9 6d09          	tnz	(9,x)
4108  01fb 2610          	jrne	L7172
4109                     ; 261 								LedDryRIcon = false;
4111  01fd 721b0002      	bres	_LedDisIcon,#5
4112                     ; 262 								LedDryBIcon = false;
4114  0201 721d0002      	bres	_LedDisIcon,#6
4115                     ; 263 								LedDryGIcon = false;
4117  0205 721f0002      	bres	_LedDisIcon,#7
4119  0209 ac4f004f      	jpf	L1652
4120  020d               L7172:
4121                     ; 265 							else if(pFuctionData->heatInf.dryHeat.setDryLevel == DRY_LEVEL_1)
4123  020d 1e01          	ldw	x,(OFST+1,sp)
4124  020f e609          	ld	a,(9,x)
4125  0211 a101          	cp	a,#1
4126  0213 2610          	jrne	L3272
4127                     ; 267 								LedDryRIcon = false;
4129  0215 721b0002      	bres	_LedDisIcon,#5
4130                     ; 268 								LedDryBIcon = true;
4132  0219 721c0002      	bset	_LedDisIcon,#6
4133                     ; 269 								LedDryGIcon = false;
4135  021d 721f0002      	bres	_LedDisIcon,#7
4137  0221 ac4f004f      	jpf	L1652
4138  0225               L3272:
4139                     ; 271 							else if(pFuctionData->heatInf.dryHeat.setDryLevel == DRY_LEVEL_2)
4141  0225 1e01          	ldw	x,(OFST+1,sp)
4142  0227 e609          	ld	a,(9,x)
4143  0229 a102          	cp	a,#2
4144  022b 2610          	jrne	L7272
4145                     ; 273 								LedDryRIcon = false;
4147  022d 721b0002      	bres	_LedDisIcon,#5
4148                     ; 274 								LedDryBIcon = false;
4150  0231 721d0002      	bres	_LedDisIcon,#6
4151                     ; 275 								LedDryGIcon = true;			
4153  0235 721e0002      	bset	_LedDisIcon,#7
4155  0239 ac4f004f      	jpf	L1652
4156  023d               L7272:
4157                     ; 279 								LedDryRIcon = true;
4159  023d 721a0002      	bset	_LedDisIcon,#5
4160                     ; 280 								LedDryBIcon = false;
4162  0241 721d0002      	bres	_LedDisIcon,#6
4163                     ; 281 								LedDryGIcon = false;			
4165  0245 721f0002      	bres	_LedDisIcon,#7
4166  0249 ac4f004f      	jpf	L1652
4167  024d               L5172:
4168                     ; 286 							if(TxComBuff.jSetSeatLevel == TEMP_OFF)
4170  024d 725d0003      	tnz	_TxComBuff+3
4171  0251 2610          	jrne	L5372
4172                     ; 289 								LedDryRIcon = false;
4174  0253 721b0002      	bres	_LedDisIcon,#5
4175                     ; 290 								LedDryBIcon = false;
4177  0257 721d0002      	bres	_LedDisIcon,#6
4178                     ; 291 								LedDryGIcon = false;
4180  025b 721f0002      	bres	_LedDisIcon,#7
4182  025f ac4f004f      	jpf	L1652
4183  0263               L5372:
4184                     ; 293 							else if(TxComBuff.jSetSeatLevel == TEMP_LEVEL1)
4186  0263 c60003        	ld	a,_TxComBuff+3
4187  0266 a101          	cp	a,#1
4188  0268 2610          	jrne	L1472
4189                     ; 296 								LedDryRIcon = false;
4191  026a 721b0002      	bres	_LedDisIcon,#5
4192                     ; 297 								LedDryBIcon = true;
4194  026e 721c0002      	bset	_LedDisIcon,#6
4195                     ; 298 								LedDryGIcon = false;
4197  0272 721f0002      	bres	_LedDisIcon,#7
4199  0276 ac4f004f      	jpf	L1652
4200  027a               L1472:
4201                     ; 300 							else if(TxComBuff.jSetSeatLevel == TEMP_LEVEL2)
4203  027a c60003        	ld	a,_TxComBuff+3
4204  027d a102          	cp	a,#2
4205  027f 2610          	jrne	L5472
4206                     ; 303 								LedDryRIcon = false;
4208  0281 721b0002      	bres	_LedDisIcon,#5
4209                     ; 304 								LedDryBIcon = false;
4211  0285 721d0002      	bres	_LedDisIcon,#6
4212                     ; 305 								LedDryGIcon = true;				
4214  0289 721e0002      	bset	_LedDisIcon,#7
4216  028d ac4f004f      	jpf	L1652
4217  0291               L5472:
4218                     ; 309 								LedDryRIcon = true;
4220  0291 721a0002      	bset	_LedDisIcon,#5
4221                     ; 310 								LedDryBIcon = false;
4223  0295 721d0002      	bres	_LedDisIcon,#6
4224                     ; 311 								LedDryGIcon = false;			
4226  0299 721f0002      	bres	_LedDisIcon,#7
4227  029d ac4f004f      	jpf	L1652
4228  02a1               L3062:
4229                     ; 317 			else if(pFuctionData->SystemCurState == TEST_MODE_STATE)
4231  02a1 1e01          	ldw	x,(OFST+1,sp)
4232  02a3 e601          	ld	a,(1,x)
4233  02a5 a102          	cp	a,#2
4234  02a7 2703          	jreq	L01
4235  02a9 cc004f        	jp	L1652
4236  02ac               L01:
4237                     ; 319 				LedPowerIcon = true;
4239  02ac 72100002      	bset	_LedDisIcon,#0
4240                     ; 320 				if(pFuctionData->seatInf.seatSensorState.bSwitchState == SW_ON
4240                     ; 321 				||pFuctionData->seatInf.SwitchSeatEn == true)
4242  02b0 1e01          	ldw	x,(OFST+1,sp)
4243  02b2 e61a          	ld	a,(26,x)
4244  02b4 a501          	bcp	a,#1
4245  02b6 2608          	jrne	L7572
4247  02b8 1e01          	ldw	x,(OFST+1,sp)
4248  02ba e611          	ld	a,(17,x)
4249  02bc a501          	bcp	a,#1
4250  02be 2714          	jreq	L5572
4251  02c0               L7572:
4252                     ; 323 					LedSeatIcon = true;
4254  02c0 72120002      	bset	_LedDisIcon,#1
4256  02c4               L1672:
4257                     ; 329 				if(pFuctionData->curFunInf.curFunc == FUNC_SPANY)
4259  02c4 1e01          	ldw	x,(OFST+1,sp)
4260  02c6 e604          	ld	a,(4,x)
4261  02c8 a101          	cp	a,#1
4262  02ca 260e          	jrne	L3672
4263                     ; 331 					LedWaterRFlickF = true;
4265  02cc 72140001      	bset	_LedDisFlickF,#2
4267  02d0 ac4f004f      	jpf	L1652
4268  02d4               L5572:
4269                     ; 327 					LedSeatIcon = false;
4271  02d4 72130002      	bres	_LedDisIcon,#1
4272  02d8 20ea          	jra	L1672
4273  02da               L3672:
4274                     ; 333 				else if(pFuctionData->curFunInf.curFunc == FUNC_WOMAN 
4274                     ; 334 				||pFuctionData->curFunInf.curFunc == FUNC_DRY)
4276  02da 1e01          	ldw	x,(OFST+1,sp)
4277  02dc e604          	ld	a,(4,x)
4278  02de a102          	cp	a,#2
4279  02e0 270b          	jreq	L1772
4281  02e2 1e01          	ldw	x,(OFST+1,sp)
4282  02e4 e604          	ld	a,(4,x)
4283  02e6 a103          	cp	a,#3
4284  02e8 2703          	jreq	L21
4285  02ea cc004f        	jp	L1652
4286  02ed               L21:
4287  02ed               L1772:
4288                     ; 336 					LedDryRFlickF = true;
4290  02ed 721a0001      	bset	_LedDisFlickF,#5
4291  02f1 ac4f004f      	jpf	L1652
4317                     ; 356 void f_pLedInit(void)
4317                     ; 357 {
4318                     	switch	.text
4319  02f5               _f_pLedInit:
4323                     ; 358 	LED_POWER(1);
4325  02f5 72145000      	bset	_PA_ODR,#2
4326                     ; 359 	LED_SEAT(1);
4328  02f9 7216500f      	bset	_PD_ODR,#3
4329                     ; 360 	LED_TEMP_WATER_RED(1);
4331  02fd 7214500f      	bset	_PD_ODR,#2
4332                     ; 361 	LED_TEMP_WATER_BULE(1);
4334  0301 721e500a      	bset	_PC_ODR,#7
4335                     ; 362 	LED_TEMP_WATER_GREEN(1);
4337  0305 721c500a      	bset	_PC_ODR,#6
4338                     ; 363 	LED_TEMP_DRY_RED(1);
4340  0309 721a500a      	bset	_PC_ODR,#5
4341                     ; 364 	LED_TEMP_DRY_BULE(1);
4343  030d 7218500a      	bset	_PC_ODR,#4
4344                     ; 365 	LED_TEMP_DRY_GREEN(1);
4346  0311 7216500a      	bset	_PC_ODR,#3
4347                     ; 366 }
4350  0315 81            	ret
4379                     ; 381 void f_pLedDriveDeal(void)
4379                     ; 382 {
4380                     	switch	.text
4381  0316               _f_pLedDriveDeal:
4385                     ; 383 	LED_POWER(1);
4387  0316 72145000      	bset	_PA_ODR,#2
4388                     ; 384 	LED_SEAT(1);
4390  031a 7216500f      	bset	_PD_ODR,#3
4391                     ; 385 	LED_TEMP_WATER_RED(1);
4393  031e 7214500f      	bset	_PD_ODR,#2
4394                     ; 386 	LED_TEMP_WATER_BULE(1);
4396  0322 721e500a      	bset	_PC_ODR,#7
4397                     ; 387 	LED_TEMP_WATER_GREEN(1);
4399  0326 721c500a      	bset	_PC_ODR,#6
4400                     ; 388 	LED_TEMP_DRY_RED(1);
4402  032a 721a500a      	bset	_PC_ODR,#5
4403                     ; 389 	LED_TEMP_DRY_BULE(1);
4405  032e 7218500a      	bset	_PC_ODR,#4
4406                     ; 390 	LED_TEMP_DRY_GREEN(1);
4408  0332 7216500a      	bset	_PC_ODR,#3
4409                     ; 391 	if(LedPowerIcon || (LedPowerFlickF && LedPowerFlickS))
4411  0336 c60002        	ld	a,_LedDisIcon
4412  0339 a501          	bcp	a,#1
4413  033b 260e          	jrne	L5103
4415  033d c60001        	ld	a,_LedDisFlickF
4416  0340 a501          	bcp	a,#1
4417  0342 270b          	jreq	L3103
4419  0344 c60000        	ld	a,_LedDisFlickS
4420  0347 a501          	bcp	a,#1
4421  0349 2704          	jreq	L3103
4422  034b               L5103:
4423                     ; 393 		LED_POWER(0);
4425  034b 72155000      	bres	_PA_ODR,#2
4426  034f               L3103:
4427                     ; 395 	if(LedSeatIcon || (LedSeatFlickF && LedSeatFlickS))
4429  034f c60002        	ld	a,_LedDisIcon
4430  0352 a502          	bcp	a,#2
4431  0354 260e          	jrne	L1203
4433  0356 c60001        	ld	a,_LedDisFlickF
4434  0359 a502          	bcp	a,#2
4435  035b 270b          	jreq	L7103
4437  035d c60000        	ld	a,_LedDisFlickS
4438  0360 a502          	bcp	a,#2
4439  0362 2704          	jreq	L7103
4440  0364               L1203:
4441                     ; 397 		LED_SEAT(0);
4443  0364 7217500f      	bres	_PD_ODR,#3
4444  0368               L7103:
4445                     ; 399 	if(LedWaterRIcon || (LedWaterRFlickF && LedWaterRFlickS))
4447  0368 c60002        	ld	a,_LedDisIcon
4448  036b a504          	bcp	a,#4
4449  036d 260e          	jrne	L5203
4451  036f c60001        	ld	a,_LedDisFlickF
4452  0372 a504          	bcp	a,#4
4453  0374 270b          	jreq	L3203
4455  0376 c60000        	ld	a,_LedDisFlickS
4456  0379 a504          	bcp	a,#4
4457  037b 2704          	jreq	L3203
4458  037d               L5203:
4459                     ; 401 		LED_TEMP_WATER_RED(0);
4461  037d 7215500f      	bres	_PD_ODR,#2
4462  0381               L3203:
4463                     ; 403 	if(LedWaterBIcon || (LedWaterBFlickF && LedWaterRFlickS))
4465  0381 c60002        	ld	a,_LedDisIcon
4466  0384 a508          	bcp	a,#8
4467  0386 260e          	jrne	L1303
4469  0388 c60001        	ld	a,_LedDisFlickF
4470  038b a508          	bcp	a,#8
4471  038d 270b          	jreq	L7203
4473  038f c60000        	ld	a,_LedDisFlickS
4474  0392 a504          	bcp	a,#4
4475  0394 2704          	jreq	L7203
4476  0396               L1303:
4477                     ; 405 		LED_TEMP_WATER_BULE(0);
4479  0396 721f500a      	bres	_PC_ODR,#7
4480  039a               L7203:
4481                     ; 407 	if(LedWaterGIcon || (LedWaterGFlickF && LedWaterGFlickS))
4483  039a c60002        	ld	a,_LedDisIcon
4484  039d a510          	bcp	a,#16
4485  039f 260e          	jrne	L5303
4487  03a1 c60001        	ld	a,_LedDisFlickF
4488  03a4 a510          	bcp	a,#16
4489  03a6 270b          	jreq	L3303
4491  03a8 c60000        	ld	a,_LedDisFlickS
4492  03ab a510          	bcp	a,#16
4493  03ad 2704          	jreq	L3303
4494  03af               L5303:
4495                     ; 409 		LED_TEMP_WATER_GREEN(0);
4497  03af 721d500a      	bres	_PC_ODR,#6
4498  03b3               L3303:
4499                     ; 411 	if(LedDryRIcon || (LedDryRFlickF && LedDryRFlickS))
4501  03b3 c60002        	ld	a,_LedDisIcon
4502  03b6 a520          	bcp	a,#32
4503  03b8 260e          	jrne	L1403
4505  03ba c60001        	ld	a,_LedDisFlickF
4506  03bd a520          	bcp	a,#32
4507  03bf 270b          	jreq	L7303
4509  03c1 c60000        	ld	a,_LedDisFlickS
4510  03c4 a520          	bcp	a,#32
4511  03c6 2704          	jreq	L7303
4512  03c8               L1403:
4513                     ; 413 		LED_TEMP_DRY_RED(0);
4515  03c8 721b500a      	bres	_PC_ODR,#5
4516  03cc               L7303:
4517                     ; 415 	if(LedDryBIcon || (LedDryBFlickF && LedDryBFlickS))
4519  03cc c60002        	ld	a,_LedDisIcon
4520  03cf a540          	bcp	a,#64
4521  03d1 260e          	jrne	L5403
4523  03d3 c60001        	ld	a,_LedDisFlickF
4524  03d6 a540          	bcp	a,#64
4525  03d8 270b          	jreq	L3403
4527  03da c60000        	ld	a,_LedDisFlickS
4528  03dd a540          	bcp	a,#64
4529  03df 2704          	jreq	L3403
4530  03e1               L5403:
4531                     ; 417 		LED_TEMP_DRY_BULE(0);
4533  03e1 7219500a      	bres	_PC_ODR,#4
4534  03e5               L3403:
4535                     ; 419 	if(LedDryGIcon || (LedDryGFlickF && LedDryGFlickS))
4537  03e5 c60002        	ld	a,_LedDisIcon
4538  03e8 a580          	bcp	a,#128
4539  03ea 260e          	jrne	L1503
4541  03ec c60001        	ld	a,_LedDisFlickF
4542  03ef a580          	bcp	a,#128
4543  03f1 270b          	jreq	L7403
4545  03f3 c60000        	ld	a,_LedDisFlickS
4546  03f6 a580          	bcp	a,#128
4547  03f8 2704          	jreq	L7403
4548  03fa               L1503:
4549                     ; 421 		LED_TEMP_DRY_GREEN(0);
4551  03fa 7217500a      	bres	_PC_ODR,#3
4552  03fe               L7403:
4553                     ; 423 	LedAllIcon = 0x00;
4555  03fe 725f0002      	clr	_LedDisIcon
4556                     ; 424 	LedAllFlickF = 0x00;
4558  0402 725f0001      	clr	_LedDisFlickF
4559                     ; 425 }
4562  0406 81            	ret
4575                     	xref	_TxComBuff
4576                     	xdef	_f_pLedDriveDeal
4577                     	xdef	_f_pLedDeal
4578                     	xdef	_f_pLedInit
4579                     	switch	.bss
4580  0000               _LedDisFlickS:
4581  0000 00            	ds.b	1
4582                     	xdef	_LedDisFlickS
4583  0001               _LedDisFlickF:
4584  0001 00            	ds.b	1
4585                     	xdef	_LedDisFlickF
4586  0002               _LedDisIcon:
4587  0002 00            	ds.b	1
4588                     	xdef	_LedDisIcon
4589  0003               _LedInf:
4590  0003 000000        	ds.b	3
4591                     	xdef	_LedInf
4611                     	end
