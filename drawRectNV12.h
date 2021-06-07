#ifndef __DRAW_RECT_NV12__
#define __DRAW_RECT_NV12__

#include <stdio.h>
#include <iostream>

typedef enum
{
	TYPE_YUV422I_UYVY,
	TYPE_YUV422I_YUYV,
	TYPE_YUV420SP_NV12,
	TYPE_YUV420SP_NV21,
	TYPE_YUV422P,
	TYPE_YUV444I,
	TYPE_YUV444P,
}YUVType;

typedef enum
{
	YUV_GREEN,
	YUV_RED,
	YUV_BLUE,
	YUV_PURPLE,
	YUV_DARK_GREEN,
	YUV_YELLOW,
	YUV_LIGHT_BLUE,
	YUV_LIGHT_PURPLE,
	YUV_DARK_BLACK,
	YUV_GRAY,
	YUV_WHITE,
	YUV_COLOR_MAX,
}YUVColor;

typedef struct
{
	uint8_t Y;
	uint8_t U;
	uint8_t V;
}YUVPixColor;

typedef struct
{
	uint16_t x;
	uint16_t y;
}imgPoint;

typedef struct
{
	imgPoint startPoint;
	imgPoint endPoint;
	uint16_t thick;
	YUVColor color;
}lineInfo;

typedef struct
{
	uint16_t x;
	uint16_t y;
	uint16_t width;
	uint16_t height;
}YUVRectangle;

typedef struct
{
	YUVType yuvType;
	uint8_t *imgdata;
	uint16_t width;
	uint16_t height;
}YUVImgInfo;

static YUVPixColor s_color_table[YUV_COLOR_MAX] = {
	{0x00, 0x00, 0x00}, // green
	{0x00, 0x00, 0xff}, // red
	{0x00, 0xff, 0x00}, // blue
	{0x00, 0xff, 0xff}, // purple
	{0xff, 0x00, 0x00}, // dark green
	{0xff, 0x00, 0xff}, // yellow
	{0xff, 0xff, 0x00}, // light blue
	{0xff, 0xff, 0xff}, // light purple
	{0x00, 0x80, 0x80}, // dark black
	{0x80, 0x80, 0x80}, // gray
	{0xff, 0x80, 0x80}, // white
};

void setYUVPix(unsigned char* YBuf, unsigned char * UVBuf, YUVType type, uint16_t width, uint16_t height, imgPoint point, YUVColor color);
void drawLine(YUVImgInfo *img, lineInfo *line);
void drawRectangle(YUVImgInfo *img, YUVRectangle rect, YUVColor color, uint16_t thick);


#endif
