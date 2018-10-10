   1                     ; C Compiler for STM8 (COSMIC Software)
   2                     ; Parser V4.8.32 - 23 Mar 2010
   3                     ; Generator V4.3.4 - 23 Mar 2010
  48                     ; 8 main()
  48                     ; 9 {
  50                     	switch	.text
  51  0000               _main:
  55                     ; 10 	storageInit(stm8_WriteToEEPROM, stm8_ReadFromEEPROM);
  57  0000 ae0000        	ldw	x,#_stm8_ReadFromEEPROM
  58  0003 89            	pushw	x
  59  0004 ae0000        	ldw	x,#_stm8_WriteToEEPROM
  60  0007 cd0000        	call	_storageInit
  62  000a 85            	popw	x
  63  000b               L12:
  64                     ; 11 	while (1);
  66  000b 20fe          	jra	L12
  79                     	xdef	_main
  80                     	xref	_stm8_ReadFromEEPROM
  81                     	xref	_stm8_WriteToEEPROM
  82                     	xref	_storageInit
 101                     	end
