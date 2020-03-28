#include <iostream>
#include <cstdio>

class DateTime
{
private:
    int year, month, day;
    int hour, minute, second;
    int total_seconds;     //作业：从1970年1月1日0时开始计算的秒数
    static int mon[];
private:
    bool is_leap_year(int year);
    void calculate();
public:
    DateTime();
    DateTime(int y, int m, int d, int hour, int minute, int second);
    DateTime(const DateTime& dt);
    ~DateTime();
    void showTime();
    void showMoon();  //作业：将当前公历转换为农历显示出来
};

int DateTime::mon[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

bool DateTime::is_leap_year(int year)
{
    if (year % 4 == 0 && year % 100 != 0)
        return true;
    else return !(year % 400);
}

void DateTime::calculate()
{
    int leap_year = 0;
	for (int i = 1970; i < year; ++i)
	{
        if (is_leap_year(i))
            ++leap_year;
	}
    int non_leap_year = year - 1970 - leap_year;
    int rest_day = 0;
    for (int i = 0; i < month - 1; ++i)
        rest_day += mon[i];
    rest_day += day;
    if (is_leap_year(year))
        if (month > 2) rest_day += 1;
    int total_day = leap_year * 366 + non_leap_year * 365 + rest_day;
    total_seconds = total_day * 3600 * 24;
}

int main()
{
    DateTime dt, dt1(2020, 3, 27, 10, 40, 55);
    DateTime dt2(dt), & dt3 = dt;
    DateTime* dt4 = &dt;
    dt.showTime();
    dt1.showTime();
    dt2.showTime();
    dt3.showTime();
    dt4->showTime();

    dt.showMoon();
    return 0;
}

DateTime::DateTime():year(1970), month(1), day(1), hour(9), minute(40), second(0),total_seconds(0)
{
    calculate();
}

DateTime::DateTime(int y, int m, int d, int hour, int minute, int second):
year(y), month(m), day(d), hour(hour), minute(minute), second(second), total_seconds(0)
{
    calculate();
}

DateTime::DateTime(const DateTime& dt):year(dt.year), month(dt.month), day(dt.day),
hour(dt.hour), minute(dt.minute), second(dt.second), total_seconds(0)
{
    calculate();
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
    int moon_year, moon_month, moon_day;
    int Q, R;
    Q = (year - 1901) / 4;
    R = (year - 1901) - 4 * Q;
    int result = 14 * Q + 10.6 * (R + 1);
    if (is_leap_year(year))
        mon[1] = 29;
    else mon[1] = 28;
    for (int x = 0; x < month - 1; ++x)
        result += mon[x];
    result += day;
    moon_month = result / 29.5;
    moon_day = round(result - moon_month * 29.5);
    if (moon_month > month)
    {
        if (month - 1 == 0)
        {
            moon_month = 12;
            moon_year = year - 1;
        }
        else {
            moon_month = month - 1;
            moon_year = year;
        }
    }
    else moon_month = month;

    printf("当前农历：%d/%d/%d\n", moon_year, moon_month, moon_day);
}
