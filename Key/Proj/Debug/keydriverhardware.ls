   1                     ; C Compiler for STM8 (COSMIC Software)
   2                     ; Parser V4.11.10 - 06 Jul 2017
   3                     ; Generator (Limited) V4.4.7 - 05 Oct 2017
  14                     .const:	section	.text
  15  0000               _keyHardware:
  16  0000 05            	dc.b	5
  18  0001 0000          	dc.w	_f_GetKeys
  19                     	switch	.ubsct
  20  0000               L5_curShakeCnt:
  21  0000 00            	ds.b	1
  22  0001               L3_lastGetKeyValue:
  23  0001 00000000      	ds.b	4
 401                     	switch	.const
 402  0003               L6:
 403  0003 00000003      	dc.l	3
 404                     ; 75 void f_GetKeys(KEY_DRIVER *pKeyDriver)
 404                     ; 76 {
 405                     	scross	off
 406                     	switch	.text
 407  0000               _f_GetKeys:
 409  0000 89            	pushw	x
 410  0001 5204          	subw	sp,#4
 411       00000004      OFST:	set	4
 414                     ; 81 	if (f_IsSysTime10Ms())//10ms
 416  0003 b605          	ld	a,_sysTimeFlag+5
 417  0005 a504          	bcp	a,#4
 418  0007 2751          	jreq	L332
 419                     ; 83 		getKeyValue = KEY_DRIVER_NO_KEY;
 421  0009 ae0000        	ldw	x,#0
 422  000c 1f03          	ldw	(OFST-1,sp),x
 423  000e ae0000        	ldw	x,#0
 424  0011 1f01          	ldw	(OFST-3,sp),x
 426                     ; 87 			getKeyValue |= KEY_SIGLE_POWER;
 428  0013 7b04          	ld	a,(OFST+0,sp)
 429  0015 aa01          	or	a,#1
 430  0017 6b04          	ld	(OFST+0,sp),a
 432                     ; 92 			getKeyValue |= KEY_SIGLE_STOP;
 434  0019 7b04          	ld	a,(OFST+0,sp)
 435  001b aa02          	or	a,#2
 436  001d 6b04          	ld	(OFST+0,sp),a
 438                     ; 96 		if (getKeyValue == lastGetKeyValue)
 440  001f ae0001        	ldw	x,#L3_lastGetKeyValue
 441  0022 cd0000        	call	c_ltor
 443  0025 ae0003        	ldw	x,#L6
 444  0028 cd0000        	call	c_lcmp
 446  002b 2621          	jrne	L532
 447                     ; 98 			if (curShakeCnt < pKeyDriver->pHardDriver->keyShakeCnt)
 449  002d 1e05          	ldw	x,(OFST+1,sp)
 450  002f ee19          	ldw	x,(25,x)
 451  0031 f6            	ld	a,(x)
 452  0032 b100          	cp	a,L5_curShakeCnt
 453  0034 2304          	jrule	L732
 454                     ; 100 				curShakeCnt ++;
 456  0036 3c00          	inc	L5_curShakeCnt
 458  0038 2020          	jra	L332
 459  003a               L732:
 460                     ; 104 				pKeyDriver->data.getKeys = getKeyValue;
 462  003a 1e05          	ldw	x,(OFST+1,sp)
 463  003c a603          	ld	a,#3
 464  003e e70d          	ld	(13,x),a
 465  0040 a600          	ld	a,#0
 466  0042 e70c          	ld	(12,x),a
 467  0044 a600          	ld	a,#0
 468  0046 e70b          	ld	(11,x),a
 469  0048 a600          	ld	a,#0
 470  004a e70a          	ld	(10,x),a
 471  004c 200c          	jra	L332
 472  004e               L532:
 473                     ; 109 			curShakeCnt = 0;
 475  004e 3f00          	clr	L5_curShakeCnt
 476                     ; 110 			lastGetKeyValue = getKeyValue;
 478  0050 ae0003        	ldw	x,#3
 479  0053 bf03          	ldw	L3_lastGetKeyValue+2,x
 480  0055 ae0000        	ldw	x,#0
 481  0058 bf01          	ldw	L3_lastGetKeyValue,x
 482  005a               L332:
 483                     ; 113 }
 486  005a 5b06          	addw	sp,#6
 487  005c 81            	ret
 512                     	xdef	_keyHardware
 513                     	xdef	_f_GetKeys
 514                     	xref.b	_sysTimeFlag
 533                     	xref	c_lcmp
 534                     	xref	c_ltor
 535                     	end
