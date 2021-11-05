/*
 * @Description: Draw line/rectangle on YUV.
 * @Version: 1.0
 * @Author: Ricardo Lu<shenglu1202@163.com>
 * @Date: 2021-11-03 11:03:18
 * @LastEditTime: 2021-11-03 11:39:51
 * @LastEditors: Please set LastEditors
 */

#include "osdyuv.h"

void setYUVPix(unsigned char* YBuf,
                unsigned char * UVBuf,
                YUVType type,
                uint16_t width,
                uint16_t height,
                imgPoint point,
                YUVPixColor color)
{
    switch(type)
    {
        case TYPE_YUV422I_UYVY:
        case TYPE_YUV422I_YUYV:
        {
            /*
                UYVY UYVY UYVY UYVY
            */
            uint32_t tmp = point.y * width * 2;
            uint32_t y_offset = 0, u_offset = 0, v_offset = 0;
            if(type == TYPE_YUV422I_UYVY) {
                u_offset = tmp + point.x / 2 * 4;
                v_offset = u_offset + 2;
                y_offset = u_offset + 1;
            }
            else {
                y_offset = tmp + point.x / 2 * 4;
                u_offset = y_offset + 1;
                v_offset = u_offset + 2;
            }
            YBuf[y_offset] = color.Y;
            YBuf[y_offset + 2] = color.Y;
            YBuf[u_offset] = color.U;
            YBuf[v_offset] = color.V;
        }break;
        case TYPE_YUV420SP_NV12:
        case TYPE_YUV420SP_NV21:
        {
            /*
                YY YY
                YY YY
                UV UV
            */
            uint32_t y_offset = point.y * width + point.x;
            uint32_t u_offset = 0, v_offset = 0;
            YBuf[y_offset] = color.Y;
            #if 0
            Int32 x_flag = 1, y_flag = 1;
            if(point.y % 2 == 0) {
                YBuf[y_offset + width] = color.Y;
                y_flag = 1;
            }
            else {
                YBuf[y_offset - width] = color.Y;
                y_flag = -1;
            }
 
            if(point.x % 2 == 0) {
                YBuf[y_offset + 1] = color.Y;
                x_flag = 1;
            }
            else {
                YBuf[y_offset - 1] = color.Y;
                x_flag = -1;
            }
            YBuf[y_offset + width * y_flag + 1 * x_flag] = color.Y;
            #endif
            
            if(type == TYPE_YUV420SP_NV12) {
                u_offset = (point.y / 2) * width + point.x / 2 * 2;
                v_offset = u_offset + 1;
            }
            else {
                v_offset = (point.y / 2) * width + point.x / 2 * 2;
                u_offset = v_offset + 1;
            }
            UVBuf[u_offset] = color.U;
            UVBuf[v_offset] = color.V;
        }break;
        case TYPE_YUV444P:
        {
            /*
                YYYYYYYY
                UUUUUUUU
                VVVVVVVV
            */
            uint32_t y_offset = 0, u_offset = 0, v_offset = 0;
            uint32_t plane_size = width * height;
            y_offset = point.y * width + point.x;
            u_offset = y_offset;
            v_offset = plane_size + u_offset;
            YBuf[y_offset] = color.Y;
            UVBuf[u_offset] = color.U;
            UVBuf[v_offset] = color.V;
        }break;
        case TYPE_YUV444I:
        {
            /*
                YUV YUV YUV YUV YUV YUV YUV YUV
            */
            uint32_t y_offset = 0, u_offset = 0, v_offset = 0;
            y_offset = point.y * width * 3 + point.x * 3;
            u_offset = y_offset + 1;
            v_offset = u_offset + 1;
            YBuf[y_offset] = color.Y;
            YBuf[u_offset] = color.U;
            YBuf[v_offset] = color.V;
        }break;
        case TYPE_YUV422P:
        {
            /*
                YYYYYYYY
                UUUU
                VVVV
            */
            uint32_t y_offset = 0, u_offset = 0, v_offset = 0;
            uint32_t plane_size = width * height / 2;
            y_offset = point.y * width + point.x;
            u_offset = y_offset / 2;
            v_offset = plane_size + y_offset / 2;
            YBuf[y_offset] = color.Y;
            UVBuf[u_offset] = color.U;
            UVBuf[v_offset] = color.V;
        }break;
    }
}

void drawLine(YUVImgInfo *img, lineInfo *line)
{
    if(!img || !img->imgdata) return;
 
    uint8_t *YBuff = NULL, *UVBuff = NULL;
    uint16_t x0 = line->startPoint.x, y0 = line->startPoint.y;
    uint16_t x1 = line->endPoint.x, y1 = line->endPoint.y;
 
    if(line->thick == 0) line->thick = 1;
    x0 = (x0 >= img->width) ? (x0 - line->thick) : x0;
    x1 = (x1 >= img->width) ? (x1 - line->thick) : x1;
    y0 = (y0 >= img->height) ? (y0 - line->thick) : y0;
    y1 = (y1 >= img->height) ? (y1 - line->thick) : y1;
 
    uint16_t dx = (x0 > x1) ? (x0 - x1) : (x1 - x0);
    uint16_t dy = (y0 > y1) ? (y0 - y1) : (y1 - y0);
 
    uint16_t xstep = (x0 < x1) ? 1 : -1;
    uint16_t ystep = (y0 < y1) ? 1 : -1;
    uint16_t nstep = 0, eps = 0;
 
    imgPoint draw_point;
    draw_point.x = x0;
    draw_point.y = y0;
 
    switch(img->yuvType)
    {
        case TYPE_YUV422I_UYVY:
        case TYPE_YUV422I_YUYV:
        case TYPE_YUV444I:
        {
            YBuff = img->imgdata;
            UVBuff = NULL;
        }break;
        case TYPE_YUV420SP_NV12:
        case TYPE_YUV420SP_NV21:
        case TYPE_YUV444P:
        case TYPE_YUV422P:
        {
            YBuff = img->imgdata;
            UVBuff = img->imgdata + img->width * img->height;
        }break;
        default:
            return;
    }
 
    // 布雷森汉姆算法画线
    if(dx > dy){
        while(nstep <= dx) {
            setYUVPix(YBuff, UVBuff, img->yuvType, img->width, img->height, draw_point, line->color);
            eps += dy;
            if( (eps << 1) >= dx ) {
                draw_point.y += ystep;
                eps -= dx;
            }
            draw_point.x += xstep;
            nstep++;
        }
    }else {
        while(nstep <= dy){	
            setYUVPix(YBuff, UVBuff, img->yuvType, img->width, img->height, draw_point, line->color);
            eps += dx;
            if( (eps << 1) >= dy ) {
                draw_point.x += xstep;
                eps -= dy;
            }
            draw_point.y += ystep;
            nstep++;
        }
    }
}

void drawRectangle(YUVImgInfo *img, YUVRectangle rect, YUVPixColor color, uint16_t thick)
{
    lineInfo line;
    line.color = color;
    line.thick = thick;

    line.startPoint.x = rect.x;
    line.startPoint.y = rect.y;
    line.endPoint.x = rect.x + rect.width;
    line.endPoint.y = rect.y;
    drawLine(img, &line);

    line.startPoint.x = rect.x;
    line.startPoint.y = rect.y;
    line.endPoint.x = rect.x;
    line.endPoint.y = rect.y + rect.height;
    drawLine(img, &line);

    line.startPoint.x = rect.x;
    line.startPoint.y = rect.y + rect.height;
    line.endPoint.x = rect.x + rect.width;
    line.endPoint.y = rect.y + rect.height;
    drawLine(img, &line);

    line.startPoint.x = rect.x + rect.width;
    line.startPoint.y = rect.y;
    line.endPoint.x = rect.x + rect.width;
    line.endPoint.y = rect.y + rect.height;
    drawLine(img, &line);
}