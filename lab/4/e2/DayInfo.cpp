enum Day{Sunday, Monday, Tuesday, Wednsday, Thursday, Friday, Saturday};
enum Weather{Sunny, Rainy};

struct DayInfo
{
    Day day;
    Weather wea;
};

bool canTravel(DayInfo info){
    if((info.day == Day::Sunday || info.day == Day::Saturday) && info.wea == Weather::Sunny) return 1;
    else return 0;
}
