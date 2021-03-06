#pragma once
#include <vector>
#include <algorithm>
#include <iostream>
#include <windows.h>

const int DX[8] = {0, 0, 1, 1, 1, -1, -1, -1}, DY[8] = {-1, 1, -1, 0, 1, -1, 0, 1};
const int SZ = 512;

int m, n, min, st, num[SZ][SZ];
HWND hwnd;
RECT win;

struct SPosition
{
    int x, y;
    SPosition() : x(0), y(0) {}
    SPosition(int _x, int _y) : x(_x), y(_y) {}

    bool on_board()
    {
        return x >= 0 && x < m && y >= 0 && y < n;
    }

    bool valid()
    {
        if (!on_board())
            return true;
        if (num[x][y] < 0 || num[x][y] > 8)
            return true;
        int open = 0, mine = 0;
        for (int i = 0; i < 8; i++)
            if (SPosition(x + DX[i], y + DY[i]).on_board())
                switch (num[x + DX[i]][y + DY[i]])
                {
                    case -1:
                        open++;
                        break;
                    case 10:
                        mine++;
                        break;
                }
        return (mine <= num[x][y] && mine + open >= num[x][y]);
    }

    bool border_valid()
    {
        if (!on_board())
            return false;
        if (num[x][y] < 0 || num[x][y] > 8)
            return false;
        for (int i = 0; i < 8; i++)
            if (SPosition(x + DX[i], y + DY[i]).on_board() && num[x + DX[i]][y + DY[i]] == -1)
                return true;
        return false;
    }

    SPosition pixel_pos()
    {
        return SPosition(win.left + y * 16 + 15, win.top + x * 16 + 101);
    }
};

inline bool operator<(const SPosition &a, const SPosition &b)
{
    return a.x < b.x || (a.x == b.x && a.y < b.y);
}