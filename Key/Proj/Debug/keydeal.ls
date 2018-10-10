   1                     ; C Compiler for STM8 (COSMIC Software)
   2                     ; Parser V4.11.10 - 06 Jul 2017
   3                     ; Generator (Limited) V4.4.7 - 05 Oct 2017
 362                     .const:	section	.text
 363  0000               L522:
 364  0000 0004          	dc.w	4
 365  0002 00000001      	dc.l	1
 366  0006 000c          	dc.w	L3
 367  0008 00000002      	dc.l	2
 368  000c 0063          	dc.w	L5
 369  000e 00000003      	dc.l	3
 370  0012 00b6          	dc.w	L11
 371  0014 00000004      	dc.l	4
 372  0018 008e          	dc.w	L7
 373  001a 0104          	dc.w	L722
 374                     ; 69 void f_KeyDeal(KEY_DRIVER *pKeyDriver)
 374                     ; 70 {
 375                     	scross	off
 376                     	switch	.text
 377  0000               _f_KeyDeal:
 379  0000 89            	pushw	x
 380       00000000      OFST:	set	0
 383                     ; 71 	switch(f_GetKeyName())
 385  0001 5c            	incw	x
 386  0002 5c            	incw	x
 387  0003 cd0000        	call	c_ltor
 390  0006 ae0000        	ldw	x,#L522
 391  0009 cd0000        	call	c_jltab
 392  000c               L3:
 393                     ; 73 		case KEY_SIGLE_POWER:
 393                     ; 74 			if (f_IsKeyState(KEY_RELEASE))
 395  000c 1e01          	ldw	x,(OFST+1,sp)
 396  000e e616          	ld	a,(22,x)
 397  0010 a502          	bcp	a,#2
 398  0012 2722          	jreq	L132
 399                     ; 76 				f_SetKeyDealDone();
 401  0014 1e01          	ldw	x,(OFST+1,sp)
 402  0016 1601          	ldw	y,(OFST+1,sp)
 403  0018 90e605        	ld	a,(5,y)
 404  001b b703          	ld	c_lreg+3,a
 405  001d 90e604        	ld	a,(4,y)
 406  0020 b702          	ld	c_lreg+2,a
 407  0022 90e603        	ld	a,(3,y)
 408  0025 b701          	ld	c_lreg+1,a
 409  0027 90e602        	ld	a,(2,y)
 410  002a b700          	ld	c_lreg,a
 411  002c 1c0012        	addw	x,#18
 412  002f cd0000        	call	c_lgor
 415  0032 ac040104      	jpf	L722
 416  0036               L132:
 417                     ; 81 			else if (f_IsKeyState(KEY_PRESS_5S))
 419  0036 1e01          	ldw	x,(OFST+1,sp)
 420  0038 e616          	ld	a,(22,x)
 421  003a a520          	bcp	a,#32
 422  003c 2603          	jrne	L6
 423  003e cc0104        	jp	L722
 424  0041               L6:
 425                     ; 83 				f_SetKeyDealDone();
 427  0041 1e01          	ldw	x,(OFST+1,sp)
 428  0043 1601          	ldw	y,(OFST+1,sp)
 429  0045 90e605        	ld	a,(5,y)
 430  0048 b703          	ld	c_lreg+3,a
 431  004a 90e604        	ld	a,(4,y)
 432  004d b702          	ld	c_lreg+2,a
 433  004f 90e603        	ld	a,(3,y)
 434  0052 b701          	ld	c_lreg+1,a
 435  0054 90e602        	ld	a,(2,y)
 436  0057 b700          	ld	c_lreg,a
 437  0059 1c0012        	addw	x,#18
 438  005c cd0000        	call	c_lgor
 440  005f ac040104      	jpf	L722
 441  0063               L5:
 442                     ; 91 		case KEY_SIGLE_STOP:
 442                     ; 92 			if (f_IsKeyState(KEY_PRESSED))
 444  0063 1e01          	ldw	x,(OFST+1,sp)
 445  0065 e616          	ld	a,(22,x)
 446  0067 a501          	bcp	a,#1
 447  0069 2603          	jrne	L01
 448  006b cc0104        	jp	L722
 449  006e               L01:
 450                     ; 94 				f_SetKeyDealDone();
 452  006e 1e01          	ldw	x,(OFST+1,sp)
 453  0070 1601          	ldw	y,(OFST+1,sp)
 454  0072 90e605        	ld	a,(5,y)
 455  0075 b703          	ld	c_lreg+3,a
 456  0077 90e604        	ld	a,(4,y)
 457  007a b702          	ld	c_lreg+2,a
 458  007c 90e603        	ld	a,(3,y)
 459  007f b701          	ld	c_lreg+1,a
 460  0081 90e602        	ld	a,(2,y)
 461  0084 b700          	ld	c_lreg,a
 462  0086 1c0012        	addw	x,#18
 463  0089 cd0000        	call	c_lgor
 465  008c 2076          	jra	L722
 466  008e               L7:
 467                     ; 100 		case KEY_SIGLE_WASH:
 467                     ; 101 			if (f_IsKeyState(KEY_PRESSED))
 469  008e 1e01          	ldw	x,(OFST+1,sp)
 470  0090 e616          	ld	a,(22,x)
 471  0092 a501          	bcp	a,#1
 472  0094 276e          	jreq	L722
 473                     ; 103 				f_SetKeyDealDone();
 475  0096 1e01          	ldw	x,(OFST+1,sp)
 476  0098 1601          	ldw	y,(OFST+1,sp)
 477  009a 90e605        	ld	a,(5,y)
 478  009d b703          	ld	c_lreg+3,a
 479  009f 90e604        	ld	a,(4,y)
 480  00a2 b702          	ld	c_lreg+2,a
 481  00a4 90e603        	ld	a,(3,y)
 482  00a7 b701          	ld	c_lreg+1,a
 483  00a9 90e602        	ld	a,(2,y)
 484  00ac b700          	ld	c_lreg,a
 485  00ae 1c0012        	addw	x,#18
 486  00b1 cd0000        	call	c_lgor
 488  00b4 204e          	jra	L722
 489  00b6               L11:
 490                     ; 109 		case KEY_COMM_RESER:
 490                     ; 110 			if (f_IsKeyState(KEY_PRESS_1S))
 492  00b6 1e01          	ldw	x,(OFST+1,sp)
 493  00b8 e616          	ld	a,(22,x)
 494  00ba a508          	bcp	a,#8
 495  00bc 2720          	jreq	L342
 496                     ; 112 				f_SetKeyDealDone();
 498  00be 1e01          	ldw	x,(OFST+1,sp)
 499  00c0 1601          	ldw	y,(OFST+1,sp)
 500  00c2 90e605        	ld	a,(5,y)
 501  00c5 b703          	ld	c_lreg+3,a
 502  00c7 90e604        	ld	a,(4,y)
 503  00ca b702          	ld	c_lreg+2,a
 504  00cc 90e603        	ld	a,(3,y)
 505  00cf b701          	ld	c_lreg+1,a
 506  00d1 90e602        	ld	a,(2,y)
 507  00d4 b700          	ld	c_lreg,a
 508  00d6 1c0012        	addw	x,#18
 509  00d9 cd0000        	call	c_lgor
 512  00dc 2026          	jra	L722
 513  00de               L342:
 514                     ; 116 			else if (f_IsKeyState(KEY_RELEASE))
 516  00de 1e01          	ldw	x,(OFST+1,sp)
 517  00e0 e616          	ld	a,(22,x)
 518  00e2 a502          	bcp	a,#2
 519  00e4 271e          	jreq	L722
 520                     ; 118 				f_SetKeyDealDone();
 522  00e6 1e01          	ldw	x,(OFST+1,sp)
 523  00e8 1601          	ldw	y,(OFST+1,sp)
 524  00ea 90e605        	ld	a,(5,y)
 525  00ed b703          	ld	c_lreg+3,a
 526  00ef 90e604        	ld	a,(4,y)
 527  00f2 b702          	ld	c_lreg+2,a
 528  00f4 90e603        	ld	a,(3,y)
 529  00f7 b701          	ld	c_lreg+1,a
 530  00f9 90e602        	ld	a,(2,y)
 531  00fc b700          	ld	c_lreg,a
 532  00fe 1c0012        	addw	x,#18
 533  0101 cd0000        	call	c_lgor
 535  0104               L31:
 536                     ; 123 		default:
 536                     ; 124 			break;
 538  0104               L722:
 539                     ; 126 }
 542  0104 85            	popw	x
 543  0105 81            	ret
 571                     ; 141 void f_KeyDealInit(void)
 571                     ; 142 {
 572                     	switch	.text
 573  0106               _f_KeyDealInit:
 577                     ; 143     f_KeyDriverInit(&keyDriver, &keyHardware, f_KeyDeal);
 579  0106 ae0000        	ldw	x,#_f_KeyDeal
 580  0109 89            	pushw	x
 581  010a ae0000        	ldw	x,#_keyHardware
 582  010d 89            	pushw	x
 583  010e ae0000        	ldw	x,#_keyDriver
 584  0111 cd0000        	call	_f_KeyDriverInit
 586  0114 5b04          	addw	sp,#4
 587                     ; 144 }
 590  0116 81            	ret
 615                     	xref	_keyHardware
 616                     	xdef	_f_KeyDeal
 617                     	xdef	_f_KeyDealInit
 618                     	switch	.ubsct
 619  0000               _keyDriver:
 620  0000 000000000000  	ds.b	29
 621                     	xdef	_keyDriver
 622                     	xref	_f_KeyDriverInit
 623                     	xref.b	c_lreg
 624                     	xref.b	c_x
 644                     	xref	c_jltab
 645                     	xref	c_lgor
 646                     	xref	c_ltor
 647                     	end
