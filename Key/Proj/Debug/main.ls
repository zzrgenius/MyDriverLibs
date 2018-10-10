   1                     ; C Compiler for STM8 (COSMIC Software)
   2                     ; Parser V4.11.10 - 06 Jul 2017
   3                     ; Generator (Limited) V4.4.7 - 05 Oct 2017
  45                     ; 9 main()
  45                     ; 10 {
  47                     	switch	.text
  48  0000               _main:
  52                     ; 11 	f_KeyDealInit();
  54  0000 cd0000        	call	_f_KeyDealInit
  56  0003               L12:
  57                     ; 14 	f_KeyDriverDeal(&keyDriver);
  59  0003 ae0000        	ldw	x,#_keyDriver
  60  0006 cd0000        	call	_f_KeyDriverDeal
  63  0009 20f8          	jra	L12
 353                     	xdef	_main
 354                     	switch	.ubsct
 355  0000               _sysTimeFlag:
 356  0000 000000000000  	ds.b	11
 357                     	xdef	_sysTimeFlag
 358                     	xref	_f_KeyDealInit
 359                     	xref.b	_keyDriver
 360                     	xref	_f_KeyDriverDeal
 380                     	end
