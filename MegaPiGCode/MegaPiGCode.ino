#include <Encoder.h>
#include <Servo.h>
struct UB_16714688
{
    bool ubo_68638907 = 0;
    byte ubo_42736581 = 0;
    byte _gtv1 = 90;
    bool _gtv2 = 0;
    float _strFunabs1 = 0.00;
    bool _tim1I = 0;
    bool _tim1O = 0;
    unsigned long _tim1P = 0UL;
    bool _tim2I = 0;
    bool _tim2O = 0;
    unsigned long _tim2P = 0UL;
    bool _trgrt1 = 0;
    bool _trgrt1I = 0;
}
;
UB_16714688 UB_16714688_Instance1;
byte UB_16714688_ubi_67111478 = 0;
int _AvlDFU3 = 0;
bool En_102238583_3;
bool Rst_102238583_3;
long Data_102238583_3;
Encoder myEnc_102238583_3(18, 31);
bool En_102238583_1;
bool Rst_102238583_1;
long Data_102238583_1;
Encoder myEnc_102238583_1(19, 38);
bool in_172724170_1;
bool out_172724170_1;
boolean temp_172724170_1=0;
bool en_105720086_2;
long Accel_105720086_2;
int in_105720086_2;
long Out_105720086_2;
unsigned long loopTime_105720086_2;
unsigned long time_105720086_2;
bool en_105720086_3;
long Accel_105720086_3;
int in_105720086_3;
long Out_105720086_3;
unsigned long loopTime_105720086_3;
unsigned long time_105720086_3;
byte servoNumPin_126371602_1;
bool ServoRun_126371602_1;
byte ServoGals_126371602_1;
Servo ServoXX_126371602_1; // Инициализация серво
bool LastSDtch_126371602_1; // Передний фронт переменной выключить
bool LastSAtch_126371602_1; // Передний фронт переменной включить
struct _poligonInexes
{
    int minIndex;
    int maxIndex;
}
;
int _Poligon_InArray_1[13] = {75, 82, 90, 100, 120, 140, 170, 200, 240, 320, 395, 475, 557};
int _Poligon_OutArray_1[13] = {60, 55, 50, 45, 40, 35, 30, 25, 20, 15, 12, 10, 8};
int _Poligon_InArray_2[13] = {105, 125, 145, 160, 175, 190, 205, 225, 260, 330, 410, 480, 570};
int _Poligon_OutArray_2[13] = {60, 55, 50, 45, 40, 35, 30, 25, 20, 15, 12, 10, 8};
int _gtv6 = 0; //Скорость левого двигателя
int _gtv7 = 0; //Скорость правого двигателя
int _gtv1 = 0; //Текущая позиция правого колеса мм (от поступления последней команды)
int _gtv2 = 0; //Текущая позиция левого колеса мм
int _gtv4 = 0; //Заданное расстояние перемещения правого колеса мм
int _gtv8 = 0; //Заданное расстояние перемещения левого колеса мм
String _gtv9; //Принимаемая команда
bool _gtv10 = 0; //Конец приема команды
bool _gtv5 = 0; //Правый двигатель вперед
bool _gtv12 = 0; //Левый двигатель вперед
bool _gtv13; //Служебный для тестов
int _gtv11 = 0; //Заданное по Bluetooth растояние перемещения
int _gtv14 = 0; //Заданный  по Bluetooth угол поворота gkfnajhvs
int _gtv22 = 130; //Заданный  по Bluetooth угол сервы
bool _gtv3 = 0; //Установить расстояние движения мм
bool _gtv16 = 0; //Установить угол поворота платформы °
bool _gtv17; //Позиция достигнута
bool _gtv21 = 0; //Сброс текущей позиции, если что...
int _gtv15 = 0; //Левый дальномер расстояние см
int _gtv18 = 0; //Правый дальномер расстояние см
int _gtv20 = 0; //Показания УЗ дальномера см
bool _gtv19; //Такт опроса дальномеров
bool _gtv23 = 0; //ServoOK - серво достиг позиции
byte _gtv24 = 1; //Захват: 0 - открывание  1 - стоп  2 - закрывание
int _gtv25 = 0; //Скорость захвата (максимально 100)
bool _gtv26 = 0; //Закрытие захвата
bool _gtv28 = 0; //Захват отработал
bool _gtv27 = 0; //Включение зеленого светодиода
bool _gtv29 = 0;
bool _tim4I = 0;
bool _tim4O = 0;
unsigned long _tim4P = 0UL;
String _GSFS1 = "0";
String _RVFU1Data;
bool _RVFU1Reset = 1;
bool _FSFS7CO = 0;
bool _tim2I = 0;
bool _tim2O = 0;
unsigned long _tim2P = 0UL;
float _strFunabs4 = 0.00;
bool _FSFS5CO = 0;
bool FTrig_1_Out = 0;
bool FTrig_1_OldStat = 0;
String _GSFS4 = "0";
float _strFunabs2 = 0.00;
bool _FSFS6CO = 0;
int _convertStringToNamberOutput_8 = 0;
bool _trgrt3 = 0;
bool _trgrt3I = 0;
bool _FSFS4CO = 0;
bool _tim3I = 0;
bool _tim3O = 0;
unsigned long _tim3P = 0UL;
String _GSFS3 = "0";
bool _FSFS3CO = 0;
int _convertStringToNamberOutput_5 = 0;
bool _tim6I = 0;
bool _tim6O = 0;
unsigned long _tim6P = 0UL;
bool _gen2I = 0;
bool _gen2O = 0;
unsigned long _gen2P = 0UL;
int _swi5;
float _strFunabs1 = 0.00;
int _convertStringToNamberOutput_7 = 0;
int _swi1;
bool _FSFS1CO = 0;
String _GSFS6 = "0";
bool _gen1I = 0;
bool _gen1O = 0;
unsigned long _gen1P = 0UL;
bool _tim5I = 0;
bool _tim5O = 0;
unsigned long _tim5P = 0UL;
String _GSFS5 = "0";
int _convertStringToNamberOutput_9 = 0;
bool _trgrt1 = 0;
bool _trgrt1I = 0;
String _GSFS2 = "0";
bool _trgrt2 = 0;
bool _trgrt2I = 0;
int _ultrasonic1O = 0;
unsigned long _ultrasonic1P = 0UL;
bool _trgrt4 = 0;
bool _trgrt4I = 0;
bool _FSFS2CO = 0;
int _convertStringToNamberOutput_10 = 0;
int _convertStringToNamberOutput_1 = 0;
String _tempVariable_String;
void setup()
{
    pinMode(69, OUTPUT);
    digitalWrite(69, 0);
    pinMode(13, OUTPUT);
    digitalWrite(13, 0);
    pinMode(34, OUTPUT);
    digitalWrite(34, 0);
    pinMode(35, OUTPUT);
    digitalWrite(35, 0);
    pinMode(37, OUTPUT);
    digitalWrite(37, 0);
    pinMode(36, OUTPUT);
    digitalWrite(36, 0);
    pinMode(43, OUTPUT);
    digitalWrite(43, 0);
    pinMode(42, OUTPUT);
    digitalWrite(42, 0);
    _startUart3();
    pinMode(64, OUTPUT);
    pinMode(60, INPUT);
    loopTime_105720086_2 = micros();
    Out_105720086_2 = -2147483648;
    loopTime_105720086_3 = micros();
    Out_105720086_3 = -2147483648;
}
void loop()
{
    if (_AvlDFU3)
    {
        _AvlDFU3=0;
    }
     else
    {
        if (Serial3.available()) 
        {
            _AvlDFU3=1;
            _readByteFromUART((Serial3.read()),3);
        }
    }
    //Плата:1
//Наименование:Считывание датчиков и дальномеров
//Комментарии:Параметр таймера регулирует частоту опроса датчиков и передачу телеметрии.
    if (!(_gtv19))
    {
         if (_tim3I) 
        {
             if (_isTimer(_tim3P, 100)) 
            {
                _tim3O = 1;
            }
        }
         else 
        {
            _tim3I =1;
            _tim3P = millis();
        }
    }
     else 
    {
        _tim3O = 0;
        _tim3I = 0;
    }
    if (_tim3O) 
    {
        _gtv18 = (_poligon(((analogRead (12))), _Poligon_InArray_2, _Poligon_OutArray_2, 13));
    }
    if (_tim3O) 
    {
        _gtv15 = (_poligon(((analogRead (13))), _Poligon_InArray_1, _Poligon_OutArray_1, 13));
    }
    if (abs((millis() - _ultrasonic1P))>100) 
    {
        digitalWrite(64, HIGH);
        delayMicroseconds(10);
        digitalWrite(64, LOW);
        int _ultrasonicTemp=(pulseIn(60, HIGH))/58;
        if(_ultrasonicTemp<200) 
        {
            _ultrasonic1O=_ultrasonicTemp;
        }
        _ultrasonic1P=millis();
    }
    if (_tim3O) 
    {
        _gtv20 = (_ultrasonic1O);
    }
    _gtv19 = _tim3O;
    if (1) 
    {
         if (_trgrt4I) 
        {
             _trgrt4 = 0;
        }
         else 
        {
            _trgrt4 = 1;
            _trgrt4I = 1;
        }
    }
     else 
    {
        _trgrt4 = 0;
        _trgrt4I = 0;
    }
    ;
    if(_trgrt4) 
    {
        _tim6O = 1;
        _tim6I = 1;
    }
     else 
    {
         if(_tim6I) 
        {
            _tim6I = 0;
            _tim6P = millis();
        }
         else 
        {
             if (_tim6O) 
            {
                if (_isTimer(_tim6P, 6000)) _tim6O = 0;
            }
        }
    }
    _gtv13 = _tim6O;
    //Плата:2
//Наименование:Текущая позиция колес (Энкодеры)
    En_102238583_1 = 1;
    Rst_102238583_1 = _gtv17;
    if(En_102238583_1) 
    {
        Data_102238583_1 = myEnc_102238583_1.read();
        if (Rst_102238583_1) 
        {
            myEnc_102238583_1.write(0);
        }
    }
    _gtv2 = (Data_102238583_1)/(11.94);
    En_102238583_3 = 1;
    Rst_102238583_3 = _gtv17;
    if(En_102238583_3) 
    {
        Data_102238583_3 = myEnc_102238583_3.read();
        if (Rst_102238583_3) 
        {
            myEnc_102238583_3.write(0);
        }
    }
    _gtv1 = ((0)-(Data_102238583_3))/(11.94);
    if (_gtv17) 
    {
        _gtv11 = 0;
    }
    if (_gtv17) 
    {
        _gtv14 = 0;
    }
    //Плата:3
//Наименование:Прием из Bluetooth
    if (_gtv10)
    {
        if(!_RVFU1Reset)
        {
            _RVFU1Data = String("");
            _RVFU1Reset =1;
        }
    }
     else 
    {
        _RVFU1Reset =0;
    }
    if(_AvlDFU3) 
    {
        _tim2O = 1;
        _tim2I = 1;
    }
     else 
    {
         if(_tim2I) 
        {
            _tim2I = 0;
            _tim2P = millis();
        }
         else 
        {
             if (_tim2O) 
            {
                if (_isTimer(_tim2P, 10)) _tim2O = 0;
            }
        }
    }
    in_172724170_1 = _tim2O;
    out_172724170_1=0;
    if(!in_172724170_1 && temp_172724170_1) 
    {
        out_172724170_1=1;
    }
    temp_172724170_1=in_172724170_1;
    _gtv10 = out_172724170_1;
    _gtv9 = _RVFU1Data;
    //Плата:4
//Наименование:Расшифровка принятого из порта
    if (_gtv10 == 1) 
    {
        _FSFS6CO = ((_gtv9).indexOf(String("F")))>-1;
        _gtv3 = _FSFS6CO;
        _GSFS5 = (_gtv9).substring((1));
        _tempVariable_String = _GSFS5;
        _convertStringToNamberOutput_9 = strtol(_tempVariable_String.c_str(),NULL,10);
        if (_FSFS6CO) 
        {
            _gtv11 = (constrain((_convertStringToNamberOutput_9), (-2500), (2500)));
        }
        _FSFS5CO = ((_gtv9).indexOf(String("R")))>-1;
        _gtv16 = _FSFS5CO;
        _GSFS4 = (_gtv9).substring((1));
        _tempVariable_String = _GSFS4;
        _convertStringToNamberOutput_8 = strtol(_tempVariable_String.c_str(),NULL,10);
        if (_FSFS5CO) 
        {
            _gtv14 = (constrain((_convertStringToNamberOutput_8), (-600), (600)));
        }
        _FSFS1CO = ((_gtv9).indexOf(String("N")))>-1;
        _gtv21 = _FSFS1CO;
        _FSFS2CO = ((_gtv9).indexOf(String("S")))>-1;
        _GSFS1 = (_gtv9).substring((1));
        _tempVariable_String = _GSFS1;
        _convertStringToNamberOutput_7 = strtol(_tempVariable_String.c_str(),NULL,10);
        if (_FSFS2CO) 
        {
            _gtv22 = (constrain((_convertStringToNamberOutput_7), (5), (130)));
        }
        _FSFS3CO = ((_gtv9).indexOf(String("H")))>-1;
        _GSFS2 = (_gtv9).substring((1));
        _tempVariable_String = _GSFS2;
        _convertStringToNamberOutput_1 = strtol(_tempVariable_String.c_str(),NULL,10);
        if (_FSFS3CO) 
        {
            _gtv24 = (constrain((_convertStringToNamberOutput_1), (0), (2)));
        }
        _FSFS4CO = ((_gtv9).indexOf(String("G")))>-1;
        _GSFS3 = (_gtv9).substring((1));
        _tempVariable_String = _GSFS3;
        _convertStringToNamberOutput_5 = strtol(_tempVariable_String.c_str(),NULL,10);
        if (_FSFS4CO) 
        {
            _gtv27 = ((constrain((_convertStringToNamberOutput_5), (0), (1)))) == (1);
        }
        _FSFS7CO = ((_gtv9).indexOf(String("L")))>-1;
        _GSFS6 = (_gtv9).substring((1));
        _tempVariable_String = _GSFS6;
        _convertStringToNamberOutput_10 = strtol(_tempVariable_String.c_str(),NULL,10);
        if (_FSFS7CO) 
        {
            _gtv29 = ((constrain((_convertStringToNamberOutput_10), (0), (1)))) == (1);
        }
    }
    //Плата:5
//Наименование:Моргание светодиодами (или их включение)
    if (_gtv29) 
    {
         if (! _gen1I) 
        {
            _gen1I = 1;
            _gen1O = 1;
            _gen1P = millis();
        }
    }
     else 
    {
        _gen1I = 0 ;
        _gen1O= 0;
    }
    if (_gen1I) 
    {
          if (_isTimer (_gen1P , 300)) 
        {
             _gen1P = millis();
            _gen1O = ! _gen1O;
        }
    }
    digitalWrite(13, _gen1O);
    if (_gtv27) 
    {
         if (! _gen2I) 
        {
            _gen2I = 1;
            _gen2O = 1;
            _gen2P = millis();
        }
    }
     else 
    {
        _gen2I = 0 ;
        _gen2O= 0;
    }
    if (_gen2I) 
    {
          if (_isTimer (_gen2P , 300)) 
        {
             _gen2P = millis();
            _gen2O = ! _gen2O;
        }
    }
    digitalWrite(69, _gen2O);
    //Плата:6
//Наименование:Команды на задание расстояний и углов
    _gtv3 = ((_gtv3) && (_gtv10));
    _gtv16 = ((_gtv10) && (_gtv16));
    _gtv21 = ((_gtv10) && (_gtv21));
    //Плата:7
//Наименование:Задание для движения вперед-назад.
    if (_gtv3 == 1) 
    {
        _gtv12 = (_gtv11) > (0);
        _gtv5 = (_gtv11) > (0);
        if((_gtv11) > (0))
        {
            _swi5=(_gtv11)+(10);
        }
        else
        {
            _swi5=(_gtv11)-(10);
        }
        _gtv4 = _swi5;
        _gtv8 = _swi5;
    }
    //Плата:8
//Наименование:Задание скорости и ускорения при движении по энкодеру
    _strFunabs4 = abs((_gtv8)-(_gtv2));
    _strFunabs1 = abs((_gtv4)-(_gtv1));
    en_105720086_3 = 1;
    Accel_105720086_3 = 800L;
    in_105720086_3 = (constrain((_strFunabs1), (0), (130)));
    if(Out_105720086_3== -2147483648) 
    {
        Out_105720086_3 = in_105720086_3;
    }
    if(en_105720086_3)
    {
        if(Accel_105720086_3 != 0) 
        {
            time_105720086_3 = 1000000 / abs(Accel_105720086_3);
            if((micros() >= (loopTime_105720086_3 + time_105720086_3))&&(Out_105720086_3<in_105720086_3))
            {
                if(Out_105720086_3 < in_105720086_3 - 1) 
                {
                    Out_105720086_3 = Out_105720086_3 + 1;
                }
                 else 
                {
                    Out_105720086_3 = in_105720086_3;
                }
                loopTime_105720086_3 = micros();
            }
            if((micros() >= (loopTime_105720086_3 + time_105720086_3))&&(Out_105720086_3>in_105720086_3))
            {
                if(Out_105720086_3 > in_105720086_3 + 1) 
                {
                    Out_105720086_3 = Out_105720086_3 - 1;
                }
                 else 
                {
                    Out_105720086_3 = in_105720086_3;
                }
                loopTime_105720086_3 = micros();
            }
        }
    }
     else 
    {
        if(0) 
        {
            Out_105720086_3 = in_105720086_3;
        }
    }
    _gtv7 = Out_105720086_3;
    if ((((_strFunabs4) < (30)) && ((_strFunabs1) < (30))))
    {
         if (_tim4I) 
        {
             if (_isTimer(_tim4P, 150)) 
            {
                _tim4O = 1;
            }
        }
         else 
        {
            _tim4I =1;
            _tim4P = millis();
        }
    }
     else 
    {
        _tim4O = 0;
        _tim4I = 0;
    }
    if (_tim4O) 
    {
         if (_trgrt3I) 
        {
             _trgrt3 = 0;
        }
         else 
        {
            _trgrt3 = 1;
            _trgrt3I = 1;
        }
    }
     else 
    {
        _trgrt3 = 0;
        _trgrt3I = 0;
    }
    ;
    _gtv17 = ((_trgrt3) || (_gtv21));
    en_105720086_2 = 1;
    Accel_105720086_2 = 800L;
    in_105720086_2 = (constrain((_strFunabs4), (0), (130)));
    if(Out_105720086_2== -2147483648) 
    {
        Out_105720086_2 = in_105720086_2;
    }
    if(en_105720086_2)
    {
        if(Accel_105720086_2 != 0) 
        {
            time_105720086_2 = 1000000 / abs(Accel_105720086_2);
            if((micros() >= (loopTime_105720086_2 + time_105720086_2))&&(Out_105720086_2<in_105720086_2))
            {
                if(Out_105720086_2 < in_105720086_2 - 2) 
                {
                    Out_105720086_2 = Out_105720086_2 + 2;
                }
                 else 
                {
                    Out_105720086_2 = in_105720086_2;
                }
                loopTime_105720086_2 = micros();
            }
            if((micros() >= (loopTime_105720086_2 + time_105720086_2))&&(Out_105720086_2>in_105720086_2))
            {
                if(Out_105720086_2 > in_105720086_2 + 2) 
                {
                    Out_105720086_2 = Out_105720086_2 - 2;
                }
                 else 
                {
                    Out_105720086_2 = in_105720086_2;
                }
                loopTime_105720086_2 = micros();
            }
        }
    }
     else 
    {
        if(0) 
        {
            Out_105720086_2 = in_105720086_2;
        }
    }
    _gtv6 = Out_105720086_2;
    if (_gtv17) 
    {
        _gtv8 = 0;
    }
    if (_gtv17) 
    {
        _gtv4 = 0;
    }
    //Плата:9
//Наименование:Задание значения для поворота
    if (_gtv16 == 1) 
    {
        _gtv12 = (_gtv14) > (0);
        _gtv5 = !((_gtv14) > (0));
        _gtv8 = (_gtv14)*(1.65);
        _gtv4 = ((0)-(_gtv14))*(1.65);
    }
    //Плата:11
//Наименование:Передача PWM на моторы
    analogWrite(12, _gtv7);
    digitalWrite(35, _gtv5);
    digitalWrite(34, !(_gtv5));
    analogWrite(8, (map((_gtv6), (0), (255), (0), (250))));
    digitalWrite(37, _gtv12);
    digitalWrite(36, !(_gtv12));
    //Плата:12
//Наименование:Поворот серво руки
    UB_16714688_ubi_67111478 = _gtv22;
    _func_UB_16714688(&UB_16714688_Instance1, UB_16714688_ubi_67111478, 10, 1, 125);
    servoNumPin_126371602_1 = 62;
    ServoRun_126371602_1 = UB_16714688_Instance1.ubo_68638907;
    ServoGals_126371602_1 = UB_16714688_Instance1.ubo_42736581;
    if(ServoRun_126371602_1 && !LastSAtch_126371602_1)
    	
    {
        	ServoXX_126371602_1.attach(servoNumPin_126371602_1);
        	
    }
    LastSAtch_126371602_1 = ServoRun_126371602_1;
    if (ServoRun_126371602_1) 
    {
        ServoXX_126371602_1.write (ServoGals_126371602_1);
        delay (2);
    }
    if(!ServoRun_126371602_1 && !LastSDtch_126371602_1)
    	
    {
        	ServoXX_126371602_1.detach();
        	
    }
    LastSDtch_126371602_1 = ServoRun_126371602_1;
    _strFunabs2 = abs((UB_16714688_Instance1.ubo_42736581)-(_gtv22));
    if ((_strFunabs2) <= (5)) 
    {
         if (_trgrt1I) 
        {
             _trgrt1 = 0;
        }
         else 
        {
            _trgrt1 = 1;
            _trgrt1I = 1;
        }
    }
     else 
    {
        _trgrt1 = 0;
        _trgrt1I = 0;
    }
    ;
    _gtv23 = _trgrt1;
    //Плата:13
//Наименование:Открытие-закрытие захвата 
    _gtv26 = (_gtv24) == (2);
    if ((((_gtv24) == (0)) || ((_gtv24) == (2)))) 
    {
         if (_trgrt2I) 
        {
             _trgrt2 = 0;
        }
         else 
        {
            _trgrt2 = 1;
            _trgrt2I = 1;
        }
    }
     else 
    {
        _trgrt2 = 0;
        _trgrt2I = 0;
    }
    ;
    if(_trgrt2) 
    {
        _tim5O = 1;
        _tim5I = 1;
    }
     else 
    {
         if(_tim5I) 
        {
            _tim5I = 0;
            _tim5P = millis();
        }
         else 
        {
             if (_tim5O) 
            {
                if (_isTimer(_tim5P, 2000)) _tim5O = 0;
            }
        }
    }
    FTrig_1_Out = 0;
    if ((!(_tim5O))&&(FTrig_1_OldStat))
    {
        FTrig_1_Out = 1;
    }
    FTrig_1_OldStat = _tim5O;
    _gtv28 = FTrig_1_Out;
    if (FTrig_1_Out) 
    {
        _gtv24 = 1;
    }
    if(_tim5O)
    {
        _swi1=100;
    }
    else
    {
        _swi1=0;
    }
    _gtv25 = _swi1;
    analogWrite(9, _gtv25);
    digitalWrite(43, _gtv26);
    digitalWrite(42, !(_gtv26));
    //Плата:14
//Наименование:Отравка телеметрии и ответных сообщений в Bluetooth
    if (_gtv19)
    {
        Serial3.println((((String(_gtv20, DEC))) + (String(" ")) + ((String(_gtv15, DEC))) + (String(" ")) + ((String(_gtv18, DEC))) + (String(" ")) + ((String(_gtv2, DEC))) + (String(" ")) + ((String(_gtv1, DEC)))));
    }
    if (((_gtv17) || (_gtv23) || (_gtv28)))
    {
        Serial3.println("OK");
    }
    if (_gtv10)
    {
        Serial3.println(((String("+")) + (_gtv9)));
    }
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
    if (port==3)
    {
        _RVFU1Data += char(data);
    }
}
int _poligon(int value, int intArray[], int outArray[], int arraySize)
{
    struct  _poligonInexes indexes;
    indexes = _getPoligonIndexes(value, intArray, arraySize);
    return map(value, intArray[indexes.minIndex], intArray[indexes.maxIndex], outArray[indexes.minIndex], outArray[indexes.maxIndex]);
}
struct  _poligonInexes _getPoligonIndexes(int value, int array[], int arraySize)
{
    struct  _poligonInexes result;
    int i;
    result.minIndex = 0;
    result.maxIndex = 0;
    for (i = 0; i < arraySize; i++) 
    {
        if (array [result.minIndex] > array[i]) 
        {
            result.minIndex = i;
        }
        if (array [result.maxIndex] < array[i]) 
        {
            result.maxIndex = i;
        }
    }
    for (i = 0; i < arraySize; i++)
    {
        if ((array [i] >= value) && (array [result.maxIndex] > array[i])) 
        {
            result.maxIndex = i;
        }
    }
    if (result.maxIndex==0)
    {
        result.minIndex = 0;
        result.maxIndex=1;
    }
     else 
    {
         result.minIndex = result.maxIndex -1;
    }
    return result;
    return result;
}
void _startUart3()
{
    int code= 6;
    Serial3.begin(115200, (_serialModeFromInt(code)));
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
void _func_UB_16714688(struct UB_16714688 *_ubInstans, byte ubi_67111478, byte ubpar_164857159, byte ubpar_52031086, byte ubpar_35791337)
{
    bool ubo_68638907 = _ubInstans->ubo_68638907;
    byte ubo_42736581 = _ubInstans->ubo_42736581;
    byte _gtv1 = _ubInstans->_gtv1;
    bool _gtv2 = _ubInstans->_gtv2;
    float _strFunabs1 = _ubInstans->_strFunabs1;
    bool _tim1I = _ubInstans->_tim1I;
    bool _tim1O = _ubInstans->_tim1O;
    unsigned long _tim1P = _ubInstans->_tim1P;
    bool _tim2I = _ubInstans->_tim2I;
    bool _tim2O = _ubInstans->_tim2O;
    unsigned long _tim2P = _ubInstans->_tim2P;
    bool _trgrt1 = _ubInstans->_trgrt1;
    bool _trgrt1I = _ubInstans->_trgrt1I;
    if (1) 
    {
         if (_trgrt1I) 
        {
             _trgrt1 = 0;
        }
         else 
        {
            _trgrt1 = 1;
            _trgrt1I = 1;
        }
    }
     else 
    {
        _trgrt1 = 0;
        _trgrt1I = 0;
    }
    ;
    if (_trgrt1) 
    {
        _gtv1 = ubpar_35791337;
    }
    if (((_gtv2) && (!((_gtv1) > (ubi_67111478))))) 
    {
        _gtv1 = (_gtv1)+(ubpar_52031086);
    }
    if ((((_gtv1) > (ubi_67111478)) && (_gtv2))) 
    {
        _gtv1 = (_gtv1)-(ubpar_52031086);
    }
    _strFunabs1 = abs((_gtv1)-(ubi_67111478));
    if (((!((_strFunabs1) <= ((ubpar_52031086)+(1)))) && (!(_gtv2))))
    {
         if (_tim2I) 
        {
             if (_isTimer(_tim2P, ubpar_164857159)) 
            {
                _tim2O = 1;
            }
        }
         else 
        {
            _tim2I =1;
            _tim2P = millis();
        }
    }
     else 
    {
        _tim2O = 0;
        _tim2I = 0;
    }
    _gtv2 = _tim2O;
    if(!((_strFunabs1) <= ((ubpar_52031086)+(1)))) 
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
                if (_isTimer(_tim1P, 150)) _tim1O = 0;
            }
        }
    }
    ubo_68638907 = _tim1O;
    ubo_42736581 = _gtv1;
    _ubInstans->ubo_68638907 = ubo_68638907;
    _ubInstans->ubo_42736581 = ubo_42736581;
    _ubInstans->_gtv1 = _gtv1;
    _ubInstans->_gtv2 = _gtv2;
    _ubInstans->_strFunabs1 = _strFunabs1;
    _ubInstans->_tim1I = _tim1I;
    _ubInstans->_tim1O = _tim1O;
    _ubInstans->_tim1P = _tim1P;
    _ubInstans->_tim2I = _tim2I;
    _ubInstans->_tim2O = _tim2O;
    _ubInstans->_tim2P = _tim2P;
    _ubInstans->_trgrt1 = _trgrt1;
    _ubInstans->_trgrt1I = _trgrt1I;
}
