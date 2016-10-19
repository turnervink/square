#include <pebble.h>
#include "lang.h"

// Days of the week
const char* dayNames[5][7] = {
	{"SUN", "MON", "TUE", "WED", "THU", "FRI", "SAT"},
	{"DIM", "LUN", "MAR", "MER", "JEU", "VEN", "SAM"},
	{"DO", "LU", "MA", "MI", "JU", "VI", "SA"},
	{"SO", "MO", "DI", "MI", "DO", "FR", "SA"},
	{"DOM", "LUN", "MAR", "MER", "GIO", "VEN", "SAB"}
};

// Months of the year
const char* monthNames[5][12] = {
	{"JAN", "FEB", "MAR", "APR", "MAY", "JUN", "JUL", "AUG", "SEP", "OCT", "NOV", "DEC"},
	{"JAN", "FEV", "MAR", "AVR", "MAI", "JUI", "JUL", "AOU", "SEP", "OCT", "NOV", "DEC"},
	{"ENE", "FEB", "MAR", "ABR", "MAY", "JUN", "JUL", "AGO", "SET", "OCT", "NOV", "DIC"},
	{"JAN", "FEB", "MÄR", "APR", "MAI", "JUN", "JUL", "AUG", "SEP", "OKT", "NOV", "DEZ"},
	{"GEN", "FEB", "MAR", "APR", "MAG", "GIU", "LUG", "AGO", "SET", "OTT", "NOV", "DIC"}
};

bool language_changed(int old, int new) {
	if (old != new) {
		return true;
	} else {
		return false;
	}
}
