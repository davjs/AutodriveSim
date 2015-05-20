/**
 * OpenDaVINCI - Portable middleware for distributed components.
 * Copyright (C) 2012 - 2015 Christian Berger
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */

#include <cmath>
#include <cstdlib>
#include <iostream>
#include <vector>

#include <opencv/cv.h>
#include <opencv/highgui.h>

#include "Example4.h"

namespace linearkalmanfilter {

    using namespace std;
    using namespace core::base;

    LinearKalmanFilter::LinearKalmanFilter(const int32_t &argc, char **argv) :
            ConferenceClientModule(argc, argv, "LinearKalmanFilter") {}

    void LinearKalmanFilter::setUp() {
        cerr << "Setting up sender..." << endl;
        cerr << "LinearKalmanFilter set up." << endl;
    }

    void LinearKalmanFilter::tearDown() {
        cerr << "Tearing down sender..." << endl;
        cerr << "LinearKalmanFilter teared down." << endl;
    }

    void LinearKalmanFilter::drawCross(IplImage *img, const CvPoint &point, const double d, const uint32_t r, const uint32_t g, const uint32_t b) {
        cvLine(img, cvPoint(point.x - d, HEIGHT - (point.y - d)), cvPoint(point.x + d, HEIGHT - (point.y + d)), CV_RGB(r, g, b), 1, 8, 0);
        cvLine(img, cvPoint(point.x + d, HEIGHT - (point.y - d)), cvPoint(point.x - d, HEIGHT - (point.y + d)), CV_RGB(r, g, b), 1, 8, 0);
    }

    ModuleState::MODULE_EXITCODE LinearKalmanFilter::body() {
        double g = 9.80665;
        double H = 0.005;
        double n = 133;

        srand(n);

        vector<double> t;
        t.push_back(0);

        vector<double> x_ideal;
        x_ideal.push_back(0);
        vector<double> y_ideal;
        y_ideal.push_back(0);

        double v_0 = 3.8;
        double vx_0 = 0.5 * v_0;
        double vy_0 = 0.86 * v_0;

        vector<double> vx_ideal;
        vx_ideal.push_back(vx_0);
        vector<double> vy_ideal;
        vy_ideal.push_back(vy_0);

        CvMat *Mat_K = cvCreateMat(4, 2, CV_32FC1);
        cvZero(Mat_K);

        CvMat *Mat_Pm = cvCreateMat(4, 4, CV_32FC1);
        cvZero(Mat_Pm);
        cvSetIdentity(Mat_Pm, cvRealScalar(1));

        // Initial estimation.
        CvMat *Mat_R = cvCreateMat(2, 2, CV_32FC1);
        cvZero(Mat_R);

        //
        //  cvmSet(Matrix, R, C, Value);
        cvmSet(Mat_R, 0, 0, 0.01);
        cvmSet(Mat_R, 1, 1, 0.01);

        CvMat *Mat_H = cvCreateMat(2, 4, CV_32FC1);
        cvZero(Mat_H);
        cvmSet(Mat_H, 0, 0, 1.0);
        cvmSet(Mat_H, 1, 1, 1.0);

        // Initial estimation.
        CvMat *Vec_Xm = cvCreateMat(4, 1, CV_32FC1);
        cvZero(Vec_Xm);
        cvmSet(Vec_Xm, 2, 0, 1.0);
        cvmSet(Vec_Xm, 3, 0, 1.0);

        vector<double> x_kal;
        x_kal.push_back(0);
        vector<double> y_kal;
        y_kal.push_back(0);
        vector<double> x_mes;
        x_mes.push_back(0);
        vector<double> y_mes;
        y_mes.push_back(0);

        CvMat *Vec_Xp = cvCreateMat(4, 1, CV_32FC1);
        cvZero(Vec_Xp);

        CvMat *Vec_Y = cvCreateMat(2, 1, CV_32FC1);
        cvZero(Vec_Y);

        CvMat *Mat_Pp = cvCreateMat(4, 4, CV_32FC1);
        cvZero(Mat_Pp);

        CvMat *Mat_I = cvCreateMat(4, 4, CV_32FC1);
        cvZero(Mat_I);
        cvSetIdentity(Mat_I, cvRealScalar(1));

        CvMat *Mat_A = cvCreateMat(4, 4, CV_32FC1);
        cvZero(Mat_A);
        cvSetIdentity(Mat_A, cvRealScalar(1));
        cvmSet(Mat_A, 0, 2, H);
        cvmSet(Mat_A, 1, 3, H);

        CvMat *Mat_B = cvCreateMat(4, 2, CV_32FC1);
        cvZero(Mat_B);
        cvmSet(Mat_B, 1, 1, 0.5 * H * H);
        cvmSet(Mat_B, 3, 1, H);

        CvMat *Vec_u = cvCreateMat(2, 1, CV_32FC1);
        cvZero(Vec_u);
        cvmSet(Vec_u, 1, 0, -g);

        CvMat *Mat_Q = cvCreateMat(4, 4, CV_32FC1);
        cvZero(Mat_Q);
        cvSetIdentity(Mat_Q, cvRealScalar(1e-5));

        cvNamedWindow("Kalman Filter", 1);
        IplImage *canvas = cvCreateImage(cvSize(WIDTH, HEIGHT), 8, 3);
        cvZero(canvas);

        // Kalman filter.
        int32_t k = 0;
        for (k = 0; k < n; k++) {
            // Compute ideal throwing parabel.
            double _t = t[k] + H;
            t.push_back(_t);

            double _x_ideal = x_ideal[k] + H * vx_ideal[k];
            x_ideal.push_back(_x_ideal);

            double _y_ideal = y_ideal[k] + H * vy_ideal[k] - 0.5 * g * H * H;
            y_ideal.push_back(_y_ideal);

            double _vx_ideal = vx_ideal[k];
            vx_ideal.push_back(_vx_ideal);

            double _vy_ideal = vy_ideal[k] - g * H;
            vy_ideal.push_back(_vy_ideal);
            cerr << "II-T: " << _t << ", _x_ideal: " << _x_ideal << ", _y_ideal: " << _y_ideal << ", _vx_ideal: " << _vx_ideal << ", _vy_ideal: " << _vy_ideal << endl;

            // "Compute" measurement.
            cvmSet(Vec_Y, 0, 0, x_ideal[k]);
            double r = ((rand() / (double)RAND_MAX) - 0.5) * 2e-1;
            // Incorporate "noise" (i.e. a tree in this example).
            if ((0.7 < x_ideal[k]) && (x_ideal[k] < 0.8)) {
                // Tree directly in front of the sensor.
                cvmSet(Vec_Y, 1, 0, 0.1 + r);

                cvmSet(Mat_R, 0, 0, 1);
                cvmSet(Mat_R, 1, 1, 1);
            } else {
                cvmSet(Vec_Y, 1, 0, y_ideal[k] + r);

                cvmSet(Mat_R, 0, 0, 0.01);
                cvmSet(Mat_R, 1, 1, 0.01);
            }

            x_mes.push_back(cvmGet(Vec_Y, 0, 0));
            y_mes.push_back(cvmGet(Vec_Y, 1, 0));

            cerr << "MM-T: " << "x_m: " << x_mes[k+1] << ", y_m: " << y_mes[k+1] << endl;

            // Apply Kalman filter.
            CvMat *Mat_4_2 = cvCreateMat(4, 2, CV_32FC1);
            cvGEMM(Mat_Pm, Mat_H, 1.0, 0, 0, Mat_4_2, CV_GEMM_B_T); // Compute Mat_Pm * Mat_H^T = Mat_4_2.

            CvMat *Mat_2_2 = cvCreateMat(2, 2, CV_32FC1);
            cvGEMM(Mat_H, Mat_4_2, 1.0, Mat_R, 1.0, Mat_2_2, 0); // Compute Mat_R + Mat_H * (Mat_4_2) = Mat_2_2.

            CvMat *Mat_2_2_inv = cvCreateMat(2, 2, CV_32FC1);
            cvInvert(Mat_2_2, Mat_2_2_inv);

            cvGEMM(Mat_H, Mat_2_2_inv, 1.0, 0, 0, Mat_4_2, CV_GEMM_A_T); // Compute Mat_H^T * (inv(Mat_2_2)) = Mat_4_2.
            cvGEMM(Mat_Pm, Mat_4_2, 1.0, 0, 0, Mat_K, 0); // Compute Mat_H^T * (inv(Mat_2_2)) = Mat_K.

            CvMat *Mat_2_1 = cvCreateMat(2, 1, CV_32FC1);
            cvGEMM(Mat_H, Vec_Xm, -1.0, Vec_Y, 1.0, Mat_2_1, 0); // Compute Vec_Y - Mat_H * Vec_Xm = Mat_2_1.

            cvGEMM(Mat_K, Mat_2_1, 1.0, Vec_Xm, 1.0, Vec_Xp, 0); // Compute Mat_K * (Mat_2_1) + Vec_Xm = Vec_Xp.

            CvMat *Mat_4_4 = cvCreateMat(4, 4, CV_32FC1);
            cvGEMM(Mat_K, Mat_H, -1.0, Mat_I, 1.0, Mat_4_4, 0); // Compute - (Mat_K * Mat_H) + Mat_I = Mat_4_4.
            cvGEMM(Mat_4_4, Mat_Pm, 1.0, 0, 0, Mat_Pp, 0); // Compute Mat_4_4 * Mat_Pm  = Mat_Pp.

            cvReleaseMat(&Mat_4_2);
            cvReleaseMat(&Mat_2_2);
            cvReleaseMat(&Mat_2_2_inv);
            cvReleaseMat(&Mat_2_1);

            // Predicting.
            CvMat *Mat_4_1 = cvCreateMat(4, 1, CV_32FC1);
            cvGEMM(Mat_A, Vec_Xp, 1.0, 0, 0, Mat_4_1, 0); // Compute Mat_A * Vec_Xp = Mat_4_1.
            cvGEMM(Mat_B, Vec_u, 1.0, Mat_4_1, 1.0, Vec_Xm, 0); // Compute Mat_B * Vec_u + Mat_4_1 = Vec_Xm.

            cvReleaseMat(&Mat_4_1);

            x_kal.push_back(cvmGet(Vec_Xm, 0, 0));
            y_kal.push_back(cvmGet(Vec_Xm, 1, 0));

            Mat_4_4 = cvCreateMat(4, 4, CV_32FC1);
            cvGEMM(Mat_Pp, Mat_A, 1.0, 0, 0, Mat_4_4, CV_GEMM_B_T); // Compute Mat_Pp Mat_A^T = Mat_4_4.
            cvGEMM(Mat_A, Mat_4_4, 1.0, Mat_Q, 1.0, Mat_Pm, 0); // Compute Mat_A * Mat_4_4 + Mat_Q = Mat_Pm.
            cvReleaseMat(&Mat_4_4);
        }

        uint32_t i = 0;
        for (i = 0; i < t.size(); i++) {
            // Draw ideal throwing parabel.
            CvPoint point;
            point.x = x_ideal[i] * 400;
            point.y = y_ideal[i] * 400;
            drawCross(canvas, point, 3, 255, 0, 0);

            // Draw measurements.
            point.x = x_mes[i] * 400;
            point.y = y_mes[i] * 400;
            drawCross(canvas, point, 3, 0, 255, 0);

            // Draw prediction.
            point.x = x_kal[i] * 400;
            point.y = y_kal[i] * 400;
            drawCross(canvas, point, 3, 0, 0, 255);

            cvShowImage("Kalman Filter", canvas);
            cvWaitKey(10);
        }

        cerr << "Hit any key." << endl;
        cvWaitKey();

        cvDestroyWindow("Kalman Filter");

        cvReleaseMat(&Mat_K);
        cvReleaseMat(&Mat_Pm);
        cvReleaseMat(&Mat_R);
        cvReleaseMat(&Mat_H);
        cvReleaseMat(&Vec_Xm);
        cvReleaseMat(&Vec_Xp);
        cvReleaseMat(&Vec_Y);
        cvReleaseMat(&Mat_Pp);
        cvReleaseMat(&Mat_I);
        cvReleaseMat(&Mat_A);
        cvReleaseMat(&Mat_B);
        cvReleaseMat(&Vec_u);
        cvReleaseMat(&Mat_Q);
        cvReleaseImage(&canvas);

        return ModuleState::OKAY;
    }
}

