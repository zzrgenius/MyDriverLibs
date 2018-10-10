   1                     ; C Compiler for STM8 (COSMIC Software)
   2                     ; Parser V4.8.32 - 23 Mar 2010
   3                     ; Generator V4.3.4 - 23 Mar 2010
3223                     ; 66 void f_pUart1SendByte(uchar nByte)
3223                     ; 67 {
3225                     	switch	.text
3226  0000               _f_pUart1SendByte:
3230                     ; 68 	UART1_DATA_DR = nByte;  
3232  0000 c75231        	ld	_UART1_DR,a
3233                     ; 69 }
3236  0003 81            	ret
3281                     ; 84 uchar f_pUart1ReceByte(void)
3281                     ; 85 {
3282                     	switch	.text
3283  0004               _f_pUart1ReceByte:
3285  0004 89            	pushw	x
3286       00000002      OFST:	set	2
3289                     ; 86 	uchar nTemp = 0;
3291                     ; 87 	volatile uchar nError = 0;
3293  0005 0f02          	clr	(OFST+0,sp)
3294                     ; 89 	nError = UART1_DATA_SR;//先读一次SR，再读DR可清除故障标志
3296  0007 c65230        	ld	a,_UART1_SR
3297  000a 6b02          	ld	(OFST+0,sp),a
3298                     ; 90 	nError = 0;
3300  000c 0f02          	clr	(OFST+0,sp)
3302  000e 2011          	jra	L3622
3303  0010               L7522:
3304                     ; 93 		nError ++;
3306  0010 0c02          	inc	(OFST+0,sp)
3307                     ; 94 		if(nError >= 30)
3309  0012 7b02          	ld	a,(OFST+0,sp)
3310  0014 a11e          	cp	a,#30
3311  0016 2509          	jrult	L3622
3312                     ; 95 			break;
3313  0018               L5622:
3314                     ; 97 	nTemp = UART1_DATA_DR;	//读寄存器会清除标志(清除故障)
3316  0018 c65231        	ld	a,_UART1_DR
3317  001b 6b01          	ld	(OFST-1,sp),a
3318                     ; 98 	return nTemp;
3320  001d 7b01          	ld	a,(OFST-1,sp)
3323  001f 85            	popw	x
3324  0020 81            	ret
3325  0021               L3622:
3326                     ; 91 	while(!(UART1_DATA_SR&0x20))//等待数据接收,RXNE
3328  0021 c65230        	ld	a,_UART1_SR
3329  0024 a520          	bcp	a,#32
3330  0026 27e8          	jreq	L7522
3331  0028 20ee          	jra	L5622
3356                     ; 114 uchar f_pUart1BufAddJudge(void)
3356                     ; 115 {
3357                     	switch	.text
3358  002a               _f_pUart1BufAddJudge:
3362                     ; 116 	if(Uart1Tx.rUart1UseLine < UART1_MAX_LINE)
3364  002a c6009f        	ld	a,_Uart1Tx+2
3365  002d a105          	cp	a,#5
3366  002f 2407          	jruge	L1032
3367                     ; 118 		Uart1Tx.rUart1UseLine ++;
3369  0031 725c009f      	inc	_Uart1Tx+2
3370                     ; 119 		return true;
3372  0035 a601          	ld	a,#1
3375  0037 81            	ret
3376  0038               L1032:
3377                     ; 123 		return false;
3379  0038 4f            	clr	a
3382  0039 81            	ret
3409                     ; 140 IT_HEADE void UART1_TX_Interrupt(void)
3409                     ; 141 {	
3411                     	switch	.text
3412  003a               f_UART1_TX_Interrupt:
3414  003a 3b0002        	push	c_x+2
3415  003d be00          	ldw	x,c_x
3416  003f 89            	pushw	x
3417  0040 3b0002        	push	c_y+2
3418  0043 be00          	ldw	x,c_y
3419  0045 89            	pushw	x
3420  0046 be02          	ldw	x,c_lreg+2
3421  0048 89            	pushw	x
3422  0049 be00          	ldw	x,c_lreg
3423  004b 89            	pushw	x
3426                     ; 142 	Uart1Tx.rUart1NoComCnt = 0;
3428  004c 5f            	clrw	x
3429  004d cf00a1        	ldw	_Uart1Tx+4,x
3430                     ; 143 	if(Uart1ComFlag.rUart1EnSendFlag)//有要发送的缓存
3432  0050 c60000        	ld	a,_Uart1ComFlag
3433  0053 a501          	bcp	a,#1
3434  0055 2734          	jreq	L5132
3435                     ; 145 		if(Uart1Tx.rUart1ComPos <= Uart1Tx.Uart1ComBuff[Uart1Tx.rUart1ComLine][0])
3437  0057 c6009d        	ld	a,_Uart1Tx
3438  005a 97            	ld	xl,a
3439  005b a61e          	ld	a,#30
3440  005d 42            	mul	x,a
3441  005e d600a3        	ld	a,(_Uart1Tx+6,x)
3442  0061 c100a0        	cp	a,_Uart1Tx+3
3443  0064 251a          	jrult	L7132
3444                     ; 147 			f_pUart1SendByte(Uart1Tx.Uart1ComBuff[Uart1Tx.rUart1ComLine][Uart1Tx.rUart1ComPos]);
3446  0066 c6009d        	ld	a,_Uart1Tx
3447  0069 97            	ld	xl,a
3448  006a a61e          	ld	a,#30
3449  006c 42            	mul	x,a
3450  006d 01            	rrwa	x,a
3451  006e cb00a0        	add	a,_Uart1Tx+3
3452  0071 2401          	jrnc	L41
3453  0073 5c            	incw	x
3454  0074               L41:
3455  0074 02            	rlwa	x,a
3456  0075 d600a3        	ld	a,(_Uart1Tx+6,x)
3457  0078 ad86          	call	_f_pUart1SendByte
3459                     ; 148 			Uart1Tx.rUart1ComPos ++;
3461  007a 725c00a0      	inc	_Uart1Tx+3
3463  007e 200b          	jra	L5132
3464  0080               L7132:
3465                     ; 152 			if(Uart1Tx.rUart1ComPos < UART1_MAX_BYTE - 1)//需要判断最后一个发送完成
3467  0080 c600a0        	ld	a,_Uart1Tx+3
3468  0083 a11d          	cp	a,#29
3469  0085 2404          	jruge	L5132
3470                     ; 154 				Uart1Tx.rUart1ComPos ++;	
3472  0087 725c00a0      	inc	_Uart1Tx+3
3473  008b               L5132:
3474                     ; 158 	UART1_DATA_SR &= (~0xC0);//TIEN,TICEN
3476  008b c65230        	ld	a,_UART1_SR
3477  008e a43f          	and	a,#63
3478  0090 c75230        	ld	_UART1_SR,a
3479                     ; 159 }
3482  0093 85            	popw	x
3483  0094 bf00          	ldw	c_lreg,x
3484  0096 85            	popw	x
3485  0097 bf02          	ldw	c_lreg+2,x
3486  0099 85            	popw	x
3487  009a bf00          	ldw	c_y,x
3488  009c 320002        	pop	c_y+2
3489  009f 85            	popw	x
3490  00a0 bf00          	ldw	c_x,x
3491  00a2 320002        	pop	c_x+2
3492  00a5 80            	iret
3517                     ; 174 IT_HEADE void UART1_RX_Interrupt(void)
3517                     ; 175 {
3518                     	switch	.text
3519  00a6               f_UART1_RX_Interrupt:
3521  00a6 3b0002        	push	c_x+2
3522  00a9 be00          	ldw	x,c_x
3523  00ab 89            	pushw	x
3524  00ac 3b0002        	push	c_y+2
3525  00af be00          	ldw	x,c_y
3526  00b1 89            	pushw	x
3527  00b2 be02          	ldw	x,c_lreg+2
3528  00b4 89            	pushw	x
3529  00b5 be00          	ldw	x,c_lreg
3530  00b7 89            	pushw	x
3533                     ; 176 	Uart1Rx.rUart1NoComCnt = 0;
3535  00b8 5f            	clrw	x
3536  00b9 cf0005        	ldw	_Uart1Rx+4,x
3537                     ; 177 	Uart1ComFlag.rUart1EnAddLine = true;
3539  00bc 72120000      	bset	_Uart1ComFlag,#1
3540                     ; 179 	if(Uart1Rx.rUart1ComPos >= UART1_MAX_BYTE)
3542  00c0 c60004        	ld	a,_Uart1Rx+3
3543  00c3 a11e          	cp	a,#30
3544  00c5 2504          	jrult	L5332
3545                     ; 181 		Uart1Rx.rUart1ComPos = UART1_MAX_BYTE - 1;
3547  00c7 351d0004      	mov	_Uart1Rx+3,#29
3548  00cb               L5332:
3549                     ; 183 	Uart1Rx.Uart1ComBuff[Uart1Rx.rUart1BuffLine][Uart1Rx.rUart1ComPos] = f_pUart1ReceByte();
3551  00cb c60002        	ld	a,_Uart1Rx+1
3552  00ce 97            	ld	xl,a
3553  00cf a61e          	ld	a,#30
3554  00d1 42            	mul	x,a
3555  00d2 01            	rrwa	x,a
3556  00d3 cb0004        	add	a,_Uart1Rx+3
3557  00d6 2401          	jrnc	L02
3558  00d8 5c            	incw	x
3559  00d9               L02:
3560  00d9 02            	rlwa	x,a
3561  00da 89            	pushw	x
3562  00db cd0004        	call	_f_pUart1ReceByte
3564  00de 85            	popw	x
3565  00df d70007        	ld	(_Uart1Rx+6,x),a
3566                     ; 184 	Uart1Rx.rUart1ComPos++;
3568  00e2 725c0004      	inc	_Uart1Rx+3
3569                     ; 185 }
3572  00e6 85            	popw	x
3573  00e7 bf00          	ldw	c_lreg,x
3574  00e9 85            	popw	x
3575  00ea bf02          	ldw	c_lreg+2,x
3576  00ec 85            	popw	x
3577  00ed bf00          	ldw	c_y,x
3578  00ef 320002        	pop	c_y+2
3579  00f2 85            	popw	x
3580  00f3 bf00          	ldw	c_x,x
3581  00f5 320002        	pop	c_x+2
3582  00f8 80            	iret
3608                     ; 200 void f_pUart1TimeCnt(void)
3608                     ; 201 {
3610                     	switch	.text
3611  00f9               _f_pUart1TimeCnt:
3615                     ; 203 	AddIntData(&Uart1Rx.rUart1NoComCnt);
3617  00f9 ae0005        	ldw	x,#_Uart1Rx+4
3618  00fc cd0000        	call	_AddIntData
3620                     ; 205 	if(Uart1ComFlag.rUart1EnAddLine)
3622  00ff c60000        	ld	a,_Uart1ComFlag
3623  0102 a502          	bcp	a,#2
3624  0104 272c          	jreq	L7432
3625                     ; 207 		if(Uart1Rx.rUart1NoComCnt >=UART1_RX_GAP_TM)//超过接收的2个字节间隙时间,认为已经换帧
3627  0106 ce0005        	ldw	x,_Uart1Rx+4
3628  0109 a30002        	cpw	x,#2
3629  010c 2524          	jrult	L7432
3630                     ; 209 			Uart1ComFlag.rUart1EnAddLine = false;
3632  010e 72130000      	bres	_Uart1ComFlag,#1
3633                     ; 210 			if(Uart1Rx.rUart1UseLine < UART1_MAX_LINE)//需解析行累加
3635  0112 c60003        	ld	a,_Uart1Rx+2
3636  0115 a105          	cp	a,#5
3637  0117 2419          	jruge	L7432
3638                     ; 212 				Uart1Rx.rUart1UseLine++;	
3640  0119 725c0003      	inc	_Uart1Rx+2
3641                     ; 214 				if(Uart1Rx.rUart1BuffLine < (UART1_MAX_LINE - 1))
3643  011d c60002        	ld	a,_Uart1Rx+1
3644  0120 a104          	cp	a,#4
3645  0122 2406          	jruge	L5532
3646                     ; 216 					Uart1Rx.rUart1BuffLine++;	
3648  0124 725c0002      	inc	_Uart1Rx+1
3650  0128 2004          	jra	L7532
3651  012a               L5532:
3652                     ; 220 					Uart1Rx.rUart1BuffLine = 0;
3654  012a 725f0002      	clr	_Uart1Rx+1
3655  012e               L7532:
3656                     ; 222 				Uart1Rx.rUart1ComPos = 0;
3658  012e 725f0004      	clr	_Uart1Rx+3
3659  0132               L7432:
3660                     ; 227 	if(Uart1Rx.rUart1NoComCnt >= 200) // 2 s
3662  0132 ce0005        	ldw	x,_Uart1Rx+4
3663  0135 a300c8        	cpw	x,#200
3664  0138 2506          	jrult	L1632
3665                     ; 229 		Uart1ComFlag.rUart1CommErrFlag = true;	
3667  013a 72160000      	bset	_Uart1ComFlag,#3
3669  013e 2004          	jra	L3632
3670  0140               L1632:
3671                     ; 233 		Uart1ComFlag.rUart1CommErrFlag = false;	
3673  0140 72170000      	bres	_Uart1ComFlag,#3
3674  0144               L3632:
3675                     ; 236 	AddIntData(&Uart1Tx.rUart1NoComCnt);
3677  0144 ae00a1        	ldw	x,#_Uart1Tx+4
3678  0147 cd0000        	call	_AddIntData
3680                     ; 237 }
3683  014a 81            	ret
3732                     ; 252 void f_pUart1Init(uint baudRate)
3732                     ; 253 {
3733                     	switch	.text
3734  014b               _f_pUart1Init:
3736  014b 5206          	subw	sp,#6
3737       00000006      OFST:	set	6
3740                     ; 255 	UART1_DATA_CR1 = 0X00;
3742  014d 725f5234      	clr	_UART1_CR1
3743                     ; 256 	UART1_DATA_CR2 = 0X00;
3745  0151 725f5235      	clr	_UART1_CR2
3746                     ; 257 	UART1_DATA_CR3 = 0X00;
3748  0155 725f5236      	clr	_UART1_CR3
3749                     ; 258 	UART1_DATA_SR = 0X00;
3751  0159 725f5230      	clr	_UART1_SR
3752                     ; 262 	nRate = SYS_CLOCK/baudRate;
3754  015d cd0000        	call	c_uitolx
3756  0160 96            	ldw	x,sp
3757  0161 1c0001        	addw	x,#OFST-5
3758  0164 cd0000        	call	c_rtol
3760  0167 ae2400        	ldw	x,#9216
3761  016a bf02          	ldw	c_lreg+2,x
3762  016c ae00f4        	ldw	x,#244
3763  016f bf00          	ldw	c_lreg,x
3764  0171 96            	ldw	x,sp
3765  0172 1c0001        	addw	x,#OFST-5
3766  0175 cd0000        	call	c_ldiv
3768  0178 be02          	ldw	x,c_lreg+2
3769  017a 1f05          	ldw	(OFST-1,sp),x
3770                     ; 263 	UART1_DATA_BR2 = (uchar)((nRate&0x000f) +( (nRate>>8)&0xf0));
3772  017c 7b05          	ld	a,(OFST-1,sp)
3773  017e a4f0          	and	a,#240
3774  0180 6b04          	ld	(OFST-2,sp),a
3775  0182 7b06          	ld	a,(OFST+0,sp)
3776  0184 a40f          	and	a,#15
3777  0186 1b04          	add	a,(OFST-2,sp)
3778  0188 c75233        	ld	_UART1_BRR2,a
3779                     ; 264 	UART1_DATA_BR1 = (uchar)(nRate>>4);
3781  018b 1e05          	ldw	x,(OFST-1,sp)
3782  018d 54            	srlw	x
3783  018e 54            	srlw	x
3784  018f 54            	srlw	x
3785  0190 54            	srlw	x
3786  0191 9f            	ld	a,xl
3787  0192 c75232        	ld	_UART1_BRR1,a
3788                     ; 265 	UART1_CR2_REN_TRUE;	//接收中断开启
3790  0195 72145235      	bset	_UART1_CR2,#2
3791                     ; 266 	UART1_CR2_RIEN_TRUE;	 
3793  0199 721a5235      	bset	_UART1_CR2,#5
3794                     ; 267 	UART1_CR2_TEN_TRUE;	 
3796  019d 72165235      	bset	_UART1_CR2,#3
3797                     ; 268 	UART1_CR2_TIEN_TRUE;	//发送中断开启 
3799  01a1 721c5235      	bset	_UART1_CR2,#6
3800                     ; 269 }
3803  01a5 5b06          	addw	sp,#6
3804  01a7 81            	ret
3807                     	bsct
3808  0000               L7042_i:
3809  0000 0000          	dc.w	0
4635                     ; 284 void f_pUart1GetSendData(BIG_STRUCT *pFuctionData)
4635                     ; 285 {
4636                     	switch	.text
4637  01a8               _f_pUart1GetSendData:
4641                     ; 287 	if(f_pUart1BufAddJudge() == false)//无法继续添加
4643  01a8 cd002a        	call	_f_pUart1BufAddJudge
4645  01ab 4d            	tnz	a
4646  01ac 2601          	jrne	L1213
4647                     ; 289 		return;
4650  01ae 81            	ret
4651  01af               L1213:
4652                     ; 291 	NeedSendInf.NeedSendFlag = false;	
4654  01af 72110139      	bres	_NeedSendInf,#0
4655                     ; 293 	TxComBuff.jHead = 0x31;
4657  01b3 3531014c      	mov	_TxComBuff,#49
4658                     ; 294 	TxComBuff.jCheck = f_CheckSum((unsigned char *)&TxComBuff, 0,sizeof(UART1_COM_TX) - 1);
4660  01b7 4b07          	push	#7
4661  01b9 4b00          	push	#0
4662  01bb ae014c        	ldw	x,#_TxComBuff
4663  01be cd0000        	call	_f_CheckSum
4665  01c1 5b02          	addw	sp,#2
4666  01c3 01            	rrwa	x,a
4667  01c4 c70153        	ld	_TxComBuff+7,a
4668  01c7 02            	rlwa	x,a
4669                     ; 296 	Uart1Tx.Uart1ComBuff[Uart1Tx.rUart1BuffLine][0] = sizeof(UART1_COM_TX);
4671  01c8 c6009e        	ld	a,_Uart1Tx+1
4672  01cb 97            	ld	xl,a
4673  01cc a61e          	ld	a,#30
4674  01ce 42            	mul	x,a
4675  01cf a608          	ld	a,#8
4676  01d1 d700a3        	ld	(_Uart1Tx+6,x),a
4677                     ; 297 	f_Memcpy(&Uart1Tx.Uart1ComBuff[Uart1Tx.rUart1BuffLine][1], &TxComBuff, sizeof(UART1_COM_TX));
4679  01d4 ae0008        	ldw	x,#8
4680  01d7 89            	pushw	x
4681  01d8 ae014c        	ldw	x,#_TxComBuff
4682  01db 89            	pushw	x
4683  01dc c6009e        	ld	a,_Uart1Tx+1
4684  01df 97            	ld	xl,a
4685  01e0 a61e          	ld	a,#30
4686  01e2 42            	mul	x,a
4687  01e3 1c00a4        	addw	x,#_Uart1Tx+7
4688  01e6 cd0000        	call	_f_Memcpy
4690  01e9 5b04          	addw	sp,#4
4691                     ; 298 	TxComBuff.jFunCmd = 0x00;
4693  01eb 725f0152      	clr	_TxComBuff+6
4694                     ; 300 	if(Uart1Tx.rUart1BuffLine< (UART1_MAX_LINE - 1))
4696  01ef c6009e        	ld	a,_Uart1Tx+1
4697  01f2 a104          	cp	a,#4
4698  01f4 2406          	jruge	L3213
4699                     ; 302 		Uart1Tx.rUart1BuffLine ++;
4701  01f6 725c009e      	inc	_Uart1Tx+1
4703  01fa 2004          	jra	L5213
4704  01fc               L3213:
4705                     ; 306 		Uart1Tx.rUart1BuffLine = 0;
4707  01fc 725f009e      	clr	_Uart1Tx+1
4708  0200               L5213:
4709                     ; 308 }
4712  0200 81            	ret
4754                     ; 323 void f_pUart1SendDeal(BIG_STRUCT *pFuctionData)
4754                     ; 324 {
4755                     	switch	.text
4756  0201               _f_pUart1SendDeal:
4760                     ; 325 	if(NeedSendInf.NeedSendFlag)	//添加	需要发送的数据
4762  0201 c60139        	ld	a,_NeedSendInf
4763  0204 a501          	bcp	a,#1
4764  0206 2702          	jreq	L7413
4765                     ; 327 		f_pUart1GetSendData(pFuctionData);
4767  0208 ad9e          	call	_f_pUart1GetSendData
4769  020a               L7413:
4770                     ; 329 	if(Uart1Tx.rUart1UseLine > 0)//有要发送的缓存
4772  020a 725d009f      	tnz	_Uart1Tx+2
4773  020e 2764          	jreq	L1513
4774                     ; 331 		Uart1ComFlag.rUart1EnSendFlag = true;	//允许发送
4776  0210 72100000      	bset	_Uart1ComFlag,#0
4777                     ; 332 		if(Uart1Tx.rUart1NoComCnt >= 50)//500ms无发送，阻塞了,重发当前帧
4779  0214 ce00a1        	ldw	x,_Uart1Tx+4
4780  0217 a30032        	cpw	x,#50
4781  021a 2508          	jrult	L3513
4782                     ; 334 			Uart1ComFlag.rUart1StartSend = true;//启动发送
4784  021c 72140000      	bset	_Uart1ComFlag,#2
4785                     ; 335 			Uart1Tx.rUart1ComPos = 0;
4787  0220 725f00a0      	clr	_Uart1Tx+3
4788  0224               L3513:
4789                     ; 337 		if(Uart1Tx.rUart1ComPos > Uart1Tx.Uart1ComBuff[Uart1Tx.rUart1ComLine][0])//当前帧发完
4791  0224 c6009d        	ld	a,_Uart1Tx
4792  0227 97            	ld	xl,a
4793  0228 a61e          	ld	a,#30
4794  022a 42            	mul	x,a
4795  022b d600a3        	ld	a,(_Uart1Tx+6,x)
4796  022e c100a0        	cp	a,_Uart1Tx+3
4797  0231 2423          	jruge	L5513
4798                     ; 339 			Uart1Tx.rUart1UseLine--;	
4800  0233 725a009f      	dec	_Uart1Tx+2
4801                     ; 340 			Uart1Tx.rUart1ComPos = 0;
4803  0237 725f00a0      	clr	_Uart1Tx+3
4804                     ; 341 			if(Uart1Tx.rUart1ComLine < (UART1_MAX_LINE - 1))
4806  023b c6009d        	ld	a,_Uart1Tx
4807  023e a104          	cp	a,#4
4808  0240 2406          	jruge	L7513
4809                     ; 343 				Uart1Tx.rUart1ComLine++;	
4811  0242 725c009d      	inc	_Uart1Tx
4813  0246 2004          	jra	L1613
4814  0248               L7513:
4815                     ; 347 				Uart1Tx.rUart1ComLine = 0;
4817  0248 725f009d      	clr	_Uart1Tx
4818  024c               L1613:
4819                     ; 349 			if(Uart1Tx.rUart1UseLine > 0)//当前发完还有需要发送
4821  024c 725d009f      	tnz	_Uart1Tx+2
4822  0250 2704          	jreq	L5513
4823                     ; 351 				Uart1ComFlag.rUart1StartSend = true;//启动发送	
4825  0252 72140000      	bset	_Uart1ComFlag,#2
4826  0256               L5513:
4827                     ; 354 		if(Uart1ComFlag.rUart1StartSend)//启动发送
4829  0256 c60000        	ld	a,_Uart1ComFlag
4830  0259 a504          	bcp	a,#4
4831  025b 2723          	jreq	L7613
4832                     ; 356 			Uart1ComFlag.rUart1StartSend = false;	
4834  025d 72150000      	bres	_Uart1ComFlag,#2
4835                     ; 357 			Uart1Tx.rUart1ComPos = 2;
4837  0261 350200a0      	mov	_Uart1Tx+3,#2
4838                     ; 358 			f_pUart1SendByte(Uart1Tx.Uart1ComBuff[Uart1Tx.rUart1ComLine][1]);//发送第1个数据
4840  0265 c6009d        	ld	a,_Uart1Tx
4841  0268 97            	ld	xl,a
4842  0269 a61e          	ld	a,#30
4843  026b 42            	mul	x,a
4844  026c d600a4        	ld	a,(_Uart1Tx+7,x)
4845  026f cd0000        	call	_f_pUart1SendByte
4847  0272 200c          	jra	L7613
4848  0274               L1513:
4849                     ; 363 		Uart1ComFlag.rUart1EnSendFlag = false;
4851  0274 72110000      	bres	_Uart1ComFlag,#0
4852                     ; 364 		Uart1ComFlag.rUart1StartSend = true;
4854  0278 72140000      	bset	_Uart1ComFlag,#2
4855                     ; 365 		Uart1Tx.rUart1NoComCnt = 0;
4857  027c 5f            	clrw	x
4858  027d cf00a1        	ldw	_Uart1Tx+4,x
4859  0280               L7613:
4860                     ; 367 }
4863  0280 81            	ret
4915                     ; 382 void f_pUart1ReceDeal(BIG_STRUCT *pFuctionData)
4915                     ; 383 {
4916                     	switch	.text
4917  0281               _f_pUart1ReceDeal:
4919  0281 89            	pushw	x
4920  0282 89            	pushw	x
4921       00000002      OFST:	set	2
4924                     ; 385 	uint nCRCbuf = 0;
4926  0283 5f            	clrw	x
4927  0284 1f01          	ldw	(OFST-1,sp),x
4928                     ; 387 	if(Uart1Rx.rUart1UseLine > 0)//有需要解析的行
4930  0286 725d0003      	tnz	_Uart1Rx+2
4931  028a 2603          	jrne	L43
4932  028c cc0389        	jp	L5123
4933  028f               L43:
4934                     ; 389 		if(Uart1Rx.Uart1ComBuff[Uart1Rx.rUart1ComLine][0] == 0x31)
4936  028f c60001        	ld	a,_Uart1Rx
4937  0292 97            	ld	xl,a
4938  0293 a61e          	ld	a,#30
4939  0295 42            	mul	x,a
4940  0296 d60007        	ld	a,(_Uart1Rx+6,x)
4941  0299 a131          	cp	a,#49
4942  029b 2703          	jreq	L63
4943  029d cc0374        	jp	L7123
4944  02a0               L63:
4945                     ; 391 			f_Memcpy(&RxComBuff, &Uart1Rx.Uart1ComBuff[Uart1Rx.rUart1ComLine][0], sizeof(UART1_COM_RX));	
4947  02a0 ae0012        	ldw	x,#18
4948  02a3 89            	pushw	x
4949  02a4 c60001        	ld	a,_Uart1Rx
4950  02a7 97            	ld	xl,a
4951  02a8 a61e          	ld	a,#30
4952  02aa 42            	mul	x,a
4953  02ab 1c0007        	addw	x,#_Uart1Rx+6
4954  02ae 89            	pushw	x
4955  02af ae013a        	ldw	x,#_RxComBuff
4956  02b2 cd0000        	call	_f_Memcpy
4958  02b5 5b04          	addw	sp,#4
4959                     ; 392 			NeedSendInf.NeedSendFlag = 1;
4961  02b7 72100139      	bset	_NeedSendInf,#0
4962                     ; 393 			pFuctionData->bInitInf = RxComBuff.nInitInf;
4964  02bb 1e03          	ldw	x,(OFST+1,sp)
4965  02bd c6013b        	ld	a,_RxComBuff+1
4966  02c0 f7            	ld	(x),a
4967                     ; 394 			pFuctionData->SystemCurState = RxComBuff.nSystemCurState;
4969  02c1 1e03          	ldw	x,(OFST+1,sp)
4970  02c3 c6013c        	ld	a,_RxComBuff+2
4971  02c6 e701          	ld	(1,x),a
4972                     ; 395 			pFuctionData->curFunInf.curFunc = RxComBuff.nCurFunc;
4974  02c8 1e03          	ldw	x,(OFST+1,sp)
4975  02ca c6013d        	ld	a,_RxComBuff+3
4976  02cd e704          	ld	(4,x),a
4977                     ; 396 			pFuctionData->WashInf.bTempChange = RxComBuff.nTempChange;
4979  02cf 1e03          	ldw	x,(OFST+1,sp)
4980  02d1 c6013e        	ld	a,_RxComBuff+4
4981  02d4 a401          	and	a,#1
4982  02d6 e71f          	ld	(31,x),a
4983                     ; 397 			pFuctionData->seatInf.seatSensorState.bSwitchState = RxComBuff.nSwitchState;
4985  02d8 1e03          	ldw	x,(OFST+1,sp)
4986  02da c6013e        	ld	a,_RxComBuff+4
4987  02dd 44            	srl	a
4988  02de a401          	and	a,#1
4989  02e0 e81a          	xor	a,(26,x)
4990  02e2 a401          	and	a,#1
4991  02e4 e81a          	xor	a,(26,x)
4992  02e6 e71a          	ld	(26,x),a
4993                     ; 398 			pFuctionData->systemErrInf.byte = RxComBuff.nSystemErrInf;
4995  02e8 1e03          	ldw	x,(OFST+1,sp)
4996  02ea 90ce013f      	ldw	y,_RxComBuff+5
4997  02ee ef20          	ldw	(32,x),y
4998                     ; 399 			pFuctionData->seatInf.SeatOffTm.hour = RxComBuff.nSeatOffHour;
5000  02f0 1e03          	ldw	x,(OFST+1,sp)
5001  02f2 90ce0141      	ldw	y,_RxComBuff+7
5002  02f6 ef18          	ldw	(24,x),y
5003                     ; 400 			pFuctionData->seatInf.SwitchSeatEn = RxComBuff.nSeatEn;
5005  02f8 1e03          	ldw	x,(OFST+1,sp)
5006  02fa c60143        	ld	a,_RxComBuff+9
5007  02fd a401          	and	a,#1
5008  02ff e811          	xor	a,(17,x)
5009  0301 a401          	and	a,#1
5010  0303 e811          	xor	a,(17,x)
5011  0305 e711          	ld	(17,x),a
5012                     ; 401 			pFuctionData->curFunInf.posState = RxComBuff.nPosState;
5014  0307 1e03          	ldw	x,(OFST+1,sp)
5015  0309 c60147        	ld	a,_RxComBuff+13
5016  030c e707          	ld	(7,x),a
5017                     ; 402 			pFuctionData->curFunInf.levelState = RxComBuff.nLevelState;
5019  030e 1e03          	ldw	x,(OFST+1,sp)
5020  0310 c60148        	ld	a,_RxComBuff+14
5021  0313 e706          	ld	(6,x),a
5022                     ; 403 			if(pFuctionData->addrInf.addrFlag == 0x00)
5024  0315 1e03          	ldw	x,(OFST+1,sp)
5025  0317 e625          	ld	a,(37,x)
5026  0319 a501          	bcp	a,#1
5027  031b 260d          	jrne	L1223
5028                     ; 405 				pFuctionData->addrInf.addrFlag = RxComBuff.nAddrFlag;//调整地址码
5030  031d 1e03          	ldw	x,(OFST+1,sp)
5031  031f c60149        	ld	a,_RxComBuff+15
5032  0322 e825          	xor	a,(37,x)
5033  0324 a401          	and	a,#1
5034  0326 e825          	xor	a,(37,x)
5035  0328 e725          	ld	(37,x),a
5036  032a               L1223:
5037                     ; 407 			pFuctionData->flushTimeState = RxComBuff.nFlushTimeState;
5039  032a 1e03          	ldw	x,(OFST+1,sp)
5040  032c c6014a        	ld	a,_RxComBuff+16
5041  032f e726          	ld	(38,x),a
5042                     ; 408 			pFuctionData->heatInf.waterHeat.setWaterLevel = RxComBuff.nSetWaterLevel;
5044  0331 1e03          	ldw	x,(OFST+1,sp)
5045  0333 c60144        	ld	a,_RxComBuff+10
5046  0336 e70d          	ld	(13,x),a
5047                     ; 409 			pFuctionData->heatInf.seatHeat.setSeatLevel = RxComBuff.nSetSeatLevel;
5049  0338 1e03          	ldw	x,(OFST+1,sp)
5050  033a c60146        	ld	a,_RxComBuff+12
5051  033d e70b          	ld	(11,x),a
5052                     ; 410 			pFuctionData->heatInf.dryHeat.setDryLevel = RxComBuff.nSetDryLevel;
5054  033f 1e03          	ldw	x,(OFST+1,sp)
5055  0341 c60145        	ld	a,_RxComBuff+11
5056  0344 e709          	ld	(9,x),a
5057                     ; 412 			if(TxComBuff.jSetSeatLevel == RxComBuff.nSetSeatLevel)
5059  0346 c6014f        	ld	a,_TxComBuff+3
5060  0349 c10146        	cp	a,_RxComBuff+12
5061  034c 260f          	jrne	L3223
5062                     ; 414 				if(LedInf.delaySeatDis)
5064  034e c60002        	ld	a,_LedInf+2
5065  0351 a501          	bcp	a,#1
5066  0353 2708          	jreq	L3223
5067                     ; 416 					LedInf.delaySeatDis = false;
5069  0355 72110002      	bres	_LedInf+2,#0
5070                     ; 417 					LedInf.DryDisCnt = 0;// 延时10S
5072  0359 725f0001      	clr	_LedInf+1
5073  035d               L3223:
5074                     ; 420 			if(TxComBuff.jSetDryLevel == RxComBuff.nSetDryLevel)
5076  035d c6014e        	ld	a,_TxComBuff+2
5077  0360 c10145        	cp	a,_RxComBuff+11
5078  0363 260f          	jrne	L7123
5079                     ; 422 				if(LedInf.delayDrytDis)
5081  0365 c60002        	ld	a,_LedInf+2
5082  0368 a502          	bcp	a,#2
5083  036a 2708          	jreq	L7123
5084                     ; 424 					LedInf.delayDrytDis = false;
5086  036c 72130002      	bres	_LedInf+2,#1
5087                     ; 425 					LedInf.DryDisCnt = 11;// 延时10S
5089  0370 350b0001      	mov	_LedInf+1,#11
5090  0374               L7123:
5091                     ; 430 		Uart1Rx.rUart1UseLine  --;
5093  0374 725a0003      	dec	_Uart1Rx+2
5094                     ; 431 		if(Uart1Rx.rUart1ComLine < (UART1_MAX_LINE - 1))
5096  0378 c60001        	ld	a,_Uart1Rx
5097  037b a104          	cp	a,#4
5098  037d 2406          	jruge	L3323
5099                     ; 433 			Uart1Rx.rUart1ComLine ++;
5101  037f 725c0001      	inc	_Uart1Rx
5103  0383 2004          	jra	L5123
5104  0385               L3323:
5105                     ; 437 			Uart1Rx.rUart1ComLine = 0;
5107  0385 725f0001      	clr	_Uart1Rx
5108  0389               L5123:
5109                     ; 440 }
5112  0389 5b04          	addw	sp,#4
5113  038b 81            	ret
5126                     	xdef	_f_pUart1GetSendData
5127                     	xdef	_f_pUart1BufAddJudge
5128                     	xdef	_f_pUart1ReceByte
5129                     	xdef	_f_pUart1SendByte
5130                     	xdef	f_UART1_RX_Interrupt
5131                     	xdef	f_UART1_TX_Interrupt
5132                     	xdef	_f_pUart1TimeCnt
5133                     	xdef	_f_pUart1ReceDeal
5134                     	xdef	_f_pUart1SendDeal
5135                     	xdef	_f_pUart1Init
5136                     	switch	.bss
5137  0000               _Uart1ComFlag:
5138  0000 00            	ds.b	1
5139                     	xdef	_Uart1ComFlag
5140  0001               _Uart1Rx:
5141  0001 000000000000  	ds.b	156
5142                     	xdef	_Uart1Rx
5143  009d               _Uart1Tx:
5144  009d 000000000000  	ds.b	156
5145                     	xdef	_Uart1Tx
5146  0139               _NeedSendInf:
5147  0139 00            	ds.b	1
5148                     	xdef	_NeedSendInf
5149  013a               _RxComBuff:
5150  013a 000000000000  	ds.b	18
5151                     	xdef	_RxComBuff
5152  014c               _TxComBuff:
5153  014c 000000000000  	ds.b	8
5154                     	xdef	_TxComBuff
5155                     	xref	_LedInf
5156                     	xref	_AddIntData
5157                     	xref	_f_CheckSum
5158                     	xref	_f_Memcpy
5159                     	xref.b	c_lreg
5160                     	xref.b	c_x
5161                     	xref.b	c_y
5181                     	xref	c_ldiv
5182                     	xref	c_rtol
5183                     	xref	c_uitolx
5184                     	end
