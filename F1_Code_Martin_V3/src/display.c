#include "display.h"

short display_init_flag = 0;

void display(){

    //printf("%c[2J", ASCII_ESC); //http://www.climagic.org/mirrors/VT100_Escape_Codes.html

    if(!display_init_flag){
        printf("╔═══════╦══════════╦═════════╦════════════╦════════════╦════════════╦═════════════╦════════════╦════════════╦════════════╦═════════════╦═════════╗\n");
        printf("║  pos  ║  car n°  ║  laps   ║  S1-time   ║  S2-time   ║  S3-time   ║   lap-time  ║  best-S1   ║  best-S2   ║  best-S3   ║  best-lap   ║  state  ║\n");
        printf("╠═══════╠══════════╬═════════╬════════════╬════════════╬════════════╬═════════════╬════════════╬════════════╬════════════╬═════════════╬═════════╣\n");
        
    }
    else{
        printf("%c[%dA", ASCII_ESC,NUMBER_OF_CARS*2);
        printf("%c[2K", ASCII_ESC);
    }
    
    for(int i=0; i<NUMBER_OF_CARS;i++){
        printf("║  %2d   ║    %2d    ║    %2d   ║   %.3f   ║   %.3f   ║   %.3f   ║   %.3f   ║   %.3f   ║   %.3f   ║   %.3f   ║   %.3f   ║    %c    ║\n",i+1,ranking[i].carNumber,ranking[i].numberOfLaps,ranking[i].s1Time,ranking[i].s2Time,ranking[i].s3Time,ranking[i].lapTime,ranking[i].bestS1Time,ranking[i].bestS2Time,ranking[i].bestS3Time,ranking[i].bestLapTime,ranking[i].state);
        if(!display_init_flag){
            printf("╠═══════╬══════════╬═════════╬════════════╬════════════╬════════════╬═════════════╬════════════╬════════════╬════════════╬═════════════╬═════════╣\n");
        }
        else{
            printf("%c[0B", ASCII_ESC);
            printf("%c[2K", ASCII_ESC);
        }
    }
    
    

    if(!display_init_flag){
        printf("%c[1A", ASCII_ESC);   //move curosr 1 line up
        printf("%c[2K", ASCII_ESC);   //delete whole line
        printf("╚═══════╩══════════╩═════════╩════════════╩════════════╩════════════╩═════════════╩════════════╩════════════╩════════════╩═════════════╩═════════╝\n");
        display_init_flag =1;
    }

}