// TimeFn.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "stdio.h"

class TimeClass {

private:

	int _hour; // current hour of the day
	int _minute; // current minute of the day
	int _second; // current second of the day

	void normalize_time(int* hour, int* minute, int* second) {

		// divide by 60 e.g. 75(s) / 60 = 1(int)
		int next = *second / 60;

		// get divide remaining and set as current second
		*second = *second % 60;

		// add calculated minutes to the time minute
		*minute += next;

		// divide by 60 e.g. 75(m) / 60 = 1(int)
		next = *minute / 60;

		// get divide remaining and set as current minute
		*minute = *minute % 60;

		// add extra hours to current hour
		*hour += next;

		// normalize hour
		*hour = *hour % 24;
	}

public:

	void set_time(int hour, int minute, int second) {

		// normalize input time
		normalize_time(&hour, &minute, &second);

		// assign hour
		_hour = hour;

		// assign minute
		_minute = minute;

		// assign second
		_second = second;
	}

	void get_time(int* hour, int* minute, int* second) {

		scanf_s("%d:%d:%d", hour, minute, second);

		getchar();
	}

	void subtract(int h1, int m1, int s1, int h2, int m2, int s2, int* hour, int* minute, int* second) {

		// subtract hours
		*hour = h2 - h1;

		// subtract minutes
		*minute = m2 - m1;

		// subtract seconds
		*second = s2 - s1;

		while (*hour < 0 || *minute < 0 || *second < 0) {

			// if hour is negative
			if (*hour < 0) {

				// fix negative hour
				*hour += 24;
			}

			if (*minute < 0) {

				// decrease hour
				*hour -= 1;

				// add 60 minutes to current minute
				*minute += 60;
			}

			if (*second < 0) {

				// decrease minute
				*minute -= 1;

				// add 60 seconds to current second
				*second += 60;
			}
		}
	}

	void add(int h1, int m1, int s1, int h2, int m2, int s2, int* hour, int* minute, int* second) {

		*hour = h1 + h2;

		*minute = m1 + m2;

		*second = s1 + s2;

		normalize_time(hour, minute, second);
	}

	void show_current_time() {

		// 
		show_time("Current system time is: %d:%d:%d\r\n", _hour, _minute, _second);
	}

	void show_time(char* format, int hour, int minute, int second) {

		// show prompt & current date/time
		printf(format, hour, minute, second);
	}
};

int main()
{
	// create new instance of time class
	TimeClass time;

	// create time variables with their default values
	int hour = 22, minute = 65, second = 80;


	// Set time from code-behind

	// set current time
	time.set_time(hour, minute, second);

	printf("Time has been updated from code.\r\n");

	// show current time
	time.show_current_time();


	// Get time from user input and update time

	// show prompt
	printf("Trying to get time from user.\r\n");

	// show prompt
	printf("Enter new time: ");

	// get time from user
	time.get_time(&hour, &minute, &second);

	// show user entered values
	printf("User entered: %d:%d:%d\r\n", hour, minute, second);

	// update time
	time.set_time(hour, minute, second);

	printf("Time has been updated by the user.\r\n");

	// show updated time
	time.show_current_time();



	// Add two times

	printf("Add two times\r\n");

	// create time variables
	int h1 = 0, m1 = 0, s1 = 0, h2 = 0, m2 = 0, s2 = 0;

	int hr = 0, mr = 0, sr = 0;

	printf("Enter time 1: ");

	// get first time from user input
	time.get_time(&h1, &m1, &s1);

	printf("Enter time 2: ");

	// get first time from user input
	time.get_time(&h2, &m2, &s2);

	// add two times together
	time.add(h1, m1, s1, h2, m2, s2, &hr, &mr, &sr);

	// show add result
	time.show_time("Add result: %d:%d:%d\r\n", hr, mr, sr);



	// subtract two times

	printf("Subtract two times\r\n");

	printf("Enter time 1: ");

	// get first time from user input
	time.get_time(&h1, &m1, &s1);

	printf("Enter time 2: ");

	// get first time from user input
	time.get_time(&h2, &m2, &s2);

	// add two times together
	time.subtract(h1, m1, s1, h2, m2, s2, &hr, &mr, &sr);

	// show add result
	time.show_time("Subtract result: %d:%d:%d\r\n", hr, mr, sr);



	// show exit prompt
	printf("Press any key to exit...");

	// prevent auto close console window
	getchar();

	return 0;
}