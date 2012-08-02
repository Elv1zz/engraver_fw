/*
    COPYRIGHT 2011 Christian Nolte
    
    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

    Dieses Programm ist Freie Software: Sie können es unter den Bedingungen
    der GNU General Public License, wie von der Free Software Foundation,
    Version 3 der Lizenz oder (nach Ihrer Option) jeder späteren
    veröffentlichten Version, weiterverbreiten und/oder modifizieren.

    Dieses Programm wird in der Hoffnung, dass es nützlich sein wird, aber
    OHNE JEDE GEWÄHRLEISTUNG, bereitgestellt; sogar ohne die implizite
    Gewährleistung der MARKTFÄHIGKEIT oder EIGNUNG FÜR EINEN BESTIMMTEN ZWECK.
    Siehe die GNU General Public License für weitere Details.

    Sie sollten eine Kopie der GNU General Public License zusammen mit diesem
    Programm erhalten haben. Wenn nicht, siehe <http://www.gnu.org/licenses/>.

*/

#include "sfr111.h"
#include "hwsetup.h"

void initUART1(void)
{ 
	p6_7s = 3;
	pd6_7 = 1;
	p6_6s =0x03;
	pd6_6 =0;
      u1brg =163-1; // UiBRG Count Source (UiC0 b1 and b0) = f1 => 9600 bps BRG n = 163 at Peripheral Clock 25MHz 
	u1mr = 0x05; 
	u1c0 = 0x10; 
    u1c1 = 0x05;
}

void sendTxD1(unsigned char data)
{
	
	while (ti_u1c1 == 0); //Wait for transmission buffer emty
	u1tb = data; // Set transmission data
	te_u1c1 = 1; // Transmission enabled

}

unsigned char receiveRxD1(void)
{
	unsigned char data = 0;
	unsigned char dummy;
	while (ir_s1ric == 0);//Warten bis Post kommt
	{
		ir_s1ric = 0; //Flag rücksetzen
		data = u1rbl; //Post rausnehmen
		dummy = u1rbh;
		re_u1c1 = 1;
	}
	return data; //und abliefern
}

unsigned char check_crc(unsigned char b2,unsigned char b3,unsigned char crc)
{
	unsigned char mycrc;
	
	mycrc=b2+b3;
	
	if(crc==mycrc)
	{
		return(1);
	}
	else
	{
		return(0);
	}
}

void main(void)
{
  unsigned char Data;
  unsigned char received_char,received_char_2,received_char_3,received_char_crc;

  pd3_0=1;
  pd2=0xff;     //P2 alles Ausgaenge
  pd7=0xff;     //P7 alles Ausgaenge
  pd10=0xff;    //P10 alles Ausgaenge
  p3_0=1;

  ConfigureOperatingFrequency();
  initUART1();

  Data = 65;
  while(1)
  {
	received_char=receiveRxD1();
    if(received_char=='a')
	{
		p3_0=0;
		received_char_2=receiveRxD1();
		received_char_3=receiveRxD1();
		received_char_crc=receiveRxD1();
		if(check_crc(received_char_2,received_char_3,received_char_crc))
		{
			//CRC OK
			p2=received_char_2;
			p10=received_char_3;
			sendTxD1('O');
		}
		else
		{
			sendTxD1('C');
			p3_0=1;
		}
	}
	else
	{
		p3_0=1;
		sendTxD1('F');
	}
  }
} 