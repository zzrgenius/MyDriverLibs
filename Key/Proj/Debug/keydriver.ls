   1                     ; C Compiler for STM8 (COSMIC Software)
   2                     ; Parser V4.11.10 - 06 Jul 2017
   3                     ; Generator (Limited) V4.4.7 - 05 Oct 2017
  71                     ; 77 uchar f_IsSingleKey(ulong KeyName)
  71                     ; 78 {
  73                     	switch	.text
  74  0000               _f_IsSingleKey:
  76  0000 89            	pushw	x
  77       00000002      OFST:	set	2
  80                     ; 80 	uchar enKeyCnt = 0;
  82  0001 0f01          	clr	(OFST-1,sp)
  84                     ; 81 	for (i = 0; i < 32; i++)
  86  0003 0f02          	clr	(OFST+0,sp)
  88  0005               L73:
  89                     ; 83 	    if ((KeyName>>i) & 0x01)
  91  0005 96            	ldw	x,sp
  92  0006 1c0005        	addw	x,#OFST+3
  93  0009 cd0000        	call	c_ltor
  95  000c 7b02          	ld	a,(OFST+0,sp)
  96  000e cd0000        	call	c_lursh
  98  0011 b603          	ld	a,c_lreg+3
  99  0013 a501          	bcp	a,#1
 100  0015 270b          	jreq	L54
 101                     ; 85 			if ( ++enKeyCnt >= 2)
 103  0017 0c01          	inc	(OFST-1,sp)
 105  0019 7b01          	ld	a,(OFST-1,sp)
 106  001b a102          	cp	a,#2
 107  001d 2503          	jrult	L54
 108                     ; 87 				return false;
 110  001f 4f            	clr	a
 112  0020 200a          	jra	L6
 113  0022               L54:
 114                     ; 81 	for (i = 0; i < 32; i++)
 116  0022 0c02          	inc	(OFST+0,sp)
 120  0024 7b02          	ld	a,(OFST+0,sp)
 121  0026 a120          	cp	a,#32
 122  0028 25db          	jrult	L73
 123                     ; 92     return true;
 125  002a a601          	ld	a,#1
 127  002c               L6:
 129  002c 85            	popw	x
 130  002d 81            	ret
 486                     ; 215 void f_KeyDriverDeal(KEY_DRIVER       *pKeyDriver)
 486                     ; 216 {
 487                     	switch	.text
 488  002e               _f_KeyDriverDeal:
 490  002e 89            	pushw	x
 491  002f 88            	push	a
 492       00000001      OFST:	set	1
 495                     ; 220 	if (!f_IsSysTime10Ms())
 497  0030 b605          	ld	a,_sysTimeFlag+5
 498  0032 a504          	bcp	a,#4
 499  0034 2710          	jreq	L21
 500                     ; 222 		return;
 502                     ; 226 	if (NULL == pKeyDriver->pHardDriver || NULL == pKeyDriver->dealCallback)
 504  0036 1e02          	ldw	x,(OFST+1,sp)
 505  0038 e61a          	ld	a,(26,x)
 506  003a ea19          	or	a,(25,x)
 507  003c 2708          	jreq	L372
 509  003e 1e02          	ldw	x,(OFST+1,sp)
 510  0040 e61c          	ld	a,(28,x)
 511  0042 ea1b          	or	a,(27,x)
 512  0044 2603          	jrne	L172
 513  0046               L372:
 514                     ; 228 		return;	
 515  0046               L21:
 518  0046 5b03          	addw	sp,#3
 519  0048 81            	ret
 520  0049               L172:
 521                     ; 232 	pKeyDriver->pHardDriver->GetKeys(pKeyDriver);
 523  0049 1e02          	ldw	x,(OFST+1,sp)
 524  004b 1602          	ldw	y,(OFST+1,sp)
 525  004d 90ee19        	ldw	y,(25,y)
 526  0050 90ee01        	ldw	y,(1,y)
 527  0053 90fd          	call	(y)
 529                     ; 235 	pKeyDriver->data.mask |= ~(pKeyDriver->data.getKeys);//一旦对应的按键释放,该位mask恢复
 531  0055 1e02          	ldw	x,(OFST+1,sp)
 532  0057 1602          	ldw	y,(OFST+1,sp)
 533  0059 90e60d        	ld	a,(13,y)
 534  005c b703          	ld	c_lreg+3,a
 535  005e 90e60c        	ld	a,(12,y)
 536  0061 b702          	ld	c_lreg+2,a
 537  0063 90e60b        	ld	a,(11,y)
 538  0066 b701          	ld	c_lreg+1,a
 539  0068 90e60a        	ld	a,(10,y)
 540  006b b700          	ld	c_lreg,a
 541  006d 3303          	cpl	c_lreg+3
 542  006f 3302          	cpl	c_lreg+2
 543  0071 3301          	cpl	c_lreg+1
 544  0073 3300          	cpl	c_lreg
 545  0075 1c000e        	addw	x,#14
 546  0078 cd0000        	call	c_lgor
 548                     ; 236 	pKeyDriver->data.newName = pKeyDriver->data.getKeys & pKeyDriver->data.mask;
 550  007b 1e02          	ldw	x,(OFST+1,sp)
 551  007d 1c000e        	addw	x,#14
 552  0080 cd0000        	call	c_ltor
 554  0083 1e02          	ldw	x,(OFST+1,sp)
 555  0085 1c000a        	addw	x,#10
 556  0088 cd0000        	call	c_land
 558  008b 1e02          	ldw	x,(OFST+1,sp)
 559  008d 1c0006        	addw	x,#6
 560  0090 cd0000        	call	c_rtol
 562                     ; 238 	f_AddU16Data(&(pKeyDriver->data.pressTm));//按下时间累加
 564  0093 1e02          	ldw	x,(OFST+1,sp)
 565  0095 cd0000        	call	_f_AddU16Data
 567                     ; 239 	switch (pKeyDriver->dealStep)
 569  0098 1e02          	ldw	x,(OFST+1,sp)
 570  009a e617          	ld	a,(23,x)
 572                     ; 310 			break;
 573  009c 4a            	dec	a
 574  009d 273a          	jreq	L15
 575  009f 4a            	dec	a
 576  00a0 2603cc012c    	jreq	L35
 577  00a5 4a            	dec	a
 578  00a6 2603          	jrne	L41
 579  00a8 cc0175        	jp	L55
 580  00ab               L41:
 581  00ab               L75:
 582                     ; 306 		default:
 582                     ; 307 			pKeyDriver->data.name = KEY_DRIVER_NO_KEY;
 584  00ab 1e02          	ldw	x,(OFST+1,sp)
 585  00ad a600          	ld	a,#0
 586  00af e705          	ld	(5,x),a
 587  00b1 a600          	ld	a,#0
 588  00b3 e704          	ld	(4,x),a
 589  00b5 a600          	ld	a,#0
 590  00b7 e703          	ld	(3,x),a
 591  00b9 a600          	ld	a,#0
 592  00bb e702          	ld	(2,x),a
 593                     ; 308 			pKeyDriver->data.newName = KEY_DRIVER_NO_KEY;
 595  00bd 1e02          	ldw	x,(OFST+1,sp)
 596  00bf a600          	ld	a,#0
 597  00c1 e709          	ld	(9,x),a
 598  00c3 a600          	ld	a,#0
 599  00c5 e708          	ld	(8,x),a
 600  00c7 a600          	ld	a,#0
 601  00c9 e707          	ld	(7,x),a
 602  00cb a600          	ld	a,#0
 603  00cd e706          	ld	(6,x),a
 604                     ; 309 			pKeyDriver->dealStep = KEY_DEAL_IDLE;
 606  00cf 1e02          	ldw	x,(OFST+1,sp)
 607  00d1 a601          	ld	a,#1
 608  00d3 e717          	ld	(23,x),a
 609                     ; 310 			break;
 611  00d5 acd101d1      	jpf	L772
 612  00d9               L15:
 613                     ; 241 		case KEY_DEAL_IDLE://按键空闲状态
 613                     ; 242 			pKeyDriver->data.pressTm = 0;
 615  00d9 1e02          	ldw	x,(OFST+1,sp)
 616  00db 905f          	clrw	y
 617  00dd ff            	ldw	(x),y
 618                     ; 243 			pKeyDriver->data.keyDone = 0;
 620  00de 1e02          	ldw	x,(OFST+1,sp)
 621  00e0 a600          	ld	a,#0
 622  00e2 e715          	ld	(21,x),a
 623  00e4 a600          	ld	a,#0
 624  00e6 e714          	ld	(20,x),a
 625  00e8 a600          	ld	a,#0
 626  00ea e713          	ld	(19,x),a
 627  00ec a600          	ld	a,#0
 628  00ee e712          	ld	(18,x),a
 629                     ; 244 			pKeyDriver->data.state = KEY_STATE_IDLE;
 631  00f0 1e02          	ldw	x,(OFST+1,sp)
 632  00f2 6f16          	clr	(22,x)
 633                     ; 245 			pKeyDriver->flag.byte = 0;
 635  00f4 1e02          	ldw	x,(OFST+1,sp)
 636  00f6 6f18          	clr	(24,x)
 637                     ; 248 			if (KEY_DRIVER_NO_KEY != pKeyDriver->data.newName)
 639  00f8 1e02          	ldw	x,(OFST+1,sp)
 640  00fa 1c0006        	addw	x,#6
 641  00fd cd0000        	call	c_lzmp
 643  0100 270e          	jreq	L103
 644                     ; 250 				pKeyDriver->dealStep = KEY_DEAL_PRESS;
 646  0102 1e02          	ldw	x,(OFST+1,sp)
 647  0104 a602          	ld	a,#2
 648  0106 e717          	ld	(23,x),a
 649                     ; 251 				pKeyDriver->data.state |= KEY_PRESSED;//产生按下信息
 651  0108 1e02          	ldw	x,(OFST+1,sp)
 652  010a e616          	ld	a,(22,x)
 653  010c aa01          	or	a,#1
 654  010e e716          	ld	(22,x),a
 655  0110               L103:
 656                     ; 253 			pKeyDriver->data.name = pKeyDriver->data.newName;
 658  0110 1e02          	ldw	x,(OFST+1,sp)
 659  0112 1602          	ldw	y,(OFST+1,sp)
 660  0114 e609          	ld	a,(9,x)
 661  0116 90e705        	ld	(5,y),a
 662  0119 e608          	ld	a,(8,x)
 663  011b 90e704        	ld	(4,y),a
 664  011e e607          	ld	a,(7,x)
 665  0120 90e703        	ld	(3,y),a
 666  0123 e606          	ld	a,(6,x)
 667  0125 90e702        	ld	(2,y),a
 668                     ; 254 			break;
 670  0128 acd101d1      	jpf	L772
 671  012c               L35:
 672                     ; 256 		case KEY_DEAL_PRESS://按键按下状态
 672                     ; 257 			pKeyDriver->flag.bit.bHasKey = true;
 674  012c 1e02          	ldw	x,(OFST+1,sp)
 675  012e e618          	ld	a,(24,x)
 676  0130 aa02          	or	a,#2
 677  0132 e718          	ld	(24,x),a
 678                     ; 260 			if (pKeyDriver->data.name != pKeyDriver->data.newName)
 680  0134 1e02          	ldw	x,(OFST+1,sp)
 681  0136 5c            	incw	x
 682  0137 5c            	incw	x
 683  0138 cd0000        	call	c_ltor
 685  013b 1e02          	ldw	x,(OFST+1,sp)
 686  013d 1c0006        	addw	x,#6
 687  0140 cd0000        	call	c_lcmp
 689  0143 2603          	jrne	L61
 690  0145 cc01d1        	jp	L772
 691  0148               L61:
 692                     ; 262 				if (f_IsSingleKey(pKeyDriver->data.name) 
 692                     ; 263 				&& KEY_DRIVER_NO_KEY != pKeyDriver->data.newName)
 694  0148 1e02          	ldw	x,(OFST+1,sp)
 695  014a 9093          	ldw	y,x
 696  014c ee04          	ldw	x,(4,x)
 697  014e 89            	pushw	x
 698  014f 93            	ldw	x,y
 699  0150 ee02          	ldw	x,(2,x)
 700  0152 89            	pushw	x
 701  0153 cd0000        	call	_f_IsSingleKey
 703  0156 5b04          	addw	sp,#4
 704  0158 4d            	tnz	a
 705  0159 2712          	jreq	L503
 707  015b 1e02          	ldw	x,(OFST+1,sp)
 708  015d 1c0006        	addw	x,#6
 709  0160 cd0000        	call	c_lzmp
 711  0163 2708          	jreq	L503
 712                     ; 266 					pKeyDriver->dealStep = KEY_DEAL_IDLE;
 714  0165 1e02          	ldw	x,(OFST+1,sp)
 715  0167 a601          	ld	a,#1
 716  0169 e717          	ld	(23,x),a
 718  016b 2064          	jra	L772
 719  016d               L503:
 720                     ; 271 					pKeyDriver->dealStep = KEY_DEAL_WATE_RELEASE;
 722  016d 1e02          	ldw	x,(OFST+1,sp)
 723  016f a603          	ld	a,#3
 724  0171 e717          	ld	(23,x),a
 725  0173 205c          	jra	L772
 726  0175               L55:
 727                     ; 284 		case KEY_DEAL_WATE_RELEASE://按键等待释放状态
 727                     ; 285 			//等待全部按键释放,释放时产生释放状态,按键已处理不产生释放信息
 727                     ; 286 			if (KEY_DRIVER_NO_KEY == pKeyDriver->data.newName)
 729  0175 1e02          	ldw	x,(OFST+1,sp)
 730  0177 1c0006        	addw	x,#6
 731  017a cd0000        	call	c_lzmp
 733  017d 2624          	jrne	L113
 734                     ; 288 				pKeyDriver->dealStep = KEY_DEAL_IDLE;
 736  017f 1e02          	ldw	x,(OFST+1,sp)
 737  0181 a601          	ld	a,#1
 738  0183 e717          	ld	(23,x),a
 739                     ; 290 				if (!f_GetKeyDealDone(pKeyDriver->data.name))
 741  0185 1e02          	ldw	x,(OFST+1,sp)
 742  0187 5c            	incw	x
 743  0188 5c            	incw	x
 744  0189 cd0000        	call	c_ltor
 746  018c 1e02          	ldw	x,(OFST+1,sp)
 747  018e 1c0012        	addw	x,#18
 748  0191 cd0000        	call	c_land
 750  0194 cd0000        	call	c_lrzmp
 752  0197 2638          	jrne	L772
 753                     ; 292 					pKeyDriver->data.state |= KEY_RELEASE;
 755  0199 1e02          	ldw	x,(OFST+1,sp)
 756  019b e616          	ld	a,(22,x)
 757  019d aa02          	or	a,#2
 758  019f e716          	ld	(22,x),a
 759  01a1 202e          	jra	L772
 760  01a3               L113:
 761                     ; 298 				if (pKeyDriver->data.name != pKeyDriver->data.newName)
 763  01a3 1e02          	ldw	x,(OFST+1,sp)
 764  01a5 5c            	incw	x
 765  01a6 5c            	incw	x
 766  01a7 cd0000        	call	c_ltor
 768  01aa 1e02          	ldw	x,(OFST+1,sp)
 769  01ac 1c0006        	addw	x,#6
 770  01af cd0000        	call	c_lcmp
 772  01b2 271d          	jreq	L772
 773                     ; 300 					pKeyDriver->data.pressTm = 0;
 775  01b4 1e02          	ldw	x,(OFST+1,sp)
 776  01b6 905f          	clrw	y
 777  01b8 ff            	ldw	(x),y
 778                     ; 301 					pKeyDriver->data.name = pKeyDriver->data.newName;
 780  01b9 1e02          	ldw	x,(OFST+1,sp)
 781  01bb 1602          	ldw	y,(OFST+1,sp)
 782  01bd e609          	ld	a,(9,x)
 783  01bf 90e705        	ld	(5,y),a
 784  01c2 e608          	ld	a,(8,x)
 785  01c4 90e704        	ld	(4,y),a
 786  01c7 e607          	ld	a,(7,x)
 787  01c9 90e703        	ld	(3,y),a
 788  01cc e606          	ld	a,(6,x)
 789  01ce 90e702        	ld	(2,y),a
 790  01d1               L772:
 791                     ; 314 	for (i = 0; (pKeyDriver->data.pressTm > 0) && (f_SetKeyTimeState(i) != KEY_STATE_RESERVE); i++)
 793  01d1 0f01          	clr	(OFST+0,sp)
 796  01d3 2039          	jra	L523
 797  01d5               L123:
 798                     ; 317 		if (pKeyDriver->data.pressTm == f_GetKeyStateTime(i))
 800  01d5 7b01          	ld	a,(OFST+0,sp)
 801  01d7 97            	ld	xl,a
 802  01d8 a603          	ld	a,#3
 803  01da 42            	mul	x,a
 804  01db 1602          	ldw	y,(OFST+1,sp)
 805  01dd 90fe          	ldw	y,(y)
 806  01df d30000        	cpw	y,(_Tab_KeySelfState,x)
 807  01e2 2628          	jrne	L133
 808                     ; 320 			if (KEY_DEAL_WATE_RELEASE == pKeyDriver->dealStep
 808                     ; 321 			&& KEY_LOCKED != f_SetKeyTimeState(i))
 810  01e4 1e02          	ldw	x,(OFST+1,sp)
 811  01e6 e617          	ld	a,(23,x)
 812  01e8 a103          	cp	a,#3
 813  01ea 260d          	jrne	L333
 815  01ec 7b01          	ld	a,(OFST+0,sp)
 816  01ee 97            	ld	xl,a
 817  01ef a603          	ld	a,#3
 818  01f1 42            	mul	x,a
 819  01f2 d60002        	ld	a,(_Tab_KeySelfState+2,x)
 820  01f5 a104          	cp	a,#4
 821  01f7 2629          	jrne	L723
 822                     ; 323 				break;
 824  01f9               L333:
 825                     ; 326 			pKeyDriver->data.state |= f_SetKeyTimeState(i);
 827  01f9 7b01          	ld	a,(OFST+0,sp)
 828  01fb 97            	ld	xl,a
 829  01fc a603          	ld	a,#3
 830  01fe 42            	mul	x,a
 831  01ff 1602          	ldw	y,(OFST+1,sp)
 832  0201 90e616        	ld	a,(22,y)
 833  0204 da0002        	or	a,(_Tab_KeySelfState+2,x)
 834  0207 90e716        	ld	(22,y),a
 835                     ; 327 			break;
 837  020a 2016          	jra	L723
 838  020c               L133:
 839                     ; 314 	for (i = 0; (pKeyDriver->data.pressTm > 0) && (f_SetKeyTimeState(i) != KEY_STATE_RESERVE); i++)
 841  020c 0c01          	inc	(OFST+0,sp)
 843  020e               L523:
 846  020e 1e02          	ldw	x,(OFST+1,sp)
 847  0210 e601          	ld	a,(1,x)
 848  0212 fa            	or	a,(x)
 849  0213 270d          	jreq	L723
 851  0215 7b01          	ld	a,(OFST+0,sp)
 852  0217 97            	ld	xl,a
 853  0218 a603          	ld	a,#3
 854  021a 42            	mul	x,a
 855  021b d60002        	ld	a,(_Tab_KeySelfState+2,x)
 856  021e a1ff          	cp	a,#255
 857  0220 26b3          	jrne	L123
 858  0222               L723:
 859                     ; 337 	if (f_IsKeyState(KEY_LOCKED))
 861  0222 1e02          	ldw	x,(OFST+1,sp)
 862  0224 e616          	ld	a,(22,x)
 863  0226 a504          	bcp	a,#4
 864  0228 2744          	jreq	L733
 865                     ; 340 		f_RemoveKey(pKeyDriver->data.getKeys);
 867  022a 1e02          	ldw	x,(OFST+1,sp)
 868  022c 1602          	ldw	y,(OFST+1,sp)
 869  022e 90e60d        	ld	a,(13,y)
 870  0231 b703          	ld	c_lreg+3,a
 871  0233 90e60c        	ld	a,(12,y)
 872  0236 b702          	ld	c_lreg+2,a
 873  0238 90e60b        	ld	a,(11,y)
 874  023b b701          	ld	c_lreg+1,a
 875  023d 90e60a        	ld	a,(10,y)
 876  0240 b700          	ld	c_lreg,a
 877  0242 3303          	cpl	c_lreg+3
 878  0244 3302          	cpl	c_lreg+2
 879  0246 3301          	cpl	c_lreg+1
 880  0248 3300          	cpl	c_lreg
 881  024a 1c000e        	addw	x,#14
 882  024d cd0000        	call	c_lgand
 884                     ; 341 		f_SetKeyDealDone();
 886  0250 1e02          	ldw	x,(OFST+1,sp)
 887  0252 1602          	ldw	y,(OFST+1,sp)
 888  0254 90e605        	ld	a,(5,y)
 889  0257 b703          	ld	c_lreg+3,a
 890  0259 90e604        	ld	a,(4,y)
 891  025c b702          	ld	c_lreg+2,a
 892  025e 90e603        	ld	a,(3,y)
 893  0261 b701          	ld	c_lreg+1,a
 894  0263 90e602        	ld	a,(2,y)
 895  0266 b700          	ld	c_lreg,a
 896  0268 1c0012        	addw	x,#18
 897  026b cd0000        	call	c_lgor
 899  026e               L733:
 900                     ; 345 	pKeyDriver->dealCallback(pKeyDriver);
 902  026e 1e02          	ldw	x,(OFST+1,sp)
 903  0270 1602          	ldw	y,(OFST+1,sp)
 904  0272 90ee1b        	ldw	y,(27,y)
 905  0275 90fd          	call	(y)
 907                     ; 348 	if (f_GetKeyDealDone(pKeyDriver->data.name))
 909  0277 1e02          	ldw	x,(OFST+1,sp)
 910  0279 5c            	incw	x
 911  027a 5c            	incw	x
 912  027b cd0000        	call	c_ltor
 914  027e 1e02          	ldw	x,(OFST+1,sp)
 915  0280 1c0012        	addw	x,#18
 916  0283 cd0000        	call	c_land
 918  0286 cd0000        	call	c_lrzmp
 920  0289 2704          	jreq	L143
 921                     ; 350 		pKeyDriver->data.state = KEY_STATE_IDLE;
 923  028b 1e02          	ldw	x,(OFST+1,sp)
 924  028d 6f16          	clr	(22,x)
 925  028f               L143:
 926                     ; 352 }
 928  028f ac460046      	jpf	L21
 989                     ; 371 void f_KeyDriverInit( KEY_DRIVER *pKeyDriver,
 989                     ; 372 							KEY_HARDWARE_DRIVER const *pKeyDriverHardware, 
 989                     ; 373 							KeyDriverCallback const pKeyDealFunc)
 989                     ; 374 {
 990                     	switch	.text
 991  0293               _f_KeyDriverInit:
 993  0293 89            	pushw	x
 994       00000000      OFST:	set	0
 997                     ; 375 	f_Memset(pKeyDriver, 0, sizeof(KEY_DRIVER));
 999  0294 ae001d        	ldw	x,#29
1000  0297 89            	pushw	x
1001  0298 4b00          	push	#0
1002  029a 1e04          	ldw	x,(OFST+4,sp)
1003  029c cd0000        	call	_f_Memset
1005  029f 5b03          	addw	sp,#3
1006                     ; 376 	pKeyDriver->data.mask = KEY_DRIVER_ALL_KEY;
1008  02a1 1e01          	ldw	x,(OFST+1,sp)
1009  02a3 a6ff          	ld	a,#255
1010  02a5 e711          	ld	(17,x),a
1011  02a7 a6ff          	ld	a,#255
1012  02a9 e710          	ld	(16,x),a
1013  02ab a6ff          	ld	a,#255
1014  02ad e70f          	ld	(15,x),a
1015  02af a6ff          	ld	a,#255
1016  02b1 e70e          	ld	(14,x),a
1017                     ; 377 	pKeyDriver->pHardDriver = pKeyDriverHardware;
1019  02b3 1e01          	ldw	x,(OFST+1,sp)
1020  02b5 1605          	ldw	y,(OFST+5,sp)
1021  02b7 ef19          	ldw	(25,x),y
1022                     ; 378 	pKeyDriver->dealCallback = pKeyDealFunc;
1024  02b9 1e01          	ldw	x,(OFST+1,sp)
1025  02bb 1607          	ldw	y,(OFST+7,sp)
1026  02bd ef1b          	ldw	(27,x),y
1027                     ; 379 }
1030  02bf 85            	popw	x
1031  02c0 81            	ret
1044                     	xdef	_f_IsSingleKey
1045                     	xref.b	_sysTimeFlag
1046                     	xref	_f_Memset
1047                     	xref	_f_AddU16Data
1048                     	xdef	_f_KeyDriverDeal
1049                     	xdef	_f_KeyDriverInit
1050                     	xref	_Tab_KeySelfState
1051                     	xref.b	c_lreg
1070                     	xref	c_lgand
1071                     	xref	c_lrzmp
1072                     	xref	c_lcmp
1073                     	xref	c_lzmp
1074                     	xref	c_rtol
1075                     	xref	c_land
1076                     	xref	c_lgor
1077                     	xref	c_lursh
1078                     	xref	c_ltor
1079                     	end
