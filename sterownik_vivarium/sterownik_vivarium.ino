/*
 Name:		sterownik_vivarium.ino
 Created:	18.03.2018 09:42:22
 Author:	Michał Kuzemczak
*/



// ile razy dziennie dane urzadzenie ma sie wlaczyc
#define WLACZENIA_WENTYLACJI	2
#define WLACZENIA_FILTRA	2
#define WLACZENIA_OSWIETLENIA 2
#define WLACZENIA_ZRASZACZY 2


// czas dzialania karzdego urzadzenia w minutach
#define CZAS_WENTYLACJI 5
#define CZAS_FILTRA 5
#define CZAS_OSWIETLENIA 5
#define CZAS_ZRASZACZY 5

#define PIN_WENTYLACJI 4
#define PIN_FILTRA 5
#define PIN_OSWIETLENIA 6
#define PIN_ZRASZACZY 7


char czasy_wentylacji[WLACZENIA_WENTYLACJI][2] = {
	{10,0},
	{16,30}
};

char czasy_filtra[WLACZENIA_FILTRA][2] = {
	{9,0},
	{17,0}
};

char czasy_oswietlenia[WLACZENIA_OSWIETLENIA][2] = {
	{ 9,30 },
	{ 19,0 }
};

char czasy_zraszaczy[WLACZENIA_ZRASZACZY][2] = {
	{ 7,0 },
	{ 20,0 }
};

int h = 0, m = 0, s = 0;
int milis = 0, lastMilis = 0;
int milisWlaczeniaWentylacji = 0, milisWlaczeniaFiltra = 0, milisWlaczeniaOswietlenia = 0, milisWlaczeniaZraszaczy = 0;
bool _wlaczWentylacje = false, _wlaczFiltr = false, _wlaczOswietlenie = false, _wlaczZraszacze = false;

// the setup function runs once when you press reset or power the board
void setup() {
	pinMode(PIN_WENTYLACJI, OUTPUT);
	pinMode(PIN_FILTRA, OUTPUT);
	pinMode(PIN_OSWIETLENIA, OUTPUT);
	pinMode(PIN_ZRASZACZY, OUTPUT);
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
		digitalWrite(PIN_WENTYLACJI, LOW);
	}
	if (_wlaczFiltr && milis - milisWlaczeniaFiltra >= CZAS_FILTRA * 60000) {
		_wlaczFiltr = false;
		digitalWrite(PIN_FILTRA, LOW);
	}
	if (_wlaczOswietlenie && milis - milisWlaczeniaOswietlenia >= CZAS_OSWIETLENIA * 60000) {
		_wlaczOswietlenie = false;
		digitalWrite(PIN_OSWIETLENIA, LOW);
	}
	if (_wlaczZraszacze && milis - milisWlaczeniaZraszaczy >= CZAS_ZRASZACZY * 60000) {
		_wlaczZraszacze = false;
		digitalWrite(PIN_ZRASZACZY, LOW);
	}

	if (!_wlaczWentylacje)
		for (int i = 0; i < WLACZENIA_WENTYLACJI; i++) {
			if (czasy_wentylacji[i][0] == h && czasy_wentylacji[i][1] == m)
				_wlaczWentylacje = true;
		}

	if (!_wlaczFiltr)
		for (int i = 0; i < WLACZENIA_FILTRA; i++) {
			if (czasy_filtra[i][0] == h && czasy_filtra[i][1] == m)
				_wlaczFiltr = true;
		}

	if (!_wlaczOswietlenie)
		for (int i = 0; i < WLACZENIA_OSWIETLENIA; i++) {
			if (czasy_oswietlenia[i][0] == h && czasy_oswietlenia[i][1] == m)
				_wlaczOswietlenie = true;
		}

	if (!_wlaczZraszacze)
		for (int i = 0; i < WLACZENIA_ZRASZACZY; i++) {
			if (czasy_zraszaczy[i][0] == h && czasy_zraszaczy[i][1] == m)
				_wlaczZraszacze = true;
		}


	if (_wlaczWentylacje) {
		digitalWrite(PIN_WENTYLACJI, HIGH);
		milisWlaczeniaWentylacji = milis;
	}
	if (_wlaczFiltr) {
		digitalWrite(PIN_FILTRA, HIGH);
		milisWlaczeniaFiltra = milis;
	}
	if (_wlaczOswietlenie) {
		digitalWrite(PIN_OSWIETLENIA, HIGH);
		milisWlaczeniaOswietlenia = milis;
	}
	if (_wlaczZraszacze) {
		digitalWrite(PIN_ZRASZACZY, HIGH);
		milisWlaczeniaZraszaczy = milis;
	}
}
