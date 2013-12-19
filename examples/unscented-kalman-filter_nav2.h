/**
 * @file 
 * @author Denise Ratasich
 * @date 20.11.2013
 *
 * @brief Example configuration UKF for navigation.
 *
 * In this second example, using only a gyroscope and an
 * accelerometer, the offset of the accelerometer to the base_link is
 * also considered. This offset causes an additional acceleration
 * (centripedal acceleration) on the y-axis of the accelerometer when
 * rotating. The centripedal acceleration can be calculated by the
 * offset parameters (radius to base_link) and the angular velocity
 * (from the gyroscope).
 */

// -----------------------------------------
// application specific defines and includes
// -----------------------------------------

#include <cmath>

#define FILTER_PERIOD	(0.1)		// filter period
#define GRAVITY		(9.81)		// 1g = 9.81m/s^2
#ifdef M_PI	
  #define PI	M_PI
#else
#define PI	(3.1415926536)
#endif

#define		ACC_RAD	(0.05)		// radius in m, i.e. distance to the base_link
#define		ACC_PHI	(-0.5)		// -45,8° in the robot's frame 
#define		ACC_FAC (0.1)		// radius*cos(phi)

// -----------------------------------------
// input
// -----------------------------------------

// Get acceleration in heading direction and angular velocity around
// z-axis (rotation).
#define TOPICS_IN						\
  ((angular_velocity, vector.z, geometry_msgs::Vector3Stamped))	\
  ((acceleration, vector.x, geometry_msgs::Vector3Stamped))	\
  ((acceleration, vector.y, geometry_msgs::Vector3Stamped))	\
  /**/

// The message includes.
#include <geometry_msgs/Vector3Stamped.h>

// -----------------------------------------
// output
// -----------------------------------------

// Publish pose (x, y and heading).
#define TOPICS_OUT			\
  ((x, 0))				\
  ((y, 1))				\
  ((th, 2))				\
  ((omega, 3))				\
  ((ds, 4))				\
  ((v, 5))				\
  ((a, 6))				\
  ((ax, 7))				\
  ((ay, 8))				\
  /**/

// -----------------------------------------
// method and its parameters
// -----------------------------------------

// Use UKF for estimation.
#define METHOD	UNSCENTED_KALMAN_FILTER

// State transition model.
//
// x0: x = x + ds * cos(th)
// x1: y = y + ds * sin(th)
// x2: th = th + omega * T
// x3: omega = omega
// x4: ds = v * T
// x5: v = v + a * T
// x6: a = ax - ay/tan(ACC_PHI) | a = ax - omega^2*r*cos(phi)
// x7: ax = ax
// x8: ay = ay
//
#define STATE_TRANSITION_MODEL			\
  (x[0] + x[4]*cos(x[2]))			\
  (x[1] + x[4]*sin(x[2]))			\
  (x[2] + x[3]*FILTER_PERIOD)			\
  (x[3])					\
  (x[5]*FILTER_PERIOD)				\
  (x[5] + x[6]*FILTER_PERIOD)			\
  (x[7] - x[3]*x[3]*ACC_FAC)			\
  (x[7])					\
  (x[8])					\
  /**/

// Observation model.
//
// All measurements arrive in fundamental units. The acceleration in
// heading direction (robot's x-axis) equals accelerometers y-axis
// because of the mounting position of the accelerometer.
//
// z0: angular_velocity.vector.z = omega
// z1: acceleration.vector.x = -ay
// z2: acceleration.vector.y = ax
//
#define OBSERVATION_MODEL			\
  (  x[3] )					\
  ( -x[8] )					\
  (  x[7] )					\
  /**/

// Process noise covariance.
// 
// guess...
//
#define PROCESS_NOISE_COVARIANCE		\
  ( (0) (0) (0) (0) (0) (0) (0) (0) (0) )	\
  ( (0) (0) (0) (0) (0) (0) (0) (0) (0) )	\
  ( (0) (0) (0) (0) (0) (0) (0) (0) (0) )	\
  ( (0) (0) (0) (0.1) (0) (0) (0) (0) (0) )	\
  ( (0) (0) (0) (0) (0) (0) (0) (0) (0) )	\
  ( (0) (0) (0) (0) (0) (0) (0) (0) (0) )	\
  ( (0) (0) (0) (0) (0) (0) (0.00001) (0) (0) )	\
  ( (0) (0) (0) (0) (0) (0) (0) (0.002) (0) )	\
  ( (0) (0) (0) (0) (0) (0) (0) (0) (0.002) )	\
  /**/

// The variance of the sensor, i.e. our measurement.
// 
// KXTF9 worst case deviation: about 0.05g=0.5m/s^2 -> choose 0.5^2
// for variance
// IMU3000: about 0.01dps=0.00017rad/s
//
#define MEASUREMENT_NOISE_COVARIANCE		\
  ( (0.00017)    (0)    (0) )			\
  ( (0)       (0.24)    (0) )			\
  ( (0)          (0) (0.24) )			\
  /**/

// optional
// Initialize with start position (0).
#define INITIAL_STATE				\
  ( 0 )						\
  ( 0 )						\
  ( 0 )						\
  ( 0 )						\
  ( 0 )						\
  ( 0 )						\
  ( 0 )						\
  ( 0 )						\
  ( 0 )						\
  /**/
