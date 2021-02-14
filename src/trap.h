#ifndef FASTCAT_TRAP_H_
#define FASTCAT_TRAP_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

typedef enum {
  TRAP_MODE_IDLE = 0,
  TRAP_MODE_RATE,
  TRAP_MODE_POS,
} trap_mode_t;

typedef struct {
  double pos_init;  //!< absolute position of the start of the trajectory
  double pos_pre;   //!< absolute position after accelerating to get |v| <=
                    //!< |vel_max|
  double pos_acc;   //!< absolute position when accelration phase is complete
  double pos_dec;   //!< absolute position when decleration phase start
  double pos_fini;  //!< absolute position of the end of the trajectory

  double vel_max;  //!< maximum velocity of the trajectory
  double acc;      //!< acceleration of the trajectory
  double acc_pre;  //!< initial accel to get velocity within limits [-vel_max,
                   //!< +vel_max]
  double dec;      //!< deceleration of the trajectory

  double t_init;  //!< absolute time of the start of the trajectory
  double t_pre;   //!< absolute time after initial state (satisfy max_vel
                  //!< constraint)
  double t_acc;   //!< absolute time when acceleration phase is complete
  double t_dec;   //!< absolute time when the deceleration phase starts
  double t_fini;  //!< absolute time of the end of the trajectory

  double vel_init;  //!< velocity at the start of the trajectory
  double vel_fini;  //!< velocity at the end of the trajectory

  double vel_pre;  //!< velocity after the initial phase
  double vel_acc;  //!< velocity after the accel phase

  int mode;

} trap_t;

int trap_generate(trap_t* self, double t_init, double pos_init, double pos_fini,
                  double vel_init, double vel_fini, double max_vel, double acc);

int trap_update(trap_t* self, double t, double* pos, double* vel);

int trap_generate_vel(trap_t* self, double t_init_sec, double pos_init,
                      double vel_init, double vel_fini, double acc,
                      double max_time);

int trap_update_vel(trap_t* self, double t, double* pos, double* vel);

#ifdef __cplusplus
}
#endif

#endif
