#include "stuinfo.hpp"
#include <cstdio>
int main()
{
    stuinfo stu[3];
    inputstu(stu, 3);
    showstu(stu, 3);
    sortstu(stu, 3);

    printf("Please input the order of the name you want to find: ");
    char name[20];
    scanf("%s", name);
    if(!findstu(stu, 3, name)){
        printf("%s is not in the students list.", name);
    }

    
    return 0;
}