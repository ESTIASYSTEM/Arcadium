
#include <NeoPixelBus.h>

const uint16_t PixelCount = 120; // make sure to set this to the number of pixels in your strip
const uint8_t PixelPin = 2;     // make sure to set this to the correct pin, ignored for Esp8266
const RgbColor CylonEyeColor(HtmlColor(0x7f0000));

NeoPixelBus<NeoGrbFeature, Neo800KbpsMethod> strip(PixelCount, PixelPin);

void setup()
{
    strip.Begin();
    strip.Show();


}

void loop()
{
    strip.Show();
}
