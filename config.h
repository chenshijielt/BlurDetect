// 【注意】请将OpenCV的包含目录、python包含目录添加到项目附加包含目录
// 将python的库目录添加到项目的附加库目录
// 然后根据实际情况修改本文件。


//////////////////////////////////////////////////////////////////////////
// OpenCV 配置
#define CV_VER "320"

#ifdef _DEBUG
#define CV_LIB_PATH "D:/opencv/opencv32/x64/lib/Debug/"
#define CV_LIB_X(LIB, VER) CV_LIB_PATH##"opencv_"##LIB##VER##"d.lib"
#else
#define CV_LIB_PATH "D:/opencv/opencv32/x64/lib/Release/"
#define CV_LIB_X(LIB, VER) CV_LIB_PATH##"opencv_"##LIB##VER##".lib"
#endif

#define USING_CV_LIB(LIB) CV_LIB_X(LIB, CV_VER) // 使用CV的库


//////////////////////////////////////////////////////////////////////////
#include "opencv2/opencv.hpp" 
#include "opencv2/core/ocl.hpp"
#include "opencv/cv.h"
using namespace cv;

#pragma comment(lib, USING_CV_LIB("core"))
#pragma comment(lib, USING_CV_LIB("highgui"))
#pragma comment(lib, USING_CV_LIB("imgproc"))
#pragma comment(lib, USING_CV_LIB("video"))
#pragma comment(lib, USING_CV_LIB("videoio"))
#pragma comment(lib, USING_CV_LIB("imgcodecs"))
#pragma comment(lib, USING_CV_LIB("photo"))

#ifdef _AFX
#define OUTPUT TRACE
#else
#define OUTPUT printf
#endif


// 是否支持IPC
#define SUPPORT_IPC 1

// 是否使检测函数为static(能避免频繁查找map)
#define STATIC_DETECTING 1

// 保存已识别人脸图像需满足的最小尺寸
#define MIN_FACESIZE 160
