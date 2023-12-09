#include "stuinfo.hpp"
#include <iostream>
#include <cstdio>
using namespace std;

void inputstu(stuinfo stu[], int n){
    printf("Please input information of %d stduents:\n", n);
    for(int i = 0; i < n; i++){
        printf("Student %d's name: ", i);
        cin.getline(stu[i].name, 20);
        printf("Student %d's scores: ", i);
        for(int j = 0; j < 3; j++) {
            scanf("%lf", &stu[i].score[j]);
            cin.get();
        }
    }

}
void showstu(stuinfo stu[] , int n){
    printf("The information of %d students you input are:\n", n);
    for(int i = 0; i < n; i++){
        printf("Student %d name: %s, scores: %lf %lf %lf\n", i, stu[i].name, stu[i].score[0], stu[i].score[1], stu[i].score[2]);
    }
}
void sortstu(stuinfo stu[] , int n){
    printf("The descending order of the students:\n");
    for(int i = 0; i < n; i++){
        stu[i].ave = (stu[i].score[0]+stu[i].score[1]+stu[i].score[2])/3.0;
    }

    stuinfo student;
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - 1 - i; j++) { 
            if (stu[j].ave > stu[j+1].ave) { 
                student = stu[j];
                stu[j] = stu[j+1];
                stu[j+1] = student;
            }
        }
    }

    for(int i = 0; i < n; i++){
        printf("Student %d name: %s, scores: %lf %lf %lf, average: %lf\n", i, stu[i].name, stu[i].score[0], stu[i].score[1], stu[i].score[2], stu[i].ave);
    }
}
bool findstu(stuinfo stu[] , int n, char ch[]){
    bool che = 0;
    for(int i = 0; i < n; i++){
        if(stu[i].name == ch){
            che = 1;
        }
    }
    return che;
}