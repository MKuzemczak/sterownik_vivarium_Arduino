/*
 Name:		sterownik_vivarium.ino
 Created:	18.03.2018 09:42:22
 Author:	Michał Kuzemczak
*/



// ile razy dziennie dane urzadzenie ma sie wlaczyc
#define WLACZENIA_WENTYLACJI	2
#define WLACZENIA_URZADZENIA_1	2
#define WLACZENIA_URZADZENIA_2 2
#define WLACZENIA_URZADZENIA_3 2


// czas dzialania karzdego urzadzenia w minutach
#define CZAS_WENTYLACJI 5
#define CZAS_URZ_1 5
#define CZAS_URZ_2 5
#define CZAS_URZ_3 5

#define PIN0 4
#define PIN1 5
#define PIN2 6
#define PIN3 7


char czasy_wentylacji[WLACZENIA_WENTYLACJI][2] = {
	{10,0},
	{16,30}
};

char czasy_urzadzenia1[WLACZENIA_URZADZENIA_1][2] = {
	{9,0},
	{17,0}
};

char czasy_urzadzenia2[WLACZENIA_URZADZENIA_2][2] = {
	{ 9,30 },
	{ 19,0 }
};

char czasy_urzadzenia3[WLACZENIA_URZADZENIA_3][2] = {
	{ 7,0 },
	{ 20,0 }
};

int h = 0, m = 0, s = 0;
int milis = 0, lastMilis = 0;
int milisWlaczeniaWentylacji = 0, milisWlaczeniaUrz1 = 0, milisWlaczeniaUrz2 = 0, milisWlaczeniaUrz3 = 0;
bool _wlaczWentylacje = false, _wlaczUrz1 = false, _wlaczUrz2 = false, _wlaczUrz3 = false;

// the setup function runs once when you press reset or power the board
void setup() {
	pinMode(PIN0, OUTPUT);
	pinMode(PIN1, OUTPUT);
	pinMode(PIN2, OUTPUT);
	pinMode(PIN3, OUTPUT);
	milis = millis();
	lastMilis = milis;
}

// the loop function runs over and over again until power down or reset
void loop() {
	milis = millis();
	if (milis - lastMilis >= 1000) {
		s++;
		lastMilis += 1000;
	}
	if (s == 60) {
		s = 0;
		m++;
	}
	if (m == 60) {
		m = 0;
		h++;
	}
	if (h == 24) {
		h = 0;
	}

	if (_wlaczWentylacje && milis - milisWlaczeniaWentylacji >= CZAS_WENTYLACJI * 60000) {
		_wlaczWentylacje = false;
		digitalWrite(PIN0, LOW);
	}
	if (_wlaczUrz1 && milis - milisWlaczeniaUrz1 >= CZAS_URZ_1 * 60000) {
		_wlaczUrz1 = false;
		digitalWrite(PIN1, LOW);
	}
	if (_wlaczUrz2 && milis - milisWlaczeniaUrz2 >= CZAS_URZ_2 * 60000) {
		_wlaczUrz2 = false;
		digitalWrite(PIN2, LOW);
	}
	if (_wlaczUrz3 && milis - milisWlaczeniaUrz3 >= CZAS_URZ_3 * 60000) {
		_wlaczUrz3 = false;
		digitalWrite(PIN3, LOW);
	}

	if (!_wlaczWentylacje)
		for (int i = 0; i < WLACZENIA_WENTYLACJI; i++) {
			if (czasy_wentylacji[i][0] == h && czasy_wentylacji[i][1] == m)
				_wlaczWentylacje = true;
		}

	if (!_wlaczUrz1)
		for (int i = 0; i < WLACZENIA_URZADZENIA_1; i++) {
			if (czasy_urzadzenia1[i][0] == h && czasy_urzadzenia1[i][1] == m)
				_wlaczUrz1 = true;
		}

	if (!_wlaczUrz2)
		for (int i = 0; i < WLACZENIA_URZADZENIA_2; i++) {
			if (czasy_urzadzenia2[i][0] == h && czasy_urzadzenia2[i][1] == m)
				_wlaczUrz2 = true;
		}

	if (!_wlaczUrz3)
		for (int i = 0; i < WLACZENIA_URZADZENIA_3; i++) {
			if (czasy_urzadzenia3[i][0] == h && czasy_urzadzenia3[i][1] == m)
				_wlaczUrz3 = true;
		}


	if (_wlaczWentylacje) {
		digitalWrite(PIN0, HIGH);
		milisWlaczeniaWentylacji = milis;
	}
	if (_wlaczUrz1) {
		digitalWrite(PIN1, HIGH);
		milisWlaczeniaUrz1 = milis;
	}
	if (_wlaczUrz2) {
		digitalWrite(PIN2, HIGH);
		milisWlaczeniaUrz2 = milis;
	}
	if (_wlaczUrz3) {
		digitalWrite(PIN3, HIGH);
		milisWlaczeniaUrz3 = milis;
	}
}
