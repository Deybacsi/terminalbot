#ifndef DIGITS_H
#define DIGITS_H

#endif // DIGITS_H
const int   MAXDIGITDESIGNS=1,
            MAXDIGITS=11,
            DIGITHEIGHT=3,
            DIGITWIDTH=3,
            ACTDIGITDESIGN=0;

// ┏ ┓ ┗ ┛ ━ ┃ ┣ ┫ ┳ ┻ ╋ ╻ ╺ ╸ ▅

/*
const string DIGITS[MAXDIGITDESIGNS][MAXDIGITS][DIGITHEIGHT]={
    {
        {
            "┏━┓",
            "┃ ┃",
            "┗━┛"
        },
        {
            "╺┓ ",
            " ┃ ",
            "╺┻╸"
        },
        {
            "┏━┓",
            "┏━┛",
            "┗━┛"
        },
        {
            "┏━┓",
            " ━┫",
            "┗━┛"
        },
        {
            "╻ ╻",
            "┗━┫",
            "  ┻"
        },
        {
            "┏━┓",
            "┗━┓",
            "┗━┛"
        },
        {
            "┏━┓",
            "┣━┓",
            "┗━┛"
        },
        {
            "┏━┓",
            "  ╋",
            "  ┻"
        },
        {
            "┏━┓",
            "┣━┫",
            "┗━┛"
        },
        {
            "┏━┓",
            "┗━┫",
            "┗━┛"
        },
        {
            "   ",
            "   ",
            " ▅ "
        }
    }
};
*/
const string DIGITS[MAXDIGITDESIGNS][MAXDIGITS][DIGITHEIGHT][DIGITWIDTH]={
    {
        {
           { "┏","━","┓"},
           { "┃"," ","┃"},
           { "┗","━","┛"}
        },
        {
           { "╺","┓"," "},
           { " ","┃"," "},
           { "╺","┻","╸"}
        },
        {
           { "╺","━","┓"},
           { "┏","━","┛"},
           { "┗","━","╸"}
        },
        {
           { "╺","━","┓"},
           { " ","━","┫"},
           { "╺","━","┛"}
        },
        {
           { "╻"," ","╻"},
           { "┗","━","┫"},
           { " "," ","┻"}
        },
        {
           { "┏","━","╸"},
           { "┗","━","┓"},
           { "╺","━","┛"}
        },
        {
           { "┏","━","╸"},
           { "┣","━","┓"},
           { "┗","━","┛"}
        },
        {
           { "╺","━","┓"},
           { " "," ","╋"},
           { " "," ","┻"}
        },
        {
           { "┏","━","┓"},
           { "┣","━","┫"},
           { "┗","━","┛"}
        },
        {
           { "┏","━","┓"},
           { "┗","━","┫"},
           { "╺","━","┛"}
        },
        {
           { " "," "," "},
           { " "," "," "},
           { " ","▆"," "}
        }
    }
};
