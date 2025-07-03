/**
 **************************************************
 *
 * @file        MeasureTemperatureAndVoltage.ino
 * 
 * @brief       Example showing how to initialize the AD8495 Thermocouple sensor
 *              and use it to measure the output voltage as well as the temperature
 *              in Celsius and Fahrenheit
 *
 * @link        solde.red/333053
 *
 * @authors     Josip Šimun Kuči @ soldered.com
 ***************************************************/

// Create an AD8495 instance on analog pin 32 (Pin A1 on the Dasduino CORE)
AD8495 sensor(A1, 10, 3.3);  // 12-bit ADC, 3.3V reference



void setup() {
  //Initialize serial communication  
  Serial.begin(115200);
  // Wait for serial connection 
  while (!Serial);

  // Optional: apply a temperature offset for calibration
  // sensor.setTemperatureOffset(4.0);  // Shift temperature readings by 4°C

  Serial.println("AD8495 Thermocouple Reader");
  Serial.println("Sampling every 2 seconds...");
}

void loop() {
  // Read averaged values using 10 samples
  float tempC = sensor.getTemperatureC(10);
  float tempF = sensor.getTemperatureF(10);
  float voltage = sensor.readVoltage(10);

  // Print results
  Serial.print("Voltage: ");
  Serial.print(voltage, 4);
  Serial.println(" V");


  Serial.print("Temperature: ");
  Serial.print(tempC, 2);
  Serial.print(" °C / ");
  Serial.print(tempF, 2);
  Serial.println(" °F");

  Serial.println("------------------------------");

  delay(2000);  // Wait 2 seconds before next reading
}
