#include <iostream>
#include <cmath>

int mon[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

bool is_leap_year(int year)
{
    if (year%4 == 0 && year%100 != 0)
        return true;
    else return !(year % 400);
}

class DateTime {
private:
  static int sth;
  int year, month, day;
  int hour, minute, second;
  int moon_year, moon_month, moon_day;
  void transfer(); 
public:
  DateTime();
  DateTime(int y, int m, int d, int hour, int minute, int second); 
  DateTime(const DateTime &dt);
  ~DateTime();
  static void showTime();
  void showMoon();  //作业：将当前公历转换为农历显示出来 
};

int DateTime::sth = 0;

int main() {
  DateTime dt, dt1(2020, 3, 27, 10, 40, 55);
  DateTime dt2(dt), &dt3 = dt;
  DateTime *dt4 = &dt;
  dt.showTime();
  dt.showMoon();
  dt1.showTime();
  dt2.showTime();
  dt3.showTime();
  dt4->showTime();
  return 0;
}
DateTime::DateTime()
{
  year = 2020; month = 3; day = 20;
  hour = 11; minute = 27; second = 55;
  sth = 11;
}
DateTime::DateTime(int y, int m, int d, int hour, int minute, int second)
{
  year = y; month = m; day = d;
  this->hour = hour; this->minute = minute; this->second = second;
}
DateTime::DateTime(const DateTime &dt)
{
  year = dt.year; month = dt.month; day = dt.day;
  hour = dt.hour; minute = dt.minute; second = dt.second;
}
DateTime::~DateTime() 
{
  std::cout << " Go die, Ha~Ha~" << std::endl;
}
void DateTime::showTime()
{
  printf("当前时间：%d/%d/%d %d:%d:%d\n", year, month, day, hour, minute, second);
}

void DateTime::showMoon()
{
	transfer();
  	printf("当前农历时间：%d/%d/%d %d:%d:%d\n", moon_year, moon_month, moon_day, hour, minute, second);	
} 

void DateTime::transfer()
{
    int Q, R;
    Q = (year - 1901)/4;
    R = (year - 1901) - 4*Q;
    int result = 14*Q + 10.6*(R+1);
    if (is_leap_year(year))
        mon[1] = 29;
    else mon[1] = 28;
    for (int x = 0; x < month-1; ++x)
        result += mon[x];
    result += day;
    moon_month = result / 29.5;
    moon_day = round(result - moon_month*29.5);
    if (moon_month > month)
    {
        if (month-1 == 0)
        {
        	moon_month = 12;
        	moon_year = year-1;
		}
        else {
        	moon_month = month-1;
			moon_year = year;	
		}
    }
    else moon_month = month;
}
 
