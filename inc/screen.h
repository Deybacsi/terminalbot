/*

    Manipulating the terminal screen

*/

using namespace std;

// frames/sec
const int   FPS=10,                     // choose wisely ...
            FPS2MILLISEC=1000/FPS,      // ... it's an int ;)
            FPS2NANOSEC =1000000/FPS;

// number of our layers to draw things
const short MAXLAYERS = 5;

// color code constants
const int   C_BLACK   = 0,
            C_RED     = 1,
            C_GREEN   = 2,
            C_YELLOW  = 3,
            C_BLUE    = 4,
            C_MAGENTA = 5,
            C_CYAN    = 6,
            C_GRAY    = 7,

            C_DGRAY   = 8,
            C_LRED    = 9,
            C_LGREEN  = 10,
            C_LYELLOW = 11,
            C_LBLUE   = 12,
            C_LMAGENTA= 13,
            C_LCYAN   = 14,
            C_WHITE   = 15,

            C_BGTRANS = 8;  // default transparent bg color -> ANSI 49m

// ANSI escape codes to print colors
const std::string COLORS[16] = { "0;30", "0;31", "0;32", "0;33", "0;34", "0;35", "0;36", "0;37", "1;30", "1;31", "1;32", "1;33", "1;34", "1;35", "1;36", "1;37" };
const std::string BCOLORS[9] = { "40", "41", "42", "43", "44", "45", "46", "47", "49" };

// optimized screen size
const int   MAXX = 1000;
const int   MAXY = 1000;

// clear screen
#define clearScreen() printf("\033[H\033[J")
// move cursor
#define gotoXy(x,y) printf("\033[%d;%dH", (x), (y))


// the simple char type
struct s_simplechar {
    string chr;
    unsigned short int col ;
    unsigned short int bcol ;
    bool transpchr;
    bool transpcol;
    bool transpbcol;
};


// simple writing char for string outputs (for debug, etc)
s_simplechar WRITECHAR = { u8" ", 7, 0, false, false, false};

// simple transparent clear char
s_simplechar CLEARCHAR = { " ", 7, 8, true, true, true};

// make arrays global to avoid storing them in the stack -> stackoverflow when maxx,maxy too big ;)
// layers with chars & attributes
s_simplechar LAYER[MAXLAYERS+1][MAXX+1][MAXY+1];
// merged layers for the final output
s_simplechar FINAL[MAXX+1][MAXY+1];

class Cscreen {
    private:

        // the actual screen size 
        int SCREENX, SCREENY;

    public:

        // initialize screen
        void init() {
            clearScreen();
            struct winsize w;
            ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
            SCREENY=w.ws_row;
            SCREENX=w.ws_col;
            if (SCREENX > MAXX || SCREENY > MAXY) {
                std::cout << "Your terminal size is too large (" << SCREENX << "x" << SCREENY << "), set it to  " << MAXX << "x" << MAXY << "\n\n";
                SCREENX=MAXX-1;
                SCREENY=MAXY-1;
                exit(1);
            }
        }

        int getScreenWidth() {
            return SCREENX;
        }

        int getScreenHeight() {
            return SCREENY;
        }

        // puts a char to x,y at given layer
        void charXy(int layer, int x, int y, s_simplechar simplechar) {
            // check if coords are inside screen, and char is not a control character
            if ( x >= 0 && x<= SCREENX && y >= 0 && y<=SCREENY ) {
                LAYER[layer][x][y]=simplechar;
            }
        }

        // puts a string to x,y at given layer
        void stringXy(int layer, int x, int y, s_simplechar simplechar, std::string s ) {
            unsigned int i;
            for (i=0; i<s.length(); i++) {
                simplechar.chr=s[i];
                charXy(layer, x+i, y, simplechar);
            }

        }

        // draws a line to layer with given char
        void lineXy (int layer, int x1, int y1, int x2, int y2, s_simplechar simplechar ) {
            int x,y=0;

            float fx,fy=0;
            int t=0;

            int kulx=x2-x1;
            int kuly=y2-y1;

            // decide if the line is tall or wide
            if (abs(kulx) >= abs(kuly)){            // wide
                fy= (float) (y2-y1) / (x2-x1) ;     // calc the "angle"
                if (x1>x2) { t=x1; x1=x2; x2=t; t=y1; y1=y2; y2=t;}
                for (x=x1; x<=x2; x++) { charXy(layer, x, round(y1 + fy * (x-x1)), simplechar ); }  // put out chars from left to right to the needed y coord
            } else {                                // tall
                fx= (float) (x2-x1) / (y2-y1) ;
                if (y1>y2) { t=x1; x1=x2; x2=t; t=y1; y1=y2; y2=t; }
                for (y=y1; y<=y2; y++) { charXy(layer, round(x1 + fx * (y-y1)), y, simplechar ); }        
            }
        }

        // fill a layer with char
        void clearLayer(int layer, s_simplechar simplechar) {
            int x,y;
            for (y=0; y<=SCREENY; y++) {
                for (x=0; x<=SCREENX; x++) {
                    LAYER[layer][x][y]=simplechar;
                }
            }
        }

        // fill all layers with char
        void clearAllLayer(s_simplechar simplechar) {
            int l;
            clearLayer(0, WRITECHAR);
            for (l=1; l< MAXLAYERS; l++) {
                clearLayer(l, simplechar);
            }
        }

        // merge all the layers from bottom to top ( 0 -> MAXLAYERS-1 ) to FINAL array
        void mergeLayers(){
            int l,x,y;
            for (l=0; l<MAXLAYERS; l++) {
                for (y=0; y<=SCREENY; y++) {
                    for (x=0; x<=SCREENX; x++) {
                        FINAL[x][y].chr = LAYER[l][x][y].transpchr  ? FINAL[x][y].chr  : LAYER[l][x][y].chr;
                        FINAL[x][y].col = LAYER[l][x][y].transpcol  ? FINAL[x][y].col  : LAYER[l][x][y].col;
                        FINAL[x][y].bcol= LAYER[l][x][y].transpbcol ? FINAL[x][y].bcol : LAYER[l][x][y].bcol;
                    }
                }
            }
        }

        // print out the final image to screen
        void printScreen() {
            int x,y;
            gotoXy(0,0); // -> cursor to upper left
            for (y=0; y<SCREENY; y++) {
                for (x=0; x<SCREENX; x++) {

                    // print the color attributes
                    printf("\033[%s;%sm", COLORS[FINAL[x][y].col].c_str(), BCOLORS[FINAL[x][y].bcol].c_str() );
                    // and the char itself
                    //putchar(FINAL[x][y].chr);
                    // putchar(FINAL[x][y].chr);
                    cout << FINAL[x][y].chr;
                    //putwchar((char32_t) FINAL[x][y].chr);
                    //cout << "\u0444";
                    //printf("%ls", FINAL[x][y].chr);
                
                }

                if ( y < SCREENY-1) { putchar(13); putchar(10); } ;
            }

            
        }

};




