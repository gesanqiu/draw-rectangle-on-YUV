#include <stdio.h>
#include <sys/time.h>

#include "drawRectNV12.h"

#define IMAGE_WIDTH 1920
#define IMAGE_HEIGHT 1080

#define YUV_IMAGE_SIZE (IMAGE_WIDTH * IMAGE_HEIGHT * 3 / 2)

int main()
{
    FILE *fp = fopen("test_nv12.yuv", "rb");
    uint8_t *img = (uint8_t *)malloc(sizeof(uint8_t) * YUV_IMAGE_SIZE);

    int size = fread(img, YUV_IMAGE_SIZE, 1, fp);
    printf("size is:%d\n", size);

    YUVImgInfo m_YUVImgInfo;

    m_YUVImgInfo.imgdata = img;
    m_YUVImgInfo.width = IMAGE_WIDTH;
    m_YUVImgInfo.height = IMAGE_HEIGHT;
    m_YUVImgInfo.yuvType = TYPE_YUV420SP_NV12;

    YUVRectangle m_Rect;
    m_Rect.x = 100;
    m_Rect.y = 100;
    m_Rect.height = 800;
    m_Rect.width = 1000;

    timeval startTime, endTime;
    long long int delta;

    gettimeofday(&startTime, NULL);
    drawRectangle(&m_YUVImgInfo, m_Rect, YUV_GREEN, 5);
    gettimeofday(&endTime, NULL);

    delta = (endTime.tv_sec - startTime.tv_sec) * 1000000 + (endTime.tv_usec - startTime.tv_usec);
    printf("cost time: %lld\n", delta);

    FILE* fp_save = fopen("./yuv_data_line.nv12", "wb+");
        fwrite(img, YUV_IMAGE_SIZE, 1, fp_save);
    
    fclose(fp);
    fclose(fp_save);

}
