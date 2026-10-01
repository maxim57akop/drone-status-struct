#include <stdio.h>

typedef enum {
    MODE_IDLE,
    MODE_FLYING,
    MODE_LANDING
} FlightMode;

typedef enum {
    ERROR_NONE = 0,
    ERROR_LOW_BATTERY = 1 << 0,
    ERROR_HIGH_TEMPERATURE = 1 << 1,
    ERROR_INVALID_SPEED = 1 << 2
} ErrorFlag;

typedef struct {
    int id;
    int battery_percent;
    int temperature_celsius;
    int speed_mps;
    int altitude_meters;
    FlightMode mode;
    unsigned int errors;
} Drone;

static const char *mode_name(FlightMode mode)
{
    switch (mode) {
    case MODE_IDLE:
        return "IDLE";
    case MODE_FLYING:
        return "FLYING";
    case MODE_LANDING:
        return "LANDING";
    default:
        return "UNKNOWN";
    }
}

static void run_safety_checks(Drone *drone)
{
    drone->errors = ERROR_NONE;

    if (drone->battery_percent <= 20) {
        drone->errors |= ERROR_LOW_BATTERY;
    }

    if (drone->temperature_celsius >= 60) {
        drone->errors |= ERROR_HIGH_TEMPERATURE;
    }

    if (drone->speed_mps < 0) {
        drone->errors |= ERROR_INVALID_SPEED;
    }
}

static void print_errors(unsigned int errors)
{
    if (errors == ERROR_NONE) {
        printf("Errors: none\n");
        return;
    }

    printf("Errors:");

    if ((errors & ERROR_LOW_BATTERY) != 0) {
        printf(" LOW_BATTERY");
    }

    if ((errors & ERROR_HIGH_TEMPERATURE) != 0) {
        printf(" HIGH_TEMPERATURE");
    }

    if ((errors & ERROR_INVALID_SPEED) != 0) {
        printf(" INVALID_SPEED");
    }

    printf("\n");
}

static void print_drone(const Drone *drone)
{
    printf("Drone #%d\n", drone->id);
    printf("Battery: %d%%\n", drone->battery_percent);
    printf("Temperature: %d C\n", drone->temperature_celsius);
    printf("Speed: %d m/s\n", drone->speed_mps);
    printf("Altitude: %d m\n", drone->altitude_meters);
    printf("Mode: %s\n", mode_name(drone->mode));
    print_errors(drone->errors);
}

int main(void)
{
    Drone drone = {
        .id = 7,
        .battery_percent = 19,
        .temperature_celsius = 64,
        .speed_mps = 12,
        .altitude_meters = 120,
        .mode = MODE_FLYING,
        .errors = ERROR_NONE
    };

    run_safety_checks(&drone);
    print_drone(&drone);

    return 0;
}
