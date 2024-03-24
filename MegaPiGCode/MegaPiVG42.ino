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
UB_16714688 UB_16714688_Instance3;
byte UB_16714688_ubi_67111478 = 0;
int _AvlDFU3 = 0;
bool En;
int myErr;
int kP;
int kD;
int kI;
int myCorr;
int correction;
int err;
int err_arr[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
int err_p= -1;
bool in_172724170_2;
bool out_172724170_2;
boolean temp_172724170_2=0;
bool En_102238583_1;
bool Rst_102238583_1;
long Data_102238583_1;
Encoder myEnc_102238583_1(18, 31);
bool En_102238583_2;
bool Rst_102238583_2;
long Data_102238583_2;
Encoder myEnc_102238583_2(19, 38);
byte servoNumPin_126371602_3;
bool ServoRun_126371602_3;
byte ServoGals_126371602_3;
Servo ServoXX_126371602_3; // Инициализация серво
bool LastSDtch_126371602_3; // Передний фронт переменной выключить
bool LastSAtch_126371602_3; // Передний фронт переменной включить
struct _poligonInexes
{
    int minIndex;
    int maxIndex;
}
;
int _Poligon_InArray_2[13] = {75, 82, 90, 100, 120, 140, 170, 200, 240, 320, 395, 475, 557};
int _Poligon_OutArray_2[13] = {60, 55, 50, 45, 40, 35, 30, 25, 20, 15, 12, 10, 8};
int _Poligon_InArray_3[13] = {105, 125, 145, 160, 175, 190, 205, 225, 260, 330, 410, 480, 570};
int _Poligon_OutArray_3[13] = {60, 55, 50, 45, 40, 35, 30, 25, 20, 15, 12, 10, 8};
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
bool _gtv29 = 0; //Системный светодиод D13 (синий)
long _gtv30 = 300; //Частота моргания светодиодов. Если сделать большую - горит долго ;)
bool _gtv31; //Найти черную линию
int _gtv32 = 0; //Ошибка датчиков линии
bool _gtv33 = 0; //Направление поиска черной линии
bool _gtv34 = 0; //Остановка поиска линии по времени 5 сек
bool _gtv35 = 0; //Ехать к стене
int _gtv36 = 200; //Расстояние до стены доехать
int _gtv37 = 10; //Повернуть дальномер
bool _gtv38 = 0;
bool _gtv39 = 0; //Платформа движется прямо вперед/назад
int _gtv40 = 0; //Рекомендуемая корректировка рассчитанная по боковому дальномеру
int _gtv41 = 0; //Корректировка скорости правого мотора на принятое значение  + ускоряется - замедляется
bool _gtv42 = 0; //Пришла корректировка скорости. После окончания движения желательно обнулять!
bool _gtv43 = 0; //Осуществляется движение по туннелю 
int _gtv46 = 0;
bool _gtv47 = 0;
int _gtv48 = 0;
bool _trgr2 = 0;
int _swi2;
bool _trgr4 = 0;
bool _trgr5 = 0;
bool _trgrt8 = 0;
bool _trgrt8I = 0;
int _convertStringToNamberOutput_5 = 0;
int _swi7;
int _convertStringToNamberOutput_20 = 0;
bool _trgr3 = 0;
String _RVFU2Data;
bool _RVFU2Reset = 1;
int _convertStringToNamberOutput_9 = 0;
bool _FSFS1CO = 0;
bool _FSFS11CO = 0;
bool _gen2I = 0;
bool _gen2O = 0;
unsigned long _gen2P = 0UL;
String _GSFS10 = "0";
int _convertStringToNamberOutput_1 = 0;
bool _FSFS13CO = 0;
bool _tim3I = 0;
bool _tim3O = 0;
unsigned long _tim3P = 0UL;
bool _trgrt2 = 0;
bool _trgrt2I = 0;
String _GSFS2 = "0";
bool _FSFS14CO = 0;
bool _tim2I = 0;
bool _tim2O = 0;
unsigned long _tim2P = 0UL;
bool _FSFS7CO = 0;
String _GSFS12 = "0";
bool _FSFS6CO = 0;
bool _FSFS8CO = 0;
String _GSFS5 = "0";
int _swi6;
float _strFunabs5 = 0.00;
int _convertStringToNamberOutput_21 = 0;
int _swi8;
bool _trgr6 = 0;
bool _tim4I = 0;
bool _tim4O = 0;
unsigned long _tim4P = 0UL;
bool _trgrt9 = 0;
bool _trgrt9I = 0;
long _convertStringToNamberOutput_8 = 0L;
bool _FSFS12CO = 0;
bool _tim5I = 0;
bool _tim5O = 0;
unsigned long _tim5P = 0UL;
bool _trgrt6 = 0;
bool _trgrt6I = 0;
String _GSFS3 = "0";
int _convertStringToNamberOutput_17 = 0;
int _convertStringToNamberOutput_10 = 0;
int _swi3;
bool _trgrt3 = 0;
bool _trgrt3I = 0;
float _strFunabs1 = 0.00;
bool _trgrt10 = 0;
bool _trgrt10I = 0;
bool _FSFS10CO = 0;
bool _tim1I = 0;
bool _tim1O = 0;
unsigned long _tim1P = 0UL;
int _convertStringToNamberOutput_13 = 0;
bool _FSFS5CO = 0;
int _swi4;
String _GSFS4 = "0";
String _GSFS9 = "0";
bool _FSFS2CO = 0;
int _convertStringToNamberOutput_7 = 0;
int _convertStringToNamberOutput_11 = 0;
bool _FSFS3CO = 0;
float _strFunabs2 = 0.00;
float _strFunabs6 = 0.00;
bool _trgrt4 = 0;
bool _trgrt4I = 0;
bool _gen3I = 0;
bool _gen3O = 0;
unsigned long _gen3P = 0UL;
String _swi5;
String _GSFS1 = "0";
bool _tim7I = 0;
bool _tim7O = 0;
unsigned long _tim7P = 0UL;
bool _FSFS4CO = 0;
String _GSFS11 = "0";
bool _trgr1 = 0;
String _GSFS6 = "0";
bool _trgrt7 = 0;
bool _trgrt7I = 0;
String _GSFS8 = "0";
String _tempVariable_String;
void setup()
{
    pinMode(68, INPUT);
    pinMode(69, OUTPUT);
    digitalWrite(69, 0);
    pinMode(65, OUTPUT);
    digitalWrite(65, 0);
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
    if (0) 
    {
        _gtv20 = 50;
    }
    if (!(_gtv19))
    {
         if (_tim5I) 
        {
             if (_isTimer(_tim5P, 50)) 
            {
                _tim5O = 1;
            }
        }
         else 
        {
            _tim5I =1;
            _tim5P = millis();
        }
    }
     else 
    {
        _tim5O = 0;
        _tim5I = 0;
    }
    if (_tim5O) 
    {
        _gtv18 = (_poligon(((analogRead (4))), _Poligon_InArray_3, _Poligon_OutArray_3, 13));
    }
    if (_tim5O) 
    {
        _gtv15 = (_poligon(((analogRead (13))), _Poligon_InArray_2, _Poligon_OutArray_2, 13));
    }
    _gtv19 = _tim5O;
    if (1) 
    {
         if (_trgrt10I) 
        {
             _trgrt10 = 0;
        }
         else 
        {
            _trgrt10 = 1;
            _trgrt10I = 1;
        }
    }
     else 
    {
        _trgrt10 = 0;
        _trgrt10I = 0;
    }
    ;
    if(_trgrt10) 
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
                if (_isTimer(_tim2P, 6000)) _tim2O = 0;
            }
        }
    }
    _gtv13 = _tim2O;
    //Плата:2
//Наименование:Условие для осуществления подсчета ошибки бокового дальномера
//Комментарии:Производится если осуществляетсяя движение вперед F и расстояние в диапазоне 50-320 мм до стены Расстояния считываются 1 раз в 50 м Ошибка от заданного значения от стены 190 мм Kp=1 Kd=1 Ki=0
    En = (((_gtv15) > (5)) && (_gtv39) && ((_gtv15) < (32)) && (_gtv19));
    myErr = (_gtv15)-(20);
    kP = 2;
    kD = 2;
    kI = 0;
    if(En == 1)
    {
        err = myErr;
        err_p = (err_p + 1) % 10;
        err_arr[err_p] = err;
        int P = err * kP;
        int D = (err_arr[err_p] - err_arr[(err_p+11) % 10])*kD;
        int err_sum = 0;
        for (int i = 0; i < 10; i++) err_sum += err_arr[i];
        int I = err_sum/10*kI;
        correction = P + I + D;
    }
    myCorr = correction;
    _gtv40 = myCorr;
    //Плата:3
//Наименование:Прием из Bluetooth
    if (_gtv10)
    {
        if(!_RVFU2Reset)
        {
            _RVFU2Data = String("");
            _RVFU2Reset =1;
        }
    }
     else 
    {
        _RVFU2Reset =0;
    }
    if(_AvlDFU3) 
    {
        _tim4O = 1;
        _tim4I = 1;
    }
     else 
    {
         if(_tim4I) 
        {
            _tim4I = 0;
            _tim4P = millis();
        }
         else 
        {
             if (_tim4O) 
            {
                if (_isTimer(_tim4P, 10)) _tim4O = 0;
            }
        }
    }
    in_172724170_2 = _tim4O;
    out_172724170_2=0;
    if(!in_172724170_2 && temp_172724170_2) 
    {
        out_172724170_2=1;
    }
    temp_172724170_2=in_172724170_2;
    _gtv10 = out_172724170_2;
    _gtv9 = _RVFU2Data;
    //Плата:4
//Наименование:Расшифровка принятого из порта
    if (_gtv10 == 1) 
    {
        _FSFS11CO = ((_gtv9).indexOf(String("F")))>-1;
        _gtv3 = _FSFS11CO;
        _GSFS9 = (_gtv9).substring((1));
        _tempVariable_String = _GSFS9;
        _convertStringToNamberOutput_21 = strtol(_tempVariable_String.c_str(),NULL,10);
        if (_FSFS11CO) 
        {
            _gtv11 = (constrain((_convertStringToNamberOutput_21), (-2500), (2500)));
        }
        _FSFS12CO = ((_gtv9).indexOf(String("R")))>-1;
        _gtv16 = _FSFS12CO;
        _GSFS10 = (_gtv9).substring((1));
        _tempVariable_String = _GSFS10;
        _convertStringToNamberOutput_11 = strtol(_tempVariable_String.c_str(),NULL,10);
        if (_FSFS12CO) 
        {
            _gtv14 = (constrain((_convertStringToNamberOutput_11), (-600), (600)));
        }
        _FSFS13CO = ((_gtv9).indexOf(String("N")))>-1;
        _gtv21 = _FSFS13CO;
        _FSFS14CO = ((_gtv9).indexOf(String("S")))>-1;
        if (_FSFS14CO) 
        {
            _gtv46 = _gtv22;
        }
        _GSFS11 = (_gtv9).substring((1));
        _tempVariable_String = _GSFS11;
        _convertStringToNamberOutput_17 = strtol(_tempVariable_String.c_str(),NULL,10);
        if (_FSFS14CO) 
        {
            _gtv22 = (constrain((_convertStringToNamberOutput_17), (35), (130)));
        }
        _gtv47 = (_gtv46) == (_gtv22);
        _GSFS12 = (_gtv9).substring((1));
        _tempVariable_String = _GSFS12;
        _convertStringToNamberOutput_20 = strtol(_tempVariable_String.c_str(),NULL,10);
        _FSFS10CO = ((_gtv9).indexOf(String("H")))>-1;
        if (_FSFS10CO) 
        {
            _gtv24 = (constrain((_convertStringToNamberOutput_20), (0), (2)));
        }
        _GSFS8 = (_gtv9).substring((1));
        _tempVariable_String = _GSFS8;
        _convertStringToNamberOutput_13 = strtol(_tempVariable_String.c_str(),NULL,10);
        _FSFS6CO = ((_gtv9).indexOf(String("G")))>-1;
        if (_FSFS6CO) 
        {
            _gtv27 = ((constrain((_convertStringToNamberOutput_13), (0), (1)))) == (1);
        }
        _GSFS5 = (_gtv9).substring((1));
        _tempVariable_String = _GSFS5;
        _convertStringToNamberOutput_9 = strtol(_tempVariable_String.c_str(),NULL,10);
        _FSFS5CO = ((_gtv9).indexOf(String("L")))>-1;
        if (_FSFS5CO) 
        {
            _gtv29 = ((constrain((_convertStringToNamberOutput_9), (0), (1)))) == (1);
        }
        _GSFS4 = (_gtv9).substring((1));
        _tempVariable_String = _GSFS4;
        _convertStringToNamberOutput_8 = strtol(_tempVariable_String.c_str(),NULL,10);
        _FSFS1CO = ((_gtv9).indexOf(String("Q")))>-1;
        if (_FSFS1CO) 
        {
            _gtv30 = (constrain((_convertStringToNamberOutput_8), (10), (120000L)));
        }
        _GSFS1 = (_gtv9).substring((1));
        _tempVariable_String = _GSFS1;
        _convertStringToNamberOutput_7 = strtol(_tempVariable_String.c_str(),NULL,10);
        _FSFS2CO = ((_gtv9).indexOf(String("X")))>-1;
        _gtv31 = _FSFS2CO;
        if (_FSFS2CO) 
        {
            _gtv33 = ((constrain((_convertStringToNamberOutput_7), (0), (1)))) == (1);
        }
        _GSFS2 = (_gtv9).substring((1));
        _tempVariable_String = _GSFS2;
        _convertStringToNamberOutput_1 = strtol(_tempVariable_String.c_str(),NULL,10);
        _FSFS3CO = ((_gtv9).indexOf(String("W")))>-1;
        _gtv35 = _FSFS3CO;
        if (_FSFS3CO) 
        {
            _gtv36 = (constrain((_convertStringToNamberOutput_1), (200), (1000)));
        }
        _FSFS4CO = ((_gtv9).indexOf(String("Y")))>-1;
        _GSFS3 = (_gtv9).substring((1));
        _tempVariable_String = _GSFS3;
        _convertStringToNamberOutput_5 = strtol(_tempVariable_String.c_str(),NULL,10);
        if (_FSFS4CO) 
        {
            _gtv37 = (constrain((_convertStringToNamberOutput_5), (5), (130)));
        }
        _FSFS7CO = ((_gtv9).indexOf(String("V")))>-1;
        _gtv42 = _FSFS7CO;
        _GSFS6 = (_gtv9).substring((1));
        _tempVariable_String = _GSFS6;
        _convertStringToNamberOutput_10 = strtol(_tempVariable_String.c_str(),NULL,10);
        if (_FSFS7CO) 
        {
            _gtv41 = (constrain((_convertStringToNamberOutput_10), (-15), (15)));
        }
        _FSFS8CO = ((_gtv9).indexOf(String("J")))>-1;
        _gtv43 = _FSFS8CO;
    }
    //Плата:5
//Наименование:Моргание светодиодами (или их включение)
    if (_gtv29) 
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
          if (_isTimer (_gen2P , _gtv30)) 
        {
             _gen2P = millis();
            _gen2O = ! _gen2O;
        }
    }
    digitalWrite(65, _gen2O);
    if (_gtv27) 
    {
         if (! _gen3I) 
        {
            _gen3I = 1;
            _gen3O = 1;
            _gen3P = millis();
        }
    }
     else 
    {
        _gen3I = 0 ;
        _gen3O= 0;
    }
    if (_gen3I) 
    {
          if (_isTimer (_gen3P , _gtv30)) 
        {
             _gen3P = millis();
            _gen3O = ! _gen3O;
        }
    }
    digitalWrite(69, _gen3O);
    //Плата:6
//Наименование:Команды на задание расстояний и углов
//Комментарии:Ограничение времени поиска линии
    if(((!(_gtv3)) && (_gtv10) && (!(_gtv42)))) _trgr1 = 0;
    if(((_gtv3) && (_gtv10))) _trgr1 = 1;
    _gtv39 = _trgr1;
    _gtv3 = ((_gtv3) && (_gtv10));
    _gtv16 = ((_gtv10) && (_gtv16));
    _gtv21 = ((_gtv10) && (_gtv21));
    if (_gtv31)
    {
         if (_tim7I) 
        {
             if (_isTimer(_tim7P, 5000)) 
            {
                _tim7O = 1;
            }
        }
         else 
        {
            _tim7I =1;
            _tim7P = millis();
        }
    }
     else 
    {
        _tim7O = 0;
        _tim7I = 0;
    }
    _gtv34 = _tim7O;
    //Плата:7
//Наименование:Текущая позиция колес (Энкодеры)
    En_102238583_1 = 1;
    Rst_102238583_1 = ((_gtv17) || (0) || (0));
    if(En_102238583_1) 
    {
        Data_102238583_1 = myEnc_102238583_1.read();
        if (Rst_102238583_1) 
        {
            myEnc_102238583_1.write(0);
        }
    }
    _gtv1 = ((0)-(Data_102238583_1))/(11.94);
    En_102238583_2 = 1;
    Rst_102238583_2 = ((_gtv17) || (0) || (0));
    if(En_102238583_2) 
    {
        Data_102238583_2 = myEnc_102238583_2.read();
        if (Rst_102238583_2) 
        {
            myEnc_102238583_2.write(0);
        }
    }
    _gtv2 = (Data_102238583_2)/(11.94);
    if (_gtv17) 
    {
        _gtv11 = 0;
    }
    if (_gtv17) 
    {
        _gtv14 = 0;
    }
    //Плата:8
//Наименование:Задание для движения вперед-назад.
    if (_gtv3 == 1) 
    {
        _gtv8 = _gtv11;
        _gtv4 = _gtv11;
    }
    //Плата:9
//Наименование:Задание значения для поворота
    if (_gtv16 == 1) 
    {
        _gtv8 = (_gtv14)*(1.592);
        _gtv4 = ((0)-(_gtv14))*(1.592);
    }
    //Плата:10
//Наименование:Задание скорости и ускорения при движении по энкодеру
    if(_gtv10) _trgr2 = 0;
    if((_gtv41) != (0)) _trgr2 = 1;
    if(_trgr2)
    {
        _swi6=_gtv48;
    }
    else
    {
        _swi6=(_gtv8)-(_gtv2);
    }
    _gtv12 = (_swi6) > (0);
    _strFunabs2 = abs(_swi6);
    if((_strFunabs2) > (3))
    {
        _swi4=45;
    }
    else
    {
        _swi4=0;
    }
    _gtv6 = ((constrain((_strFunabs2), (0), (90))))+(_swi4);
    _gtv48 = (_gtv4)-(_gtv1);
    _gtv5 = ((_gtv4)-(_gtv1)) > (0);
    _strFunabs1 = abs((_gtv4)-(_gtv1));
    if(!((_strFunabs1) < (3)))
    {
        _swi7=45;
    }
    else
    {
        _swi7=0;
    }
    _gtv7 = (((constrain((_strFunabs1), (0), (90))))+(_swi7))+(_gtv41);
    if ((_strFunabs1) < (3))
    {
         if (_tim1I) 
        {
             if (_isTimer(_tim1P, 40)) 
            {
                _tim1O = 1;
            }
        }
         else 
        {
            _tim1I =1;
            _tim1P = millis();
        }
    }
     else 
    {
        _tim1O = 0;
        _tim1I = 0;
    }
    if (_tim1O) 
    {
         if (_trgrt6I) 
        {
             _trgrt6 = 0;
        }
         else 
        {
            _trgrt6 = 1;
            _trgrt6I = 1;
        }
    }
     else 
    {
        _trgrt6 = 0;
        _trgrt6I = 0;
    }
    ;
    if(_gtv10) _trgr3 = 0;
    if(((_trgrt6) || (_gtv21))) _trgr3 = 1;
    if (_trgr3) 
    {
         if (_trgrt7I) 
        {
             _trgrt7 = 0;
        }
         else 
        {
            _trgrt7 = 1;
            _trgrt7I = 1;
        }
    }
     else 
    {
        _trgrt7 = 0;
        _trgrt7I = 0;
    }
    ;
    if (_trgrt7) 
    {
        _gtv41 = 0;
    }
    _gtv17 = _trgrt7;
    if (_gtv17) 
    {
        _gtv8 = 0;
    }
    if (_gtv17) 
    {
        _gtv4 = 0;
    }
    //Плата:13
//Наименование:Поворот в поиске черной линии
    if (_gtv31 == 1) 
    {
        _gtv6 = 60;
        _gtv7 = 60;
        _gtv5 = _gtv33;
        _gtv12 = !(_gtv33);
        _strFunabs5 = abs(_gtv32);
        if ((((((_strFunabs5) <= (4)) && ((_strFunabs5) >= (2)))) || (_gtv34))) 
        {
            _gtv17 = 1;
        }
        if ((((((_strFunabs5) <= (4)) && ((_strFunabs5) >= (2)))) || (_gtv34))) 
        {
            _gtv31 = 0;
        }
        if ((((((_strFunabs5) <= (4)) && ((_strFunabs5) >= (2)))) || (_gtv34))) 
        {
            _gtv7 = 0;
        }
        if ((((((_strFunabs5) <= (4)) && ((_strFunabs5) >= (2)))) || (_gtv34))) 
        {
            _gtv6 = 0;
        }
    }
    //Плата:14
    if (_gtv35 == 1) 
    {
        _gtv6 = 130;
        _gtv7 = 130;
        _gtv5 = 1;
        _gtv12 = 1;
        if ((((_gtv36) > ((10)*(_gtv20))) || (_gtv21))) 
        {
            _gtv17 = 1;
        }
        if ((((_gtv36) > ((10)*(_gtv20))) || (_gtv21))) 
        {
            _gtv35 = 0;
        }
        if ((((_gtv36) > ((10)*(_gtv20))) || (_gtv21))) 
        {
            _gtv7 = 0;
        }
        if ((((_gtv36) > ((10)*(_gtv20))) || (_gtv21))) 
        {
            _gtv6 = 0;
        }
    }
    //Плата:16
//Наименование:Передача PWM на моторы
    digitalWrite(35, _gtv5);
    digitalWrite(34, !(_gtv5));
    if(_gtv5)
    {
        _swi8=(map((_gtv7), (0), (255), (0), (255)));
    }
    else
    {
        _swi8=(map((_gtv7), (0), (255), (0), (252)));
    }
    analogWrite(12, _swi8);
    digitalWrite(36, !(_gtv12));
    digitalWrite(37, _gtv12);
    if(_gtv12)
    {
        _swi2=(map((_gtv6), (0), (255), (0), (250)));
    }
    else
    {
        _swi2=(map((_gtv6), (0), (255), (0), (255)));
    }
    analogWrite(8, _swi2);
    //Плата:17
//Наименование:Поворот серво руки
    UB_16714688_ubi_67111478 = _gtv22;
    _func_UB_16714688(&UB_16714688_Instance3, UB_16714688_ubi_67111478, 10, 1, 125);
    servoNumPin_126371602_3 = 62;
    ServoRun_126371602_3 = (((_gtv22) > (35)) && ((_gtv22) <= (131)) && (UB_16714688_Instance3.ubo_68638907));
    ServoGals_126371602_3 = UB_16714688_Instance3.ubo_42736581;
    if(ServoRun_126371602_3 && !LastSAtch_126371602_3)
    	
    {
        	ServoXX_126371602_3.attach(servoNumPin_126371602_3);
        	
    }
    LastSAtch_126371602_3 = ServoRun_126371602_3;
    if (ServoRun_126371602_3) 
    {
        ServoXX_126371602_3.write (ServoGals_126371602_3);
        delay (2);
    }
    if(!ServoRun_126371602_3 && !LastSDtch_126371602_3)
    	
    {
        	ServoXX_126371602_3.detach();
        	
    }
    LastSDtch_126371602_3 = ServoRun_126371602_3;
    _strFunabs6 = abs((UB_16714688_Instance3.ubo_42736581)-(_gtv22));
    if ((_strFunabs6) <= (5)) 
    {
         if (_trgrt9I) 
        {
             _trgrt9 = 0;
        }
         else 
        {
            _trgrt9 = 1;
            _trgrt9I = 1;
        }
    }
     else 
    {
        _trgrt9 = 0;
        _trgrt9I = 0;
    }
    ;
    _gtv23 = _trgrt9;
    //Плата:19
//Наименование:Открытие-закрытие захвата 
    _gtv26 = (_gtv24) == (2);
    if(_gtv28) _trgr4 = 0;
    if((((_gtv24) == (0)) || ((_gtv24) == (2)))) _trgr4 = 1;
    if (_trgr4)
    {
         if (_tim3I) 
        {
             if (_isTimer(_tim3P, 2850)) 
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
    if(_gtv10) _trgr6 = 0;
    if(_trgrt4) _trgr6 = 1;
    if (_trgr6) 
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
    _gtv28 = _trgrt2;
    if (_trgrt4) 
    {
        _gtv24 = 1;
    }
    if(_trgr4)
    {
        _swi3=60;
    }
    else
    {
        _swi3=0;
    }
    _gtv25 = _swi3;
    analogWrite(9, _gtv25);
    digitalWrite(43, _gtv26);
    digitalWrite(42, !(_gtv26));
    //Плата:20
//Наименование:Отравка телеметрии и ответных сообщений в Bluetooth
    if((digitalRead (68)))
    {
        _swi5=String("1");
    }
    else
    {
        _swi5=String("0");
    }
    if (_gtv19)
    {
        Serial3.println((((String(_gtv20, DEC))) + (String(" ")) + ((String(_gtv15, DEC))) + (String(" ")) + ((String(_gtv18, DEC))) + (String(" ")) + ((String(_gtv2, DEC))) + (String(" ")) + ((String(_gtv1, DEC))) + (String(" ")) + ((String(_gtv32, DEC))) + (String(" ")) + (_swi5)));
    }
    if (_gtv47) 
    {
         if (_trgrt8I) 
        {
             _trgrt8 = 0;
        }
         else 
        {
            _trgrt8 = 1;
            _trgrt8I = 1;
        }
    }
     else 
    {
        _trgrt8 = 0;
        _trgrt8I = 0;
    }
    ;
    if(_gtv10) _trgr5 = 0;
    if(((_gtv17) || (_gtv23) || (_gtv28) || (_gtv38) || (_trgrt8))) _trgr5 = 1;
    if (_trgr5) 
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
    if (_trgrt3)
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
        _RVFU2Data += char(data);
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
