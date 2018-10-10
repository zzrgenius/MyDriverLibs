   1                     ; C Compiler for STM8 (COSMIC Software)
   2                     ; Parser V4.8.32 - 23 Mar 2010
   3                     ; Generator V4.3.4 - 23 Mar 2010
2847                     	bsct
2848  0000               L5202_LedInitCnt:
2849  0000 00            	dc.b	0
2850  0001               L7202_LedNoWatrFlag:
2851  0001 00            	dc.b	0
2852  0002               L1302_LedNoWaterCnt:
2853  0002 00            	dc.b	0
3750                     ; 66 void f_pLedDeal(BIG_STRUCT *pFuctionData)
3750                     ; 67 {
3752                     	switch	.text
3753  0000               _f_pLedDeal:
3755  0000 89            	pushw	x
3756       00000000      OFST:	set	0
3759                     ; 71 	if((pFuctionData->bInitInf== rSYS_INIT_NO) || (pFuctionData->bInitInf == rSYS_INIT_HLAF))
3761  0001 7d            	tnz	(x)
3762  0002 2705          	jreq	L7062
3764  0004 f6            	ld	a,(x)
3765  0005 a101          	cp	a,#1
3766  0007 2648          	jrne	L5062
3767  0009               L7062:
3768                     ; 73 		LedPowerIcon = true;
3770  0009 72100004      	bset	_LedDisIcon,#0
3771                     ; 74 		if(LedInitCnt < 29)
3773  000d b600          	ld	a,L5202_LedInitCnt
3774  000f a11d          	cp	a,#29
3775  0011 2420          	jruge	L1162
3776                     ; 76 			LedInitCnt++;
3778  0013 3c00          	inc	L5202_LedInitCnt
3779                     ; 77 			LedSeatIcon = true;
3781  0015 72120004      	bset	_LedDisIcon,#1
3782                     ; 85 			LedWaterRIcon = false;
3784  0019 72150004      	bres	_LedDisIcon,#2
3785                     ; 86 			LedWaterBIcon = true;
3787  001d 72160004      	bset	_LedDisIcon,#3
3788                     ; 87 			LedWaterGIcon = false;
3790  0021 72190004      	bres	_LedDisIcon,#4
3791                     ; 88 			LedDryRIcon = false;
3793  0025 721b0004      	bres	_LedDisIcon,#5
3794                     ; 89 			LedDryBIcon = true;
3796  0029 721c0004      	bset	_LedDisIcon,#6
3797                     ; 90 			LedDryGIcon = false;
3799  002d 721f0004      	bres	_LedDisIcon,#7
3801  0031 201c          	jra	L5162
3802  0033               L1162:
3803                     ; 94 			LedSeatIcon = false;
3805  0033 72130004      	bres	_LedDisIcon,#1
3806                     ; 95 			LedWaterRIcon = false;
3808  0037 72150004      	bres	_LedDisIcon,#2
3809                     ; 96 			LedWaterBIcon = false;
3811  003b 72170004      	bres	_LedDisIcon,#3
3812                     ; 97 			LedWaterGIcon = false;
3814  003f 72190004      	bres	_LedDisIcon,#4
3815                     ; 98 			LedDryRIcon = false;
3817  0043 721b0004      	bres	_LedDisIcon,#5
3818                     ; 99 			LedDryBIcon = false;
3820  0047 721d0004      	bres	_LedDisIcon,#6
3821                     ; 100 			LedDryGIcon = false;
3823  004b 721f0004      	bres	_LedDisIcon,#7
3824  004f               L5162:
3825                     ; 347 }
3828  004f 85            	popw	x
3829  0050 81            	ret
3830  0051               L5062:
3831                     ; 103 	else if(pFuctionData->bInitInf == rSYS_INIT_OK)
3833  0051 1e01          	ldw	x,(OFST+1,sp)
3834  0053 f6            	ld	a,(x)
3835  0054 a102          	cp	a,#2
3836  0056 26f7          	jrne	L5162
3837                     ; 105 		if(LedNoWatrFlag == 0)
3839  0058 3d01          	tnz	L7202_LedNoWatrFlag
3840  005a 2620          	jrne	L1262
3841                     ; 107 			if(pFuctionData->systemErrInf.flag.bNoWaterErr == true)
3843  005c 1e01          	ldw	x,(OFST+1,sp)
3844  005e e620          	ld	a,(32,x)
3845  0060 a508          	bcp	a,#8
3846  0062 2712          	jreq	L3262
3847                     ; 109 				LedNoWaterCnt++;
3849  0064 3c02          	inc	L1302_LedNoWaterCnt
3850                     ; 110 				LedPowerFlickF = true;
3852  0066 72100003      	bset	_LedDisFlickF,#0
3853                     ; 111 				if(LedNoWaterCnt > 32)
3855  006a b602          	ld	a,L1302_LedNoWaterCnt
3856  006c a121          	cp	a,#33
3857  006e 25df          	jrult	L5162
3858                     ; 113 					LedNoWatrFlag = 1;
3860  0070 35010001      	mov	L7202_LedNoWatrFlag,#1
3861  0074 20d9          	jra	L5162
3862  0076               L3262:
3863                     ; 118 				LedNoWatrFlag = 1;
3865  0076 35010001      	mov	L7202_LedNoWatrFlag,#1
3866  007a 20d3          	jra	L5162
3867  007c               L1262:
3868                     ; 123 			if(pFuctionData->SystemCurState == STANDBY_STATE)
3870  007c 1e01          	ldw	x,(OFST+1,sp)
3871  007e 6d01          	tnz	(1,x)
3872  0080 2606          	jrne	L3362
3873                     ; 125 				LedAllIcon = 0x00;
3875  0082 725f0004      	clr	_LedDisIcon
3877  0086 20c7          	jra	L5162
3878  0088               L3362:
3879                     ; 127 			else if(pFuctionData->SystemCurState == RUNNING_STATE)
3881  0088 1e01          	ldw	x,(OFST+1,sp)
3882  008a e601          	ld	a,(1,x)
3883  008c a101          	cp	a,#1
3884  008e 2703          	jreq	L6
3885  0090 cc029a        	jp	L7362
3886  0093               L6:
3887                     ; 129 				if(pFuctionData->seatInf.SeatOffTm.hour >= 24)
3889  0093 1e01          	ldw	x,(OFST+1,sp)
3890  0095 9093          	ldw	y,x
3891  0097 90ee18        	ldw	y,(24,y)
3892  009a 90a30018      	cpw	y,#24
3893  009e 2506          	jrult	L1462
3894                     ; 131 					LedAllIcon = 0x00;
3896  00a0 725f0004      	clr	_LedDisIcon
3898  00a4 20a9          	jra	L5162
3899  00a6               L1462:
3900                     ; 136 					if(pFuctionData->systemErrInf.flag.bZeroCrossErr == false)
3902  00a6 1e01          	ldw	x,(OFST+1,sp)
3903  00a8 e620          	ld	a,(32,x)
3904  00aa a520          	bcp	a,#32
3905  00ac 2606          	jrne	L5462
3906                     ; 138 						LedPowerIcon = true;
3908  00ae 72100004      	bset	_LedDisIcon,#0
3910  00b2 2004          	jra	L7462
3911  00b4               L5462:
3912                     ; 142 						LedPower500msf = true;
3914  00b4 72100001      	bset	_LedDisPower500F,#0
3915  00b8               L7462:
3916                     ; 145 					if(pFuctionData->seatInf.seatSensorState.bSwitchState == SW_ON
3916                     ; 146 					||pFuctionData->seatInf.SwitchSeatEn == true
3916                     ; 147 					||pFuctionData->flushTimeState > 0)
3918  00b8 1e01          	ldw	x,(OFST+1,sp)
3919  00ba e61a          	ld	a,(26,x)
3920  00bc a501          	bcp	a,#1
3921  00be 260e          	jrne	L3562
3923  00c0 1e01          	ldw	x,(OFST+1,sp)
3924  00c2 e611          	ld	a,(17,x)
3925  00c4 a501          	bcp	a,#1
3926  00c6 2606          	jrne	L3562
3928  00c8 1e01          	ldw	x,(OFST+1,sp)
3929  00ca 6d26          	tnz	(38,x)
3930  00cc 272b          	jreq	L1562
3931  00ce               L3562:
3932                     ; 149 						LedSeatIcon = true;
3934  00ce 72120004      	bset	_LedDisIcon,#1
3936  00d2               L7562:
3937                     ; 157 					if(pFuctionData->systemErrInf.flag.bHeatCommunErr == false)
3939  00d2 1e01          	ldw	x,(OFST+1,sp)
3940  00d4 e620          	ld	a,(32,x)
3941  00d6 a510          	bcp	a,#16
3942  00d8 2703cc016e    	jrne	L1662
3943                     ; 159 						if(pFuctionData->heatInf.waterHeat.setWaterLevel == TEMP_OFF)
3945  00dd 1e01          	ldw	x,(OFST+1,sp)
3946  00df 6d0d          	tnz	(13,x)
3947  00e1 262c          	jrne	L3662
3948                     ; 161 							if(pFuctionData->WashInf.bTempChange == TEMP_NO_CHANGE)
3950  00e3 1e01          	ldw	x,(OFST+1,sp)
3951  00e5 6d1f          	tnz	(31,x)
3952  00e7 2616          	jrne	L5662
3953                     ; 163 								LedWaterRIcon = false;
3955  00e9 72150004      	bres	_LedDisIcon,#2
3956                     ; 164 								LedWaterBIcon = false;
3958  00ed 72170004      	bres	_LedDisIcon,#3
3959                     ; 165 								LedWaterGIcon = false;
3961  00f1 72190004      	bres	_LedDisIcon,#4
3963  00f5 acba01ba      	jpf	L7172
3964  00f9               L1562:
3965                     ; 153 						LedSeatIcon = false;
3967  00f9 72130004      	bres	_LedDisIcon,#1
3968  00fd 20d3          	jra	L7562
3969  00ff               L5662:
3970                     ; 172 								LedWaterRFlickF = false;
3972  00ff 72150003      	bres	_LedDisFlickF,#2
3973                     ; 173 								LedWaterBFlickF = true;
3975  0103 72160003      	bset	_LedDisFlickF,#3
3976                     ; 174 								LedWaterGFlickF = false;
3978  0107 72190003      	bres	_LedDisFlickF,#4
3979  010b acba01ba      	jpf	L7172
3980  010f               L3662:
3981                     ; 177 						else if(pFuctionData->heatInf.waterHeat.setWaterLevel == TEMP_LEVEL1)
3983  010f 1e01          	ldw	x,(OFST+1,sp)
3984  0111 e60d          	ld	a,(13,x)
3985  0113 a101          	cp	a,#1
3986  0115 261b          	jrne	L3762
3987                     ; 179 							if(pFuctionData->WashInf.bTempChange == TEMP_NO_CHANGE)
3989  0117 1e01          	ldw	x,(OFST+1,sp)
3990  0119 6d1f          	tnz	(31,x)
3991  011b 2606          	jrne	L5762
3992                     ; 181 								LedWaterBIcon = true;
3994  011d 72160004      	bset	_LedDisIcon,#3
3996  0121 2004          	jra	L7762
3997  0123               L5762:
3998                     ; 185 								LedWaterBFlickF = true;								
4000  0123 72160003      	bset	_LedDisFlickF,#3
4001  0127               L7762:
4002                     ; 187 							LedWaterRIcon = false;
4004  0127 72150004      	bres	_LedDisIcon,#2
4005                     ; 188 							LedWaterGIcon = false;
4007  012b 72190004      	bres	_LedDisIcon,#4
4009  012f cc01ba        	jra	L7172
4010  0132               L3762:
4011                     ; 190 						else if(pFuctionData->heatInf.waterHeat.setWaterLevel == TEMP_LEVEL2)
4013  0132 1e01          	ldw	x,(OFST+1,sp)
4014  0134 e60d          	ld	a,(13,x)
4015  0136 a102          	cp	a,#2
4016  0138 261a          	jrne	L3072
4017                     ; 192 							if(pFuctionData->WashInf.bTempChange == TEMP_NO_CHANGE)
4019  013a 1e01          	ldw	x,(OFST+1,sp)
4020  013c 6d1f          	tnz	(31,x)
4021  013e 2606          	jrne	L5072
4022                     ; 194 								LedWaterGIcon = true;
4024  0140 72180004      	bset	_LedDisIcon,#4
4026  0144 2004          	jra	L7072
4027  0146               L5072:
4028                     ; 198 								LedWaterGFlickF = true;									
4030  0146 72180003      	bset	_LedDisFlickF,#4
4031  014a               L7072:
4032                     ; 200 							LedWaterRIcon = false;
4034  014a 72150004      	bres	_LedDisIcon,#2
4035                     ; 201 							LedWaterBIcon = false;
4037  014e 72170004      	bres	_LedDisIcon,#3
4039  0152 2066          	jra	L7172
4040  0154               L3072:
4041                     ; 205 							if(pFuctionData->WashInf.bTempChange == TEMP_NO_CHANGE)
4043  0154 1e01          	ldw	x,(OFST+1,sp)
4044  0156 6d1f          	tnz	(31,x)
4045  0158 2606          	jrne	L3172
4046                     ; 207 								LedWaterRIcon = true;
4048  015a 72140004      	bset	_LedDisIcon,#2
4050  015e 2004          	jra	L5172
4051  0160               L3172:
4052                     ; 211 								LedWaterRFlickF = true;									
4054  0160 72140003      	bset	_LedDisFlickF,#2
4055  0164               L5172:
4056                     ; 213 							LedWaterGIcon = false;
4058  0164 72190004      	bres	_LedDisIcon,#4
4059                     ; 214 							LedWaterBIcon = false;
4061  0168 72170004      	bres	_LedDisIcon,#3
4062  016c 204c          	jra	L7172
4063  016e               L1662:
4064                     ; 219 						if(pFuctionData->heatInf.waterHeat.setWaterLevel == TEMP_OFF)
4066  016e 1e01          	ldw	x,(OFST+1,sp)
4067  0170 6d0d          	tnz	(13,x)
4068  0172 260e          	jrne	L1272
4069                     ; 224 							LedWaterRFlickF = false;
4071  0174 72150003      	bres	_LedDisFlickF,#2
4072                     ; 225 							LedWaterBFlickF = true;
4074  0178 72160003      	bset	_LedDisFlickF,#3
4075                     ; 226 							LedWaterGFlickF = false;
4077  017c 72190003      	bres	_LedDisFlickF,#4
4079  0180 2038          	jra	L7172
4080  0182               L1272:
4081                     ; 228 						else if(pFuctionData->heatInf.waterHeat.setWaterLevel == TEMP_LEVEL1)
4083  0182 1e01          	ldw	x,(OFST+1,sp)
4084  0184 e60d          	ld	a,(13,x)
4085  0186 a101          	cp	a,#1
4086  0188 260e          	jrne	L5272
4087                     ; 230 							LedWaterBFlickF = true;								
4089  018a 72160003      	bset	_LedDisFlickF,#3
4090                     ; 231 							LedWaterRIcon = false;
4092  018e 72150004      	bres	_LedDisIcon,#2
4093                     ; 232 							LedWaterGIcon = false;
4095  0192 72190004      	bres	_LedDisIcon,#4
4097  0196 2022          	jra	L7172
4098  0198               L5272:
4099                     ; 234 						else if(pFuctionData->heatInf.waterHeat.setWaterLevel == TEMP_LEVEL2)
4101  0198 1e01          	ldw	x,(OFST+1,sp)
4102  019a e60d          	ld	a,(13,x)
4103  019c a102          	cp	a,#2
4104  019e 260e          	jrne	L1372
4105                     ; 236 							LedWaterGFlickF = true;									
4107  01a0 72180003      	bset	_LedDisFlickF,#4
4108                     ; 237 							LedWaterRIcon = false;
4110  01a4 72150004      	bres	_LedDisIcon,#2
4111                     ; 238 							LedWaterBIcon = false;
4113  01a8 72170004      	bres	_LedDisIcon,#3
4115  01ac 200c          	jra	L7172
4116  01ae               L1372:
4117                     ; 242 							LedWaterRFlickF = true;									
4119  01ae 72140003      	bset	_LedDisFlickF,#2
4120                     ; 243 							LedWaterGIcon = false;
4122  01b2 72190004      	bres	_LedDisIcon,#4
4123                     ; 244 							LedWaterBIcon = false;
4125  01b6 72170004      	bres	_LedDisIcon,#3
4126  01ba               L7172:
4127                     ; 249 					if(pFuctionData->systemErrInf.flag.bSeatTempHighErr)
4129  01ba 1e01          	ldw	x,(OFST+1,sp)
4130  01bc e620          	ld	a,(32,x)
4131  01be a502          	bcp	a,#2
4132  01c0 2710          	jreq	L5372
4133                     ; 251 						LedDryRIcon = false;
4135  01c2 721b0004      	bres	_LedDisIcon,#5
4136                     ; 252 						LedDryGIcon = false;
4138  01c6 721f0004      	bres	_LedDisIcon,#7
4139                     ; 253 						LedDryBFlickF = true;
4141  01ca 721c0003      	bset	_LedDisFlickF,#6
4143  01ce ac4f004f      	jpf	L5162
4144  01d2               L5372:
4145                     ; 255 					else if(pFuctionData->systemErrInf.flag.bDryTempHighErr)
4147  01d2 1e01          	ldw	x,(OFST+1,sp)
4148  01d4 e620          	ld	a,(32,x)
4149  01d6 a504          	bcp	a,#4
4150  01d8 2710          	jreq	L1472
4151                     ; 257 						LedDryRFlickF = true;
4153  01da 721a0003      	bset	_LedDisFlickF,#5
4154                     ; 258 						LedDryGIcon = false;
4156  01de 721f0004      	bres	_LedDisIcon,#7
4157                     ; 259 						LedDryBIcon = false;
4159  01e2 721d0004      	bres	_LedDisIcon,#6
4161  01e6 ac4f004f      	jpf	L5162
4162  01ea               L1472:
4163                     ; 263 						if(LedInf.DryDisCnt > 0)
4165  01ea 725d0006      	tnz	_LedInf+1
4166  01ee 2756          	jreq	L5472
4167                     ; 265 							if(pFuctionData->heatInf.dryHeat.setDryLevel == DRY_OFF)
4169  01f0 1e01          	ldw	x,(OFST+1,sp)
4170  01f2 6d09          	tnz	(9,x)
4171  01f4 2610          	jrne	L7472
4172                     ; 267 								LedDryRIcon = false;
4174  01f6 721b0004      	bres	_LedDisIcon,#5
4175                     ; 268 								LedDryBIcon = false;
4177  01fa 721d0004      	bres	_LedDisIcon,#6
4178                     ; 269 								LedDryGIcon = false;
4180  01fe 721f0004      	bres	_LedDisIcon,#7
4182  0202 ac4f004f      	jpf	L5162
4183  0206               L7472:
4184                     ; 271 							else if(pFuctionData->heatInf.dryHeat.setDryLevel == DRY_LEVEL_1)
4186  0206 1e01          	ldw	x,(OFST+1,sp)
4187  0208 e609          	ld	a,(9,x)
4188  020a a101          	cp	a,#1
4189  020c 2610          	jrne	L3572
4190                     ; 273 								LedDryRIcon = false;
4192  020e 721b0004      	bres	_LedDisIcon,#5
4193                     ; 274 								LedDryBIcon = true;
4195  0212 721c0004      	bset	_LedDisIcon,#6
4196                     ; 275 								LedDryGIcon = false;
4198  0216 721f0004      	bres	_LedDisIcon,#7
4200  021a ac4f004f      	jpf	L5162
4201  021e               L3572:
4202                     ; 277 							else if(pFuctionData->heatInf.dryHeat.setDryLevel == DRY_LEVEL_2)
4204  021e 1e01          	ldw	x,(OFST+1,sp)
4205  0220 e609          	ld	a,(9,x)
4206  0222 a102          	cp	a,#2
4207  0224 2610          	jrne	L7572
4208                     ; 279 								LedDryRIcon = false;
4210  0226 721b0004      	bres	_LedDisIcon,#5
4211                     ; 280 								LedDryBIcon = false;
4213  022a 721d0004      	bres	_LedDisIcon,#6
4214                     ; 281 								LedDryGIcon = true;			
4216  022e 721e0004      	bset	_LedDisIcon,#7
4218  0232 ac4f004f      	jpf	L5162
4219  0236               L7572:
4220                     ; 285 								LedDryRIcon = true;
4222  0236 721a0004      	bset	_LedDisIcon,#5
4223                     ; 286 								LedDryBIcon = false;
4225  023a 721d0004      	bres	_LedDisIcon,#6
4226                     ; 287 								LedDryGIcon = false;			
4228  023e 721f0004      	bres	_LedDisIcon,#7
4229  0242 ac4f004f      	jpf	L5162
4230  0246               L5472:
4231                     ; 292 							if(TxComBuff.jSetSeatLevel == TEMP_OFF)
4233  0246 725d0003      	tnz	_TxComBuff+3
4234  024a 2610          	jrne	L5672
4235                     ; 295 								LedDryRIcon = false;
4237  024c 721b0004      	bres	_LedDisIcon,#5
4238                     ; 296 								LedDryBIcon = false;
4240  0250 721d0004      	bres	_LedDisIcon,#6
4241                     ; 297 								LedDryGIcon = false;
4243  0254 721f0004      	bres	_LedDisIcon,#7
4245  0258 ac4f004f      	jpf	L5162
4246  025c               L5672:
4247                     ; 299 							else if(TxComBuff.jSetSeatLevel == TEMP_LEVEL1)
4249  025c c60003        	ld	a,_TxComBuff+3
4250  025f a101          	cp	a,#1
4251  0261 2610          	jrne	L1772
4252                     ; 302 								LedDryRIcon = false;
4254  0263 721b0004      	bres	_LedDisIcon,#5
4255                     ; 303 								LedDryBIcon = true;
4257  0267 721c0004      	bset	_LedDisIcon,#6
4258                     ; 304 								LedDryGIcon = false;
4260  026b 721f0004      	bres	_LedDisIcon,#7
4262  026f ac4f004f      	jpf	L5162
4263  0273               L1772:
4264                     ; 306 							else if(TxComBuff.jSetSeatLevel == TEMP_LEVEL2)
4266  0273 c60003        	ld	a,_TxComBuff+3
4267  0276 a102          	cp	a,#2
4268  0278 2610          	jrne	L5772
4269                     ; 309 								LedDryRIcon = false;
4271  027a 721b0004      	bres	_LedDisIcon,#5
4272                     ; 310 								LedDryBIcon = false;
4274  027e 721d0004      	bres	_LedDisIcon,#6
4275                     ; 311 								LedDryGIcon = true;				
4277  0282 721e0004      	bset	_LedDisIcon,#7
4279  0286 ac4f004f      	jpf	L5162
4280  028a               L5772:
4281                     ; 315 								LedDryRIcon = true;
4283  028a 721a0004      	bset	_LedDisIcon,#5
4284                     ; 316 								LedDryBIcon = false;
4286  028e 721d0004      	bres	_LedDisIcon,#6
4287                     ; 317 								LedDryGIcon = false;			
4289  0292 721f0004      	bres	_LedDisIcon,#7
4290  0296 ac4f004f      	jpf	L5162
4291  029a               L7362:
4292                     ; 323 			else if(pFuctionData->SystemCurState == TEST_MODE_STATE)
4294  029a 1e01          	ldw	x,(OFST+1,sp)
4295  029c e601          	ld	a,(1,x)
4296  029e a102          	cp	a,#2
4297  02a0 2703          	jreq	L01
4298  02a2 cc004f        	jp	L5162
4299  02a5               L01:
4300                     ; 325 				LedPowerIcon = true;
4302  02a5 72100004      	bset	_LedDisIcon,#0
4303                     ; 326 				if(pFuctionData->seatInf.seatSensorState.bSwitchState == SW_ON
4303                     ; 327 				||pFuctionData->seatInf.SwitchSeatEn == true)
4305  02a9 1e01          	ldw	x,(OFST+1,sp)
4306  02ab e61a          	ld	a,(26,x)
4307  02ad a501          	bcp	a,#1
4308  02af 2608          	jrne	L7003
4310  02b1 1e01          	ldw	x,(OFST+1,sp)
4311  02b3 e611          	ld	a,(17,x)
4312  02b5 a501          	bcp	a,#1
4313  02b7 2714          	jreq	L5003
4314  02b9               L7003:
4315                     ; 329 					LedSeatIcon = true;
4317  02b9 72120004      	bset	_LedDisIcon,#1
4319  02bd               L1103:
4320                     ; 335 				if(pFuctionData->curFunInf.curFunc == FUNC_SPANY)
4322  02bd 1e01          	ldw	x,(OFST+1,sp)
4323  02bf e604          	ld	a,(4,x)
4324  02c1 a101          	cp	a,#1
4325  02c3 260e          	jrne	L3103
4326                     ; 337 					LedWaterRFlickF = true;
4328  02c5 72140003      	bset	_LedDisFlickF,#2
4330  02c9 ac4f004f      	jpf	L5162
4331  02cd               L5003:
4332                     ; 333 					LedSeatIcon = false;
4334  02cd 72130004      	bres	_LedDisIcon,#1
4335  02d1 20ea          	jra	L1103
4336  02d3               L3103:
4337                     ; 339 				else if(pFuctionData->curFunInf.curFunc == FUNC_WOMAN 
4337                     ; 340 				||pFuctionData->curFunInf.curFunc == FUNC_DRY)
4339  02d3 1e01          	ldw	x,(OFST+1,sp)
4340  02d5 e604          	ld	a,(4,x)
4341  02d7 a102          	cp	a,#2
4342  02d9 270b          	jreq	L1203
4344  02db 1e01          	ldw	x,(OFST+1,sp)
4345  02dd e604          	ld	a,(4,x)
4346  02df a103          	cp	a,#3
4347  02e1 2703          	jreq	L21
4348  02e3 cc004f        	jp	L5162
4349  02e6               L21:
4350  02e6               L1203:
4351                     ; 342 					LedDryRFlickF = true;
4353  02e6 721a0003      	bset	_LedDisFlickF,#5
4354  02ea ac4f004f      	jpf	L5162
4380                     ; 362 void f_pLedInit(void)
4380                     ; 363 {
4381                     	switch	.text
4382  02ee               _f_pLedInit:
4386                     ; 364 	LED_POWER(1);
4388  02ee 72145000      	bset	_PA_ODR,#2
4389                     ; 365 	LED_SEAT(1);
4391  02f2 7216500f      	bset	_PD_ODR,#3
4392                     ; 366 	LED_TEMP_WATER_RED(1);
4394  02f6 7214500f      	bset	_PD_ODR,#2
4395                     ; 367 	LED_TEMP_WATER_BULE(1);
4397  02fa 721e500a      	bset	_PC_ODR,#7
4398                     ; 368 	LED_TEMP_WATER_GREEN(1);
4400  02fe 721c500a      	bset	_PC_ODR,#6
4401                     ; 369 	LED_TEMP_DRY_RED(1);
4403  0302 721a500a      	bset	_PC_ODR,#5
4404                     ; 370 	LED_TEMP_DRY_BULE(1);
4406  0306 7218500a      	bset	_PC_ODR,#4
4407                     ; 371 	LED_TEMP_DRY_GREEN(1);
4409  030a 7216500a      	bset	_PC_ODR,#3
4410                     ; 372 }
4413  030e 81            	ret
4444                     ; 387 void f_pLedDriveDeal(void)
4444                     ; 388 {
4445                     	switch	.text
4446  030f               _f_pLedDriveDeal:
4450                     ; 389 	LED_POWER(1);
4452  030f 72145000      	bset	_PA_ODR,#2
4453                     ; 390 	LED_SEAT(1);
4455  0313 7216500f      	bset	_PD_ODR,#3
4456                     ; 391 	LED_TEMP_WATER_RED(1);
4458  0317 7214500f      	bset	_PD_ODR,#2
4459                     ; 392 	LED_TEMP_WATER_BULE(1);
4461  031b 721e500a      	bset	_PC_ODR,#7
4462                     ; 393 	LED_TEMP_WATER_GREEN(1);
4464  031f 721c500a      	bset	_PC_ODR,#6
4465                     ; 394 	LED_TEMP_DRY_RED(1);
4467  0323 721a500a      	bset	_PC_ODR,#5
4468                     ; 395 	LED_TEMP_DRY_BULE(1);
4470  0327 7218500a      	bset	_PC_ODR,#4
4471                     ; 396 	LED_TEMP_DRY_GREEN(1);
4473  032b 7216500a      	bset	_PC_ODR,#3
4474                     ; 397 	if(LedPowerIcon || (LedPowerFlickF && LedPowerFlickS)||(LedPower500msf && LedPower500mss))
4476  032f c60004        	ld	a,_LedDisIcon
4477  0332 a501          	bcp	a,#1
4478  0334 261c          	jrne	L5403
4480  0336 c60003        	ld	a,_LedDisFlickF
4481  0339 a501          	bcp	a,#1
4482  033b 2707          	jreq	L1503
4484  033d c60002        	ld	a,_LedDisFlickS
4485  0340 a501          	bcp	a,#1
4486  0342 260e          	jrne	L5403
4487  0344               L1503:
4489  0344 c60001        	ld	a,_LedDisPower500F
4490  0347 a501          	bcp	a,#1
4491  0349 270b          	jreq	L3403
4493  034b c60000        	ld	a,_LedDisPower500S
4494  034e a501          	bcp	a,#1
4495  0350 2704          	jreq	L3403
4496  0352               L5403:
4497                     ; 399 		LED_POWER(0);
4499  0352 72155000      	bres	_PA_ODR,#2
4500  0356               L3403:
4501                     ; 401 	if(LedSeatIcon || (LedSeatFlickF && LedSeatFlickS))
4503  0356 c60004        	ld	a,_LedDisIcon
4504  0359 a502          	bcp	a,#2
4505  035b 260e          	jrne	L5503
4507  035d c60003        	ld	a,_LedDisFlickF
4508  0360 a502          	bcp	a,#2
4509  0362 270b          	jreq	L3503
4511  0364 c60002        	ld	a,_LedDisFlickS
4512  0367 a502          	bcp	a,#2
4513  0369 2704          	jreq	L3503
4514  036b               L5503:
4515                     ; 403 		LED_SEAT(0);
4517  036b 7217500f      	bres	_PD_ODR,#3
4518  036f               L3503:
4519                     ; 405 	if(LedWaterRIcon || (LedWaterRFlickF && LedWaterRFlickS))
4521  036f c60004        	ld	a,_LedDisIcon
4522  0372 a504          	bcp	a,#4
4523  0374 260e          	jrne	L1603
4525  0376 c60003        	ld	a,_LedDisFlickF
4526  0379 a504          	bcp	a,#4
4527  037b 270b          	jreq	L7503
4529  037d c60002        	ld	a,_LedDisFlickS
4530  0380 a504          	bcp	a,#4
4531  0382 2704          	jreq	L7503
4532  0384               L1603:
4533                     ; 407 		LED_TEMP_WATER_RED(0);
4535  0384 7215500f      	bres	_PD_ODR,#2
4536  0388               L7503:
4537                     ; 409 	if(LedWaterBIcon || (LedWaterBFlickF && LedWaterRFlickS))
4539  0388 c60004        	ld	a,_LedDisIcon
4540  038b a508          	bcp	a,#8
4541  038d 260e          	jrne	L5603
4543  038f c60003        	ld	a,_LedDisFlickF
4544  0392 a508          	bcp	a,#8
4545  0394 270b          	jreq	L3603
4547  0396 c60002        	ld	a,_LedDisFlickS
4548  0399 a504          	bcp	a,#4
4549  039b 2704          	jreq	L3603
4550  039d               L5603:
4551                     ; 411 		LED_TEMP_WATER_BULE(0);
4553  039d 721f500a      	bres	_PC_ODR,#7
4554  03a1               L3603:
4555                     ; 413 	if(LedWaterGIcon || (LedWaterGFlickF && LedWaterGFlickS))
4557  03a1 c60004        	ld	a,_LedDisIcon
4558  03a4 a510          	bcp	a,#16
4559  03a6 260e          	jrne	L1703
4561  03a8 c60003        	ld	a,_LedDisFlickF
4562  03ab a510          	bcp	a,#16
4563  03ad 270b          	jreq	L7603
4565  03af c60002        	ld	a,_LedDisFlickS
4566  03b2 a510          	bcp	a,#16
4567  03b4 2704          	jreq	L7603
4568  03b6               L1703:
4569                     ; 415 		LED_TEMP_WATER_GREEN(0);
4571  03b6 721d500a      	bres	_PC_ODR,#6
4572  03ba               L7603:
4573                     ; 417 	if(LedDryRIcon || (LedDryRFlickF && LedDryRFlickS))
4575  03ba c60004        	ld	a,_LedDisIcon
4576  03bd a520          	bcp	a,#32
4577  03bf 260e          	jrne	L5703
4579  03c1 c60003        	ld	a,_LedDisFlickF
4580  03c4 a520          	bcp	a,#32
4581  03c6 270b          	jreq	L3703
4583  03c8 c60002        	ld	a,_LedDisFlickS
4584  03cb a520          	bcp	a,#32
4585  03cd 2704          	jreq	L3703
4586  03cf               L5703:
4587                     ; 419 		LED_TEMP_DRY_RED(0);
4589  03cf 721b500a      	bres	_PC_ODR,#5
4590  03d3               L3703:
4591                     ; 421 	if(LedDryBIcon || (LedDryBFlickF && LedDryBFlickS))
4593  03d3 c60004        	ld	a,_LedDisIcon
4594  03d6 a540          	bcp	a,#64
4595  03d8 260e          	jrne	L1013
4597  03da c60003        	ld	a,_LedDisFlickF
4598  03dd a540          	bcp	a,#64
4599  03df 270b          	jreq	L7703
4601  03e1 c60002        	ld	a,_LedDisFlickS
4602  03e4 a540          	bcp	a,#64
4603  03e6 2704          	jreq	L7703
4604  03e8               L1013:
4605                     ; 423 		LED_TEMP_DRY_BULE(0);
4607  03e8 7219500a      	bres	_PC_ODR,#4
4608  03ec               L7703:
4609                     ; 425 	if(LedDryGIcon || (LedDryGFlickF && LedDryGFlickS))
4611  03ec c60004        	ld	a,_LedDisIcon
4612  03ef a580          	bcp	a,#128
4613  03f1 260e          	jrne	L5013
4615  03f3 c60003        	ld	a,_LedDisFlickF
4616  03f6 a580          	bcp	a,#128
4617  03f8 270b          	jreq	L3013
4619  03fa c60002        	ld	a,_LedDisFlickS
4620  03fd a580          	bcp	a,#128
4621  03ff 2704          	jreq	L3013
4622  0401               L5013:
4623                     ; 427 		LED_TEMP_DRY_GREEN(0);
4625  0401 7217500a      	bres	_PC_ODR,#3
4626  0405               L3013:
4627                     ; 429 	LedAllIcon = 0x00;
4629  0405 725f0004      	clr	_LedDisIcon
4630                     ; 430 	LedAllFlickF = 0x00;
4632  0409 725f0003      	clr	_LedDisFlickF
4633                     ; 431 	LedPower500msF = 0x00;
4635  040d 725f0001      	clr	_LedDisPower500F
4636                     ; 432 }
4639  0411 81            	ret
4652                     	xref	_TxComBuff
4653                     	xdef	_f_pLedDriveDeal
4654                     	xdef	_f_pLedDeal
4655                     	xdef	_f_pLedInit
4656                     	switch	.bss
4657  0000               _LedDisPower500S:
4658  0000 00            	ds.b	1
4659                     	xdef	_LedDisPower500S
4660  0001               _LedDisPower500F:
4661  0001 00            	ds.b	1
4662                     	xdef	_LedDisPower500F
4663  0002               _LedDisFlickS:
4664  0002 00            	ds.b	1
4665                     	xdef	_LedDisFlickS
4666  0003               _LedDisFlickF:
4667  0003 00            	ds.b	1
4668                     	xdef	_LedDisFlickF
4669  0004               _LedDisIcon:
4670  0004 00            	ds.b	1
4671                     	xdef	_LedDisIcon
4672  0005               _LedInf:
4673  0005 000000        	ds.b	3
4674                     	xdef	_LedInf
4694                     	end
