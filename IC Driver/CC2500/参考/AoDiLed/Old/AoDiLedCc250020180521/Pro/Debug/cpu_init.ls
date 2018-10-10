   1                     ; C Compiler for STM8 (COSMIC Software)
   2                     ; Parser V4.8.32 - 23 Mar 2010
   3                     ; Generator V4.3.4 - 23 Mar 2010
2623                     ; 66 void f_pCpuClkInit(void)
2623                     ; 67 {
2625                     	switch	.text
2626  0000               _f_pCpuClkInit:
2630                     ; 68 	CLK_ECKR &= 0xfe;			//使用内部晶振(PA1.2可用于GPIO)
2632  0000 721150c1      	bres	_CLK_ECKR,#0
2633                     ; 69 	CLK_CKDIVR = 0x00;          		// 01: fHSI= fHSI RC output/1 = 16M. 
2635  0004 725f50c6      	clr	_CLK_CKDIVR
2637  0008               L7761:
2638                     ; 70 	while(!(CLK_ICKR&0x02));		//等待就绪
2640  0008 c650c0        	ld	a,_CLK_ICKR
2641  000b a502          	bcp	a,#2
2642  000d 27f9          	jreq	L7761
2643                     ; 71 }
2646  000f 81            	ret
2682                     ; 86 void f_pCpuIoInit(void)
2682                     ; 87 {
2683                     	switch	.text
2684  0010               _f_pCpuIoInit:
2688                     ; 95     PA_DDR = 0b00001110; 
2690  0010 350e5002      	mov	_PA_DDR,#14
2691                     ; 96     PA_CR1 = 0b11111111;          		
2693  0014 35ff5003      	mov	_PA_CR1,#255
2694                     ; 97     PA_CR2 = 0b00000000; 					  		
2696  0018 725f5004      	clr	_PA_CR2
2697                     ; 99     PB_DDR = 0b00000000; 
2699  001c 725f5007      	clr	_PB_DDR
2700                     ; 100     PB_CR1 = 0b11001111;          		
2702  0020 35cf5008      	mov	_PB_CR1,#207
2703                     ; 101     PB_CR2 = 0b00100000;      
2705  0024 35205009      	mov	_PB_CR2,#32
2706                     ; 102     EXTI_CR1 |= 0x08;//PB口下降沿中断 
2708  0028 721650a0      	bset	_EXTI_CR1,#3
2709                     ; 103     PC_DDR = 0b11111000;          		
2711  002c 35f8500c      	mov	_PC_DDR,#248
2712                     ; 104     PC_CR1 = 0b11111111;          		
2714  0030 35ff500d      	mov	_PC_CR1,#255
2715                     ; 105     PC_CR2 = 0b00000000;          		
2717  0034 725f500e      	clr	_PC_CR2
2718                     ; 107     PD_DDR = 0b00111100;   
2720  0038 353c5011      	mov	_PD_DDR,#60
2721                     ; 108     PD_CR1 = 0b10111111; 
2723  003c 35bf5012      	mov	_PD_CR1,#191
2724                     ; 109     PD_CR2 = 0b00000000;  
2726  0040 725f5013      	clr	_PD_CR2
2727                     ; 143 }
2730  0044 81            	ret
2757                     ; 158 void f_pCpuAdPortInit(void)
2757                     ; 159 {
2758                     	switch	.text
2759  0045               _f_pCpuAdPortInit:
2763                     ; 160 	ADC_CR1 = 0x62;		//fadc=fmaster/12,连续模式,启动AD
2765  0045 35625401      	mov	_ADC_CR1,#98
2766                     ; 161 	ADC_CR2 = 0x00;		//数据左对齐，禁止扫描模式,
2768  0049 725f5402      	clr	_ADC_CR2
2769                     ; 163 	ADC_TDRL = 0x00;	//作I/O时使能端口的施密特触发器功能，作ad口时必须禁止施密特触发器可以降低I/O口静态功耗
2771  004d 725f5407      	clr	_ADC_TDRL
2772                     ; 164 	ADC_TDRH = 0x00;
2774  0051 725f5406      	clr	_ADC_TDRH
2775                     ; 165 }
2778  0055 81            	ret
2804                     ; 180 void f_pCpuDongInit(void)
2804                     ; 181 {
2805                     	switch	.text
2806  0056               _f_pCpuDongInit:
2810                     ; 182 	IWDG_KR = 0xcc;					//启动看门狗
2812  0056 35cc50e0      	mov	_IWDG_KR,#204
2813                     ; 183 	IWDG_KR = 0x55;					//看门狗寄存器去保护
2815  005a 355550e0      	mov	_IWDG_KR,#85
2816                     ; 184 	IWDG_RLR = 0xff;					//看门狗重新装载数值
2818  005e 35ff50e2      	mov	_IWDG_RLR,#255
2819                     ; 185 	IWDG_PR = 0x06;					//64K的128分频,最长1.02S
2821  0062 350650e1      	mov	_IWDG_PR,#6
2822                     ; 186 	IWDG_KR = 0xaa;					//看门狗寄存器保护,同时启动看门狗
2824  0066 35aa50e0      	mov	_IWDG_KR,#170
2825                     ; 187 }
2828  006a 81            	ret
2852                     ; 202 void f_pCpuFeedDog(void)
2852                     ; 203 {
2853                     	switch	.text
2854  006b               _f_pCpuFeedDog:
2858                     ; 204 	IWDG_KR=0xaa;					//喂狗
2860  006b 35aa50e0      	mov	_IWDG_KR,#170
2861                     ; 205 }
2864  006f 81            	ret
2893                     ; 220 void f_pTimeInit(void)
2893                     ; 221 {
2894                     	switch	.text
2895  0070               _f_pTimeInit:
2899                     ; 223 	TIM1_PSCRH = 0;
2901  0070 725f5260      	clr	_TIM1_PSCRH
2902                     ; 224 	TIM1_PSCRL = 0x0f;	//f= fmain/(PSCR+1)=16/(15 + 1)=1M=1us
2904  0074 350f5261      	mov	_TIM1_PSCRL,#15
2905                     ; 225 	TIM1_ARRH = 0x03;	//产生一个1mss的时基 ARR = 999
2907  0078 35035262      	mov	_TIM1_ARRH,#3
2908                     ; 226 	TIM1_ARRL = 0xe7;
2910  007c 35e75263      	mov	_TIM1_ARRL,#231
2911                     ; 227 	TIM1_IER |= 0x01;
2913  0080 72105254      	bset	_TIM1_IER,#0
2914                     ; 228 	TIM1_CR1  |= 0x01;	//使能定时器1
2916  0084 72105250      	bset	_TIM1_CR1,#0
2917                     ; 246 }
2920  0088 81            	ret
2948                     ; 261 void f_pCpuInit(void)
2948                     ; 262 {
2949                     	switch	.text
2950  0089               _f_pCpuInit:
2954                     ; 263 	f_pCpuClkInit();
2956  0089 cd0000        	call	_f_pCpuClkInit
2958                     ; 264 	f_pCpuIoInit();
2960  008c ad82          	call	_f_pCpuIoInit
2962                     ; 265 	f_pTimeInit();
2964  008e ade0          	call	_f_pTimeInit
2966                     ; 266     f_pCpuAdPortInit();
2968  0090 adb3          	call	_f_pCpuAdPortInit
2970                     ; 267 	f_pCpuDongInit();
2972  0092 adc2          	call	_f_pCpuDongInit
2974                     ; 268 }
2977  0094 81            	ret
2990                     	xdef	_f_pTimeInit
2991                     	xdef	_f_pCpuDongInit
2992                     	xdef	_f_pCpuAdPortInit
2993                     	xdef	_f_pCpuIoInit
2994                     	xdef	_f_pCpuClkInit
2995                     	xdef	_f_pCpuFeedDog
2996                     	xdef	_f_pCpuInit
3015                     	end
