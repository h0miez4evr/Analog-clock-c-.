#include <graphics.h>
#include <conio.h>
#include <cmath>
#include <iostream>
const float PI = 3.14159265;
using namespace std;
// Function to convert degrees to radians.
float degreesToRadians(float degrees)
 {
    return degrees * PI / 180;
}
// Function to draw a clock hand.
void drawHand(int centerX, int centerY, float angle, float length, int color)
 {
    int xEnd = centerX + length * cos(degreesToRadians(angle - 90));
    int yEnd = centerY + length * sin(degreesToRadians(angle - 90));
    setcolor(color);
    line(centerX, centerY, xEnd, yEnd);
}
// Function to draw minute markers.
void drawMinuteMarkers(int centerX, int centerY, int radius) 
{
    for (int i = 0; i < 60; ++i) {
        float angle = i * 6; // 360 degrees / 60 minutes
        int xStart = centerX + (radius - 10) * cos(degreesToRadians(angle - 90));
        int yStart = centerY + (radius - 10) * sin(degreesToRadians(angle - 90));
        int xEnd = centerX + radius * cos(degreesToRadians(angle - 90));
        int yEnd = centerY + radius * sin(degreesToRadians(angle - 90));
        setcolor(WHITE);
        line(xStart, yStart, xEnd, yEnd);
    }
}
// Function to display a custom date inside the clock.
void displayDate(int centerX, int centerY, int day, int month, int year) 
{
    char dateStr[20];//creates the BUffer memory to store the output data.
    snprintf(dateStr, sizeof(dateStr), "%02d/%02d/%04d", day, month, year);
     /*
               sprintf()
               -> IT STENDS FOR Sting Print Formatted.
               sprint(Buffer,"your formatted string",integervalues) 
        */
    setcolor(WHITE);
    outtextxy(centerX - 40, centerY + 100, dateStr);//TO Calculate The position and display at the position.
}
// Function to get user input for initial time.
void getInitialTime(int &hours, int &minutes, int &seconds) {
    cout << "Enter initial time  " << endl;
    cout << "ENTER HOUR: ";
    cin >> hours;
    cout << "ENTER MINUTE: ";
    cin >> minutes;
    cout << "ENTER SECOND: ";
    cin >> seconds;
    cout << endl;
    // Validate input.
    if (hours < 0 || hours > 23 || minutes < 0 || minutes > 59 || seconds < 0 || seconds > 59) 
    {
        cout << "Invalid time entered. Setting to 00:00:00." << endl;
        hours = 0;
        minutes = 0;
        seconds = 0;
    }
}
// Function to check the validity of the date.
int check(int year, int month, int day)
 {
    if (year > 2000 && year < 3000 && month > 0 && month < 13 && day > 0 && day < 33) {
        return 1;
    } else {
        return 0;
    }
}
// Function to check if a year is a leap year.
bool isLeapYear(int year) 
{
    if (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0)) {
        return true;
    }
    return false;
}
// Function to get the number of days in a month.
int daysInMonth(int month, int year) {
    switch (month) {
        case 1: case 3: case 5: case 7: case 8: case 10: case 12:
            return 31;
        case 4: case 6: case 9: case 11:
            return 30;
        case 2:
            return isLeapYear(year) ? 29 : 28;
        default:
            return 0;
    }
}
int main() 
{
    int centerX, centerY, day, month, year;
    int hours, minutes, seconds; 
    RAM:
    cout << "ENTER THE DATE." << endl;
    cout << "ENTER YEAR: ";
    cin >> year;
    cout << "ENTER MONTH: ";
    cin >> month;
    cout << "ENTER DAY: ";
    cin >> day;
    cout << endl;

    int temp = check(year, month, day);
    if (temp == 0) {
        cout << "INVALID DATE" << endl;
        goto RAM;
    }
    getInitialTime(hours, minutes, seconds);
    int gd = DETECT, gm;
    initwindow(1366, 768, "ANALOG CLOCK.");
    // Define clock parameters.
    const int clockRadius = 250;
    const int hourHandLength = 150;
    const int minuteHandLength = 190;
    const int secondHandLength = 220;
    // Calculate the center of the clock.
    centerX = getmaxx() / 2;//get the x -cordinate of the center.
    centerY = getmaxy() / 2;//get the y-cordiinate of the  center.
    // Draw the static clock face.
    setcolor(WHITE);
    circle(centerX, centerY, clockRadius);
    drawMinuteMarkers(centerX, centerY, clockRadius);
    // Draw clock numbers.
    for (int i = 1; i <= 12; ++i)
     {
        int angle = i * 30 - 90; // Positions numbers at 30-degree intervals
        int xText = centerX + (clockRadius - 30) * cos(degreesToRadians(angle));
        int yText = centerY + (clockRadius - 30) * sin(degreesToRadians(angle));
        char number[3];//it creates the buffer memory to store the output  data.
        snprintf(number, sizeof(number), "%d", i);// function.
        outtextxy(xText - 10, yText - 10, number);// IT displays the NUmbers and at the specific positions. 
    }
    while (1) 
    {
        // Clear only the dynamic parts (the hands).
        setcolor(BLACK);
        drawHand(centerX, centerY, 360.f * (seconds / 60.f), secondHandLength, BLACK);
        drawHand(centerX, centerY, 360.f * (minutes / 60.f), minuteHandLength, BLACK);
        drawHand(centerX, centerY, 360.f * ((hours % 12 + minutes / 60.f) / 12.f), hourHandLength, BLACK);
        // Update time & Date.
        seconds++;
        if (seconds >= 60)
         {
            seconds = 0;
            minutes++;
            if (minutes >= 60) 
            {
                minutes = 0;
                hours++;
                if (hours >= 24) 
                {
                    hours = 0;
                    day++;
                    if (day > daysInMonth(month, year))
                     {
                        day = 1;
                        month++;
                        if (month > 12) 
                        {
                            month = 1;
                            year++;
                        }
                    }
                }
            }
        }
        // Draw the clock hands.
        drawHand(centerX, centerY, 360.f * (seconds / 60.f), secondHandLength, RED);//for the second-hand cloclk.
        drawHand(centerX, centerY, 360.f * (minutes / 60.f), minuteHandLength, YELLOW);//for the minute-hand cloclk.
        // Smoothly move the hour hand by considering minutes.Not exactaly at the position but angle-wise.
        float hourAngle = 360.f * ((hours % 12 + minutes / 60.f) / 12.f);
        drawHand(centerX, centerY, hourAngle, hourHandLength, GREEN);// for the houur-hand clock.
        // Display the updated date inside the clock.
        displayDate(centerX, centerY, day, month, year);// funnction to display the date.
        delay(1000); // Delay for 1 second.
    }
    closegraph();// Built in function to clode the graph.
    return 0;
}
