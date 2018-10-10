   1                     ; C Compiler for STM8 (COSMIC Software)
   2                     ; Parser V4.11.10 - 06 Jul 2017
   3                     ; Generator (Limited) V4.4.7 - 05 Oct 2017
  54                     ; 66 void f_AddU8Data(uchar *pData)
  54                     ; 67 {
  56                     	switch	.text
  57  0000               _f_AddU8Data:
  61                     ; 68     if (*pData < 0xff)
  63  0000 f6            	ld	a,(x)
  64  0001 a1ff          	cp	a,#255
  65  0003 2401          	jruge	L72
  66                     ; 70 		(*pData) ++;
  68  0005 7c            	inc	(x)
  69  0006               L72:
  70                     ; 72 }
  73  0006 81            	ret
 108                     ; 87 void f_DecU8Data(uchar *pData)
 108                     ; 88 {
 109                     	switch	.text
 110  0007               _f_DecU8Data:
 114                     ; 89     if (*pData > 0)
 116  0007 7d            	tnz	(x)
 117  0008 2701          	jreq	L74
 118                     ; 91 		(*pData) --;
 120  000a 7a            	dec	(x)
 121  000b               L74:
 122                     ; 93 }
 125  000b 81            	ret
 160                     ; 108 void f_AddU16Data(uint *pData)
 160                     ; 109 {
 161                     	switch	.text
 162  000c               _f_AddU16Data:
 166                     ; 110     if (*pData < 0xffff)
 168  000c 9093          	ldw	y,x
 169  000e 90fe          	ldw	y,(y)
 170  0010 90a3ffff      	cpw	y,#65535
 171  0014 2408          	jruge	L76
 172                     ; 112 		(*pData) ++;
 174  0016 9093          	ldw	y,x
 175  0018 fe            	ldw	x,(x)
 176  0019 1c0001        	addw	x,#1
 177  001c 90ff          	ldw	(y),x
 178  001e               L76:
 179                     ; 114 }
 182  001e 81            	ret
 217                     ; 129 void f_DecU16Data(uint *pData)
 217                     ; 130 {
 218                     	switch	.text
 219  001f               _f_DecU16Data:
 223                     ; 131     if (*pData > 0)
 225  001f e601          	ld	a,(1,x)
 226  0021 fa            	or	a,(x)
 227  0022 2708          	jreq	L701
 228                     ; 133 		(*pData) --;
 230  0024 9093          	ldw	y,x
 231  0026 fe            	ldw	x,(x)
 232  0027 1d0001        	subw	x,#1
 233  002a 90ff          	ldw	(y),x
 234  002c               L701:
 235                     ; 135 }
 238  002c 81            	ret
 273                     .const:	section	.text
 274  0000               L61:
 275  0000 ffffffff      	dc.l	-1
 276                     ; 150 void f_AddU32Data(ulong *pData)
 276                     ; 151 {
 277                     	switch	.text
 278  002d               _f_AddU32Data:
 280  002d 89            	pushw	x
 281       00000000      OFST:	set	0
 284                     ; 152     if (*pData < 0xffffffff)
 286  002e cd0000        	call	c_ltor
 288  0031 ae0000        	ldw	x,#L61
 289  0034 cd0000        	call	c_lcmp
 291  0037 2407          	jruge	L721
 292                     ; 154 		(*pData) ++;
 294  0039 1e01          	ldw	x,(OFST+1,sp)
 295  003b a601          	ld	a,#1
 296  003d cd0000        	call	c_lgadc
 298  0040               L721:
 299                     ; 156 }
 302  0040 85            	popw	x
 303  0041 81            	ret
 338                     ; 171 void f_DecU32Data(ulong *pData)
 338                     ; 172 {
 339                     	switch	.text
 340  0042               _f_DecU32Data:
 342  0042 89            	pushw	x
 343       00000000      OFST:	set	0
 346                     ; 173     if (*pData > 0)
 348  0043 cd0000        	call	c_lzmp
 350  0046 2707          	jreq	L741
 351                     ; 175 		(*pData) --;
 353  0048 1e01          	ldw	x,(OFST+1,sp)
 354  004a a601          	ld	a,#1
 355  004c cd0000        	call	c_lgsbc
 357  004f               L741:
 358                     ; 177 }
 361  004f 85            	popw	x
 362  0050 81            	ret
 422                     ; 192 void f_AddRunTimerMinute(MINUTE_DEF *pTime)
 422                     ; 193 {
 423                     	switch	.text
 424  0051               _f_AddRunTimerMinute:
 428                     ; 194 	pTime->second ++;
 430  0051 7c            	inc	(x)
 431                     ; 195 	if ((pTime->second ++) >= 60)
 433  0052 f6            	ld	a,(x)
 434  0053 7c            	inc	(x)
 435  0054 a13c          	cp	a,#60
 436  0056 2504          	jrult	L102
 437                     ; 197 		pTime->second = 0;
 439  0058 7f            	clr	(x)
 440                     ; 198 		f_AddU16Data(&(pTime->minute));
 442  0059 5c            	incw	x
 443  005a adb0          	call	_f_AddU16Data
 445  005c               L102:
 446                     ; 200 }
 449  005c 81            	ret
 515                     ; 215 void f_AddRunTimerHour(HOUR_DEF *pTime)
 515                     ; 216 {
 516                     	switch	.text
 517  005d               _f_AddRunTimerHour:
 521                     ; 217 	pTime->second ++;
 523  005d 7c            	inc	(x)
 524                     ; 218 	if ((pTime->second ++) >= 60)
 526  005e f6            	ld	a,(x)
 527  005f 7c            	inc	(x)
 528  0060 a13c          	cp	a,#60
 529  0062 250d          	jrult	L532
 530                     ; 220 		pTime->second = 0;
 532  0064 7f            	clr	(x)
 533                     ; 221 		if ((pTime->minute ++) >= 60)
 535  0065 e601          	ld	a,(1,x)
 536  0067 6c01          	inc	(1,x)
 537  0069 a13c          	cp	a,#60
 538  006b 2504          	jrult	L532
 539                     ; 223 			f_AddU16Data(&(pTime->hour));
 541  006d 5c            	incw	x
 542  006e 5c            	incw	x
 543  006f ad9b          	call	_f_AddU16Data
 545  0071               L532:
 546                     ; 226 }
 549  0071 81            	ret
 612                     ; 241 void f_Memset(void *pData, uchar setValue, uint size)
 612                     ; 242 {
 613                     	switch	.text
 614  0072               _f_Memset:
 616  0072 89            	pushw	x
 617  0073 89            	pushw	x
 618       00000002      OFST:	set	2
 621                     ; 243     uchar *pValue = (uchar *)pData;
 623  0074 1f01          	ldw	(OFST-1,sp),x
 626  0076 200d          	jra	L772
 627  0078               L372:
 628                     ; 247 		*pValue ++ = setValue;
 630  0078 7b07          	ld	a,(OFST+5,sp)
 631  007a 1e01          	ldw	x,(OFST-1,sp)
 632  007c 1c0001        	addw	x,#1
 633  007f 1f01          	ldw	(OFST-1,sp),x
 634  0081 1d0001        	subw	x,#1
 636  0084 f7            	ld	(x),a
 637  0085               L772:
 638                     ; 245 	while (size --)
 640  0085 1e08          	ldw	x,(OFST+6,sp)
 641  0087 1d0001        	subw	x,#1
 642  008a 1f08          	ldw	(OFST+6,sp),x
 643  008c 1c0001        	addw	x,#1
 644  008f a30000        	cpw	x,#0
 645  0092 26e4          	jrne	L372
 646                     ; 249 }
 649  0094 5b04          	addw	sp,#4
 650  0096 81            	ret
 663                     	xdef	_f_Memset
 664                     	xdef	_f_DecU8Data
 665                     	xdef	_f_DecU32Data
 666                     	xdef	_f_DecU16Data
 667                     	xdef	_f_AddU8Data
 668                     	xdef	_f_AddU32Data
 669                     	xdef	_f_AddU16Data
 670                     	xdef	_f_AddRunTimerMinute
 671                     	xdef	_f_AddRunTimerHour
 690                     	xref	c_lgsbc
 691                     	xref	c_lzmp
 692                     	xref	c_lgadc
 693                     	xref	c_lcmp
 694                     	xref	c_ltor
 695                     	end
