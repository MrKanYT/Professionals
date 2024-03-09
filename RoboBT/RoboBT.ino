int _AvlDFU0 = 0;
bool En_182203794_1;
char receivedChar_182203794_1;
int MaxSpeed_182203794_1;
int AverSpeed_182203794_1;
int LowSpeed_182203794_1;
bool LeftCour_182203794_1;
int LeftSpeed_182203794_1;
bool RghtCour_182203794_1;
int RghtSpeed_182203794_1;
bool _gtv13 = 0;
char _gtv5;
bool _gtv20 = 0;
int _gtv14 = 0;
int _gtv38 = 0;
bool _gtv9 = 0;
bool _gtv16 = 0;
char _RVFU2Data;
bool _tim3I = 0;
bool _tim3O = 0;
unsigned long _tim3P = 0UL;
bool _tim1I = 0;
bool _tim1O = 0;
unsigned long _tim1P = 0UL;
void setup()
{
    pinMode(4, OUTPUT);
    digitalWrite(4, 0);
    pinMode(7, OUTPUT);
    digitalWrite(7, 0);
    pinMode(13, OUTPUT);
    digitalWrite(13, 0);
    _startUart0();
}
void loop()
{
    if (_AvlDFU0)
    {
        _AvlDFU0=0;
    }
     else
    {
        if (Serial.available()) 
        {
            _AvlDFU0=1;
            _readByteFromUART((Serial.read()),0);
        }
    }
    //Плата:1
//Наименование:Прием символа контроль связи
    _gtv20 = _AvlDFU0;
    _gtv5 = _RVFU2Data;
    if(_gtv20) 
    {
        _tim3O = 1;
        _tim3I = 1;
    }
     else 
    {
         if(_tim3I) 
        {
            _tim3I = 0;
            _tim3P = millis();
        }
         else 
        {
             if (_tim3O) 
            {
                if (_isTimer(_tim3P, 500)) _tim3O = 0;
            }
        }
    }
    _gtv13 = _tim3O;
    if(_gtv20) 
    {
        _tim1O = 1;
        _tim1I = 1;
    }
     else 
    {
         if(_tim1I) 
        {
            _tim1I = 0;
            _tim1P = millis();
        }
         else 
        {
             if (_tim1O) 
            {
                if (_isTimer(_tim1P, 10)) _tim1O = 0;
            }
        }
    }
    digitalWrite(13, _tim1O);
    //Плата:2
    En_182203794_1 = _gtv20;
    receivedChar_182203794_1 = _gtv5;
    MaxSpeed_182203794_1 = 250;
    AverSpeed_182203794_1 = 180;
    LowSpeed_182203794_1 = 100;
    if(En_182203794_1==1)
    {
        	switch (receivedChar_182203794_1) 
        {
            		case 'F':
            		Cours_182203794_1(1,MaxSpeed_182203794_1,1,MaxSpeed_182203794_1);
            		break;
            	case 'f':
            		Cours_182203794_1(1,AverSpeed_182203794_1,1,AverSpeed_182203794_1);
            		break;
            	case 'B':
            		Cours_182203794_1(0,AverSpeed_182203794_1,0,AverSpeed_182203794_1);
            		break;
            	case 'N':
            		Cours_182203794_1(1,AverSpeed_182203794_1,1,MaxSpeed_182203794_1);
            		break;
            	case 'n':
            		Cours_182203794_1(1,LowSpeed_182203794_1,1,AverSpeed_182203794_1);
            		break;
            	case 'G':
            		Cours_182203794_1(1,LowSpeed_182203794_1,1,MaxSpeed_182203794_1);
            		break;
            	case 'g':
            		Cours_182203794_1(1,0,1,AverSpeed_182203794_1);
            		break;
            	case 'H':
            		Cours_182203794_1(0,LowSpeed_182203794_1,0,AverSpeed_182203794_1);
            		break;
            	case 'h':
            		Cours_182203794_1(0,0,0,AverSpeed_182203794_1);
            		break;
            	case 'M':
            		Cours_182203794_1(1,MaxSpeed_182203794_1,1,AverSpeed_182203794_1);
            		break;
            	case 'm':
            		Cours_182203794_1(1,AverSpeed_182203794_1,1,LowSpeed_182203794_1);
            		break;
            	case 'I':
            		Cours_182203794_1(1,MaxSpeed_182203794_1,1,LowSpeed_182203794_1);
            		break;
            	case 'i':
            		Cours_182203794_1(1,AverSpeed_182203794_1,1,0);
            		break;
            	case 'J':
            		Cours_182203794_1(0,AverSpeed_182203794_1,0,LowSpeed_182203794_1);
            		break;
            	case 'j':
            		Cours_182203794_1(0,AverSpeed_182203794_1,0,0);
            		break;
            	case 'L':
            		Cours_182203794_1(0,AverSpeed_182203794_1,1,AverSpeed_182203794_1);
            		break;
            	case 'l':
            		Cours_182203794_1(0,LowSpeed_182203794_1,1,LowSpeed_182203794_1);
            		break;
            	case 'R':
            		Cours_182203794_1(1,AverSpeed_182203794_1,0,AverSpeed_182203794_1);
            		break;
            	case 'r':
            		Cours_182203794_1(1,LowSpeed_182203794_1,0,LowSpeed_182203794_1);
            		break;
            	default:
            		Cours_182203794_1(1,0,1,0);
        }
    }
    _gtv38 = RghtSpeed_182203794_1;
    _gtv9 = RghtCour_182203794_1;
    _gtv14 = LeftSpeed_182203794_1;
    _gtv16 = LeftCour_182203794_1;
    //Плата:3
    digitalWrite(7, _gtv16);
    analogWrite(6, _gtv14);
    digitalWrite(4, _gtv9);
    analogWrite(5, _gtv38);
}
bool _isTimer(unsigned long startTime, unsigned long period)
{
    unsigned long currentTime;
    currentTime = millis();
    if (currentTime>= startTime) 
    {
        return (currentTime>=(startTime + period));
    }
     else 
    {
        return (currentTime >=(4294967295-startTime+period));
    }
}
void _readByteFromUART(byte data,int port)
{
    if (port==0)
    {
        _RVFU2Data = char(data);
    }
}
bool Cours_182203794_1(bool LC, int LS, bool RC, int RS)
{
    LeftCour_182203794_1 = LC;
    LeftSpeed_182203794_1 = LS;
    RghtCour_182203794_1 = RC;
    RghtSpeed_182203794_1 = RS;
}
void _startUart0()
{
    int code= 6;
    Serial.begin(9600, (_serialModeFromInt(code)));
}
int  _serialModeFromInt(int code)
{
    switch (code) 
    {
        case 0x00: return SERIAL_5N1;
        break;
        case 0x02: return SERIAL_6N1;
        break;
        case 0x04: return SERIAL_7N1;
        break;
        case 0x06: return SERIAL_8N1;
        break;
        case 0x08: return SERIAL_5N2;
        break;
        case 0x0A: return SERIAL_6N2;
        break;
        case 0x0C: return SERIAL_7N2 ;
        break;
        case 0x0E: return SERIAL_8N2;
        break;
        case 0x20: return SERIAL_5E1;
        break;
        case 0x22: return SERIAL_6E1;
        break;
        case 0x24: return SERIAL_7E1 ;
        break;
        case 0x26: return SERIAL_8E1;
        break;
        case 0x28: return SERIAL_5E2 ;
        break;
        case 0x2A: return SERIAL_6E2;
        break;
        case 0x2C: return SERIAL_7E2;
        break;
        case 0x2E: return SERIAL_8E2;
        break;
        case 0x30: return SERIAL_5O1;
        break;
        case 0x32: return SERIAL_6O1;
        break;
        case 0x34: return SERIAL_7O1;
        break;
        case 0x36: return SERIAL_8O1;
        break;
        case 0x38: return SERIAL_5O2;
        break;
        case 0x3A: return SERIAL_6O2 ;
        break;
        case 0x3C: return SERIAL_7O2;
        break;
        case 0x3E: return SERIAL_8O2;
        break;
    }
    return SERIAL_8N1;
}
