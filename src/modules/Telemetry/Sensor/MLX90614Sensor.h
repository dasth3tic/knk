#include "configuration.h"

#if !MESHTASTIC_EXCLUDE_ENVIRONMENTAL_SENSOR
#include "../mesh/generated/meshtastic/telemetry.pb.h"
#include "TelemetrySensor.h"
#include <Adafruit_MLX90614.h>

class MLX90614Sensor : public TelemetrySensor
{
  private:
    Adafruit_MLX90614 mlx = Adafruit_MLX90614();

  protected:
    virtual void setup() override;

  public:
    MLX90614Sensor();
    virtual int32_t runOnce() override;
    virtual bool getMetrics(meshtastic_Telemetry *measurement) override;
};

#endif
