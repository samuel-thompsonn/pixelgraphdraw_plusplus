#ifndef SETTINGS
#define SETTINGS 1
#define SCREEN_WIDTH 20
#define SCREEN_HEIGHT SCREEN_WIDTH
#define PI 3.14159265358
#define PROJECTION_MATRIX {{ { (float)-cos(PI / 6), (float)cos(PI / 6), 0 }, { (float)sin(PI / 6), (float)sin(PI / 6), -1 } }}
#define X_FUNC return x / 3.f;
#define Y_FUNC return y / 3.f;
#define XY_FUNC return (x+y) / 3;
#define COS_X_FUNC return cos(x);
#define COS_Y_FUNC return cos(y);
#define FLAT_FUNC return 0;
#define SADDLE_FUNC return 0.010 * (pow(x, 2) - pow(y, 2));
#endif