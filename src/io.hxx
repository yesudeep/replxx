#ifndef REPLXX_IO_HXX_INCLUDED
#define REPLXX_IO_HXX_INCLUDED 1

#include <deque>

#ifdef _WIN32
#include <windows.h>
#else
#include <termios.h>
#endif

namespace replxx {

class Terminal {
public:
	enum class EVENT_TYPE {
		KEY_PRESS,
		MESSAGE
	};
private:
#ifdef _WIN32
	HANDLE _consoleOut;
	HANDLE _consoleIn;
	DWORD _oldMode;
	WORD _oldDisplayAttribute;
	UINT const _inputCodePage;
	UINT const _outputCodePage;
#else
	struct termios _origTermios; /* in order to restore at exit */
	int _interrupt[2];
#endif
	bool _rawMode; /* for destructor to check if restore is needed */
public:
	enum class CLEAR_SCREEN {
		WHOLE,
		TO_END
	};
public:
	Terminal( void );
	~Terminal( void );
	void write32( char32_t const*, int );
	void write8( void const*, int );
	int get_screen_columns(void);
	int get_screen_rows(void);
	int enable_raw_mode(void);
	void disable_raw_mode(void);
	char32_t read_char(void);
	void clear_screen( CLEAR_SCREEN );
	EVENT_TYPE wait_for_input( void );
	void notify_event( EVENT_TYPE );
#ifdef _WIN32
	void jump_cursor( int, int );
	void clear_section( int );
#endif
private:
	Terminal( Terminal const& ) = delete;
	Terminal& operator = ( Terminal const& ) = delete;
	Terminal( Terminal&& ) = delete;
	Terminal& operator = ( Terminal&& ) = delete;
};

void beep();
char32_t read_unicode_character(void);

namespace tty {

extern bool in;
extern bool out;

}

}

#endif

