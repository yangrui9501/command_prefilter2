# Command Prefilter

## Example

```cpp
// 2023-05-13
// Sample code foe CommandPrefilter utility.

#include <Arduino.h>
#include <command_prefilter.h>

CommandPrefilter cmd_filter;

int idx = 0;
double T = 0.001; // Sample interval
double t = 0.0;
double cmd_pos = 0.0; // Original command
double pos_f = 0.0, vel_f = 0.0, acc_f = 0.0;

/* Function Declaration */
double sign(double u_in);

// Main 
void setup()
{
    Serial.begin(115200);

    // Initialization
    double fc = 2.5;
    cmd_filter.init(fc, T);

    delay(3000);
}

void loop()
{
    // Generate command data
    t = (double)(idx) * T;
    cmd_pos = sign(sin(2.0 * PI / 5.0 * t));

    // Filter the command 
    cmd_filter.update(&cmd_pos, pos_f, vel_f, acc_f);
    
    // Print data
    Serial.print(String() + cmd_pos + " " + pos_f + " " + vel_f + " " + acc_f);
    Serial.println();
    Serial.flush();

    idx++;

    delay(1);
}

double sign(double u_in)
{
    if (u_in > 0.0)
        return 1.0;
    else if (u_in < 0.0)
        return -1.0;
    return 0.0;
    }
```
