#ifndef _ADAFRUIT_MMA8451_H_
#define _ADAFRUIT_MMA8451_H_

#include <stdint.h>
#include <string.h>

/* Constants */
#define SENSORS_GRAVITY_EARTH (9.80665F) /**< Earth's gravity in m/s^2 */
#define SENSORS_GRAVITY_MOON (1.6F)      /**< The moon's gravity in m/s^2 */
#define SENSORS_GRAVITY_SUN (275.0F)     /**< The sun's gravity in m/s^2 */
#define SENSORS_GRAVITY_STANDARD (SENSORS_GRAVITY_EARTH)
#define SENSORS_MAGFIELD_EARTH_MAX                                             \
  (60.0F) /**< Maximum magnetic field on Earth's surface */
#define SENSORS_MAGFIELD_EARTH_MIN                                             \
  (30.0F) /**< Minimum magnetic field on Earth's surface */
#define SENSORS_PRESSURE_SEALEVELHPA                                           \
  (1013.25F) /**< Average sea level pressure is 1013.25 hPa */
#define SENSORS_DPS_TO_RADS                                                    \
  (0.017453293F) /**< Degrees/s to rad/s multiplier                            \
                  */
#define SENSORS_RADS_TO_DPS                                                    \
  (57.29577793F) /**< Rad/s to degrees/s  multiplier */
#define SENSORS_GAUSS_TO_MICROTESLA                                            \
  (100) /**< Gauss to micro-Tesla multiplier */

/** Sensor types */
typedef enum {
  SENSOR_TYPE_ACCELEROMETER = (1), /**< Gravity + linear acceleration */
  SENSOR_TYPE_MAGNETIC_FIELD = (2),
  SENSOR_TYPE_ORIENTATION = (3),
  SENSOR_TYPE_GYROSCOPE = (4),
  SENSOR_TYPE_LIGHT = (5),
  SENSOR_TYPE_PRESSURE = (6),
  SENSOR_TYPE_PROXIMITY = (8),
  SENSOR_TYPE_GRAVITY = (9),
  SENSOR_TYPE_LINEAR_ACCELERATION = (10), /**< Acceleration not including gravity */
  SENSOR_TYPE_ROTATION_VECTOR = (11),
  SENSOR_TYPE_RELATIVE_HUMIDITY = (12),
  SENSOR_TYPE_AMBIENT_TEMPERATURE = (13),
  SENSOR_TYPE_OBJECT_TEMPERATURE = (14),
  SENSOR_TYPE_VOLTAGE = (15),
  SENSOR_TYPE_CURRENT = (16),
  SENSOR_TYPE_COLOR = (17),
  SENSOR_TYPE_TVOC = (18),
  SENSOR_TYPE_VOC_INDEX = (19),
  SENSOR_TYPE_NOX_INDEX = (20),
  SENSOR_TYPE_CO2 = (21),
  SENSOR_TYPE_ECO2 = (22),
  SENSOR_TYPE_PM10_STD = (23),
  SENSOR_TYPE_PM25_STD = (24),
  SENSOR_TYPE_PM100_STD = (25),
  SENSOR_TYPE_PM10_ENV = (26),
  SENSOR_TYPE_PM25_ENV = (27),
  SENSOR_TYPE_PM100_ENV = (28),
  SENSOR_TYPE_GAS_RESISTANCE = (29),
  SENSOR_TYPE_UNITLESS_PERCENT = (30)
} sensors_type_t;

/** struct sensors_vec_s is used to return a vector in a common format. */
typedef struct {
  union {
    float v[3]; ///< 3D vector elements
    struct {
      float x; ///< X component of vector
      float y; ///< Y component of vector
      float z; ///< Z component of vector
    };         ///< Struct for holding XYZ component
    /* Orientation sensors */
    struct {
      float roll; /**< Rotation around the longitudinal axis (the plane body, 'X
                     axis'). Roll is positive and increasing when moving
                     downward. -90 degrees <= roll <= 90 degrees */
      float pitch;   /**< Rotation around the lateral axis (the wing span, 'Y
                        axis'). Pitch is positive and increasing when moving
                        upwards. -180 degrees <= pitch <= 180 degrees) */
      float heading; /**< Angle between the longitudinal axis (the plane body)
                        and magnetic north, measured clockwise when viewing from
                        the top of the device. 0-359 degrees */
    };               ///< Struct for holding roll/pitch/heading
  };                 ///< Union that can hold 3D vector array, XYZ components or
                     ///< roll/pitch/heading
  int8_t status;     ///< Status byte
  uint8_t reserved[3]; ///< Reserved
} sensors_vec_t;

/** struct sensors_color_s is used to return color data in a common format. */
typedef struct {
  union {
    float c[3]; ///< Raw 3-element data
    /* RGB color space */
    struct {
      float r;   /**< Red component */
      float g;   /**< Green component */
      float b;   /**< Blue component */
    };           ///< RGB data in floating point notation
  };             ///< Union of various ways to describe RGB colorspace
  uint32_t rgba; /**< 24-bit RGBA value */
} sensors_color_t;

/* Sensor event (36 bytes) */
/** struct sensor_event_s is used to provide a single sensor event in a common
 * format. */
typedef struct {
  int32_t version;   /**< must be sizeof(struct sensors_event_t) */
  int32_t sensor_id; /**< unique sensor identifier */
  int32_t type;      /**< sensor type */
  int32_t reserved0; /**< reserved */
  int32_t timestamp; /**< time is in milliseconds */
  union {
    float data[4];              ///< Raw data */
    sensors_vec_t acceleration; /**< acceleration values are in meter per second
                                   per second (m/s^2) */
    sensors_vec_t
        magnetic; /**< magnetic vector values are in micro-Tesla (uT) */
    sensors_vec_t orientation; /**< orientation values are in degrees */
    sensors_vec_t gyro;        /**< gyroscope values are in rad/s */
    float temperature; /**< temperature is in degrees centigrade (Celsius) */
    float distance;    /**< distance in centimeters */
    float light;       /**< light in SI lux units */
    float pressure;    /**< pressure in hectopascal (hPa) */
    float relative_humidity; /**< relative humidity in percent */
    float current;           /**< current in milliamps (mA) */
    float voltage;           /**< voltage in volts (V) */
    float tvoc;              /**< Total Volatile Organic Compounds, in ppb */
    float voc_index; /**< VOC (Volatile Organic Compound) index where 100 is
                          normal (unitless) */
    float nox_index; /**< NOx (Nitrogen Oxides) index where 100 is normal
                          (unitless) */
    float CO2;       /**< Measured CO2 in parts per million (ppm) */
    float eCO2;      /**< equivalent/estimated CO2 in parts per million (ppm
                        estimated from some other measurement) */
    float pm10_std;  /**< Standard Particulate Matter <=1.0 in parts per million
                        (ppm) */
    float pm25_std;  /**< Standard Particulate Matter <=2.5 in parts per million
                        (ppm) */
    float pm100_std; /**< Standard Particulate Matter <=10.0 in parts per
                        million (ppm) */
    float pm10_env;  /**< Environmental Particulate Matter <=1.0 in parts per
                        million (ppm) */
    float pm25_env;  /**< Environmental Particulate Matter <=2.5 in parts per
                        million (ppm) */
    float pm100_env; /**< Environmental Particulate Matter <=10.0 in parts per
                        million (ppm) */
    float gas_resistance;   /**< Proportional to the amount of VOC particles in
                               the air (Ohms) */
    float unitless_percent; /**<Percentage, unit-less (%) */
    sensors_color_t color;  /**< color in RGB component values */
  };                        ///< Union for the wide ranges of data we can carry
} sensors_event_t;

/* Sensor details (40 bytes) */
/** struct sensor_s is used to describe basic information about a specific
 * sensor. */
typedef struct {
  char name[12];     /**< sensor name */
  int32_t version;   /**< version of the hardware + driver */
  int32_t sensor_id; /**< unique sensor identifier */
  int32_t type;      /**< this sensor's type (ex. SENSOR_TYPE_LIGHT) */
  float max_value;   /**< maximum value of this sensor's value in SI units */
  float min_value;   /**< minimum value of this sensor's value in SI units */
  float resolution; /**< smallest difference between two values reported by this
                       sensor */
  int32_t min_delay; /**< min delay in microseconds between events. zero = not a
                        constant rate */
} sensor_t;

#define MMA8451_REG_OUT_X_MSB 0x01 //!< Read-only device output register
#define MMA8451_REG_SYSMOD 0x0B    //!< SYSMOD system mode register
#define MMA8451_REG_WHOAMI 0x0D    //!< WHO_AM_I device ID register
#define MMA8451_REG_XYZ_DATA_CFG                                               \
  0x0E //!< XYZ_DATA_CFG register, sets dynamic range and high-pass filter for
       //!< output data
#define MMA8451_REG_PL_STATUS                                                  \
  0x10 //!< PL_STATUS portrait/landscape status register
#define MMA8451_REG_PL_CFG 0x11 //!< Portrait/landscape configuration register
#define MMA8451_REG_CTRL_REG1 0x2A //!< CTRL_REG1 system control 1 register
#define MMA8451_REG_CTRL_REG2 0x2B //!< CTRL_REG2 system control 2 register
#define MMA8451_REG_CTRL_REG4 0x2D //!< CTRL_REG4 system control 4 register
#define MMA8451_REG_CTRL_REG5 0x2E //!< CTRL_REG5 system control 5 register

///@{
//* Different portrait and landscape settings */
#define MMA8451_PL_PUF 0
#define MMA8451_PL_PUB 1
#define MMA8451_PL_PDF 2
#define MMA8451_PL_PDB 3
#define MMA8451_PL_LRF 4
#define MMA8451_PL_LRB 5
#define MMA8451_PL_LLF 6
#define MMA8451_PL_LLB 7
///@}

/*!
 * @brief Different range settings
 */
typedef enum {
  MMA8451_RANGE_8_G = 0b10, // +/- 8g
  MMA8451_RANGE_4_G = 0b01, // +/- 4g
  MMA8451_RANGE_2_G = 0b00  // +/- 2g (default value)
} mma8451_range_t;

/*! Used with register 0x2A (MMA8451_REG_CTRL_REG1) to set bandwidth */
typedef enum {
  MMA8451_DATARATE_800_HZ = 0b000,  //  800Hz
  MMA8451_DATARATE_400_HZ = 0b001,  //  400Hz
  MMA8451_DATARATE_200_HZ = 0b010,  //  200Hz
  MMA8451_DATARATE_100_HZ = 0b011,  //  100Hz
  MMA8451_DATARATE_50_HZ = 0b100,   //   50Hz
  MMA8451_DATARATE_12_5_HZ = 0b101, // 12.5Hz
  MMA8451_DATARATE_6_25HZ = 0b110,  // 6.25Hz
  MMA8451_DATARATE_1_56_HZ = 0b111, // 1.56Hz

  MMA8451_DATARATE_MASK = 0b111
} mma8451_dataRate_t;

#define MMA8451_DEFAULT_ADDRESS 0x1D << 1 //!< Default MMA8451 I2C address, if A is GND, its 0x1C

typedef struct{
    int16_t x, y, z;         // Valor en cada eje
    float x_g, y_g, z_g;     // Aceleración en cada eje
    char orientation[25];    // Orientación
} mma8451_t;

// Escritura en un registro del acelerometro
void write_register(uint8_t , uint8_t , I2C_HandleTypeDef, UART_HandleTypeDef);

// Lectura de un registro del acelerometro
uint8_t read_register(uint8_t , I2C_HandleTypeDef, UART_HandleTypeDef);

// Inicializa el acelerometro con una configuración por defecto
void init_mma8451(I2C_HandleTypeDef);


// Actualiza los datos sobre la orientación
void get_orientation(mma8451_t *data, I2C_HandleTypeDef, UART_HandleTypeDef);

// Actualiza los datos sobre la aceleración
void read(mma8451_t *data, I2C_HandleTypeDef, UART_HandleTypeDef);

// Cambia el rango de aceleración
void set_range(mma8451_range_t range, I2C_HandleTypeDef, UART_HandleTypeDef);

// Devuelve el range actual
mma8451_range_t get_range(I2C_HandleTypeDef, UART_HandleTypeDef);

// Printea la información del acelerometro
void print_info(mma8451_t data, UART_HandleTypeDef);

#endif