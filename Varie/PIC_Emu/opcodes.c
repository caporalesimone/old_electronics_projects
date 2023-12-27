    switch(opc & 0x3000)
	{
	case 0x0000:
		switch(opc & 0x0F00)
		{
		case 0x0000:
			switch(opc & 0x0080)
			{
			case 0x0000:
				break;
			case 0x0080:
				//MOVWF   f  	Move W to f                  1     0000001 fffffff
				if(print)printf("MOVWF %#04X\n",opc & 0x007F);
				pic->ram[bank|(opc & 0x007F)]=pic->w;
				pic->lram=bank|(opc & 0x007F);
				break;
			}
			break;
		case 0x0100:
			switch(opc & 0x0080)
			{
			case 0x0000:
				//CLRW    --  	Clear W                      1     0000010 xxxxxxx 	Z
				if(print)printf("CLRW\n");
				pic->w=0;
				break;
			case 0x0080:
				//CLRF    f  	Clear f                      1     0000011 fffffff 	Z       2
				if(print)printf("CLRF %#04X\n",opc & 0x007F);
				pic->ram[bank|(opc & 0x007F) ]=0;
				pic->lram=bank|(opc & 0x007F);
				break;
			};
			break;
		case 0x0200:
			//SUBWF   f, d 	Subtract W from f            1     000010 dfffffff 	C,DC,Z  1, 2
			if(print)printf("SUBWF %#04X,%d\n",opc & 0x007F,(opc & 0x0080)>>7);

			if((0xF0&((0x0F&(~pic->w))+1+(0x0F&pic->ram[bank|(opc & 0x007F)]))) !=0)
				*status|=0x02;
			else
				*status&=~0x02;

			temp=(~pic->w+1)+pic->ram[bank|(opc & 0x007F)];

			if ((0xFF00&temp) != 0)
				*status&=~0x01;
			else
				*status|=0x01;

			if((opc & 0x0080) == 0 )
			{
				pic->w = (unsigned char)(0x00FF &temp);
				if (pic->w == 0)
					*status|=0x04;
				else
					*status&=~0x04;
			}
			else
			{
				pic->ram[bank|(opc & 0x007F)]=(unsigned char)(0x00FF &temp);
				pic->lram=bank|(opc & 0x007F);
				if (pic->ram[bank|(opc & 0x007F) ] == 0)
					*status|=0x04;
				else
					*status&=~0x04;
			};
			break;
		case 0x0300:
			//DECF    f, d 	Decrement f                  1     000011 dfffffff  	Z       1, 2
			if(print)printf("DECF %#04X,%d\n",opc & 0x007F,(opc & 0x0080)>>7);
			if((opc & 0x0080) == 0 )
			{
				pic->w=pic->ram[bank|(opc & 0x007F)]-1;
				if (pic->w == 0)
					*status|=0x04;
				else
					*status&=~0x04;
			}
			else
			{
				pic->ram[bank|(opc & 0x007F) ]--;
				pic->lram=bank|(opc & 0x007F);
				if (pic->ram[bank|(opc & 0x007F) ] == 0)
					*status|=0x04;
				else
					*status&=~0x04;
			};
			break;
		case 0x0400:
			//IORWF   f, d 	Inclusive OR W with f        1     000100 dfffffff   	Z       1, 2
			if(print)printf("IORWF %#04X,%d\n",opc & 0x007F,(opc & 0x0080)>>7);
			if((opc & 0x0080) == 0 )
			{
				pic->w= pic->w | pic->ram[bank|(opc & 0x007F)];
				if (pic->w == 0)
					*status|=0x04;
				else
					*status&=~0x04;
			}
			else
			{
				pic->ram[bank|(opc & 0x007F) ]= pic->w | pic->ram[bank|(opc & 0x007F)];
				pic->lram=bank|(opc & 0x007F);
				if (pic->ram[bank|(opc & 0x007F) ] == 0)
					*status|=0x04;
				else
					*status&=~0x04;
			};
			break;
		case 0x0500:
			//ANDWF   f, d 	AND W with f                 1     000101 dfffffff	Z       1, 2
			if(print)printf("ANDWF %#04X,%d\n",opc & 0x007F,(opc & 0x0080)>>7);
			if((opc & 0x0080) == 0 )
			{
				pic->w= pic->w & pic->ram[bank|(opc & 0x007F)];
				if (pic->w == 0)
					*status|=0x04;
				else
					*status&=~0x04;
			}
			else
			{
				pic->ram[bank|(opc & 0x007F) ]= pic->w & pic->ram[bank|(opc & 0x007F)];
				pic->lram=bank|(opc & 0x007F);
				if (pic->ram[bank|(opc & 0x007F) ] == 0)
					*status|=0x04;
				else
					*status&=~0x04;
			};
			break;
		case 0x0600:
			//XORWF   f, d 	Exclusive OR W with f        1     000110 dfffffff  	Z       1, 2
			if(print)printf("XORWF %#04X,%d\n",opc & 0x007F,(opc & 0x0080)>>7);
			if((opc & 0x0080) == 0 )
			{
				pic->w= pic->w ^ pic->ram[bank|(opc & 0x007F)];
				if (pic->w == 0)
					*status|=0x04;
				else
					*status&=~0x04;
			}
			else
			{
				pic->ram[bank|(opc & 0x007F) ]= pic->w ^ pic->ram[bank|(opc & 0x007F)];
				pic->lram=bank|(opc & 0x007F);
				if (pic->ram[bank|(opc & 0x007F) ] == 0)
					*status|=0x04;
				else
					*status&=~0x04;
			};
			break;
		case 0x0700:
			//ADDWF	f, d 	Add W and f                  1     000111 dfffffff	C,DC,Z  1, 2
			if(print)printf("ADDWF %#04X,%d\n",opc & 0x007F,(opc & 0x0080)>>7);

			if((0xF0&((0x0F&pic->w)+(0x0F&pic->ram[bank|(opc & 0x007F)]))) !=0)
				*status|=0x02;
			else
				*status&=~0x02;

			temp=pic->w+pic->ram[bank|(opc & 0x007F)];

			if ((0xFF00&temp) != 0)
				*status|=0x01;
			else
				*status&=~0x01;

			if((opc & 0x0080) == 0 )
			{
				pic->w = (unsigned char)(0x00FF &temp);
				if (pic->w == 0)
					*status|=0x04;
				else
					*status&=~0x04;
			}
			else
			{
				pic->ram[bank|(opc & 0x007F)]=(unsigned char)(0x00FF &temp);
				pic->lram=bank|(opc & 0x007F);
				if (pic->ram[bank|(opc & 0x007F) ] == 0)
					*status|=0x04;
				else
					*status&=~0x04;
			};
			break;
		case 0x0800:
			//MOVF    f, d 	Move f                       1     001000 dfffffff 	Z       1, 2
			if(print)printf("MOVF %#04X,%d\n",opc & 0x007F,(opc & 0x0080)>>7);
			if((opc & 0x0080) == 0 )
			{
				pic->w=pic->ram[bank|(opc & 0x007F)];
				if (pic->w == 0)
					*status|=0x04;
				else
					*status&=~0x04;
				pic->rram=bank|(opc & 0x007F);
			}
			else
			{
				if (pic->ram[bank|(opc & 0x007F) ] == 0)
					*status|=0x04;
				else
					*status&=~0x04;
				pic->rram=bank|(opc & 0x007F);
				pic->lram=bank|(opc & 0x007F);
			};
			break;
		case 0x0900:
			//COMF    f, d 	Complement f                 1     001001 dfffffff 	Z       1, 2
			if(print)printf("COMF %#04X,%d\n",opc & 0x007F,(opc & 0x0080)>>7);
			if((opc & 0x0080) == 0 )
			{
				pic->w=~pic->ram[bank|(opc & 0x007F)];
				if (pic->w == 0)
					*status|=0x04;
				else
					*status&=~0x04;
			}
			else
			{
				pic->ram[bank|(opc & 0x007F) ]=~pic->ram[bank|(opc & 0x007F) ];
				pic->lram=bank|(opc & 0x007F);
				if (pic->ram[bank|(opc & 0x007F) ] == 0)
					*status|=0x04;
				else
					*status&=~0x04;
			};
			break;
		case 0x0A00:
			//INCF    f, d 	Increment f                  1     001010 dfffffff	Z       1, 2
			if(print)printf("INCF %#04X,%d\n",opc & 0x007F,(opc & 0x0080)>>7);
			if((opc & 0x0080) == 0 )
			{
				pic->w=pic->ram[bank|(opc & 0x007F)]+1;
				if (pic->w == 0)
					*status|=0x04;
				else
					*status&=~0x04;
			}
			else
			{
				pic->ram[bank|(opc & 0x007F) ]++;
				pic->lram=bank|(opc & 0x007F);
				if (pic->ram[bank|(opc & 0x007F) ] == 0)
					*status|=0x04;
				else
					*status&=~0x04;
			};
			break;
		case 0x0B00:
			//DECFSZ  f, d 	Decrement f, Skip if 0       1(2)  001011 dfffffff 		1, 2, 3
			if(print)printf("DECFSZ %#04X,%d\n",opc & 0x007F,(opc & 0x0080)>>7);
			if((opc & 0x0080) == 0 )
			{
				pic->w=pic->ram[bank|(opc & 0x007F)]-1;
				if (pic->w == 0)
				{
					pic->jpc=pic->pc+1;
					pic->s2=1;
				};
			}
			else
			{
				pic->ram[bank|(opc & 0x007F) ]--;
				pic->lram=bank|(opc & 0x007F);
				if (pic->ram[bank|(opc & 0x007F) ] == 0)
				{
					pic->jpc=pic->pc+1;
					pic->s2=1;
				};
			};
			break;
		case 0x0C00:
			//RRF     f, d 	Rotate Right f through Carry 1     001100 dfffffff	C       1, 2
			if(print)printf("RRF %#04X,%d\n",opc & 0x007F,(opc & 0x0080)>>7);
			temp=(pic->ram[bank|(opc & 0x007F)]);
			if((*status&0x01) ==0x01)temp|=0x0100;
			if((temp&0x0001) ==0x01)
				*status|=0x01;
			else
				*status&=~0x01;
			temp=temp>>1;
			if((opc & 0x0080) == 0 )
			{
				pic->w=0x00FF&temp;
			}
			else
			{
				pic->ram[bank|(opc & 0x007F) ]=0x00FF&temp;
				pic->lram=bank|(opc & 0x007F);
			};
			break;
		case 0x0D00:
			//RLF     f, d 	Rotate Left f through Carry  1     001101 dfffffff	C       1, 2
			if(print)printf("RLF %#04X,%d\n",opc & 0x007F,(opc & 0x0080)>>7);
			temp=(pic->ram[bank|(opc & 0x007F)]);
			temp=temp<<1;
			if((*status&0x01) ==0x01)temp|=0x0001;
			if((temp&0x0100) ==0x0100)
				*status|=0x0001;
			else
				*status&=~0x0001;
			if((opc & 0x0080) == 0 )
			{
				pic->w=0x00FF & temp;
			}
			else
			{
				pic->ram[bank|(opc & 0x007F) ]= 0x00FF & temp;
				pic->lram=bank|(opc & 0x007F);
			};
			break;
		case 0x0E00:
			//SWAPF   f, d 	Swap nibbles in f            1     001110 dfffffff 		1, 2
			if(print)printf("SWAPF %#04X,%d\n",opc & 0x007F,(opc & 0x0080)>>7);
			if((opc & 0x0080) == 0 )
			{
				pic->w=((pic->ram[bank|(opc & 0x007F)]&0x0F)<<4)|
					((pic->ram[bank|(opc & 0x007F)]&0xF0)>>4);

			}
			else
			{
				pic->ram[bank|(opc & 0x007F) ]=
					((pic->ram[bank|(opc & 0x007F)]&0x0F)<<4)|
					((pic->ram[bank|(opc & 0x007F)]&0xF0)>>4);
				pic->lram=bank|(opc & 0x007F);
			};
			break;
		case 0x0F00:
			//INCFSZ  f, d 	Increment f, Skip if 0       1(2)  001111 dfffffff		1, 2, 3
			if(print)printf("INCFSZ %#04X,%d\n",opc & 0x007F,(opc & 0x0080)>>7);
			if((opc & 0x0080) == 0 )
			{
				pic->w=pic->ram[bank|(opc & 0x007F)]+1;
				if (pic->w == 0)
				{
					pic->jpc=pic->pc+1;
					pic->s2=1;
				};
			}
			else
			{
				pic->ram[bank|(opc & 0x007F) ]++;
				pic->lram=bank|(opc & 0x007F);
				if (pic->ram[bank|(opc & 0x007F) ] == 0)
				{
					pic->jpc=pic->pc+1;
					pic->s2=1;
				};
			};
			break;
		}
		break;
	case 0x1000:
		switch(opc & 0x0C00)
		{
		case 0x0000:
			//BCF     f, b 	Bit Clear f                  1     0100 bbbfffffff           1, 2
			if(print)printf("BCF %#04X,%d\n",opc & 0x007F,(opc & 0x0380)>>7);
			pic->ram[bank|(opc & 0x007F)]&=~(0x01<<((opc & 0x0380)>>7));
			pic->lram=bank|(opc & 0x007F);
			break;
		case 0x0400:
			//BSF     f, b 	Bit Set f                    1     0101 bbbfffffff           1, 2
			if(print)printf("BSF %#04X,%d\n",opc & 0x007F,(opc & 0x0380)>>7);
			pic->ram[bank|(opc & 0x007F)]|=(0x01<<((opc & 0x0380)>>7));
			pic->lram=bank|(opc & 0x007F);
			break;
		case 0x0800:
			//BTFSC   f, b 	Bit Test f, Skip if Clear    1(2)  0110 bbbfffffff           3
			if(print)printf("BTFSC %#04X,%d\n",opc & 0x007F,(opc & 0x0380)>>7);
			if((pic->ram[bank|(opc & 0x007F)] & (0x01<<((opc & 0x0380)>>7))) == 0)
			{
				pic->jpc=pic->pc+1;
				pic->s2=1;
			}
			break;
		case 0x0C00:
			//BTFSS   f, b 	Bit Test f, Skip if Set      1(2)  0111 bbbfffffff           3
			if(print)printf("BTFSS %#04X,%d\n",opc & 0x007F,(opc & 0x0380)>>7);
			if((pic->ram[bank|(opc & 0x007F)] & (0x01<<((opc & 0x0380)>>7))) != 0)
			{
				pic->jpc=pic->pc+1;
				pic->s2=1;
			}
			break;
		};
		break;
	case 0x2000:
		switch(opc & 0x0800)
		{
		case 0x0000:
			//CALL    k  	Call subroutine              2     100 kkkkkkkkkkk
			if(print)printf("CALL %#05X\n",opc & 0x07FF);
			for(temp=7;temp>0;temp--)
				pic->stack[temp]=pic->stack[temp-1];
			pic->stack[0]=pic->pc;
			pic->jpc=((pic->ram[bank|(PCLATH & 0x007F)]&0x18)<<8)|(opc & 0x07FF);
			pic->s2=1;
			break;
		case 0x0800:
			//GOTO    k  	Go to address                2     101 kkkkkkkkkkk
			if(print)printf("GOTO %#05X\n",opc & 0x07FF);
			if(((pic->config[0] & 0x0800) == 0)&&(((pic->ram[ICKBUG])&0x80)== 0x80) )//DEBUG ON
				pic->jpc=((0x18)<<8)|(opc & 0x07FF);
			else
				pic->jpc=((pic->ram[bank|(PCLATH & 0x007F)]&0x18)<<8)|(opc & 0x07FF);
			pic->s2=1;
			break;
		}
		break;
	case 0x3000:
		switch(opc & 0x0F00)
		{
		case 0x0000:
		case 0x0100:
		case 0x0200:
		case 0x0300:
			//MOVLW   k  	Move literal to W            1     1100xx kkkkkkkk
			if(print)printf("MOVLW %#04X\n",opc & 0x00FF);
			pic->w= (opc & 0x00FF);
			break;
		case 0x0400:
		case 0x0500:
		case 0x0600:
		case 0x0700:
			//RETLW   k  	Return with literal in W     2     1101xx kkkkkkkk
			if(print)printf("RETLW %#04X\n",opc & 0x00FF);
			pic->jpc=pic->stack[0];
			for(temp=0;temp<7;temp++)
				pic->stack[temp]=pic->stack[temp+1];
			pic->stack[7]=0;
			pic->s2=1;
			pic->w= (opc & 0x00FF);
			break;
		case 0x0800:
			//IORLW   k  	Inclusive OR literal with W  1     111000 kkkkkkkk   	Z
			if(print)printf("IORLW %#04X\n",opc & 0x00FF);
			pic->w |= (opc & 0x00FF);
			if (pic->w == 0)
				*status|=0x04;
			else
				*status&=~0x04;
			break;
		case 0x0900:
			//ANDLW   k 	AND literal with W           1     111001 kkkkkkkk   	Z
			if(print)printf("ANDLW %#04X\n",opc & 0x00FF);
			pic->w &= (opc & 0x00FF);
			if (pic->w == 0)
				*status|=0x04;
			else
				*status&=~0x04;
			break;
		case 0x0A00:
			//XORLW   k  	Exclusive OR literal with W  1     111010 kkkkkkkk   	Z
			if(print)printf("XORLW %#04X\n",opc & 0x00FF);
			pic->w ^= (opc & 0x00FF);
			if (pic->w == 0)
				*status|=0x04;
			else
				*status&=~0x04;
			break;
		case 0x0C00:
		case 0x0D00:
			//SUBLW   k  	Subtract W from literal      1     11110x kkkkkkkk   	C,DC,Z
			if(print)printf("SUBLW %#04X\n",opc & 0x00FF);

			if((0xF0&((0x0F&(~pic->w))+1+(opc & 0x000F))) !=0)
				*status|=0x02;
			else
				*status&=~0x02;

			temp=(~pic->w+1)+(opc & 0x00FF);
			pic->w = (unsigned char)(0x00FF &temp);

			if ((0xFF00&temp) != 0)
				*status&=~0x01;
			else
				*status|=0x01;

			if (pic->w == 0)
				*status|=0x04;
			else
				*status&=~0x04;
			break;
		case 0x0E00:
		case 0x0F00:
			//ADDLW   k  	Add literal and W            1     11111x kkkkkkkk   	C,DC,Z
			if(print)printf("ADDLW %#04X\n",opc & 0x00FF);

			if((0xF0&((0x0F&pic->w)+(opc & 0x000F))) !=0)
				*status|=0x02;
			else
				*status&=~0x02;

			temp=pic->w+(opc & 0x00FF);
			pic->w = (unsigned char)(0x00FF &temp);

			if ((0xFF00&temp) != 0)
				*status|=0x01;
			else
				*status&=~0x01;

			if (pic->w == 0)
				*status|=0x04;
			else
				*status&=~0x04;
			break;
		}
		break;
	}
