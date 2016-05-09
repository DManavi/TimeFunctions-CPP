// TimeFn.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>

using namespace std;

struct time {
	int hour;
	int minute;
	int second;
};

class TimeClass {

private:

	int _hour; // current hour of the day
	int _minute; // current minute of the day
	int _second; // current second of the day

	time normalize_time(time input) {

		// divide by 60 e.g. 75(s) / 60 = 1(int)
		int next = input.second / 60;

		// get divide remaining and set as current second
		input.second = input.second % 60;

		// add calculated minutes to the time minute
		input.minute += next;


		// divide by 60 e.g. 75(m) / 60 = 1(int)
		next = input.minute / 60;

		// get divide remaining and set as current minute
		input.minute = input.minute % 60;

		while (input.hour < 0 || input.minute < 0 || input.second < 0) {

			// add extra hours to current hour
			input.hour += next;

			// normalize hour
			input.hour = input.hour % 24;

			// if second is negative
			if (input.second < 0) {

				// decrease minute
				input.minute--;

				// add 60 seconds to second
				input.second += 60;
			}

			// if minute is negative
			if (input.minute < 0) {

				// decrease hour
				input.hour--;

				// add 60 minutes to input
				input.minute += 60;
			}

			// if hour is negative
			if (input.hour < 0) {

				// add 24 hours to hour
				input.hour += 24;
			}
		}

		// return normalized value to the caller
		return input;
	}

public:

	TimeClass() {

		// reset hour
		_hour = 0;

		// reset minute
		_minute = 0;

		// reset second
		_second = 0;

		// set default time
		set_time(0, 0, 0);
	}

	TimeClass(int hour, int minute, int second) {

		// set time on construction
		set_time(hour, minute, second);
	}

	TimeClass(time t) {

		// set time on construction
		set_time(t);
	}

	void set_time(time t) {

		// normalize input time
		t = normalize_time(t);

		// assign hour
		_hour = t.hour;

		// assign minute
		_minute = t.minute;

		// assign second
		_second = t.second;
	}

	void set_time(int hour, int minute, int second) {

		// create new time variable
		time t;

		// assign hour
		t.hour = hour;

		// assign minute
		t.minute = minute;

		// assign second
		t.second = second;

		// call set_time with time struct
		set_time(t);
	}

	time get_time() {

		// create output variable
		time output;

		cout << "Hour: ";

		// get hour
		cin >> output.hour;

		cout << "Minute: ";

		// get minute
		cin >> output.minute;

		cout << "Second: ";

		// get second
		cin >> output.second;

		// return output to caller
		return output;
	}

	time subtract(time t1, time t2) {

		// create output variable
		time output;

		// subtract hours
		output.hour = t2.hour - t1.hour;

		// subtract minutes
		output.minute = t2.minute - t1.minute;

		// subtract seconds
		output.second = t2.second - t1.second;

		while (output.hour < 0 || output.minute < 0 || output.second < 0) {

			// if hour is negative
			if (output.hour < 0) {

				// fix negative hour
				output.hour += 24;
			}

			if (output.minute < 0) {

				// decrease hour
				output.hour--;

				// add 60 minutes to current minute
				output.minute += 60;
			}

			if (output.second < 0) {

				// decrease minute
				output.minute--;

				// add 60 seconds to current second
				output.second += 60;
			}
		}

		// normalize time again
		output = normalize_time(output);

		// return output to caller
		return output;
	}

	time add(time t1, time t2) {

		// create output variable
		time output;

		// add hours
		output.hour = t1.hour + t2.hour;

		// add minutes
		output.minute = t1.minute + t2.minute;

		// add seconds
		output.second = t1.second + t2.second;

		// normalize add result
		output = normalize_time(output);

		// return normalized time to the caller
		return output;
	}

	time current_time() {

		time tOutput;

		tOutput.hour = _hour;

		tOutput.minute = _minute;

		tOutput.second = _second;

		return tOutput;
	}

	void show_current_time() {

		// show prompt
		cout << "Current system time is: ";

		// show time
		show_time(_hour, _minute, _second);
	}

	void show_time(int hour, int minute, int second) {

		// print time
		cout << hour << ":" << minute << ":" << second;
	}

	int total_seconds() {

		return _hour * 3600 + _minute * 60 + _second;
	}

	TimeClass operator+ (const TimeClass& other) {


		// get time from current time
		time t1 = current_time();

		// get time from second timeClass
		time t2;

		t2.hour = other._hour;

		t2.minute = other._minute;

		t2.second = other._second;

		// add times together
		time tOutput = add(t1, t2);

		// return output to caller
		return TimeClass(tOutput);
	}

	TimeClass operator- (const TimeClass& other) {

		// get time from current time
		time t1 = current_time();

		// get time from second timeClass
		time t2;

		t2.hour = other._hour;

		t2.minute = other._minute;

		t2.second = other._second;

		// subtract times
		time tOutput = subtract(t2, t1);

		// return output to caller
		return TimeClass(tOutput);
	}

	TimeClass& operator++ () {

		_second++;

		set_time(_hour, _minute, _second);

		return *this;
	}

	TimeClass operator++(int) {

		TimeClass tmp(*this); // copy

		operator++(); // pre-increment

		return tmp;   // return old value
	}

	TimeClass& operator-- () {

		_second--;

		set_time(_hour, _minute, _second);

		return *this;
	}

	TimeClass operator-- (int) {

		TimeClass tmp(*this); // copy

		operator--(); // pre-increment

		return tmp;   // return old value
	}

	TimeClass& operator+ (int n) {

		_second = _second + n;

		set_time(_hour, _minute, _second);

		return *this;
	}

	TimeClass& operator- (int n) {

		_second = _second - n;

		set_time(_hour, _minute, _second);

		return *this;
	}

	bool operator< (TimeClass& rhs) {

		int rhs_totalSeconds = rhs.total_seconds();

		return this->total_seconds() < rhs_totalSeconds;
	}

	bool operator> (TimeClass& rhs) {

		int rhs_totalSeconds = rhs.total_seconds();

		return this->total_seconds() > rhs_totalSeconds;
	}

	bool operator<=(TimeClass& rhs) {
		
		int rhs_totalSeconds = rhs.total_seconds();
		
		int current_totalSeconds = this->total_seconds();

		return current_totalSeconds < rhs_totalSeconds || current_totalSeconds == rhs_totalSeconds;
	}

	bool operator>=(TimeClass& rhs) {

		int rhs_totalSeconds = rhs.total_seconds();

		int current_totalSeconds = this->total_seconds();

		return current_totalSeconds > rhs_totalSeconds || current_totalSeconds == rhs_totalSeconds;
	}

	bool operator==(TimeClass& rhs) {

		int rhs_totalSeconds = rhs.total_seconds();

		int current_totalSeconds = this->total_seconds();

		return current_totalSeconds == rhs_totalSeconds;
	}

	bool operator!=(TimeClass& rhs) {

		int rhs_totalSeconds = rhs.total_seconds();

		int current_totalSeconds = this->total_seconds();

		return current_totalSeconds != rhs_totalSeconds;
	}
};

int main()
{
	// create new instance of time class
	TimeClass timeEmpty;

	// create new instance of time class with integer params
	TimeClass timeWithIntParams(22, 65, 59);

	// create time
	time t;

	// set hour
	t.hour = 22;

	// set minute
	t.minute = 65;

	// set second
	t.second = 80;

	// create new instance of time class with time param
	TimeClass timeWithTimeParam(t);

	// show prompt
	cout << "Time is" << "\r\n\r\n";

	// show prompt
	cout << "\r\n" << "time class with default time constructor" << "\r\n";

	// show crrent time of the timeEmpty instance
	timeEmpty.show_current_time();

	// show prompt
	cout << "\r\n" << "time class with int parameters" << "\r\n";

	// show current time of the timeWithIntParams instance
	timeWithIntParams.show_current_time();

	cout << "\r\n" << "Time after increament is (postfix)" << "\r\n";

	timeWithIntParams++;

	// show current time of the timeWithIntParams instance
	timeWithIntParams.show_current_time();

	cout << "\r\n" << "Time after decreament is (postfix)" << "\r\n";

	// decrease time
	timeWithIntParams--;

	// show current time of the timeWithIntParams instance
	timeWithIntParams.show_current_time();


	cout << "\r\n" << "Time after adding 5 seconds is" << "\r\n";

	// add time with 5
	timeWithIntParams = timeWithIntParams + 5;

	// show current time after add
	timeWithIntParams.show_current_time();


	cout << "\r\n" << "Time after subtracting 5 seconds is" << "\r\n";

	// add time with 5
	timeWithIntParams = timeWithIntParams - 5;

	// show current time after add
	timeWithIntParams.show_current_time();


	// show prompt
	cout << "\r\n" << "time class with time parameters" << "\r\n";

	// show current time of the timeWithTimeParam instance
	timeWithTimeParam.show_current_time();


	// Set time from code-behind

	// set current time
	timeEmpty.set_time(18, 35, 66);

	// show prompt
	cout << "\r\n" << "Time has been updated from code." << "\r\n\r\n" << "Time is: ";

	// show current time
	timeEmpty.show_current_time();

	// Get time from user input and update time

	// show prompt
	cout << "\r\n\r\n" << "Trying to get time from user.\r\n";

	// show prompt
	cout << "Enter new time: \r\n";

	// get time from user
	time userTime = timeEmpty.get_time();

	// show user entered values
	cout << "\r\n" << "User entered: " << userTime.hour << ":" << userTime.minute << ":" << userTime.second;

	// update time
	timeEmpty.set_time(userTime);

	cout << "\r\n" << "Time has been updated by the user. New time is: ";

	// show updated time
	timeEmpty.show_current_time();


	// Add two times

	cout << "\r\n\r\nAdd two times\r\n\r\n";

	// shor prompt
	cout << "Enter time 1: " << "\r\n";

	// get time from user
	time t1 = timeEmpty.get_time();

	// show prompt
	cout << "Enter time 2: " << "\r\n";

	// get second time from user
	time t2 = timeEmpty.get_time();

	// add two times
	time tResult = timeEmpty.add(t1, t2);

	// show add result
	cout << "\r\nAdd result: " << tResult.hour << ":" << tResult.minute << ":" << tResult.second;

	// create two time classes from t1 & t2
	TimeClass timeClass1(t1), timeClass2(t2), operatorResult;

	operatorResult = timeClass1 + timeClass2;

	time operatorTime = operatorResult.current_time();

	// show add result
	cout << "\r\nAdd result (By operator): " << operatorTime.hour << ":" << operatorTime.minute << ":" << operatorTime.second;

	// subtract two times

	cout << "\r\n\r\nSubtract two times\r\n\r\n";

	// shor prompt
	cout << "Enter time 1: " << "\r\n";

	// get time from user
	t1 = timeEmpty.get_time();

	// show prompt
	cout << "Enter time 2: " << "\r\n";

	// get second time from user
	t2 = timeEmpty.get_time();

	// subtract two times
	tResult = timeEmpty.subtract(t1, t2);

	// show add result
	cout << "\r\nSubtract result: " << tResult.hour << ":" << tResult.minute << ":" << tResult.second;

	timeClass1 = TimeClass(t1);

	timeClass2 = TimeClass(t2);

	operatorResult = timeClass2 - timeClass1;

	operatorTime = operatorResult.current_time();

	// show add result
	cout << "\r\nSubtract result (By operator): " << operatorTime.hour << ":" << operatorTime.minute << ":" << operatorTime.second;


	// compare two times

	cout << "\r\n\r\nCompare two times\r\n\r\n";

	// shor prompt
	cout << "Enter time 1: " << "\r\n";

	// get time from user
	t1 = timeEmpty.get_time();

	// show prompt
	cout << "Enter time 2: " << "\r\n";

	t2 = timeEmpty.get_time();

	// equality check
	bool isEqual = timeClass1 == timeClass2;

	// inequality check
	bool inEqual = timeClass1 != timeClass2;

	// is left side greater than right side
	bool isLeftGtRight = timeClass1 > timeClass2;

	// is left side greater than or equal right side
	bool isLeftGtEqualRight = timeClass1 >= timeClass2;

	// is left side less than right side
	bool isLeftLtRight = timeClass1 < timeClass2;

	// is left side less than or equal right side
	bool isLeftLtEqualRight = timeClass1 <= timeClass2;

	// show equality result
	cout << "\r\nT1 == T2: ";

	if (isEqual) {
		cout << "true";
	}
	else {
		cout << "false";
	}

	cout << "\r\nT1 != T2: ";

	if (inEqual) {
		cout << "true";
	}
	else {
		cout << "false";
	}

	// show greater than result
	cout << "\r\nT1 > T2: ";

	if (isLeftGtRight) {
		cout << "true";
	}
	else {
		cout << "false";
	}

	// show greater than or equal result
	cout << "\r\nT1 => T2: ";

	if (isLeftGtEqualRight) {
		cout << "true";
	}
	else {
		cout << "false";
	}

	// show less than result
	cout << "\r\nT1 < T2: ";

	if (isLeftLtRight) {
		cout << "true";
	}
	else {
		cout << "false";
	}

	// show less than or equal result
	cout << "\r\nT1 <= T2: ";

	if (isLeftLtEqualRight) {
		cout << "true";
	}
	else {
		cout << "false";
	}

	getchar();

	// show exit prompt
	cout << "\r\nPress return to exit...";

	// prevent auto close console window
	cin.ignore();

	return 0;
}