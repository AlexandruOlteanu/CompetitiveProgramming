https://github.com/AlexandruOlteanu/CompetitiveProgramming/edit/main/template/FastRead/FastRead.cpp
namespace FastRead {
    const int Dim(10000);
    char buff[Dim];
    int pos, len;
    inline char nc() {
        if (pos == len) {
            pos = 0;
            len = fread(buff, 1, Dim, stdin);
            if (!len) return EOF;
        }
        return buff[pos++];
    }
    template<class T> inline void Read(T& x) {
        char ch;
        int sgn(1);
        while (!isdigit(ch = nc()))
            if (ch == '-')
                sgn = -1;
        x = ch - '0';
        while (isdigit(ch = nc()))
            x = x * 10 + (ch - '0');
        x *= sgn;
    }
}
using namespace FastRead;

// use as Read(x)
