/**
 * @file 
 * @author Denise Ratasich
 * @date 03.09.2013
 *
 * @brief Example configuration MA 2.
 */

// -----------------------------------------
// input
// -----------------------------------------

// List input topics here, format (no commas needed between topic
// tuples): ((name, field, type)).
#define TOPICS_IN						\
  ((acceleration, vector.x, geometry_msgs::Vector3Stamped))	\
  /**/

// Define the includes needed for these topics!
#include <geometry_msgs/Vector3Stamped.h>

// -----------------------------------------
// output
// -----------------------------------------

#define TOPICS_OUT				\
  ((kxtf9_ax_avg, 0))				\
  /**/

// -----------------------------------------
// method and its parameters
// -----------------------------------------

#define METHOD			MOVING_AVERAGE
#define WINDOW_SIZE		9
#define WEIGHTING_COEFFICIENTS					\
  (0.1) (0.2) (0.55) (0.7) (0.8) (0.7) (0.55) (0.2) (0.1)
