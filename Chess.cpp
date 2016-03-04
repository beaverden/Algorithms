bool sameColor(int x1, int y1, int x2, int y2) {
    return ( (x1+y1)%2 == (x2+y2)%2 );
}

bool color(int x, int y) {
    if ( (x+y)% 2 == 0 ) return 0; //Black
    if ( (x+y)% 2 != 0 ) return 1; //White
}

bool rook(int x1, int y1, int x2, int y2) {
    return (x1==x2 || y1 == y2);
}

bool bishop(int x1, int y1, int x2, int y2) {
    return (abs(x1-x2) == abs(y1-y2));
}

bool knight(int x1, int y1, int x2, int y2) {
    return (abs(x1-x2)*abs(y1-y2) == 2);
}

bool king(int x1, int y1, int x2, int y2) {
    return (abs(x1-x2) <= 1 && abs(y1-y2) <= 1);
}

bool pawn(int x1, int y1, int x2, int y2) {
    return (x1 == x2 && (
                 (y1 != 8 && y1>y2 &&
                    (
                     (y1 == 7 && y1-y2<3) ||
                     (y1-y2<2)
                    )
                  ) ||
                 (y1 != 1 && y2>y1 &&
                    (
                     (y1 == 2 && y2-y1<3) ||
                     (y2-y1<2)
                    )
                 )
             )
            );
}

bool queen(int x1, int y1, int x2, int y2) {
    return (x1==x2 || y1 == y2) || (abs(x1-x2) == abs(y1-y2));
}


