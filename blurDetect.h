#pragma once

#include "config.h"

// ����x([-255, 255])����ֵ, ���㹫ʽ��abs(a) = X[a+255]
void calcuXabs();

// ����һ���Ҷ�ͼ����ݶ�ֵ����Χ��[0, 255]
double BlurDetect(const Mat& img);

// ����һ��ͼ��ķ�ֵ�����
double ImagePsnr(const Mat& img);
