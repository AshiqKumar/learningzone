/*
# Sensor Fusion Example: C++ Kalman Filter with Eigen

This example demonstrates a simple sensor fusion algorithm using a Kalman filter in C++ with the Eigen library.
It fuses radar and camera measurements to estimate position and velocity in a 2D space.

*/
#include <iostream>
#include <Eigen/Dense>

using namespace Eigen;

class SensorFusion {
public:
    Vector4d state; // [x, vx, y, vy]
    Matrix4d P;     // Covariance matrix
    Matrix4d F;     // State transition
    Matrix4d Q;     // Process noise
    MatrixXd H;     // Measurement matrix
    MatrixXd R;     // Measurement noise

    SensorFusion() {
        state << 0, 0, 0, 0;
        P = Matrix4d::Identity() * 1000;
        F = Matrix4d::Identity();
        Q = Matrix4d::Identity() * 0.1;
        H = MatrixXd(2, 4);
        H << 1, 0, 0, 0,
             0, 1, 0, 0;
        R = MatrixXd::Identity(2, 2) * 5;
    }

    void predict(double dt) {
        F(0, 1) = dt;
        F(2, 3) = dt;
        state = F * state;
        P = F * P * F.transpose() + Q;
    }

    void update(const Vector2d& z) {
        Vector2d y = z - H * state;
        MatrixXd S = H * P * H.transpose() + R;
        MatrixXd K = P * H.transpose() * S.inverse();
        state = state + K * y;
        P = (Matrix4d::Identity() - K * H) * P;
    }
};

int main() {
    SensorFusion fusion;

    // Simulated radar and camera measurements
    Vector2d radar_meas(30.0, 5.0);  // [distance, velocity]
    Vector2d camera_meas(29.5, 0.0); // [estimated distance, no velocity]

    fusion.predict(0.1); // Predict with 100ms timestep
    fusion.update(radar_meas);
    fusion.update(camera_meas);

    std::cout << "Fused State: \n" << fusion.state << std::endl;
    return 0;
}
