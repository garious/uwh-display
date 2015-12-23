#include "BigNumber.h"

#include <canvas.h>
#include <led-matrix.h>
#include <graphics.h>

#include <cassert>

using namespace uwhtimer;
using namespace rgb_matrix;

#define _ 0

static char Number32x32_0[256] =
{   _,   _,   _,   _, 0xF, 0xF, 0xF, 0xF, 0xF, 0xF, 0xF, 0xF,   _,   _,   _,   _,
    _,   _,   _, 0xF, 0xF, 0xF, 0xF, 0xF, 0xF, 0xF, 0xF, 0xF, 0xF,   _,   _,   _,
    _,   _, 0xF, 0xF, 0xF,   _,   _,   _,   _,   _,   _, 0xF, 0xF, 0xF,   _,   _,
    _,   _, 0xF, 0xF,   _,   _,   _,   _,   _,   _,   _, 0xF, 0xF, 0xF,   _,   _,
    _,   _, 0xF, 0xF,   _,   _,   _,   _,   _,   _, 0xF, 0xF, 0xF, 0xF,   _,   _,
    _,   _, 0xF, 0xF,   _,   _,   _,   _,   _, 0xF, 0xF, 0xF, 0xF, 0xF,   _,   _,
    _,   _, 0xF, 0xF,   _,   _,   _,   _, 0xF, 0xF, 0xF,   _, 0xF, 0xF,   _,   _,
    _,   _, 0xF, 0xF,   _,   _,   _, 0xF, 0xF, 0xF,   _,   _, 0xF, 0xF,   _,   _,
    _,   _, 0xF, 0xF,   _,   _, 0xF, 0xF, 0xF,   _,   _,   _, 0xF, 0xF,   _,   _,
    _,   _, 0xF, 0xF,   _, 0xF, 0xF, 0xF,   _,   _,   _,   _, 0xF, 0xF,   _,   _,
    _,   _, 0xF, 0xF, 0xF, 0xF, 0xF,   _,   _,   _,   _,   _, 0xF, 0xF,   _,   _,
    _,   _, 0xF, 0xF, 0xF, 0xF,   _,   _,   _,   _,   _,   _, 0xF, 0xF,   _,   _,
    _,   _, 0xF, 0xF, 0xF,   _,   _,   _,   _,   _,   _,   _, 0xF, 0xF,   _,   _,
    _,   _, 0xF, 0xF, 0xF,   _,   _,   _,   _,   _,   _, 0xF, 0xF, 0xF,   _,   _,
    _,   _,   _, 0xF, 0xF, 0xF, 0xF, 0xF, 0xF, 0xF, 0xF, 0xF, 0xF,   _,   _,   _,
    _,   _,   _,   _, 0xF, 0xF, 0xF, 0xF, 0xF, 0xF, 0xF, 0xF,   _,   _,   _,   _ };

static char Number32x32_1[256] =
{   _,   _,   _,   _,   _,   _,   _, 0xF, 0xF,   _,   _,   _,   _,   _,   _,   _,
    _,   _,   _,   _,   _,   _, 0xF, 0xF, 0xF,   _,   _,   _,   _,   _,   _,   _,
    _,   _,   _,   _,   _, 0xF, 0xF, 0xF, 0xF,   _,   _,   _,   _,   _,   _,   _,
    _,   _,   _,   _, 0xF, 0xF, 0xF, 0xF, 0xF,   _,   _,   _,   _,   _,   _,   _,
    _,   _,   _, 0xF, 0xF, 0xF,   _, 0xF, 0xF,   _,   _,   _,   _,   _,   _,   _,
    _,   _,   _, 0xF, 0xF,   _,   _, 0xF, 0xF,   _,   _,   _,   _,   _,   _,   _,
    _,   _,   _,   _,   _,   _,   _, 0xF, 0xF,   _,   _,   _,   _,   _,   _,   _,
    _,   _,   _,   _,   _,   _,   _, 0xF, 0xF,   _,   _,   _,   _,   _,   _,   _,
    _,   _,   _,   _,   _,   _,   _, 0xF, 0xF,   _,   _,   _,   _,   _,   _,   _,
    _,   _,   _,   _,   _,   _,   _, 0xF, 0xF,   _,   _,   _,   _,   _,   _,   _,
    _,   _,   _,   _,   _,   _,   _, 0xF, 0xF,   _,   _,   _,   _,   _,   _,   _,
    _,   _,   _,   _,   _,   _,   _, 0xF, 0xF,   _,   _,   _,   _,   _,   _,   _,
    _,   _,   _,   _,   _,   _,   _, 0xF, 0xF,   _,   _,   _,   _,   _,   _,   _,
    _,   _,   _,   _,   _,   _,   _, 0xF, 0xF,   _,   _,   _,   _,   _,   _,   _,
    _,   _,   _, 0xF, 0xF, 0xF, 0xF, 0xF, 0xF, 0xF, 0xF, 0xF, 0xF,   _,   _,   _,
    _,   _,   _, 0xF, 0xF, 0xF, 0xF, 0xF, 0xF, 0xF, 0xF, 0xF, 0xF,   _,   _,   _ };

static char Number32x32_2[256] =
{   _,   _,   _,   _,   _, 0xF, 0xF, 0xF, 0xF, 0xF, 0xF, 0xF,   _,   _,   _,   _,
    _,   _,   _,   _, 0xF, 0xF, 0xF, 0xF, 0xF, 0xF, 0xF, 0xF, 0xF,   _,   _,   _,
    _,   _,   _, 0xF, 0xF, 0xF,   _,   _,   _,   _,   _, 0xF, 0xF,   _,   _,   _,
    _,   _,   _, 0xF, 0xF,   _,   _,   _,   _,   _,   _, 0xF, 0xF,   _,   _,   _,
    _,   _,   _,   _,   _,   _,   _,   _,   _,   _,   _, 0xF, 0xF,   _,   _,   _,
    _,   _,   _,   _,   _,   _,   _,   _,   _,   _,   _, 0xF, 0xF,   _,   _,   _,
    _,   _,   _,   _,   _,   _,   _,   _,   _,   _, 0xF, 0xF, 0xF,   _,   _,   _,
    _,   _,   _,   _,   _,   _,   _,   _,   _, 0xF, 0xF, 0xF,   _,   _,   _,   _,
    _,   _,   _,   _,   _,   _,   _,   _, 0xF, 0xF, 0xF,   _,   _,   _,   _,   _,
    _,   _,   _,   _,   _,   _,   _, 0xF, 0xF, 0xF,   _,   _,   _,   _,   _,   _,
    _,   _,   _,   _,   _,   _, 0xF, 0xF, 0xF,   _,   _,   _,   _,   _,   _,   _,
    _,   _,   _,   _,   _, 0xF, 0xF, 0xF,   _,   _,   _,   _,   _,   _,   _,   _,
    _,   _,   _,   _, 0xF, 0xF, 0xF,   _,   _,   _,   _,   _,   _,   _,   _,   _,
    _,   _,   _, 0xF, 0xF, 0xF,   _,   _,   _,   _,   _,   _,   _,   _,   _,   _,
    _,   _,   _, 0xF, 0xF, 0xF, 0xF, 0xF, 0xF, 0xF, 0xF, 0xF, 0xF,   _,   _,   _,
    _,   _,   _, 0xF, 0xF, 0xF, 0xF, 0xF, 0xF, 0xF, 0xF, 0xF, 0xF,   _,   _,   _ };

static char Number32x32_3[256] =
{   _,   _,   _,   _, 0xF, 0xF, 0xF, 0xF, 0xF, 0xF, 0xF, 0xF,   _,   _,   _,   _,
    _,   _,   _, 0xF, 0xF, 0xF, 0xF, 0xF, 0xF, 0xF, 0xF, 0xF, 0xF,   _,   _,   _,
    _,   _,   _, 0xF, 0xF,   _,   _,   _,   _,   _,   _, 0xF, 0xF,   _,   _,   _,
    _,   _,   _,   _,   _,   _,   _,   _,   _,   _,   _, 0xF, 0xF,   _,   _,   _,
    _,   _,   _,   _,   _,   _,   _,   _,   _,   _,   _, 0xF, 0xF,   _,   _,   _,
    _,   _,   _,   _,   _,   _,   _,   _,   _,   _,   _, 0xF, 0xF,   _,   _,   _,
    _,   _,   _,   _,   _,   _,   _,   _,   _,   _,   _, 0xF, 0xF,   _,   _,   _,
    _,   _,   _,   _,   _,   _, 0xF, 0xF, 0xF, 0xF, 0xF, 0xF,   _,   _,   _,   _,
    _,   _,   _,   _,   _,   _, 0xF, 0xF, 0xF, 0xF, 0xF, 0xF,   _,   _,   _,   _,
    _,   _,   _,   _,   _,   _,   _,   _,   _,   _,   _, 0xF, 0xF,   _,   _,   _,
    _,   _,   _,   _,   _,   _,   _,   _,   _,   _,   _, 0xF, 0xF,   _,   _,   _,
    _,   _,   _,   _,   _,   _,   _,   _,   _,   _,   _, 0xF, 0xF,   _,   _,   _,
    _,   _,   _,   _,   _,   _,   _,   _,   _,   _,   _, 0xF, 0xF,   _,   _,   _,
    _,   _,   _, 0xF, 0xF,   _,   _,   _,   _,   _,   _, 0xF, 0xF,   _,   _,   _,
    _,   _,   _, 0xF, 0xF, 0xF, 0xF, 0xF, 0xF, 0xF, 0xF, 0xF, 0xF,   _,   _,   _,
    _,   _,   _,   _, 0xF, 0xF, 0xF, 0xF, 0xF, 0xF, 0xF, 0xF,   _,   _,   _,   _ };

static char Number32x32_4[256] =
{   _,   _,   _,   _,   _,   _,   _,   _,   _,   _, 0xF, 0xF,   _,   _,   _,   _,
    _,   _,   _,   _,   _,   _,   _,   _,   _, 0xF, 0xF, 0xF,   _,   _,   _,   _,
    _,   _,   _,   _,   _,   _,   _,   _, 0xF, 0xF, 0xF, 0xF,   _,   _,   _,   _,
    _,   _,   _,   _,   _,   _,   _, 0xF, 0xF,   _, 0xF, 0xF,   _,   _,   _,   _,
    _,   _,   _,   _,   _,   _, 0xF, 0xF,   _,   _, 0xF, 0xF,   _,   _,   _,   _,
    _,   _,   _,   _,   _, 0xF, 0xF,   _,   _,   _, 0xF, 0xF,   _,   _,   _,   _,
    _,   _,   _,   _, 0xF, 0xF,   _,   _,   _,   _, 0xF, 0xF,   _,   _,   _,   _,
    _,   _,   _, 0xF, 0xF,   _,   _,   _,   _,   _, 0xF, 0xF,   _,   _,   _,   _,
    _,   _,   _, 0xF, 0xF, 0xF, 0xF, 0xF, 0xF, 0xF, 0xF, 0xF, 0xF,   _,   _,   _,
    _,   _,   _, 0xF, 0xF, 0xF, 0xF, 0xF, 0xF, 0xF, 0xF, 0xF, 0xF,   _,   _,   _,
    _,   _,   _,   _,   _,   _,   _,   _,   _,   _, 0xF, 0xF,   _,   _,   _,   _,
    _,   _,   _,   _,   _,   _,   _,   _,   _,   _, 0xF, 0xF,   _,   _,   _,   _,
    _,   _,   _,   _,   _,   _,   _,   _,   _,   _, 0xF, 0xF,   _,   _,   _,   _,
    _,   _,   _,   _,   _,   _,   _,   _,   _,   _, 0xF, 0xF,   _,   _,   _,   _,
    _,   _,   _,   _,   _,   _,   _,   _,   _,   _, 0xF, 0xF,   _,   _,   _,   _,
    _,   _,   _,   _,   _,   _,   _,   _,   _,   _, 0xF, 0xF,   _,   _,   _,   _ };

static char Number32x32_5[256] =
{   _,   _,   _, 0xF, 0xF, 0xF, 0xF, 0xF, 0xF, 0xF, 0xF, 0xF, 0xF,   _,   _,   _,
    _,   _,   _, 0xF, 0xF, 0xF, 0xF, 0xF, 0xF, 0xF, 0xF, 0xF, 0xF,   _,   _,   _,
    _,   _,   _, 0xF, 0xF,   _,   _,   _,   _,   _,   _,   _,   _,   _,   _,   _,
    _,   _,   _, 0xF, 0xF,   _,   _,   _,   _,   _,   _,   _,   _,   _,   _,   _,
    _,   _,   _, 0xF, 0xF,   _,   _,   _,   _,   _,   _,   _,   _,   _,   _,   _,
    _,   _,   _, 0xF, 0xF,   _,   _,   _,   _,   _,   _,   _,   _,   _,   _,   _,
    _,   _,   _, 0xF, 0xF,   _,   _,   _,   _,   _,   _,   _,   _,   _,   _,   _,
    _,   _,   _, 0xF, 0xF, 0xF, 0xF, 0xF, 0xF, 0xF, 0xF,   _,   _,   _,   _,   _,
    _,   _,   _, 0xF, 0xF, 0xF, 0xF, 0xF, 0xF, 0xF, 0xF, 0xF,   _,   _,   _,   _,
    _,   _,   _,   _,   _,   _,   _,   _,   _,   _, 0xF, 0xF, 0xF,   _,   _,   _,
    _,   _,   _,   _,   _,   _,   _,   _,   _,   _,   _, 0xF, 0xF,   _,   _,   _,
    _,   _,   _,   _,   _,   _,   _,   _,   _,   _,   _, 0xF, 0xF,   _,   _,   _,
    _,   _,   _,   _,   _,   _,   _,   _,   _,   _,   _, 0xF, 0xF,   _,   _,   _,
    _,   _,   _,   _,   _,   _,   _,   _,   _,   _, 0xF, 0xF, 0xF,   _,   _,   _,
    _,   _,   _, 0xF, 0xF, 0xF, 0xF, 0xF, 0xF, 0xF, 0xF, 0xF,   _,   _,   _,   _,
    _,   _,   _, 0xF, 0xF, 0xF, 0xF, 0xF, 0xF, 0xF, 0xF,   _,   _,   _,   _,   _ };

static char Number32x32_6[256] =
{   _,   _,   _,   _,   _,   _, 0xF, 0xF,   _,   _,   _,   _,   _,   _,   _,   _,
    _,   _,   _,   _,   _, 0xF, 0xF, 0xF,   _,   _,   _,   _,   _,   _,   _,   _,
    _,   _,   _,   _, 0xF, 0xF,   _,   _,   _,   _,   _,   _,   _,   _,   _,   _,
    _,   _,   _, 0xF, 0xF,   _,   _,   _,   _,   _,   _,   _,   _,   _,   _,   _,
    _,   _,   _, 0xF, 0xF,   _,   _,   _,   _,   _,   _,   _,   _,   _,   _,   _,
    _,   _,   _, 0xF, 0xF,   _,   _,   _,   _,   _,   _,   _,   _,   _,   _,   _,
    _,   _,   _, 0xF, 0xF,   _,   _,   _,   _,   _,   _,   _,   _,   _,   _,   _,
    _,   _,   _, 0xF, 0xF, 0xF, 0xF, 0xF, 0xF, 0xF, 0xF,   _,   _,   _,   _,   _,
    _,   _,   _, 0xF, 0xF, 0xF, 0xF, 0xF, 0xF, 0xF, 0xF, 0xF,   _,   _,   _,   _,
    _,   _,   _, 0xF, 0xF,   _,   _,   _,   _,   _, 0xF, 0xF, 0xF,   _,   _,   _,
    _,   _,   _, 0xF, 0xF,   _,   _,   _,   _,   _,   _, 0xF, 0xF,   _,   _,   _,
    _,   _,   _, 0xF, 0xF,   _,   _,   _,   _,   _,   _, 0xF, 0xF,   _,   _,   _,
    _,   _,   _, 0xF, 0xF,   _,   _,   _,   _,   _,   _, 0xF, 0xF,   _,   _,   _,
    _,   _,   _, 0xF, 0xF, 0xF,   _,   _,   _,   _, 0xF, 0xF, 0xF,   _,   _,   _,
    _,   _,   _,   _, 0xF, 0xF, 0xF, 0xF, 0xF, 0xF, 0xF, 0xF,   _,   _,   _,   _,
    _,   _,   _,   _,   _, 0xF, 0xF, 0xF, 0xF, 0xF, 0xF,   _,   _,   _,   _,   _ };

static char Number32x32_7[256] =
{   _,   _,   _,   _, 0xF, 0xF, 0xF, 0xF, 0xF, 0xF, 0xF, 0xF,   _,   _,   _,   _,
    _,   _,   _, 0xF, 0xF, 0xF, 0xF, 0xF, 0xF, 0xF, 0xF, 0xF, 0xF,   _,   _,   _,
    _,   _,   _, 0xF, 0xF,   _,   _,   _,   _,   _,   _, 0xF, 0xF,   _,   _,   _,
    _,   _,   _,   _,   _,   _,   _,   _,   _,   _,   _, 0xF, 0xF,   _,   _,   _,
    _,   _,   _,   _,   _,   _,   _,   _,   _,   _,   _, 0xF, 0xF,   _,   _,   _,
    _,   _,   _,   _,   _,   _,   _,   _,   _,   _,   _, 0xF, 0xF,   _,   _,   _,
    _,   _,   _,   _,   _,   _,   _,   _,   _,   _, 0xF, 0xF, 0xF,   _,   _,   _,
    _,   _,   _,   _,   _,   _,   _,   _,   _, 0xF, 0xF, 0xF,   _,   _,   _,   _,
    _,   _,   _,   _,   _,   _,   _,   _, 0xF, 0xF, 0xF,   _,   _,   _,   _,   _,
    _,   _,   _,   _,   _,   _,   _, 0xF, 0xF, 0xF,   _,   _,   _,   _,   _,   _,
    _,   _,   _,   _,   _,   _,   _, 0xF, 0xF,   _,   _,   _,   _,   _,   _,   _,
    _,   _,   _,   _,   _,   _,   _, 0xF, 0xF,   _,   _,   _,   _,   _,   _,   _,
    _,   _,   _,   _,   _,   _,   _, 0xF, 0xF,   _,   _,   _,   _,   _,   _,   _,
    _,   _,   _,   _,   _,   _,   _, 0xF, 0xF,   _,   _,   _,   _,   _,   _,   _,
    _,   _,   _,   _,   _,   _,   _, 0xF, 0xF,   _,   _,   _,   _,   _,   _,   _,
    _,   _,   _,   _,   _,   _,   _, 0xF, 0xF,   _,   _,   _,   _,   _,   _,   _ };

static char Number32x32_8[256] =
{   _,   _,   _,   _,   _, 0xF, 0xF, 0xF, 0xF, 0xF, 0xF,   _,   _,   _,   _,   _,
    _,   _,   _,   _, 0xF, 0xF, 0xF, 0xF, 0xF, 0xF, 0xF, 0xF,   _,   _,   _,   _,
    _,   _,   _, 0xF, 0xF, 0xF,   _,   _,   _,   _, 0xF, 0xF, 0xF,   _,   _,   _,
    _,   _,   _, 0xF, 0xF,   _,   _,   _,   _,   _,   _, 0xF, 0xF,   _,   _,   _,
    _,   _,   _, 0xF, 0xF,   _,   _,   _,   _,   _,   _, 0xF, 0xF,   _,   _,   _,
    _,   _,   _, 0xF, 0xF,   _,   _,   _,   _,   _,   _, 0xF, 0xF,   _,   _,   _,
    _,   _,   _, 0xF, 0xF, 0xF,   _,   _,   _,   _, 0xF, 0xF, 0xF,   _,   _,   _,
    _,   _,   _,   _, 0xF, 0xF, 0xF, 0xF, 0xF, 0xF, 0xF, 0xF,   _,   _,   _,   _,
    _,   _,   _,   _, 0xF, 0xF, 0xF, 0xF, 0xF, 0xF, 0xF, 0xF,   _,   _,   _,   _,
    _,   _,   _, 0xF, 0xF, 0xF,   _,   _,   _,   _, 0xF, 0xF, 0xF,   _,   _,   _,
    _,   _,   _, 0xF, 0xF,   _,   _,   _,   _,   _,   _, 0xF, 0xF,   _,   _,   _,
    _,   _,   _, 0xF, 0xF,   _,   _,   _,   _,   _,   _, 0xF, 0xF,   _,   _,   _,
    _,   _,   _, 0xF, 0xF,   _,   _,   _,   _,   _,   _, 0xF, 0xF,   _,   _,   _,
    _,   _,   _, 0xF, 0xF, 0xF,   _,   _,   _,   _, 0xF, 0xF, 0xF,   _,   _,   _,
    _,   _,   _,   _, 0xF, 0xF, 0xF, 0xF, 0xF, 0xF, 0xF, 0xF,   _,   _,   _,   _,
    _,   _,   _,   _,   _, 0xF, 0xF, 0xF, 0xF, 0xF, 0xF,   _,   _,   _,   _,   _ };

static char Number32x32_9[256] =
{   _,   _,   _,   _, 0xF, 0xF, 0xF, 0xF, 0xF, 0xF, 0xF, 0xF,   _,   _,   _,   _,
    _,   _,   _, 0xF, 0xF, 0xF, 0xF, 0xF, 0xF, 0xF, 0xF, 0xF, 0xF,   _,   _,   _,
    _,   _,   _, 0xF, 0xF,   _,   _,   _,   _,   _,   _, 0xF, 0xF,   _,   _,   _,
    _,   _,   _, 0xF, 0xF,   _,   _,   _,   _,   _,   _, 0xF, 0xF,   _,   _,   _,
    _,   _,   _, 0xF, 0xF,   _,   _,   _,   _,   _,   _, 0xF, 0xF,   _,   _,   _,
    _,   _,   _, 0xF, 0xF,   _,   _,   _,   _,   _,   _, 0xF, 0xF,   _,   _,   _,
    _,   _,   _, 0xF, 0xF,   _,   _,   _,   _,   _,   _, 0xF, 0xF,   _,   _,   _,
    _,   _,   _, 0xF, 0xF, 0xF, 0xF, 0xF, 0xF, 0xF, 0xF, 0xF, 0xF,   _,   _,   _,
    _,   _,   _,   _, 0xF, 0xF, 0xF, 0xF, 0xF, 0xF, 0xF, 0xF, 0xF,   _,   _,   _,
    _,   _,   _,   _,   _,   _,   _,   _,   _,   _,   _, 0xF, 0xF,   _,   _,   _,
    _,   _,   _,   _,   _,   _,   _,   _,   _,   _,   _, 0xF, 0xF,   _,   _,   _,
    _,   _,   _,   _,   _,   _,   _,   _,   _,   _,   _, 0xF, 0xF,   _,   _,   _,
    _,   _,   _,   _,   _,   _,   _,   _,   _,   _,   _, 0xF, 0xF,   _,   _,   _,
    _,   _,   _,   _,   _,   _,   _,   _,   _,   _,   _, 0xF, 0xF,   _,   _,   _,
    _,   _,   _,   _,   _,   _,   _,   _,   _,   _,   _, 0xF, 0xF,   _,   _,   _,
    _,   _,   _,   _,   _,   _,   _,   _,   _,   _,   _, 0xF, 0xF,   _,   _,   _ };

static char Number32x32_empty[256] =
{   _,   _,   _,   _,   _,   _,   _,   _,   _,   _,   _,   _,   _,   _,   _,   _,
    _,   _,   _,   _,   _,   _,   _,   _,   _,   _,   _,   _,   _,   _,   _,   _,
    _,   _,   _,   _,   _,   _,   _,   _,   _,   _,   _,   _,   _,   _,   _,   _,
    _,   _,   _,   _,   _,   _,   _,   _,   _,   _,   _,   _,   _,   _,   _,   _,
    _,   _,   _,   _,   _,   _,   _,   _,   _,   _,   _,   _,   _,   _,   _,   _,
    _,   _,   _,   _,   _,   _,   _,   _,   _,   _,   _,   _,   _,   _,   _,   _,
    _,   _,   _,   _,   _,   _,   _,   _,   _,   _,   _,   _,   _,   _,   _,   _,
    _,   _,   _,   _,   _,   _,   _,   _,   _,   _,   _,   _,   _,   _,   _,   _,
    _,   _,   _,   _,   _,   _,   _,   _,   _,   _,   _,   _,   _,   _,   _,   _,
    _,   _,   _,   _,   _,   _,   _,   _,   _,   _,   _,   _,   _,   _,   _,   _,
    _,   _,   _,   _,   _,   _,   _,   _,   _,   _,   _,   _,   _,   _,   _,   _,
    _,   _,   _,   _,   _,   _,   _,   _,   _,   _,   _,   _,   _,   _,   _,   _,
    _,   _,   _,   _,   _,   _,   _,   _,   _,   _,   _,   _,   _,   _,   _,   _,
    _,   _,   _,   _,   _,   _,   _,   _,   _,   _,   _,   _,   _,   _,   _,   _,
    _,   _,   _,   _,   _,   _,   _,   _,   _,   _,   _,   _,   _,   _,   _,   _,
    _,   _,   _,   _,   _,   _,   _,   _,   _,   _,   _,   _,   _,   _,   _,   _ };

static char *Numbers32x32[] = {
   Number32x32_0,
   Number32x32_1,
   Number32x32_2,
   Number32x32_3,
   Number32x32_4,
   Number32x32_5,
   Number32x32_6,
   Number32x32_7,
   Number32x32_8,
   Number32x32_9,
   Number32x32_empty,
};

static char Number16x32_0[128] =
{   _,   _, 0xF, 0xF, 0xF, 0xF,   _,   _,
    _, 0xF, 0xF, 0xF, 0xF, 0xF, 0xF,   _,
    _, 0xF, 0xF,   _,   _, 0xF, 0xF,   _,
    _, 0xF, 0xF,   _,   _, 0xF, 0xF,   _,
    _, 0xF, 0xF,   _,   _, 0xF, 0xF,   _,
    _, 0xF, 0xF,   _,   _, 0xF, 0xF,   _,
    _, 0xF, 0xF,   _, 0xF, 0xF, 0xF,   _,
    _, 0xF, 0xF, 0xF, 0xF, 0xF, 0xF,   _,
    _, 0xF, 0xF, 0xF, 0xF, 0xF, 0xF,   _,
    _, 0xF, 0xF, 0xF,   _, 0xF, 0xF,   _,
    _, 0xF, 0xF,   _,   _, 0xF, 0xF,   _,
    _, 0xF, 0xF,   _,   _, 0xF, 0xF,   _,
    _, 0xF, 0xF,   _,   _, 0xF, 0xF,   _,
    _, 0xF, 0xF,   _,   _, 0xF, 0xF,   _,
    _,   _, 0xF, 0xF, 0xF, 0xF, 0xF,   _,
    _,   _, 0xF, 0xF, 0xF, 0xF,   _,   _ };

static char Number16x32_1[128] =
{   _,   _,   _, 0xF, 0xF,   _,   _,   _,
    _,   _, 0xF, 0xF, 0xF,   _,   _,   _,
    _, 0xF, 0xF, 0xF, 0xF,   _,   _,   _,
    _, 0xF,   _, 0xF, 0xF,   _,   _,   _,
    _,   _,   _, 0xF, 0xF,   _,   _,   _,
    _,   _,   _, 0xF, 0xF,   _,   _,   _,
    _,   _,   _, 0xF, 0xF,   _,   _,   _,
    _,   _,   _, 0xF, 0xF,   _,   _,   _,
    _,   _,   _, 0xF, 0xF,   _,   _,   _,
    _,   _,   _, 0xF, 0xF,   _,   _,   _,
    _,   _,   _, 0xF, 0xF,   _,   _,   _,
    _,   _,   _, 0xF, 0xF,   _,   _,   _,
    _,   _,   _, 0xF, 0xF,   _,   _,   _,
    _,   _,   _, 0xF, 0xF,   _,   _,   _,
    _, 0xF, 0xF, 0xF, 0xF, 0xF, 0xF,   _,
    _, 0xF, 0xF, 0xF, 0xF, 0xF, 0xF,   _, };

static char Number16x32_2[128] =
{   _,   _, 0xF, 0xF, 0xF, 0xF,   _,   _,
    _, 0xF, 0xF, 0xF, 0xF, 0xF, 0xF,   _,
    _, 0xF, 0xF,   _,   _, 0xF, 0xF,   _,
    _,   _,   _,   _,   _, 0xF, 0xF,   _,
    _,   _,   _,   _,   _, 0xF, 0xF,   _,
    _,   _,   _,   _,   _, 0xF, 0xF,   _,
    _,   _,   _,   _,   _, 0xF, 0xF,   _,
    _,   _,   _,   _, 0xF, 0xF, 0xF,   _,
    _,   _,   _, 0xF, 0xF, 0xF,   _,   _,
    _,   _, 0xF, 0xF, 0xF,   _,   _,   _,
    _, 0xF, 0xF, 0xF,   _,   _,   _,   _,
    _, 0xF, 0xF,   _,   _,   _,   _,   _,
    _, 0xF, 0xF,   _,   _,   _,   _,   _,
    _, 0xF, 0xF,   _,   _,   _,   _,   _,
    _, 0xF, 0xF, 0xF, 0xF, 0xF, 0xF,   _,
    _, 0xF, 0xF, 0xF, 0xF, 0xF, 0xF,   _ };

static char Number16x32_3[128] =
{   _,   _, 0xF, 0xF, 0xF, 0xF,   _,   _,
    _, 0xF, 0xF, 0xF, 0xF, 0xF, 0xF,   _,
    _, 0xF, 0xF,   _,   _, 0xF, 0xF,   _,
    _,   _,   _,   _,   _, 0xF, 0xF,   _,
    _,   _,   _,   _,   _, 0xF, 0xF,   _,
    _,   _,   _,   _,   _, 0xF, 0xF,   _,
    _,   _,   _,   _,   _, 0xF, 0xF,   _,
    _,   _,   _, 0xF, 0xF, 0xF,   _,   _,
    _,   _,   _, 0xF, 0xF, 0xF,   _,   _,
    _,   _,   _,   _,   _, 0xF, 0xF,   _,
    _,   _,   _,   _,   _, 0xF, 0xF,   _,
    _,   _,   _,   _,   _, 0xF, 0xF,   _,
    _,   _,   _,   _,   _, 0xF, 0xF,   _,
    _, 0xF, 0xF,   _,   _, 0xF, 0xF,   _,
    _, 0xF, 0xF, 0xF, 0xF, 0xF, 0xF,   _,
    _,   _, 0xF, 0xF, 0xF, 0xF,   _,   _ };

static char Number16x32_4[128] =
{   _,   _,   _,   _,   _, 0xF, 0xF,   _,
    _,   _,   _,   _, 0xF, 0xF, 0xF,   _,
    _,   _,   _, 0xF, 0xF, 0xF, 0xF,   _,
    _,   _, 0xF, 0xF, 0xF, 0xF, 0xF,   _,
    _, 0xF, 0xF, 0xF,   _, 0xF, 0xF,   _,
    _, 0xF, 0xF,   _,   _, 0xF, 0xF,   _,
    _, 0xF, 0xF,   _,   _, 0xF, 0xF,   _,
    _, 0xF, 0xF, 0xF, 0xF, 0xF, 0xF,   _,
    _, 0xF, 0xF, 0xF, 0xF, 0xF, 0xF,   _,
    _,   _,   _,   _,   _, 0xF, 0xF,   _,
    _,   _,   _,   _,   _, 0xF, 0xF,   _,
    _,   _,   _,   _,   _, 0xF, 0xF,   _,
    _,   _,   _,   _,   _, 0xF, 0xF,   _,
    _,   _,   _,   _,   _, 0xF, 0xF,   _,
    _,   _,   _,   _,   _, 0xF, 0xF,   _,
    _,   _,   _,   _,   _, 0xF, 0xF,   _ };

static char Number16x32_5[128] =
{   _, 0xF, 0xF, 0xF, 0xF, 0xF, 0xF,   _,
    _, 0xF, 0xF, 0xF, 0xF, 0xF, 0xF,   _,
    _, 0xF, 0xF,   _,   _,   _,   _,   _,
    _, 0xF, 0xF,   _,   _,   _,   _,   _,
    _, 0xF, 0xF,   _,   _,   _,   _,   _,
    _, 0xF, 0xF,   _,   _,   _,   _,   _,
    _, 0xF, 0xF,   _,   _,   _,   _,   _,
    _, 0xF, 0xF, 0xF, 0xF, 0xF,   _,   _,
    _, 0xF, 0xF, 0xF, 0xF, 0xF, 0xF,   _,
    _,   _,   _,   _,   _, 0xF, 0xF,   _,
    _,   _,   _,   _,   _, 0xF, 0xF,   _,
    _,   _,   _,   _,   _, 0xF, 0xF,   _,
    _,   _,   _,   _,   _, 0xF, 0xF,   _,
    _,   _,   _,   _,   _, 0xF, 0xF,   _,
    _, 0xF, 0xF, 0xF, 0xF, 0xF, 0xF,   _,
    _, 0xF, 0xF, 0xF, 0xF, 0xF,   _,   _ };

static char Number16x32_6[128] =
{   _,   _, 0xF, 0xF, 0xF, 0xF,   _,   _,
    _, 0xF, 0xF, 0xF, 0xF, 0xF,   _,   _,
    _, 0xF, 0xF,   _,   _,   _,   _,   _,
    _, 0xF, 0xF,   _,   _,   _,   _,   _,
    _, 0xF, 0xF,   _,   _,   _,   _,   _,
    _, 0xF, 0xF,   _,   _,   _,   _,   _,
    _, 0xF, 0xF,   _,   _,   _,   _,   _,
    _, 0xF, 0xF, 0xF, 0xF, 0xF,   _,   _,
    _, 0xF, 0xF, 0xF, 0xF, 0xF, 0xF,   _,
    _, 0xF, 0xF,   _,   _, 0xF, 0xF,   _,
    _, 0xF, 0xF,   _,   _, 0xF, 0xF,   _,
    _, 0xF, 0xF,   _,   _, 0xF, 0xF,   _,
    _, 0xF, 0xF,   _,   _, 0xF, 0xF,   _,
    _, 0xF, 0xF,   _,   _, 0xF, 0xF,   _,
    _, 0xF, 0xF, 0xF, 0xF, 0xF, 0xF,   _,
    _,   _, 0xF, 0xF, 0xF, 0xF,   _,   _ };

static char Number16x32_7[128] =
{   _,   _, 0xF, 0xF, 0xF, 0xF,   _,   _,
    _, 0xF, 0xF, 0xF, 0xF, 0xF, 0xF,   _,
    _, 0xF, 0xF,   _,   _, 0xF, 0xF,   _,
    _,   _,   _,   _,   _, 0xF, 0xF,   _,
    _,   _,   _,   _,   _, 0xF, 0xF,   _,
    _,   _,   _,   _,   _, 0xF, 0xF,   _,
    _,   _,   _,   _,   _, 0xF, 0xF,   _,
    _,   _,   _,   _, 0xF, 0xF,   _,   _,
    _,   _,   _, 0xF, 0xF,   _,   _,   _,
    _,   _,   _, 0xF, 0xF,   _,   _,   _,
    _,   _,   _, 0xF, 0xF,   _,   _,   _,
    _,   _,   _, 0xF, 0xF,   _,   _,   _,
    _,   _,   _, 0xF, 0xF,   _,   _,   _,
    _,   _,   _, 0xF, 0xF,   _,   _,   _,
    _,   _,   _, 0xF, 0xF,   _,   _,   _,
    _,   _,   _, 0xF, 0xF,   _,   _,   _ };

static char Number16x32_8[128] =
{   _,   _, 0xF, 0xF, 0xF, 0xF,   _,   _,
    _, 0xF, 0xF, 0xF, 0xF, 0xF, 0xF,   _,
    _, 0xF, 0xF,   _,   _, 0xF, 0xF,   _,
    _, 0xF, 0xF,   _,   _, 0xF, 0xF,   _,
    _, 0xF, 0xF,   _,   _, 0xF, 0xF,   _,
    _, 0xF, 0xF,   _,   _, 0xF, 0xF,   _,
    _, 0xF, 0xF,   _,   _, 0xF, 0xF,   _,
    _,   _, 0xF, 0xF, 0xF, 0xF,   _,   _,
    _,   _, 0xF, 0xF, 0xF, 0xF,   _,   _,
    _, 0xF, 0xF,   _,   _, 0xF, 0xF,   _,
    _, 0xF, 0xF,   _,   _, 0xF, 0xF,   _,
    _, 0xF, 0xF,   _,   _, 0xF, 0xF,   _,
    _, 0xF, 0xF,   _,   _, 0xF, 0xF,   _,
    _, 0xF, 0xF,   _,   _, 0xF, 0xF,   _,
    _, 0xF, 0xF, 0xF, 0xF, 0xF, 0xF,   _,
    _,   _, 0xF, 0xF, 0xF, 0xF,   _,   _ };

static char Number16x32_9[128] =
{   _,   _, 0xF, 0xF, 0xF, 0xF,   _,   _,
    _, 0xF, 0xF, 0xF, 0xF, 0xF, 0xF,   _,
    _, 0xF, 0xF,   _,   _, 0xF, 0xF,   _,
    _, 0xF, 0xF,   _,   _, 0xF, 0xF,   _,
    _, 0xF, 0xF,   _,   _, 0xF, 0xF,   _,
    _, 0xF, 0xF,   _,   _, 0xF, 0xF,   _,
    _, 0xF, 0xF,   _,   _, 0xF, 0xF,   _,
    _,   _, 0xF, 0xF, 0xF, 0xF, 0xF,   _,
    _,   _, 0xF, 0xF, 0xF, 0xF, 0xF,   _,
    _,   _,   _,   _,   _, 0xF, 0xF,   _,
    _,   _,   _,   _,   _, 0xF, 0xF,   _,
    _,   _,   _,   _,   _, 0xF, 0xF,   _,
    _,   _,   _,   _,   _, 0xF, 0xF,   _,
    _,   _,   _,   _,   _, 0xF, 0xF,   _,
    _,   _,   _,   _,   _, 0xF, 0xF,   _,
    _,   _,   _,   _,   _, 0xF, 0xF,   _ };

static char Number16x32_empty[128] =
{   _,   _,   _,   _,   _,   _,   _,   _,
    _,   _,   _,   _,   _,   _,   _,   _,
    _,   _,   _,   _,   _,   _,   _,   _,
    _,   _,   _,   _,   _,   _,   _,   _,
    _,   _,   _,   _,   _,   _,   _,   _,
    _,   _,   _,   _,   _,   _,   _,   _,
    _,   _,   _,   _,   _,   _,   _,   _,
    _,   _,   _,   _,   _,   _,   _,   _,
    _,   _,   _,   _,   _,   _,   _,   _,
    _,   _,   _,   _,   _,   _,   _,   _,
    _,   _,   _,   _,   _,   _,   _,   _,
    _,   _,   _,   _,   _,   _,   _,   _,
    _,   _,   _,   _,   _,   _,   _,   _,
    _,   _,   _,   _,   _,   _,   _,   _,
    _,   _,   _,   _,   _,   _,   _,   _,
    _,   _,   _,   _,   _,   _,   _,   _ };

static char *Numbers16x32[] = {
  Number16x32_0,
  Number16x32_1,
  Number16x32_2,
  Number16x32_3,
  Number16x32_4,
  Number16x32_5,
  Number16x32_6,
  Number16x32_7,
  Number16x32_8,
  Number16x32_9,
  Number16x32_empty
};

#undef _

void BigNumber::Render(Canvas *Canvas,
                       unsigned Display,
                       unsigned Value,
                       const Color &FG,
                       const Color *BG) {
  assert(Value < 100 && "Value out of range");

  if (Value < 10)
    RenderSingle(Canvas, Display, Value, FG, BG);
  else if (Value < 100)
    RenderDouble(Canvas, Display, Value, FG, BG);
}


void BigNumber::RenderSingle(Canvas *Canvas,
                             unsigned Display,
                             unsigned Value,
                             const Color &FG,
                             const Color *BG) {
  assert(Value < 10 && "Value out of range");
  unsigned xoffs = Display * 32;
  for (unsigned y = 0; y < 16; y++) {
    for (unsigned x = 0; x < 16; x++) {
      if (Numbers32x32[Value][x + y * 16] & 1) {
        Canvas->SetPixel(xoffs + x * 2 + 0, y * 2 + 0, FG.r, FG.g, FG.b);
      } else if (BG) {
        Canvas->SetPixel(xoffs + x * 2 + 0, y * 2 + 0, BG->r, BG->g, BG->b);
      }

      if (Numbers32x32[Value][x + y * 16] & 2) {
        Canvas->SetPixel(xoffs + x * 2 + 0, y * 2 + 1, FG.r, FG.g, FG.b);
      } else if (BG) {
        Canvas->SetPixel(xoffs + x * 2 + 0, y * 2 + 1, BG->r, BG->g, BG->b);
      }

      if (Numbers32x32[Value][x + y * 16] & 4) {
        Canvas->SetPixel(xoffs + x * 2 + 1, y * 2 + 0, FG.r, FG.g, FG.b);
      } else if (BG) {
        Canvas->SetPixel(xoffs + x * 2 + 1, y * 2 + 0, BG->r, BG->g, BG->b);
      }

      if (Numbers32x32[Value][x + y * 16] & 8) {
        Canvas->SetPixel(xoffs + x * 2 + 1, y * 2 + 1, FG.r, FG.g, FG.b);
      } else if (BG) {
        Canvas->SetPixel(xoffs + x * 2 + 1, y * 2 + 1, BG->r, BG->g, BG->b);
      }
    }
  }
}

void BigNumber::RenderDouble(Canvas *Canvas,
                             unsigned Display,
                             unsigned Value,
                             const Color &FG,
                             const Color *BG) {
  assert(Value < 100 && "Value out of range");

  unsigned Tens = Value / 10;
  unsigned Ones = Value % 10;

  unsigned xoffs = Display * 32;

  for (unsigned y = 0; y < 16; y++) {
    for (unsigned x = 0; x < 8; x++) {
      if (Tens != 0 && Numbers16x32[Tens][x + y * 8] & 1) {
        Canvas->SetPixel(xoffs + x * 2 + 0, y * 2 + 0, FG.r, FG.g, FG.b);
      } else if (BG) {
        Canvas->SetPixel(xoffs + x * 2 + 0, y * 2 + 0, BG->r, BG->g, BG->b);
      }

      if (Tens != 0 && Numbers16x32[Tens][x + y * 8] & 2) {
        Canvas->SetPixel(xoffs + x * 2 + 0, y * 2 + 1, FG.r, FG.g, FG.b);
      } else if (BG) {
        Canvas->SetPixel(xoffs + x * 2 + 0, y * 2 + 1, BG->r, BG->g, BG->b);
      }

      if (Tens != 0 && Numbers16x32[Tens][x + y * 8] & 4) {
        Canvas->SetPixel(xoffs + x * 2 + 1, y * 2 + 0, FG.r, FG.g, FG.b);
      } else if (BG) {
        Canvas->SetPixel(xoffs + x * 2 + 1, y * 2 + 0, BG->r, BG->g, BG->b);
      }

      if (Tens != 0 && Numbers16x32[Tens][x + y * 8] & 8) {
        Canvas->SetPixel(xoffs + x * 2 + 1, y * 2 + 1, FG.r, FG.g, FG.b);
      } else if (BG) {
        Canvas->SetPixel(xoffs + x * 2 + 1, y * 2 + 1, BG->r, BG->g, BG->b);
      }
    }
  }

  xoffs += 16;
  for (unsigned y = 0; y < 16; y++) {
    for (unsigned x = 0; x < 8; x++) {
      if (Numbers16x32[Ones][x + y * 8] & 1) {
        Canvas->SetPixel(xoffs + x * 2 + 0, y * 2 + 0, FG.r, FG.g, FG.b);
      } else if (BG) {
        Canvas->SetPixel(xoffs + x * 2 + 0, y * 2 + 0, BG->r, BG->g, BG->b);
      }

      if (Numbers16x32[Ones][x + y * 8] & 2) {
        Canvas->SetPixel(xoffs + x * 2 + 0, y * 2 + 1, FG.r, FG.g, FG.b);
      } else if (BG) {
        Canvas->SetPixel(xoffs + x * 2 + 0, y * 2 + 1, BG->r, BG->g, BG->b);
      }

      if (Numbers16x32[Ones][x + y * 8] & 4) {
        Canvas->SetPixel(xoffs + x * 2 + 1, y * 2 + 0, FG.r, FG.g, FG.b);
      } else if (BG) {
        Canvas->SetPixel(xoffs + x * 2 + 1, y * 2 + 0, BG->r, BG->g, BG->b);
      }

      if (Numbers16x32[Ones][x + y * 8] & 8) {
        Canvas->SetPixel(xoffs + x * 2 + 1, y * 2 + 1, FG.r, FG.g, FG.b);
      } else if (BG) {
        Canvas->SetPixel(xoffs + x * 2 + 1, y * 2 + 1, BG->r, BG->g, BG->b);
      }
    }
  }
}
