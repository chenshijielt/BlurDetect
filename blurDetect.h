#pragma once

#include "config.h"

// ����x([-255, 255])����ֵ, ���㹫ʽ��abs(a) = X[a+255]
void calcuXabs();

// ����һ���Ҷ�ͼ����ݶ�ֵ
double BlurDetect(const Mat& img_gray);
