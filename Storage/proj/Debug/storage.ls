   1                     ; C Compiler for STM8 (COSMIC Software)
   2                     ; Parser V4.8.32 - 23 Mar 2010
   3                     ; Generator V4.3.4 - 23 Mar 2010
  15                     .const:	section	.text
  16  0000               _initValueZero:
  17  0000 00000000      	dc.l	0
  18  0004               _initTestValue:
  19  0004 000a          	dc.w	10
  20  0006               _storageValueTable:
  21  0006 0007          	dc.w	_blockWriteCnt
  22  0008 04            	dc.b	4
  23  0009 0000          	dc.w	_initValueZero
 192                     	switch	.const
 193  000b               L6:
 194  000b 0006ddd0      	dc.l	450000
 195  000f               L01:
 196  000f 00000032      	dc.l	50
 197                     ; 40 void judgeStorageBlock(void)
 197                     ; 41 {
 198                     	scross	off
 199                     	switch	.text
 200  0000               _judgeStorageBlock:
 202  0000 5204          	subw	sp,#4
 203       00000004      OFST:	set	4
 206                     ; 45     blockWriteCnt ++;
 208  0002 ae0007        	ldw	x,#_blockWriteCnt
 209  0005 a601          	ld	a,#1
 210  0007 cd0000        	call	c_lgadc
 212                     ; 48     if (blockWriteCnt >= MAX_WRITE_TIMES || writeErrCnt > CHANGE_BLOCK_ERROR_CNT)
 214  000a ae0007        	ldw	x,#_blockWriteCnt
 215  000d cd0000        	call	c_ltor
 217  0010 ae000b        	ldw	x,#L6
 218  0013 cd0000        	call	c_lcmp
 220  0016 2406          	jruge	L511
 222  0018 b604          	ld	a,_writeErrCnt
 223  001a a115          	cp	a,#21
 224  001c 256c          	jrult	L311
 225  001e               L511:
 226                     ; 50         for (i = 0; i < TOTAL_STORAGE_SIZE; i++)
 228  001e 5f            	clrw	x
 229  001f 1f03          	ldw	(OFST-1,sp),x
 230  0021               L711:
 231                     ; 52             valueOffset += (uint)storageValueTable[i].valueType;
 233  0021 1e03          	ldw	x,(OFST-1,sp)
 234  0023 90ae0005      	ldw	y,#5
 235  0027 cd0000        	call	c_imul
 237  002a d60008        	ld	a,(_storageValueTable+2,x)
 238  002d 5f            	clrw	x
 239  002e 97            	ld	xl,a
 240  002f 72fb01        	addw	x,(OFST-3,sp)
 241  0032 1f01          	ldw	(OFST-3,sp),x
 242                     ; 50         for (i = 0; i < TOTAL_STORAGE_SIZE; i++)
 244  0034 1e03          	ldw	x,(OFST-1,sp)
 245  0036 1c0001        	addw	x,#1
 246  0039 1f03          	ldw	(OFST-1,sp),x
 249  003b 1e03          	ldw	x,(OFST-1,sp)
 250  003d a30001        	cpw	x,#1
 251  0040 25df          	jrult	L711
 252                     ; 54         valueOffset += 1;
 254  0042 1e01          	ldw	x,(OFST-3,sp)
 255  0044 1c0001        	addw	x,#1
 256  0047 1f01          	ldw	(OFST-3,sp),x
 257                     ; 56         blockWriteCnt = 0;
 259  0049 ae0000        	ldw	x,#0
 260  004c bf09          	ldw	_blockWriteCnt+2,x
 261  004e ae0000        	ldw	x,#0
 262  0051 bf07          	ldw	_blockWriteCnt,x
 263                     ; 57         writeErrCnt = 0;
 265  0053 3f04          	clr	_writeErrCnt
 266                     ; 60         if (baseAddr + valueOffset < BLOCK_RAMGE)
 268  0055 1e01          	ldw	x,(OFST-3,sp)
 269  0057 72bb0005      	addw	x,_baseAddr
 270  005b a30400        	cpw	x,#1024
 271  005e 241c          	jruge	L521
 272                     ; 62             baseAddr += valueOffset;
 274  0060 be05          	ldw	x,_baseAddr
 275  0062 72fb01        	addw	x,(OFST-3,sp)
 276  0065 bf05          	ldw	_baseAddr,x
 277                     ; 64             for (i = 0; i < TOTAL_STORAGE_SIZE; i++)
 279  0067 5f            	clrw	x
 280  0068 1f03          	ldw	(OFST-1,sp),x
 281  006a               L721:
 282                     ; 66                 writeValues(i);
 284  006a 1e03          	ldw	x,(OFST-1,sp)
 285  006c ad33          	call	_writeValues
 287                     ; 64             for (i = 0; i < TOTAL_STORAGE_SIZE; i++)
 289  006e 1e03          	ldw	x,(OFST-1,sp)
 290  0070 1c0001        	addw	x,#1
 291  0073 1f03          	ldw	(OFST-1,sp),x
 294  0075 1e03          	ldw	x,(OFST-1,sp)
 295  0077 a30001        	cpw	x,#1
 296  007a 25ee          	jrult	L721
 297  007c               L521:
 298                     ; 69         storageWrite(BASE_ADDR_OFFSET, VALUE_U16, (uchar *)&baseAddr);
 300  007c ae0005        	ldw	x,#_baseAddr
 301  007f 89            	pushw	x
 302  0080 4b02          	push	#2
 303  0082 ae0003        	ldw	x,#3
 304  0085 92cd02        	call	[_storageWrite.w]
 306  0088 5b03          	addw	sp,#3
 307  008a               L311:
 308                     ; 73     if (blockWriteCnt % 50)
 310  008a ae0007        	ldw	x,#_blockWriteCnt
 311  008d cd0000        	call	c_ltor
 313  0090 ae000f        	ldw	x,#L01
 314  0093 cd0000        	call	c_lumd
 316  0096 cd0000        	call	c_lrzmp
 318  0099 2703          	jreq	L531
 319                     ; 75         writeValues(STORAGE_WriteCnt);
 321  009b 5f            	clrw	x
 322  009c ad03          	call	_writeValues
 324  009e               L531:
 325                     ; 77 }
 328  009e 5b04          	addw	sp,#4
 329  00a0 81            	ret
 386                     ; 86 void writeValues(uint index)
 386                     ; 87 {
 387                     	switch	.text
 388  00a1               _writeValues:
 390  00a1 89            	pushw	x
 391  00a2 5204          	subw	sp,#4
 392       00000004      OFST:	set	4
 395                     ; 91     judgeStorageBlock();
 397  00a4 cd0000        	call	_judgeStorageBlock
 399                     ; 93     realOffset = baseAddr;
 401  00a7 be05          	ldw	x,_baseAddr
 402  00a9 1f01          	ldw	(OFST-3,sp),x
 403                     ; 94     if (index > 0)
 405  00ab 1e05          	ldw	x,(OFST+1,sp)
 406  00ad 2725          	jreq	L561
 407                     ; 96         for (i = 0; i < index; i++)
 409  00af 5f            	clrw	x
 410  00b0 1f03          	ldw	(OFST-1,sp),x
 412  00b2 201a          	jra	L371
 413  00b4               L761:
 414                     ; 98             realOffset += (uint)storageValueTable[i].valueType;
 416  00b4 1e03          	ldw	x,(OFST-1,sp)
 417  00b6 90ae0005      	ldw	y,#5
 418  00ba cd0000        	call	c_imul
 420  00bd d60008        	ld	a,(_storageValueTable+2,x)
 421  00c0 5f            	clrw	x
 422  00c1 97            	ld	xl,a
 423  00c2 72fb01        	addw	x,(OFST-3,sp)
 424  00c5 1f01          	ldw	(OFST-3,sp),x
 425                     ; 96         for (i = 0; i < index; i++)
 427  00c7 1e03          	ldw	x,(OFST-1,sp)
 428  00c9 1c0001        	addw	x,#1
 429  00cc 1f03          	ldw	(OFST-1,sp),x
 430  00ce               L371:
 433  00ce 1e03          	ldw	x,(OFST-1,sp)
 434  00d0 1305          	cpw	x,(OFST+1,sp)
 435  00d2 25e0          	jrult	L761
 436  00d4               L561:
 437                     ; 102     if (BOOL_FALSE == storageWrite(realOffset, storageValueTable[index].valueType, (uchar *)storageValueTable[index].pValue))
 439  00d4 1e05          	ldw	x,(OFST+1,sp)
 440  00d6 90ae0005      	ldw	y,#5
 441  00da cd0000        	call	c_imul
 443  00dd de0006        	ldw	x,(_storageValueTable,x)
 444  00e0 89            	pushw	x
 445  00e1 1e07          	ldw	x,(OFST+3,sp)
 446  00e3 90ae0005      	ldw	y,#5
 447  00e7 cd0000        	call	c_imul
 449  00ea d60008        	ld	a,(_storageValueTable+2,x)
 450  00ed 88            	push	a
 451  00ee 1e04          	ldw	x,(OFST+0,sp)
 452  00f0 92cd02        	call	[_storageWrite.w]
 454  00f3 5b03          	addw	sp,#3
 455  00f5 4d            	tnz	a
 456  00f6 2602          	jrne	L771
 457                     ; 104         writeErrCnt ++;
 459  00f8 3c04          	inc	_writeErrCnt
 460  00fa               L771:
 461                     ; 106 }
 464  00fa 5b06          	addw	sp,#6
 465  00fc 81            	ret
 520                     ; 115 void readValues(uint index)
 520                     ; 116 {
 521                     	switch	.text
 522  00fd               _readValues:
 524  00fd 89            	pushw	x
 525  00fe 5204          	subw	sp,#4
 526       00000004      OFST:	set	4
 529                     ; 117     uint realOffset = baseAddr;
 531  0100 be05          	ldw	x,_baseAddr
 532  0102 1f01          	ldw	(OFST-3,sp),x
 533                     ; 120     if (index > 0)
 535  0104 1e05          	ldw	x,(OFST+1,sp)
 536  0106 2725          	jreq	L722
 537                     ; 122         for (i = 0; i < index; i++)
 539  0108 5f            	clrw	x
 540  0109 1f03          	ldw	(OFST-1,sp),x
 542  010b 201a          	jra	L532
 543  010d               L132:
 544                     ; 125             realOffset += (uint)storageValueTable[i].valueType;
 546  010d 1e03          	ldw	x,(OFST-1,sp)
 547  010f 90ae0005      	ldw	y,#5
 548  0113 cd0000        	call	c_imul
 550  0116 d60008        	ld	a,(_storageValueTable+2,x)
 551  0119 5f            	clrw	x
 552  011a 97            	ld	xl,a
 553  011b 72fb01        	addw	x,(OFST-3,sp)
 554  011e 1f01          	ldw	(OFST-3,sp),x
 555                     ; 122         for (i = 0; i < index; i++)
 557  0120 1e03          	ldw	x,(OFST-1,sp)
 558  0122 1c0001        	addw	x,#1
 559  0125 1f03          	ldw	(OFST-1,sp),x
 560  0127               L532:
 563  0127 1e03          	ldw	x,(OFST-1,sp)
 564  0129 1305          	cpw	x,(OFST+1,sp)
 565  012b 25e0          	jrult	L132
 566  012d               L722:
 567                     ; 128     storageRead(realOffset, storageValueTable[index].valueType, (uchar *)storageValueTable[index].pValue);
 569  012d 1e05          	ldw	x,(OFST+1,sp)
 570  012f 90ae0005      	ldw	y,#5
 571  0133 cd0000        	call	c_imul
 573  0136 de0006        	ldw	x,(_storageValueTable,x)
 574  0139 89            	pushw	x
 575  013a 1e07          	ldw	x,(OFST+3,sp)
 576  013c 90ae0005      	ldw	y,#5
 577  0140 cd0000        	call	c_imul
 579  0143 d60008        	ld	a,(_storageValueTable+2,x)
 580  0146 88            	push	a
 581  0147 1e04          	ldw	x,(OFST+0,sp)
 582  0149 92cd00        	call	[_storageRead.w]
 584  014c 5b03          	addw	sp,#3
 585                     ; 129 }
 588  014e 5b06          	addw	sp,#6
 589  0150 81            	ret
 683                     ; 139 void storageInit(writeFunc write, readFunc read)
 683                     ; 140 {
 684                     	switch	.text
 685  0151               _storageInit:
 687  0151 89            	pushw	x
 688  0152 5209          	subw	sp,#9
 689       00000009      OFST:	set	9
 692                     ; 145     storageWrite = write;
 694  0154 bf02          	ldw	_storageWrite,x
 695                     ; 146     storageRead = read;
 697  0156 1e0e          	ldw	x,(OFST+5,sp)
 698  0158 bf00          	ldw	_storageRead,x
 699                     ; 149     storageRead(HEAD_OFFSET, 3, (uchar *)&head);
 701  015a 96            	ldw	x,sp
 702  015b 1c0005        	addw	x,#OFST-4
 703  015e 89            	pushw	x
 704  015f 4b03          	push	#3
 705  0161 5f            	clrw	x
 706  0162 92cd00        	call	[_storageRead.w]
 708  0165 5b03          	addw	sp,#3
 709                     ; 150     if ('X' == head[0] && 'D' == head[1] && 'D' == head[2])
 711  0167 7b05          	ld	a,(OFST-4,sp)
 712  0169 a158          	cp	a,#88
 713  016b 2631          	jrne	L503
 715  016d 7b06          	ld	a,(OFST-3,sp)
 716  016f a144          	cp	a,#68
 717  0171 262b          	jrne	L503
 719  0173 7b07          	ld	a,(OFST-2,sp)
 720  0175 a144          	cp	a,#68
 721  0177 2625          	jrne	L503
 722                     ; 153         storageRead(BASE_ADDR_OFFSET, VALUE_U16, (uchar *)&baseAddr);
 724  0179 ae0005        	ldw	x,#_baseAddr
 725  017c 89            	pushw	x
 726  017d 4b02          	push	#2
 727  017f ae0003        	ldw	x,#3
 728  0182 92cd00        	call	[_storageRead.w]
 730  0185 5b03          	addw	sp,#3
 731                     ; 156         for (i = 0; i < TOTAL_STORAGE_SIZE; i++)
 733  0187 5f            	clrw	x
 734  0188 1f08          	ldw	(OFST-1,sp),x
 735  018a               L703:
 736                     ; 158             readValues(i);
 738  018a 1e08          	ldw	x,(OFST-1,sp)
 739  018c cd00fd        	call	_readValues
 741                     ; 156         for (i = 0; i < TOTAL_STORAGE_SIZE; i++)
 743  018f 1e08          	ldw	x,(OFST-1,sp)
 744  0191 1c0001        	addw	x,#1
 745  0194 1f08          	ldw	(OFST-1,sp),x
 748  0196 1e08          	ldw	x,(OFST-1,sp)
 749  0198 27f0          	jreq	L703
 751  019a ac7d027d      	jpf	L513
 752  019e               L503:
 753                     ; 163         baseAddr = BASE_ADDR_VALUE;
 755  019e ae0005        	ldw	x,#5
 756  01a1 bf05          	ldw	_baseAddr,x
 757                     ; 164         storageWrite(BASE_ADDR_OFFSET, VALUE_U16, (uchar *)&baseAddr);
 759  01a3 ae0005        	ldw	x,#_baseAddr
 760  01a6 89            	pushw	x
 761  01a7 4b02          	push	#2
 762  01a9 ae0003        	ldw	x,#3
 763  01ac 92cd02        	call	[_storageWrite.w]
 765  01af 5b03          	addw	sp,#3
 766                     ; 167         for (i = 0; i < TOTAL_STORAGE_SIZE; i++)
 768  01b1 5f            	clrw	x
 769  01b2 1f08          	ldw	(OFST-1,sp),x
 770  01b4               L713:
 771                     ; 169             if (VALUE_U8 == storageValueTable[i].valueType)
 773  01b4 1e08          	ldw	x,(OFST-1,sp)
 774  01b6 90ae0005      	ldw	y,#5
 775  01ba cd0000        	call	c_imul
 777  01bd d60008        	ld	a,(_storageValueTable+2,x)
 778  01c0 a101          	cp	a,#1
 779  01c2 261c          	jrne	L523
 780                     ; 171                 *(uchar *)storageValueTable[i].pValue = *(uchar *)storageValueTable[i].pInitValue;
 782  01c4 1e08          	ldw	x,(OFST-1,sp)
 783  01c6 90ae0005      	ldw	y,#5
 784  01ca cd0000        	call	c_imul
 786  01cd de0009        	ldw	x,(_storageValueTable+3,x)
 787  01d0 f6            	ld	a,(x)
 788  01d1 1e08          	ldw	x,(OFST-1,sp)
 789  01d3 90ae0005      	ldw	y,#5
 790  01d7 cd0000        	call	c_imul
 792  01da de0006        	ldw	x,(_storageValueTable,x)
 793  01dd f7            	ld	(x),a
 795  01de 2071          	jra	L723
 796  01e0               L523:
 797                     ; 173             else if (VALUE_U16 == storageValueTable[i].valueType)
 799  01e0 1e08          	ldw	x,(OFST-1,sp)
 800  01e2 90ae0005      	ldw	y,#5
 801  01e6 cd0000        	call	c_imul
 803  01e9 d60008        	ld	a,(_storageValueTable+2,x)
 804  01ec a102          	cp	a,#2
 805  01ee 2620          	jrne	L133
 806                     ; 175                 *(uint *)storageValueTable[i].pValue = *(uint *)storageValueTable[i].pInitValue;
 808  01f0 1e08          	ldw	x,(OFST-1,sp)
 809  01f2 90ae0005      	ldw	y,#5
 810  01f6 cd0000        	call	c_imul
 812  01f9 de0009        	ldw	x,(_storageValueTable+3,x)
 813  01fc fe            	ldw	x,(x)
 814  01fd 1f03          	ldw	(OFST-6,sp),x
 815  01ff 1e08          	ldw	x,(OFST-1,sp)
 816  0201 90ae0005      	ldw	y,#5
 817  0205 cd0000        	call	c_imul
 819  0208 de0006        	ldw	x,(_storageValueTable,x)
 820  020b 1603          	ldw	y,(OFST-6,sp)
 821  020d ff            	ldw	(x),y
 823  020e 2041          	jra	L723
 824  0210               L133:
 825                     ; 177             else if (VALUE_U32 == storageValueTable[i].valueType)
 827  0210 1e08          	ldw	x,(OFST-1,sp)
 828  0212 90ae0005      	ldw	y,#5
 829  0216 cd0000        	call	c_imul
 831  0219 d60008        	ld	a,(_storageValueTable+2,x)
 832  021c a104          	cp	a,#4
 833  021e 2631          	jrne	L723
 834                     ; 179                 *(ulong *)storageValueTable[i].pValue = *(ulong *)storageValueTable[i].pInitValue;
 836  0220 1e08          	ldw	x,(OFST-1,sp)
 837  0222 90ae0005      	ldw	y,#5
 838  0226 cd0000        	call	c_imul
 840  0229 de0009        	ldw	x,(_storageValueTable+3,x)
 841  022c cd0000        	call	c_ltor
 843  022f 96            	ldw	x,sp
 844  0230 1c0001        	addw	x,#OFST-8
 845  0233 cd0000        	call	c_rtol
 847  0236 1e08          	ldw	x,(OFST-1,sp)
 848  0238 90ae0005      	ldw	y,#5
 849  023c cd0000        	call	c_imul
 851  023f de0006        	ldw	x,(_storageValueTable,x)
 852  0242 7b04          	ld	a,(OFST-5,sp)
 853  0244 e703          	ld	(3,x),a
 854  0246 7b03          	ld	a,(OFST-6,sp)
 855  0248 e702          	ld	(2,x),a
 856  024a 7b02          	ld	a,(OFST-7,sp)
 857  024c e701          	ld	(1,x),a
 858  024e 7b01          	ld	a,(OFST-8,sp)
 859  0250 f7            	ld	(x),a
 860  0251               L723:
 861                     ; 181             writeValues(i);
 863  0251 1e08          	ldw	x,(OFST-1,sp)
 864  0253 cd00a1        	call	_writeValues
 866                     ; 167         for (i = 0; i < TOTAL_STORAGE_SIZE; i++)
 868  0256 1e08          	ldw	x,(OFST-1,sp)
 869  0258 1c0001        	addw	x,#1
 870  025b 1f08          	ldw	(OFST-1,sp),x
 873  025d 1e08          	ldw	x,(OFST-1,sp)
 874  025f 2603          	jrne	L02
 875  0261 cc01b4        	jp	L713
 876  0264               L02:
 877                     ; 184         head[0] = 'X';
 879  0264 a658          	ld	a,#88
 880  0266 6b05          	ld	(OFST-4,sp),a
 881                     ; 185         head[1] = 'D';
 883  0268 a644          	ld	a,#68
 884  026a 6b06          	ld	(OFST-3,sp),a
 885                     ; 186         head[2] = 'D';
 887  026c a644          	ld	a,#68
 888  026e 6b07          	ld	(OFST-2,sp),a
 889                     ; 187         storageWrite(HEAD_OFFSET, 3, (uchar *)&head);
 891  0270 96            	ldw	x,sp
 892  0271 1c0005        	addw	x,#OFST-4
 893  0274 89            	pushw	x
 894  0275 4b03          	push	#3
 895  0277 5f            	clrw	x
 896  0278 92cd02        	call	[_storageWrite.w]
 898  027b 5b03          	addw	sp,#3
 899  027d               L513:
 900                     ; 190 }
 903  027d 5b0b          	addw	sp,#11
 904  027f 81            	ret
 970                     	xdef	_judgeStorageBlock
 971                     	switch	.ubsct
 972  0000               _storageRead:
 973  0000 0000          	ds.b	2
 974                     	xdef	_storageRead
 975  0002               _storageWrite:
 976  0002 0000          	ds.b	2
 977                     	xdef	_storageWrite
 978  0004               _writeErrCnt:
 979  0004 00            	ds.b	1
 980                     	xdef	_writeErrCnt
 981  0005               _baseAddr:
 982  0005 0000          	ds.b	2
 983                     	xdef	_baseAddr
 984                     	xdef	_storageValueTable
 985  0007               _blockWriteCnt:
 986  0007 00000000      	ds.b	4
 987                     	xdef	_blockWriteCnt
 988                     	xdef	_initTestValue
 989                     	xdef	_initValueZero
 990                     	xdef	_storageInit
 991                     	xdef	_readValues
 992                     	xdef	_writeValues
 993                     	xref.b	c_x
1013                     	xref	c_rtol
1014                     	xref	c_lrzmp
1015                     	xref	c_lumd
1016                     	xref	c_imul
1017                     	xref	c_lcmp
1018                     	xref	c_ltor
1019                     	xref	c_lgadc
1020                     	end
