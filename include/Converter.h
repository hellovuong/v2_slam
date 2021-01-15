/**
* This file is part of ORB-SLAM2.
*
* Copyright (C) 2014-2016 Raúl Mur-Artal <raulmur at unizar dot es> (University of Zaragoza)
* For more information see <https://github.com/raulmur/ORB_SLAM2>
*
* ORB-SLAM2 is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* ORB-SLAM2 is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with ORB-SLAM2. If not, see <http://www.gnu.org/licenses/>.
*/

// Modified by Vuong 2021
// Add function to normalize_angle; toSE2; toCvSE3

#ifndef CONVERTER_H
#define CONVERTER_H

#include<opencv2/core/core.hpp>

#include<Eigen/Dense>
#include"Thirdparty/g2o/g2o/types/types_six_dof_expmap.h"
#include"Thirdparty/g2o/g2o/types/types_seven_dof_expmap.h"
#include"Thirdparty/g2o/g2o/types/vertex_se2.h"
#include"Thirdparty/g2o/g2o/types/se2.h"

namespace ORB_SLAM2
{

class Converter
{
public:
    static std::vector<cv::Mat> toDescriptorVector(const cv::Mat &Descriptors);

    static inline double normalize_angle(double theta)
    {
        if (theta >= -M_PI && theta < M_PI)
        return theta;

        double multiplier = floor(theta / (2*M_PI));
        theta = theta - multiplier*2*M_PI;
        if (theta >= M_PI)
        theta -= 2*M_PI;
        if (theta < -M_PI)
        theta += 2*M_PI;

        return theta;
    }

    static g2o::SE2 toSE2(const cv::Mat &cvT);
    static cv::Mat toCvSE3(const Eigen::Vector3d &SE2)
    {
        double x = SE2[0];
        double y = SE2[1];
        double theta = SE2[2];

        double c = std::cos(theta);
        double s = std::sin(theta);
        
        return (cv::Mat_<float>(4,4) <<
                c,-s, 0, x,
                s, c, 0, y,
                0, 0, 1, 0,
                0, 0, 0, 1);
    }
    static g2o::SE3Quat toSE3Quat(const cv::Mat &cvT);
    static g2o::SE3Quat toSE3Quat(const g2o::Sim3 &gSim3);

    static cv::Mat toCvMat(const g2o::SE3Quat &SE3);
    static cv::Mat toCvMat(const g2o::Sim3 &Sim3);
    static cv::Mat toCvMat(const Eigen::Matrix<double,4,4> &m);
    static cv::Mat toCvMat(const Eigen::Matrix3d &m);
    static cv::Mat toCvMat(const Eigen::Matrix<double,3,1> &m);
    static cv::Mat toCvSE3(const Eigen::Matrix<double,3,3> &R, const Eigen::Matrix<double,3,1> &t);

    static Eigen::Matrix<double,3,1> toVector3d(const cv::Mat &cvVector);
    static Eigen::Matrix<double,3,1> toVector3d(const cv::Point3f &cvPoint);
    static Eigen::Matrix<double,3,3> toMatrix3d(const cv::Mat &cvMat3);

    static std::vector<float> toQuaternion(const cv::Mat &M);
};

}// namespace ORB_SLAM

#endif // CONVERTER_H
